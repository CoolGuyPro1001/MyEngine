#include "Units.h"

Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(const Vector2& v) 
{
    x = v.x;
    y = v.y;
}

bool Vector2::operator==(const Vector2& v) const
{
    return v.x == x && v.y == y;
}

bool Vector2::operator!=(const Vector2& v) const
{
    return v.x != x || v.y != y;
}

bool Vector2::operator>(const Vector2& v) const
{
    return x > v.x && y > v.y;
}

bool Vector2::operator>=(const Vector2& v) const
{
    return x >= v.x && y >= v.y;
}

bool Vector2::operator<(const Vector2& v) const
{
    return x < v.x && y < v.y;
}

bool Vector2::operator<=(const Vector2& v) const
{
    return x <= v.x && y <= v.y;
}

void Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

void Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
}

void Vector2::operator*=(const Vector2& v)
{
    x *= v.x;
    y *= v.y;
}

void Vector2::operator/=(const Vector2& v)
{
    x /= v.x;
    y /= v.y;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
    return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator*(const float& f) const
{
    return Vector2(x * f, y * f);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
    return Vector2(x / v.x, y / v.y);
}

Vector3 Vector2::ToVector3()
{
    return Vector3(x, y, 0.0f);
}









Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& v) 
{
    x = v.x;
    y = v.y;
    z = v.z;
}

bool Vector3::operator==(const Vector3& v) const
{
    return v.x == x && v.y == y && v.z == z;
}

bool Vector3::operator!=(const Vector3& v) const
{
    return v.x != x || v.y != y || v.z != z;
}

bool Vector3::operator>(const Vector3& v) const
{
    return x > v.x && y > v.y && z > v.z;
}

bool Vector3::operator>=(const Vector3& v) const
{
    return x >= v.x && y >= v.y && z >= v.z;
}

bool Vector3::operator<(const Vector3& v) const
{
    return x < v.x && y < v.y && z < v.z;
}

bool Vector3::operator<=(const Vector3& v) const
{
    return x <= v.x && y <= v.y && z <= v.z;
}

void Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

void Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

