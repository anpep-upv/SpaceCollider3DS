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

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "../Graphics/Scene.hpp"

/**
 * The App class abstracts the main application logic. It's purpose is to instantiate objects used throughout the entire
 * application lifecycle.
 */
struct App final : NonCopyable, NonMoveable {
    /**
     * Instantiates the application.
     */
    App();

    /**
     * Releases all resources used by the application.
     */
    ~App();

    /**
     * Executes the main application loop.
     */
    void run();

private:
    static constexpr auto k_tag = "App";

    /* Socket service */
    static constexpr uint32_t k_soc_align = 0x1000;
    static constexpr uint32_t k_soc_buffer_size = 0x100000;
    uint32_t* m_soc_buffer;

    /* Graphics */
    Scene* m_top_scene;
    Scene *m_bottom_scene;

    C3D_RenderTarget* m_top_screen;
    C3D_RenderTarget *m_bottom_screen;
};