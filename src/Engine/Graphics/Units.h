#ifndef UNITS_H
#define UNITS_H

namespace Graphics
{
    struct Vector3
    {
        float x, y, z;
        Vector3(float x, float y, float z) : x(x), y(y), z(z){};
        Vector3(){};

        void operator =(const Vector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        bool operator ==(Vector3& v)
        {
            if(v.x == x && v.y == y && v.z == z)
                return true;
            else
                return false;
        }

        bool operator !=(Vector3& v)
        {
            if(v.x != x || v.y != y || v.z == z)
                return true;
            else
                return false;
        }
    };

    struct Color
    {
        float r, g, b, a;
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
        Color(){};

        void operator =(const Color& c)
        {
            r = c.r;
            g = c.g;
            b = c.b;
            a = c.a;
        }

        bool operator ==(Color& c)
        {
            if(c.r == r && c.g == g && c.b == b && c.a == a)
                return true;
            else
                return false;
        }

        bool operator !=(Color& c)
        {
            if(c.r != r || c.g != g || c.b != b || c.a != a)
                return true;
            else
                return false;
        }
    };

    struct Vertex
    {
        Vector3 vector;
        Color color;
        Vertex(Vector3 vector, Color color) : vector(vector), color(color) {};

        void operator =(const Vertex& v)
        {
            vector = v.vector;
            color = v.color;
        }

        bool operator ==(Vertex& v)
        {
            if(v.vector == vector && v.color == color)
                return true;
            else
                return false;
        }

        bool operator !=(Vertex& v)
        {
            if(v.vector != vector || v.color != color)
                return true;
            else
                return false;
        }
    };
}

#endif