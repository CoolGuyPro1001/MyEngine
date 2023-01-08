#ifndef MATRIX_H
#define MATRIX_H

#include "Error.h"

//In this file, you can dodge bullets

//Row Major Matrix
template<typename T, std::size_t R, std::size_t C>
struct Matrix
{
    Matrix();
    Matrix(const u8* data, const size_t data_size);

    template<std::size_t R0, std::size_t C0>
    Matrix(const Matrix<T, R0, C0>& other);

    T data[R][C]; //C Style Array For Easier Memory Copying
    uint rows;
    uint columns;

    bool operator==(const Matrix<T, R, C>& m) const;
    bool operator!=(const Matrix<T, R, C>& m) const;
    T* operator[](const uint i);
};

typedef Matrix<float, 3, 3> Mat3;
typedef Matrix<float, 4, 4> Mat4;

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C>::Matrix()
{
    rows = R;
    columns = C;

    memset(data, 0, R * C * sizeof(T));
}

template<typename T, std::size_t R, std::size_t C>
Matrix<T, R, C>::Matrix(const u8* data, const size_t size)
{
    rows = R;
    columns = C;

    if(size != R * C * sizeof(T))
    {
        CriticalError(ENGINE_ERROR, "Byte Size Not Equal To Row * Column * Sizeof(Type), Filling Matrix With 0's\n");
        memset(this->data, 0, R * C * sizeof(T));
    }

    memcpy(this->data, data, size);
}

template<typename T, std::size_t R, std::size_t C>
template<std::size_t R0, std::size_t C0>
Matrix<T, R, C>::Matrix(const Matrix<T, R0, C0>& other) : Matrix()
{
    int row_min = std::min(rows, other.rows);

    for(int r = 0; r < row_min; r++)
        memcpy(data[r], other.data[r], row_min * sizeof(T));
}

template<typename T, std::size_t R, std::size_t C>
bool Matrix<T, R, C>::operator==(const Matrix<T, R, C>& m) const
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            if(data[r][c] != m[r][c])
                return false;
        }
    }

    return true;
}

template<typename T, std::size_t R, std::size_t C>
bool Matrix<T, R, C>::operator!=(const Matrix<T, R, C>& m) const
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            if(data[r][c] != m[r][c])
                return true;
        }
    }

    return false;
}

template<typename T, std::size_t R, std::size_t C>
T* Matrix<T, R, C>::operator[](const uint i)
{
    if(i < rows)
        return data[i];

    CriticalError(ENGINE_ERROR, "Index Greater Than Matrix Data Size, Returning Row 0\n");
    return data[0];
}
#endif
