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

#include <cassert>

#include <citro3d.h>

#include <Foundation/Util.hpp>
#include <Graphics/Scene.hpp>

#include "vshader_shbin.h"

Scene::Scene()
{
    // Load the vertex shader
    m_shader_dvlb = DVLB_ParseFile((uint32_t*)vshader_shbin, vshader_shbin_size);
    debug_trace("DVLB parsing OK");
    // Create shader program
    shaderProgramInit(&m_shader_program);
    shaderProgramSetVsh(&m_shader_program, &m_shader_dvlb->DVLE[0]);
    debug_trace("shader program created");
    // Bind shader program
    C3D_BindProgram(&m_shader_program);
    debug_trace("shader program bound to GPU");

    // Get the location of the uniforms
    uloc_projection = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "projection");
    uloc_model_view = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "modelView");
    uloc_light_vec = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "lightVec");
    uloc_light_half_vec = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "lightHalfVec");
    uloc_light_clr = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "lightClr");
    uloc_material = shaderInstanceGetUniformLocation(m_shader_program.vertexShader, "material");

    // Configure vertex shader attributes
    m_attr_info = C3D_GetAttrInfo();
    AttrInfo_Init(m_attr_info);
    AttrInfo_AddLoader(m_attr_info, 0, GPU_FLOAT, 3); // v0 (position)
    AttrInfo_AddLoader(m_attr_info, 1, GPU_FLOAT, 2); // v1 (texcoord)
    AttrInfo_AddLoader(m_attr_info, 2, GPU_FLOAT, 3); // v2 (normal)
    debug_trace("vertex shader attributes OK");

    // Compute the projection matrix
    Mtx_PerspTilt(&projection_matrix, k_camera_fov, C3D_AspectRatioTop, k_camera_near, k_camera_far, false);
    debug_trace("initial projection matrix OK");
}

Scene::~Scene()
{
    debug_trace("destructor");
#if 0
    // XXX: Calling shaderProgramFree() before C3D_Fini() seems to crash emulator
    // Investigate this issue or keep as-is? (~Scene should almost never be called -- test on real device)
    C3D_Fini();
#endif
    shaderProgramFree(&m_shader_program);
    DVLB_Free(m_shader_dvlb);
}

void Scene::update() { }

void Scene::render()
{
    C3D_BindProgram(&m_shader_program);
    C3D_SetAttrInfo(m_attr_info);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uloc_projection, &projection_matrix);
}
