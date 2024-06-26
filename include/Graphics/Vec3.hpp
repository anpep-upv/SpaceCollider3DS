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

template <typename T> struct Vec3 final {
    T x, y, z;

    Vec3(const Vec3<T>& other)
        : Vec3(other.x, other.y, other.z)
    {
    }

    explicit Vec3(T all)
        : Vec3(all, all, all)
    {
    }

    Vec3(T x = {}, T y = {}, T z = {})
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    T magnitude() const { return static_cast<T>(sqrt(x * x + y * y + z * z)); }

    Vec3 normalized() const
    {
        const T m = magnitude();
        if (m == T())
            return {};

        return *this / Vec3 { m };
    }

    T angleCos(const Vec3<T>& other) const
    {
        return (x * other.x + y * other.y + z * other.z) / (magnitude() * other.magnitude());
    }

    T angle(const Vec3<T>& other) const { return static_cast<T>(acos(angleCos(other))); }

    Vec3 rotated(const Vec3& r) const
    {
        const auto cosYaw = std::cos(r.x), cosPitch = std::cos(r.y), cosRoll = std::cos(r.z);
        const auto sinYaw = std::sin(r.x), sinPitch = std::sin(r.y), sinRoll = std::sin(r.z);
        const auto axx = cosYaw * cosPitch, axy = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll,
                   axz = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;
        const auto ayx = sinYaw * cosPitch, ayy = sinYaw * sinPitch * sinRoll + cosYaw * cosRoll,
                   ayz = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;
        const auto azx = -sinPitch, azy = cosPitch * sinRoll, azz = cosPitch * cosRoll;

        return { axx * x + axy * y + axz * z, ayx * y + ayy * y + ayz * z, azx * x + azy * y + azz * z };
    }

    Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; }

    void operator+=(const Vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    Vec3 operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; }

    void operator-=(const Vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    Vec3 operator*(const T& value) const { return { x * value, y * value, z * value }; }

    void operator*=(const T& value)
    {
        x *= value;
        y *= value;
        z *= value;
    }

    Vec3 operator*(const Vec3& other) const { return { x * other.x, y * other.y, z * other.z }; }

    void operator*=(const Vec3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    Vec3 operator/(const T& value) const { return { x / value, y / value, z / value }; }

    void operator/=(const T& value)
    {
        x /= value;
        y /= value;
        z /= value;
    }

    Vec3 operator/(const Vec3& other) const { return { x / other.x, y / other.y, z / other.z }; }

    void operator/=(const Vec3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
};