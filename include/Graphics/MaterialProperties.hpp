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

#include "Vec4.hpp"

struct MaterialProperties {
    MaterialProperties(const Vec4<float>& ambient = {}, const Vec4<float>& diffuse = {},
        const Vec4<float>& specular = {}, const Vec4<float>& emission = {})
        : m_ambient(ambient)
        , m_diffuse(diffuse)
        , m_specular(specular)
        , m_emission(emission)
    {
    }

    const Vec4<float>& get_ambient() const { return m_ambient; }
    const Vec4<float>& get_diffuse() const { return m_diffuse; }
    const Vec4<float>& get_specular() const { return m_specular; }
    const Vec4<float>& get_emission() const { return m_emission; }

    void set_ambient(const Vec4<float>& ambient) { m_ambient = ambient; }
    void set_diffuse(const Vec4<float>& diffuse) { m_diffuse = diffuse; }
    void set_specular0(const Vec4<float>& specular) { m_specular = specular; }
    void set_emission(const Vec4<float>& emission) { m_emission = emission; }

private:
    Vec4<float> m_ambient;
    Vec4<float> m_diffuse;
    Vec4<float> m_specular;
    Vec4<float> m_emission;
};