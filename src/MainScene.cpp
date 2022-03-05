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

#include <SpaceCollider3DS/MainScene.hpp>

MainScene::MainScene()
    : m_character_model(*this, { 0, 35, -50 }, { M_PI, M_PI, 0 })
    , m_character_model2(*this, { 15, 35, -50 }, { M_PI, M_PI, 0 })
{
    m_character_model.load_from_file("romfs:/model/wolf_link.dat");
    m_character_model2.load_from_file("romfs:/model/wolf_link.dat");

    m_text.set_text_alignment(TextObject::TextAlignment::Center);
    m_text.set_position({ 120, 24 });
    m_text.set_scale({ 1, 1 });
    m_text.set_color({ 0, 0, 0, 0.5 });
    m_text.set_text("Hello, world!");
}

void MainScene::update() {
    Scene::update();
    m_character_model.get_rotation().y += 0.15;
    m_character_model2.get_rotation().z += 0.075;
}

void MainScene::render()
{
    Scene::render();

    m_character_model.render();
    m_character_model2.render();

    C2D_Prepare();
    m_text.render();
    C2D_Flush();
}