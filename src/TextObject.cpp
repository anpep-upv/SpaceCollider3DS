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

#include <cassert>

#include <Graphics/TextObject.hpp>

TextObject::TextObject(const std::string& text, const Vec3<float>& position, const Vec2<float>& scale, const Vec4<float>& color)
    : m_position(position)
    , m_scale(scale)
    , m_color(color)
{
    set_text(text);
}

TextObject::~TextObject() { clear(); }

void TextObject::set_text(const std::string& text)
{
    if (text.empty()) {
        clear();
        return;
    }

    const auto newSize = text.size();

    if (!m_c2d_text_buffer) {
        // Text buffer not yet allocated
        m_c2d_text_buffer = C2D_TextBufNew(newSize);
        assert(m_c2d_text_buffer);
    } else if (newSize > C2D_TextBufGetNumGlyphs(m_c2d_text_buffer)) {
        // New text would overflow the buffer
        m_c2d_text_buffer = C2D_TextBufResize(m_c2d_text_buffer, newSize);
        assert(m_c2d_text_buffer);
    } else {
        // The buffer stays the same
        C2D_TextBufClear(m_c2d_text_buffer);
    }

    // Set actual text
    const auto result = C2D_TextParse(&m_c2d_text, m_c2d_text_buffer, text.c_str());
    assert(result);
    C2D_TextOptimize(&m_c2d_text);

    // Cache dimensions
    C2D_TextGetDimensions(&m_c2d_text, m_scale.x, m_scale.y, &m_dimensions.x, &m_dimensions.y);
}

void TextObject::clear()
{
    if (m_c2d_text_buffer) {
        C2D_TextBufDelete(m_c2d_text_buffer);
        m_c2d_text_buffer = nullptr;
        m_text.clear();
    }
}

static uint32_t translate_text_alignment_to_flags(TextObject::TextAlignment text_alignment)
{
    switch (text_alignment) {
    case TextObject::TextAlignment::Left:
        return C2D_AlignLeft;
    case TextObject::TextAlignment::Center:
        return C2D_AlignCenter;
    case TextObject::TextAlignment::Right:
        return C2D_AlignRight;
    }
    return {};
}

void TextObject::render() const
{
    if (m_text_style == TextStyle::Outlined) {
        const auto outline_color = C2D_Color32f(0.f, 0.f, 0.f, 1.f);
        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                float offset_x = i == 0 ? -1.f : 1.f;
                float offset_y = j == 0 ? -1.f : 1.f;
                C2D_DrawText(&m_c2d_text, C2D_WithColor | translate_text_alignment_to_flags(m_text_alignment),
                    m_position.x + offset_x, m_position.y + offset_y, m_position.z, m_scale.x, m_scale.y,
                    outline_color);
            }
        }
    }

    C2D_DrawText(&m_c2d_text, C2D_WithColor | translate_text_alignment_to_flags(m_text_alignment), m_position.x,
        m_position.y, m_position.z, m_scale.x, m_scale.y, C2D_Color32f(m_color.x, m_color.y, m_color.z, m_color.w));
}
