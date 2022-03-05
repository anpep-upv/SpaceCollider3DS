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

#include <string>
#include <vector>

#include <citro2d.h>

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "Sprite.hpp"

struct SpriteSheet final : NonCopyable, NonMoveable {
    explicit SpriteSheet(const std::string& path);
    ~SpriteSheet();

    size_t get_sprite_count() const { return m_sprite_count; }
    Sprite& get_sprite(size_t index) { return m_sprites[index]; }
    std::vector<Sprite>& get_sprites() { return m_sprites; }

private:
    C2D_SpriteSheet m_c2d_sprite_sheet;
    size_t m_sprite_count;
    std::vector<Sprite> m_sprites;
};