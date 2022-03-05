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

#include <memory>
#include <vector>

#include "../Foundation/CTRLinearAllocator.hpp"
#include "GPUVertex.hpp"
#include "MaterialProperties.hpp"
#include "Scene.hpp"
#include "Texture2D.hpp"

using VertexBufferObject = std::vector<GPUVertex, CTRLinearAllocator<GPUVertex>>;

struct Material {
    /**
     * Creates a material
     * @param properties Pointer to the material properties
     * @param texture
     * @param initial_vbo_capacity
     */
    Material(Scene& scene, std::unique_ptr<MaterialProperties>& properties, std::unique_ptr<Texture2D>& texture,
        std::unique_ptr<VertexBufferObject>& vbo)
        : m_scene(scene)
        , m_properties(std::move(properties))
        , m_texture(std::move(texture))
        , m_vbo(std::move(vbo))
    {
    }

    void render(C3D_Mtx* model_view_matrix) const
    {
        auto buf_info = C3D_GetBufInfo();
        BufInfo_Init(buf_info);
        BufInfo_Add(buf_info, m_vbo->data(), sizeof(GPUVertex), 3, 0x210);

        C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_scene.uloc_model_view, model_view_matrix);
        C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, m_scene.uloc_material, reinterpret_cast<C3D_Mtx*>(m_properties.get()));
        C3D_FVUnifSet(GPU_VERTEX_SHADER, m_scene.uloc_light_vec, 0.0f, 0.0f, -1.0f, 0.0f);
        C3D_FVUnifSet(GPU_VERTEX_SHADER, m_scene.uloc_light_half_vec, 0.0f, 0.0f, -1.0f, 0.0f);
        C3D_FVUnifSet(GPU_VERTEX_SHADER, m_scene.uloc_light_clr, 1.0f, 1.0f, 1.0f, 1.0f);

        if (m_texture)
            m_texture->bind();
        C3D_DrawArrays(GPU_TRIANGLES, 0, m_vbo->size());
    }

private:
    static constexpr auto k_tag = "Material";

    Scene& m_scene;

    std::unique_ptr<MaterialProperties> m_properties;
    std::unique_ptr<Texture2D> m_texture;
    std::unique_ptr<VertexBufferObject> m_vbo;

    C3D_Mtx m_model_view_matrix;
    C3D_Mtx m_material_properties_matrix;
};