void Vector3::operator/=(const Vector3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*(const float f) const
{
    return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
    return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector2 Vector3::ToVector2()
{
    return Vector2(x, y);
}








Color::Color()
{
}

Color::Color(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) 
{
}

Color::Color(const Color& c) 
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

bool Color::operator==(const Color& c) const
{
    return c.r == r && c.g == g && c.b == b && c.a == a;
}

bool Color::operator!=(const Color& c) const
{
    return c.r != r || c.g != g || c.b != b || c.a != a;
}

bool Color::operator>(const Color& c) const
{
    return r > c.r && g > c.g && b > c.b && a > c.a;
}

bool Color::operator>=(const Color& c) const
{
    return r >= c.r && g >= c.g && b >= c.b && a >= c.a;
}

bool Color::operator<(const Color& c) const
{
    return r < c.r && g < c.g && b < c.b && a < c.a;
}

bool Color::operator<=(const Color& c) const
{
    return r <= c.r && g <= c.g && b <= c.b && a <= c.a;
}

void Color::operator=(const Color& c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

void Color::operator+=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
}

void Color::operator-=(const Color& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
}

void Color::operator*=(const Color& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *- c.a;
}

void Color::operator/=(const Color& c)
{
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
}

Color Color::operator+(const Color& c) const
{
    return Color(r + c.r, g + c.g, b + c.b, a + c.a);
}

Color Color::operator-(const Color& c) const
{
    return Color(r - c.r, g - c.g, b - c.b, a - c.a);
}

Color Color::operator*(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b, a * c.a);
}

Color Color::operator/(const Color& c) const
{
    return Color(r / c.r, g / c.g, b / c.b, a / c.a);
}








TextureCoords::TextureCoords()
{
}

TextureCoords::TextureCoords(float u, float v) : u(u), v(v)
{
}

TextureCoords::TextureCoords(const TextureCoords& t) 
{
    u = t.u;
    v = t.v;
}

bool TextureCoords::operator==(const TextureCoords& t) const
{
    return u == t.u && v == t.v;
}

bool TextureCoords::operator!=(const TextureCoords& t) const
{
    return u != t.u || v != t.v;
}

bool TextureCoords::operator>(const TextureCoords& t) const
{
    return u > t.u && v > t.v;
}

bool TextureCoords::operator>=(const TextureCoords& t) const
{
    return u >= t.u && v >= t.v;
}

bool TextureCoords::operator<(const TextureCoords& t) const
{
    return u < t.u && v < t.v;
}

bool TextureCoords::operator<=(const TextureCoords& t) const
{
    return u <= t.u && v <= t.v;
}

void TextureCoords::operator=(const TextureCoords& t)
{
    u = t.u;
    v = t.v;
}

void TextureCoords::operator+=(const TextureCoords& t)
{
    u += t.u;
    v += t.v;
}

void TextureCoords::operator-=(const TextureCoords& t)
{
    u -= t.u;
    v -= t.v;
}

void TextureCoords::operator*=(const TextureCoords& t)
{
    u *= t.u;
    v *= t.v;
}

void TextureCoords::operator/=(const TextureCoords& t)
{
    u /= t.u;
    v /= t.v;
}

TextureCoords TextureCoords::operator+(const TextureCoords& t) const
{
    return TextureCoords(u + t.u, v + t.v);
}

TextureCoords TextureCoords::operator-(const TextureCoords& t) const
{
    return TextureCoords(u - t.u, v - t.v);
}

TextureCoords TextureCoords::operator*(const TextureCoords& t) const
{
    return TextureCoords(u * t.u, v * t.v);
}

TextureCoords TextureCoords::operator/(const TextureCoords& t) const
{
    return TextureCoords(u / t.u, v / t.v);
}








Vertex::Vertex()
{
}

Vertex::Vertex(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coords = v.texture_coords;
}

Vertex::Vertex(Vector3 vector, Color color) : color(color), vector(vector)
{
    texture_coords = TextureCoords(0.0f, 0.0f);
}

Vertex::Vertex(Vector2 vector, Color color) : color(color)
{
    this->vector = vector.ToVector3();
    texture_coords = TextureCoords(0.0f, 0.0f);
}

Vertex::Vertex(Vector3 vector, TextureCoords texture_coords) : vector(vector), texture_coords(texture_coords)
{
    color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Vertex::Vertex(Vector2 vector, TextureCoords texture_coords) : texture_coords(texture_coords)
{
    this->vector = vector.ToVector3();
    color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Vertex::Vertex(Vector3 vector, Color color, TextureCoords texture_coords) : color(color), vector(vector), 
    texture_coords(texture_coords)
{
}

Vertex::Vertex(Vector2 vector, Color color, TextureCoords texture_coords) : color(color), texture_coords(texture_coords)
{
    this->vector = vector.ToVector3();
}

bool Vertex::operator==(const Vertex& v) const
{
    return v.vector == vector && v.color == color && v.texture_coords == texture_coords;
}

bool Vertex::operator!=(const Vertex& v) const
{
    return v.vector != vector || v.color != color || v.texture_coords == texture_coords;
}

bool Vertex::operator>(const Vertex& v) const
{
    return vector > v.vector && color > v.color && texture_coords > v.texture_coords;
}

bool Vertex::operator>=(const Vertex& v) const
{
    return vector >= v.vector && color >= v.color && texture_coords >= v.texture_coords;
}

bool Vertex::operator<(const Vertex& v) const
{
    return vector < v.vector && color < v.color && texture_coords < v.texture_coords;
}

bool Vertex::operator<=(const Vertex& v) const
{
    return vector <= v.vector && color <= v.color && texture_coords <= v.texture_coords;
}

void Vertex::operator=(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coords = v.texture_coords;
}

void Vertex::operator+=(const Vertex& v)
{
    vector += v.vector;
    color += v.color;
    texture_coords += v.texture_coords;
}

void Vertex::operator-=(const Vertex& v)
{
    vector -= v.vector;
    color -= v.color;
    texture_coords -= v.texture_coords;
}

void Vertex::operator*=(const Vertex& v)
{
    vector *= v.vector;
    color *= v.color;
    texture_coords *= v.texture_coords;
}

void Vertex::operator/=(const Vertex& v)
{
    vector /= v.vector;
    color /= v.color;
    texture_coords /= v.texture_coords;
}

Vertex Vertex::operator+(const Vertex& v) const
{
    return Vertex(vector + v.vector, color + v.color, texture_coords + v.texture_coords);
}

Vertex Vertex::operator-(const Vertex& v) const
{
    return Vertex(vector - v.vector, color - v.color, texture_coords - v.texture_coords);
}

Vertex Vertex::operator*(const Vertex& v) const
{
    return Vertex(vector * v.vector, color * v.color, texture_coords * v.texture_coords);
}

Vertex Vertex::operator/(const Vertex& v) const
{
    return Vertex(vector / v.vector, color / v.color, texture_coords / v.texture_coords);
}