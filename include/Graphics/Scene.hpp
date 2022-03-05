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
#include <cstdint>

#include <citro3d.h>

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "../Foundation/Util.hpp"

struct Scene : NonCopyable, NonMoveable {
    virtual ~Scene();
    virtual void update();
    virtual void render();

    C3D_Mtx projection_matrix = {};

    int8_t uloc_projection = 0, uloc_model_view = 0;
    int8_t uloc_light_vec = 0, uloc_light_half_vec = 0, uloc_light_clr = 0;
    int8_t uloc_material = 0;

protected:
    Scene();

    /* GPUVertex shader */
    DVLB_s* m_shader_dvlb = nullptr;
    shaderProgram_s m_shader_program = {};

    /* GPU attributes */
    C3D_AttrInfo* m_attr_info;

    /* Camera */
    static constexpr float k_camera_fov = 55.0f;
    static constexpr float k_camera_near = 20.f;
    static constexpr float k_camera_far = 10000.0f;

private:
    static constexpr auto k_tag = "Scene";
};