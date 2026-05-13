#pragma once

struct Vec2
{
    float X = 0.0f;
    float Y = 0.0f;

    Vec2 operator/(float scalar)
    {
        return { X / scalar, Y / scalar };
    }

    Vec2 operator*(float scalar)
    {
        return { X * scalar, Y * scalar };
    }

    Vec2 operator-(Vec2 other)
    {
        return { X - other.X, Y - other.Y };
    }

    operator bool()
    {
        return X != 0.0f && Y != 0.0f;
    }
};

struct IVec2
{
    int X = 0;
    int Y = 0;

    IVec2 operator-(IVec2 other)
    {
        return { X - other.X, Y - other.Y };
    }

    IVec2& operator-=(int value)
    {
        X -= value;
        Y -= value;
        return *this;
    }

    IVec2& operator+=(int value)
    {
        X += value;
        Y += value;
        return *this;
    }

    IVec2 operator/(int scalar)
    {
        return { X / scalar, Y / scalar };
    }
};