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

#include <citro2d.h>

#include "../Foundation/NonCopyable.hpp"
#include "../Foundation/NonMoveable.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

struct TextObject final : NonCopyable, NonMoveable {
    enum class TextAlignment { Left, Center, Right };
    enum class TextStyle { Default, Outlined };

    TextObject() = default;

    /**
     * Creates a @c TextObject with the specified text.
     * @param text Text to be contained in this @c TextObject.
     * @param position Viewport position of the text. Defaults to the origin of viewport coordinates.
     * @param scale Scale factors for the text. Defaults to medium size (0.5, 0.5)
     * @param color Foreground color of the text. Defaults to opaque white.
     */
    explicit TextObject(const std::string& text, const Vec3<float>& position = { 0, 0, 0 },
        const Vec2<float>& scale = { 0.5, 0.5 }, const Vec4<float>& color = { 1, 1, 1, 1 });

    ~TextObject();

    const std::string& get_text() const { return m_text; }

    /**
     * Sets the text in this @c TextObject.
     * @param text New text for this @c TextObject.
     * @remarks If the new text does not fit the previously allocated buffer, it will be resized. Otherwise, no action
     *          will be taken, so you might want to call @c TextObject::clear() if you allocated a large string before.
     */
    void set_text(const std::string& text);

    TextAlignment get_text_alignment() const { return m_text_alignment; }
    void set_text_alignment(TextAlignment text_alignment) { m_text_alignment = text_alignment; }

    TextStyle get_text_style() const { return m_text_style; }
    void set_text_style(TextStyle text_style) { m_text_style = text_style; }

    const Vec3<float>& get_position() const { return m_position; };
    void set_position(const Vec3<float>& position) { m_position = position; }

    const Vec2<float>& get_scale() const { return m_scale; }
    void set_scale(const Vec2<float>& scale) { m_scale = scale; }

    const Vec4<float>& get_color() const { return m_color; }
    void set_color(const Vec4<float>& color) { m_color = color; }

    /**
     * Obtains the viewport dimensions of this @c TextObject.
     * @return A 2D vector containing the viewport width/height occupied by the rendered @c TextObject.
     * @remarks When the text is empty, the height (Y) dimension will also have a value of 0.0.
     */
    const Vec2<float>& get_dimensions() const { return m_dimensions; }

    void clear();

    void render() const;

private:
    std::string m_text = {};
    TextAlignment m_text_alignment = TextAlignment::Left;
    TextStyle m_text_style = TextStyle::Default;

    Vec3<float> m_position { 0, 0, 0 };
    Vec2<float> m_scale { 0.5, 0.5 };
    Vec4<float> m_color { 1, 1, 1, 1 };

    C2D_Text m_c2d_text {};
    struct C2D_TextBuf_s* m_c2d_text_buffer {};
    Vec2<float> m_dimensions { 0, 0 };
};