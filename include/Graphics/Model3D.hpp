// SpaceCollider3DS -- A simple game for the AEV course at UPV
// Copyright (c) 2022 Ángel Pérez <aperpor@upv.edu.es>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#pragma once

#include <cassert>
#include <fstream>
#include <memory>
#include <vector>

#include <citro3d.h>

#include "../Foundation/CTRLinearAllocator.hpp"
#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "GPUVertex.hpp"
#include "Material.hpp"
#include "MaterialProperties.hpp"
#include "Scene.hpp"
#include "Texture2D.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

struct Model3D : NonCopyable, NonMoveable {
    explicit Model3D(Scene& scene, const Vec3<float>& position = {}, const Vec3<float>& rotation = {})
        : m_scene(scene)
        , m_position(position)
        , m_rotation(rotation)
    {
    }

    Vec3<float>& get_position() { return m_position; }
    void set_position(const Vec3<float>& position) { m_position = position; }

    Vec3<float>& get_rotation() { return m_rotation; }
    void set_rotation(const Vec3<float>& position) { m_position = position; }

    void load_from_file(const std::string& file_path)
    {
        debug_trace("loading from %s", file_path.c_str());
        std::ifstream stream(file_path);

        if (stream.is_open()) {
            debug_trace("model load OK");
        } else {
            debug_trace("model load failed: error %d", errno);
            return;
        }

        struct {
            uint16_t magic_value : 16;
            uint16_t number_of_materials : 16;
        } file_header;

        // Read file header
        stream.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
        assert(stream.good());

        assert(file_header.magic_value == 0xCAFE);
        assert(file_header.number_of_materials > 0);

        for (uint16_t material_index = 0; material_index < file_header.number_of_materials; material_index++) {
            std::unique_ptr<MaterialProperties> material_properties = std::make_unique<MaterialProperties>();
            std::unique_ptr<Texture2D> texture = nullptr;

            // Read material properties length (8 bit unsigned)
            uint16_t material_properties_length = 0;
            stream.read(reinterpret_cast<char*>(&material_properties_length), sizeof(material_properties_length));
            assert(stream.good());
            assert(material_properties_length == sizeof(MaterialProperties));

            // Read material properties
            char *buf = new char[material_properties_length];
            stream.read(buf, material_properties_length);
            assert(stream.good());

            // TODO: copy directly from stream.read() to unique_ptr<>?
            memcpy(material_properties.get(), buf, material_properties_length);

            // Read texture file path length (8 bit unsigned)
            uint16_t texture_file_path_length = 0;
            stream.read(reinterpret_cast<char*>(&texture_file_path_length), sizeof(texture_file_path_length));
            assert(stream.good());
            if (texture_file_path_length > 0) {
                // Read texture file path
                char buffer[texture_file_path_length];
                stream.read(buffer, texture_file_path_length);
                assert(stream.good());

                // Create texture
                texture = std::make_unique<Texture2D>(std::string { buffer, buffer + texture_file_path_length });
            }

            // Read VBO length (16-bit unsigned int)
            uint16_t vbo_length = 0;
            stream.read(reinterpret_cast<char*>(&vbo_length), sizeof(vbo_length));
            assert(stream.good());
            assert(vbo_length > 0);

            // Read VBO
            auto vbo = std::make_unique<VertexBufferObject>();
            vbo->resize(vbo_length / sizeof(GPUVertex), GPUVertex {});
            stream.read(reinterpret_cast<char*>(vbo->data()), vbo_length);
            assert(stream.good());
            assert(vbo->capacity() >= vbo->size());
            assert(vbo->size() == vbo_length / sizeof(GPUVertex));

            // Create material
            m_materials.push_back(Material { m_scene, material_properties, texture, vbo });
        }

        // We should have ended gracefully
        stream.ignore();
        assert(stream.eof());
    }

    void render()
    {
        C3D_Mtx model_view_matrix;
        Mtx_Identity(&model_view_matrix);
        Mtx_RotateX(&model_view_matrix, m_rotation.x, false);
        Mtx_RotateY(&model_view_matrix, m_rotation.y, false);
        Mtx_RotateZ(&model_view_matrix, m_rotation.z, false);
        Mtx_Translate(&model_view_matrix, m_position.x, m_position.y, m_position.z, false);

        for (auto& material : m_materials)
            material.render(&model_view_matrix);
    }

private:
    static constexpr auto k_tag = "Model3D";

    Scene& m_scene;
    std::vector<Material> m_materials;

    Vec3<float> m_position;
    Vec3<float> m_rotation;
};