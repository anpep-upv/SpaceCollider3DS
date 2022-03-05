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

#include <citro3d.h>

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"

struct Texture2D final : NonCopyable, NonMoveable {
    explicit Texture2D(const std::string& path);
    ~Texture2D();

    void bind();

private:
    static constexpr auto k_tag = "Texture2D";

    bool m_loaded = false;
    C3D_Tex m_c3d_tex = {};
};