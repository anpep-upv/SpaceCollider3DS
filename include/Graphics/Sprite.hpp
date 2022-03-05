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

#include <citro2d.h>

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "Vec2.hpp"

struct Sprite {
    Sprite(C2D_SpriteSheet sprite_sheet, size_t sprite_index);

    float get_depth() const { return m_depth; }
    void set_depth(float depth)
    {
        m_depth = depth;
        C2D_SpriteSetDepth(&m_c2d_sprite, depth);
    }

    const Vec2<float>& get_center() const { return m_center; }
    void set_center(const Vec2<float>& center)
    {
        m_center = center;
        C2D_SpriteSetCenter(&m_c2d_sprite, center.x, center.y);
    }

    const Vec2<float>& get_scale() const { return m_scale; }
    void set_scale(const Vec2<float>& scale)
    {
        m_scale = scale;
        C2D_SpriteSetScale(&m_c2d_sprite, scale.x, scale.y);
    }

    const Vec2<float>& get_position() const { return m_position; }
    void set_position(const Vec2<float>& position)
    {
        m_position = position;
        C2D_SpriteSetPos(&m_c2d_sprite, position.x, position.y);
    }

    void render() const;

private:
    C2D_Sprite m_c2d_sprite {};

    float m_depth = 0;
    Vec2<float> m_center {};
    Vec2<float> m_scale {};
    Vec2<float> m_position {};
};
