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

#include "Vec2.hpp"
#include "Vec3.hpp"

struct GPUVertex {
    GPUVertex(const Vec3<float>& position = {}, const Vec2<float>& texcoord = {}, const Vec3<float>& normal = {})
        : m_position(position)
        , m_texcoord(texcoord)
        , m_normal(normal)
    {
    }

    const Vec3<float>& get_position() const { return m_position; }
    const Vec2<float>& get_texcoord() const { return m_texcoord; }
    const Vec3<float>& get_normal() const { return m_normal; }

    void set_position(const Vec3<float>& position) { m_position = position; }
    void set_texcoord(const Vec2<float>& texcoord) { m_texcoord = texcoord; }
    void set_normal(const Vec3<float>& normal) { m_normal = normal; }

private:
    Vec3<float> m_position;
    Vec2<float> m_texcoord;
    Vec3<float> m_normal;
};