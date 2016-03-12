//
//  Matrix4.h
//  CookieEngine
//
//  Created by Amos Byon on 3/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#ifndef CookieEngine_Matrix4_h
#define CookieEngine_Matrix4_h

#include <smmintrin.h>
#include <cmath>

namespace CookieEngine
{
// Forward declaration to avoid circular dependency
class Vector3;

// 4x4 Matrix class using SSE4.1
class Matrix4
{
private:
    __m128 mRows[4];
public:
    friend class Vector3;
    
    // Default constructor does nothing
    __attribute__((always_inline)) Matrix4() {}
    
    // Contruct a 4x4 Matrix from the passed in float array
    __attribute__((always_inline)) Matrix4(float mat[4][4])
    {
        mRows[0] = _mm_setr_ps(mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
        mRows[1] = _mm_setr_ps(mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
        mRows[2] = _mm_setr_ps(mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
        mRows[3] = _mm_setr_ps(mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
    }
    
    __attribute__((always_inline)) void Set(float mat[4][4])
    {
        mRows[0] = _mm_setr_ps(mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
        mRows[1] = _mm_setr_ps(mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
        mRows[2] = _mm_setr_ps(mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
        mRows[3] = _mm_setr_ps(mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
    }
    
    // Copy constructor
    __attribute__((always_inline)) Matrix4(const Matrix4& rhs)
    {
        mRows[0] = rhs.mRows[0];
        mRows[1] = rhs.mRows[1];
        mRows[2] = rhs.mRows[2];
        mRows[3] = rhs.mRows[3];
    }
    
    // Assignment operator
    __attribute__((always_inline)) Matrix4& operator=(const Matrix4& rhs)
    {
        mRows[0] = rhs.mRows[0];
        mRows[1] = rhs.mRows[1];
        mRows[2] = rhs.mRows[2];
        mRows[3] = rhs.mRows[3];
        return *this;
    }
    
    // Multiplies this Matrix by the rhs matrix
    void Multiply(const Matrix4& rhs)
    {
        __m128 rhs_row0 = rhs.mRows[0];
        __m128 rhs_row1 = rhs.mRows[1];
        __m128 rhs_row2 = rhs.mRows[2];
        __m128 rhs_row3 = rhs.mRows[3];
        
        // transpose the rhs matrix
        _MM_TRANSPOSE4_PS(rhs_row0, rhs_row1, rhs_row2, rhs_row3);
        
        for(int i = 0; i < 4; i++)
        {
            __m128 x = _mm_dp_ps(mRows[i], rhs_row0, 0xF8);
            __m128 y = _mm_dp_ps(mRows[i], rhs_row1, 0xF8);
            __m128 z = _mm_dp_ps(mRows[i], rhs_row2, 0xF8);
            __m128 w = _mm_dp_ps(mRows[i], rhs_row3, 0xF8);
            mRows[i] = _mm_insert_ps(mRows[i], x, 0xC0);
            mRows[i] = _mm_insert_ps(mRows[i], y, 0xD0);
            mRows[i] = _mm_insert_ps(mRows[i], z, 0xE0);
            mRows[i] = _mm_insert_ps(mRows[i], w, 0xF0);
        }
    }
    
    // Transpose this Matrix
    void Transpose()
    {
        _MM_TRANSPOSE4_PS(mRows[0], mRows[1], mRows[2], mRows[3]);
    }
    
    // Adds the rhs matrix to this one
    __attribute__((always_inline)) void Add(Matrix4& rhs)
    {
        mRows[0] = _mm_add_ps(mRows[0], rhs.mRows[0]);
        mRows[1] = _mm_add_ps(mRows[1], rhs.mRows[1]);
        mRows[2] = _mm_add_ps(mRows[2], rhs.mRows[2]);
        mRows[3] = _mm_add_ps(mRows[3], rhs.mRows[3]);
    }
    
    // Subtracts the rhs matrix to this one
    __attribute__((always_inline)) void Sub(Matrix4& rhs)
    {
        mRows[0] = _mm_sub_ps(mRows[0], rhs.mRows[0]);
        mRows[1] = _mm_sub_ps(mRows[1], rhs.mRows[1]);
        mRows[2] = _mm_sub_ps(mRows[2], rhs.mRows[2]);
        mRows[3] = _mm_sub_ps(mRows[3], rhs.mRows[3]);
    }
    
    // Create a Scale matrix from passed in scale value
    __attribute__((always_inline)) void CreateScale(float scale)
    {
        mRows[0] = _mm_set_ss(scale);
        mRows[0] = _mm_shuffle_ps(mRows[0], mRows[0], _MM_SHUFFLE(1, 1, 1, 0));
        
        mRows[1] = _mm_set_ss(scale);
        mRows[1] = _mm_shuffle_ps(mRows[0], mRows[0], _MM_SHUFFLE(1, 1, 0, 1));
        
        mRows[2] = _mm_set_ss(scale);
        mRows[2] = _mm_shuffle_ps(mRows[0], mRows[0], _MM_SHUFFLE(1, 0, 1, 1));
        
        mRows[3] = _mm_set_ss(1.0f);
        mRows[3] = _mm_shuffle_ps(mRows[0], mRows[0], _MM_SHUFFLE(0, 1, 1, 1));
    }
    
    // Create a rotation about X axis given angle in radians
    __attribute__((always_inline)) void CreateRotationX(float angle)
    {
        //  1  0  0  0
        //  0  c -s  0
        //  0  s  c  0
        //  0  0  0  1
        
        float cos = cosf(angle);
        float sin = sinf(angle);
        
        mRows[0] = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
        mRows[1] = _mm_setr_ps(0.0f, cos, sin * -1.0f, 0.0f);
        mRows[2] = _mm_setr_ps(0.0f, sin, cos, 0.0f);
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    // Create a rotation about Y axis given angle in radians
    __attribute__((always_inline)) void CreateRotationY(float angle)
    {
        //  c  0  s  0
        //  0  1  0  0
        // -s  0  c  0
        //  0  0  0  1
        
        float cos = cosf(angle);
        float sin = sinf(angle);
        
        mRows[0] = _mm_setr_ps(cos, 0.0f, sin, 0.0f);
        mRows[1] = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0);
        mRows[2] = _mm_setr_ps(sin * -1.0f, 0.0f, cos, 0.0f);
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    // Create a rotation about Z axis given angle in radians
    __attribute__((always_inline)) void CreateRotationZ(float angle)
    {
        //  c -s  0  0
        //  s  c  0  0
        //  0  0  1  0
        //  0  0  0  1
        
        float cos = cosf(angle);
        float sin = sinf(angle);
        
        mRows[0] = _mm_setr_ps(cos, sin * -1.0f, 0.0f, 0.0f);
        mRows[1] = _mm_setr_ps(sin, cos, 0.0f, 0.0f);
        mRows[2] = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    __attribute__((always_inline)) friend Matrix4 Lerp(const Matrix4& a, const Matrix4& b, float f)
    {
        Matrix4 result;
        
        __m128 rhsF = _mm_set_ps1(f);
        __m128 lhsF = _mm_set_ps1(1.0f);
        lhsF = _mm_sub_ps(lhsF, rhsF);
        
        result.mRows[0] = _mm_mul_ps(a.mRows[0], lhsF);
        result.mRows[0] = _mm_add_ps(result.mRows[0], _mm_mul_ps(b.mRows[0], rhsF));
        result.mRows[1] = _mm_mul_ps(a.mRows[1], lhsF);
        result.mRows[1] = _mm_add_ps(result.mRows[1], _mm_mul_ps(b.mRows[1], rhsF));
        result.mRows[2] = _mm_mul_ps(a.mRows[2], lhsF);
        result.mRows[2] = _mm_add_ps(result.mRows[2], _mm_mul_ps(b.mRows[2], rhsF));
        result.mRows[3] = _mm_mul_ps(a.mRows[3], lhsF);
        result.mRows[3] = _mm_add_ps(result.mRows[3], _mm_mul_ps(b.mRows[3], rhsF));
        
        return result;
    }
    
    // Given translation vector, construct a translation matrix
    void CreateTranslation(const Vector3& translation);
    
    // Constructs a Look At Matrix
    // CAUTION vUp MUST BE NORMALIZED
    void CreateLookAt(const Vector3& vEye, const Vector3& vAt, const Vector3& vUp);
    
    // Constructs a Perspective FOV matrix
    void CreatePerspective(float fovy, float fAspectRatio, float fNear, float fFar);
    
    // Identity Matrix
    static const Matrix4 Identity;
} __attribute__ ((aligned (16)));

} // namespace CookieEngine

#endif
