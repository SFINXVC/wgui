#ifndef WGUI__UTILS__VEC2I_H
#define WGUI__UTILS__VEC2I_H

namespace wgui
{
    struct vec2i
    {
        int x;
        int y;

        vec2i(int _x, int _y)
            : x(_x), y(_y)
        {
            
        }

        const vec2i& operator=(const vec2i& rhs) 
        {
            if (this != &rhs) 
            {
                x = rhs.x;
                y = rhs.y;
            }
            return *this;
        }

        vec2i operator+(const vec2i& rhs) const 
        {
            return vec2i(x + rhs.x, y + rhs.y);
        }

        vec2i operator-(const vec2i& rhs) const 
        {
            return vec2i(x - rhs.x, y - rhs.y);
        }

        vec2i operator*(int scalar) const 
        {
            return vec2i(x * scalar, y * scalar);
        }

        vec2i operator/(int scalar) const 
        {
            return vec2i(x / scalar, y / scalar);
        }

        bool operator==(const vec2i& rhs) const 
        {
            return x == rhs.x && y == rhs.y;
        }

        bool operator<(const vec2i& rhs) const 
        {
            return x < rhs.x || (x == rhs.x && y < rhs.y);
        }

        bool operator<=(const vec2i& rhs) const 
        {
            return !(rhs > *this);
        }

        bool operator>(const vec2i& rhs) const 
        {
            return !(*this <= rhs);
        }

        bool operator>=(const vec2i& rhs) const 
        {
            return !(rhs < *this);
        }
    };
}

#endif // WGUI__UTILS__VEC2I_H