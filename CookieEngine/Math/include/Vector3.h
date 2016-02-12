//
//  Vector3.h
//  CookieEngine
//
//  Created by Amos Byon on 2/11/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#ifndef CookieEngine_Vector3_h
#define CookieEngine_Vector3_h

#include <smmintrin.h>

namespace CookieEngine
{
// 3D vector class using SSE4.1
class Vector3
{
private:
    __m128 mData;
    
public:
    // Default constructor does nothing
    __attribute__((always_inline)) Vector3() {}
    
    // Constructs a vector given passed x, y, and z components
    // w is set to 1.0f
    __attribute__((always_inline)) Vector3(float x, float y, float z)
    {
        mData = _mm_setr_ps(x, y, z, 1.0f);
    }
    
    // Constructs a vector given an __m128
    __attribute__((always_inline)) Vector3(__m128 value)
    {
        mData = value;
    }
    
    // Copy constructor
    __attribute__((always_inline)) Vector3(const Vector3& rhs)
    {
        mData = rhs.mData;
    }
    
    // Assignment operator
    __attribute__((always_inline)) Vector3& operator=(const Vector3& rhs)
    {
        mData = rhs.mData;
        return *this;
    }
    
    // Returns the X component of Vector (THIS OPERATION IS VERY SLOW)
    __attribute__((always_inline)) float GetX() const
    {
        return mData[0];
    }
    
    // Returns the Y component of Vector (THIS OPERATION IS VERY SLOW)
    __attribute__((always_inline)) float GetY() const
    {
        return mData[1];
    }
    
    // Returns the Z component of Vector (THIS OPERATION IS VERY SLOW)
    __attribute__((always_inline)) float GetZ() const
    {
        return mData[2];
    }
    
    // Returns the W component of Vector (THIS OPERATION IS VERY SLOW)
    __attribute__((always_inline)) float GetW() const
    {
        return mData[3];
    }
    
    // Sets x, y, and z components of vector
    // w is automatically set to 1.0f
    __attribute__((always_inline)) void Set(float x, float y, float z)
    {
        mData = _mm_setr_ps(x, y, z, 1.0f);
    }
    
    // Sets x component of vector
    __attribute__((always_inline)) void SetX(float x)
    {
        __m128 temp = _mm_set_ss(x);
        mData = _mm_insert_ps(mData, temp, 0x00);
    }
    
    // Sets y component of vector
    __attribute__((always_inline)) void SetY(float y)
    {
        __m128 temp = _mm_set_ss(y);
        mData = _mm_insert_ps(mData, temp, 0x10);
    }
    
    // Sets z component of vector
    __attribute__((always_inline)) void SetZ(float z)
    {
        __m128 temp = _mm_set_ss(z);
        mData = _mm_insert_ps(mData, temp, 0x20);
    }
    
    // Sets w component of vector
    __attribute__((always_inline)) void SetW(float w)
    {
        __m128 temp = _mm_set_ss(w);
        mData = _mm_insert_ps(mData, temp, 0x30);
    }
    
    // Calculates the dot product of this vector and rhs
    __attribute__((always_inline)) float Dot(const Vector3& rhs) const
    {
        return _mm_dp_ps(mData, rhs.mData, 0.7F)[0];
    }
    
    // Does a componentwise addition with rhs and stores in this
    __attribute__((always_inline)) void Add(const Vector3& rhs)
    {
        mData = _mm_add_ps(mData, rhs.mData);
    }
    
    // Does a componentwise subtraction with rhs and stores in this
    __attribute__((always_inline)) void Sub(const Vector3& rhs)
    {
        mData = _mm_sub_ps(mData, rhs.mData);
    }
    
    // Multiplies each component by scalar
    __attribute__((always_inline)) void Multiply(float scalar)
    {
        __m128 temp = _mm_set_ps1(scalar);
        mData = _mm_mul_ps(mData, temp);
    }
    
    // Normalizes this vector
    __attribute__((always_inline)) void Normalize()
    {
        __m128 temp = _mm_dp_ps(mData, mData, 0x7F);
        temp = _mm_rsqrt_ps(temp);
        mData = _mm_mul_ps(mData, temp);
    }
    
    // Returns the squared length of this vector
    __attribute__((always_inline)) float LengthSquared() const
    {
        return _mm_dp_ps(mData, mData, 0x7F)[0];
    }
    
    // Returns the length of this vector
    __attribute__((always_inline)) float Length() const
    {
        __m128 temp = _mm_dp_ps(mData, mData, 0x7F);
        __m128 rsqrt = _mm_rsqrt_ps(temp);
        return _mm_mul_ps(temp, rsqrt)[0];
    }
    
    // Computes the cross product between lhs and rhs
    // returns the result by value
    __attribute__((always_inline)) friend Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
    {
        __m128 tempA = _mm_shuffle_ps(lhs.mData, lhs.mData, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 tempB = _mm_shuffle_ps(rhs.mData, rhs.mData, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 result = _mm_mul_ps(tempA, tempB);
        
        tempA = _mm_shuffle_ps(lhs.mData, lhs.mData, _MM_SHUFFLE(3, 1, 0, 2));
        tempB = _mm_shuffle_ps(rhs.mData, rhs.mData, _MM_SHUFFLE(3, 0, 2, 1));
        tempA = _mm_mul_ps(tempA, tempB);
        
        return _mm_sub_ps(result, tempA);
    }
    
    // Interpolates between vector a and b
    // returns resulting vector by value
    __attribute__((always_inline)) friend Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
    {
        __m128 input = _mm_set_ps1(f);
        __m128 diff = _mm_set_ps1(1.0f - f);
        
        __m128 multA = _mm_mul_ps(a.mData, diff);
        __m128 multB = _mm_mul_ps(b.mData, input);
        
        return _mm_add_ps(multA, multB);
    }
    
    // Calculates a 4 way blend
    // returns resulting vector by value
    __attribute__((always_inline)) friend Vector3 Blend(const Vector3& a, const Vector3& b,
                                                        const Vector3& c, const Vector3& d,
                                                        float fa, float fb, float fc)
    {
        __m128 input = _mm_set_ps1(fa);
        __m128 result = _mm_mul_ps(a.mData, input);
        
        input = _mm_set_ps1(fb);
        __m128 mult = _mm_mul_ps(b.mData, input);
        result = _mm_add_ps(result, mult);
        
        input = _mm_set_ps1(fc);
        mult = _mm_mul_ps(c.mData, input);
        result = _mm_add_ps(result, mult);
        
        input = _mm_set_ps1(1.0f - fa - fb - fc);
        mult = _mm_mul_ps(d.mData, input);
        
        return _mm_add_ps(result, mult);
    }
    
    // TODO: Transform (multiply by transform matrix)
    
    // TODO: Transform as Vector (multiply by transform matrix & set w to 0f)
    
    // TODO: Rotate (multiply by quaternion)
    
    static const Vector3 Zero;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 NegativeUnitX;
    static const Vector3 NegativeUnitY;
    static const Vector3 NegativeUnitZ;
    static const Vector3 Right;
    static const Vector3 Up;
    static const Vector3 Forward;
    
} __attribute__ ((aligned (16)));

} // namespace CookieEngine
#endif
