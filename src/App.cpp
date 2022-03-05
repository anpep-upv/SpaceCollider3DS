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

#include <3ds.h>
#include <arpa/inet.h>
#include <citro2d.h>
#include <citro3d.h>
#include <malloc.h>

#include <Foundation/Util.hpp>

#include <SpaceCollider3DS/App.hpp>
#include <SpaceCollider3DS/MainScene.hpp>

App::App()
{
    /* Console initialization */
    gfxInitDefault();
    consoleDebugInit(debugDevice_CONSOLE);

    /* Initialize socket service */
    m_soc_buffer = static_cast<uint32_t*>(memalign(k_soc_align, k_soc_buffer_size));
    if (!m_soc_buffer)
        fprintf(stderr, "memalign() failed\n");
    if (auto result = socInit(m_soc_buffer, k_soc_buffer_size); result != 0)
        fprintf(stderr, "socInit() failed: %ld\n", result);

    /* Connect to 3dslink socket */
    char host_addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &__3dslink_host, host_addr, INET_ADDRSTRLEN);
    if (!strcmp(host_addr, "0.0.0.0")) {
        // No 3dslink host (outdated hbmenu?)
#ifdef __3DSLINK_HOST
        fprintf(stderr, "built-in 3dslink host: " __3DSLINK_HOST "\n");
        inet_pton(AF_INET, __3DSLINK_HOST, &__3dslink_host);
#endif
    }

    if (auto result = link3dsStdioForDebug(); result < 0) {
        fprintf(stderr, "link3dsStdioForDebug() failed: %d\n", result);
    } else {
        consoleDebugInit(debugDevice_NULL);
    }

    /* romfs initialization */
    romfsInit();

    /* 2D graphics initialization */
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    debug_trace("C2D initialized");

    /* 3D graphics initialization */
    constexpr auto display_transfer_flags = (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0)
        | GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8)
        | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO));
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    debug_trace("C3D initialized");
    m_top_screen = C3D_RenderTargetCreate(
        240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
    m_bottom_screen = C3D_RenderTargetCreate(
        240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
    debug_trace("C3D render targets created");
    C3D_RenderTargetSetOutput(m_top_screen, GFX_TOP, GFX_LEFT, display_transfer_flags);
    C3D_RenderTargetSetOutput(m_bottom_screen, GFX_BOTTOM, GFX_LEFT, display_transfer_flags);
    debug_trace("C3D render target outputs set");

    m_top_scene = new MainScene;
    m_bottom_scene = new MainScene;
}

App::~App()
{
    delete m_top_scene;
    C3D_Fini();
    C2D_Fini();
    gfxExit();
    romfsExit();
    socExit();
    free(m_soc_buffer);
}

void App::run()
{
    while (aptMainLoop()) {
        hidScanInput();

        if (hidKeysDown() & KEY_START) {
            debug_trace("user break");
            break;
        }

        m_top_scene->update();
        m_bottom_scene->update();

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C3D_RenderTargetClear(m_top_screen, C3D_CLEAR_ALL, 0x68B0D8FF, 0);
        C3D_FrameDrawOn(m_top_screen);
        C2D_SceneTarget(m_top_screen);

        m_top_scene->render();
        m_top_scene->render();

        C3D_RenderTargetClear(m_bottom_screen, C3D_CLEAR_ALL, 0xD8B068FF, 0);
        C3D_FrameDrawOn(m_bottom_screen);
        C2D_SceneTarget(m_bottom_screen);
        m_bottom_scene->render();
        C3D_FrameEnd(0);
    }
}