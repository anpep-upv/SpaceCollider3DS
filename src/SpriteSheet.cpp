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

#include <Graphics/Sprite.hpp>
#include <Graphics/SpriteSheet.hpp>

SpriteSheet::SpriteSheet(const std::string& path)
    : m_c2d_sprite_sheet(nullptr)
{
    m_c2d_sprite_sheet = C2D_SpriteSheetLoad(path.c_str());
    m_sprite_count = C2D_SpriteSheetCount(m_c2d_sprite_sheet);

    m_sprites.reserve(m_sprite_count);
    for (size_t i = 0; i < m_sprite_count; i++)
        m_sprites.emplace_back(m_c2d_sprite_sheet, i);
}

SpriteSheet::~SpriteSheet()
{
    m_sprites.clear();
    if (m_c2d_sprite_sheet)
        C2D_SpriteSheetFree(m_c2d_sprite_sheet);
    m_c2d_sprite_sheet = nullptr;
}
