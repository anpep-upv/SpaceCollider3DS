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

#include "../Graphics/Model3D.hpp"
#include "../Graphics/Scene.hpp"
#include "../Graphics/TextObject.hpp"

struct MainScene final : Scene {
    MainScene();
    void update() override;
    void render() override;

private:
    Model3D m_character_model;
    Model3D m_character_model2;
    TextObject m_text;
};