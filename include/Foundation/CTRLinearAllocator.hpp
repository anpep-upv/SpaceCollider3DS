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

#include <new>

#include <3ds.h>

#include "Util.hpp"

template <typename T> struct CTRLinearAllocator {
    typedef T value_type;

    CTRLinearAllocator() = default;
    template <typename U> constexpr CTRLinearAllocator(const CTRLinearAllocator<U>&) noexcept { }

    T* allocate(std::size_t size)
    {
        // XXX: STL requires std::bad_alloc to be thrown on allocation errors
        // However, we're working with exceptions disabled so we're being non-conformant here
        debug_trace("allocating %d * %d = %d bytes", size, sizeof(T), size * sizeof(T));
        return static_cast<T*>(linearAlloc(size * sizeof(T)));
    }

    void deallocate(T* ptr, std::size_t size) noexcept { linearFree(ptr); }

private:
    static constexpr auto k_tag = "CTRLinearAllocator";
};