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

#include <citro3d.h>
#include <tex3ds.h>

#include <Foundation/Util.hpp>
#include <Graphics/Texture2D.hpp>

Texture2D::Texture2D(const std::string& path)
{
    debug_trace("loading %s", path.c_str());
    auto fp = fopen(path.c_str(), "r");
    if (!fp) {
        debug_trace("error %d", errno);
        return;
    }
    debug_trace("file open");

    debug_trace("importing texture");
    auto t3x = Tex3DS_TextureImportStdio(fp, &m_c3d_tex, nullptr, true);
    if (!t3x) {
        debug_trace("failed");
        fclose(fp);
        return;
    }
    debug_trace("ok");

    m_loaded = true;
    Tex3DS_TextureFree(t3x);
    fclose(fp);
}

Texture2D::~Texture2D()
{
    if (m_loaded)
        C3D_TexDelete(&m_c3d_tex);
}
void Texture2D::bind()
{
    C3D_TexSetFilter(&m_c3d_tex, GPU_LINEAR, GPU_NEAREST);
    C3D_TexBind(0, &m_c3d_tex);

    C3D_TexEnv* env = C3D_GetTexEnv(0);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR);
    C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);
}
