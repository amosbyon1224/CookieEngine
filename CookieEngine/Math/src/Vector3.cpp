//
//  Vector3.cpp
//  CookieEngine
//
//  Created by Amos Byon on 2/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#include "Vector3.h"
#include "Matrix4.h"

namespace CookieEngine
{
    
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NegativeUnitX(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NegativeUnitY(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NegativeUnitZ(0.0f, 0.0f, -1.0f);
    
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
    
void Vector3::Transform(const Matrix4& mat)
{
    __m128 temp = _mm_set_ss(1.0f);
    mData = _mm_insert_ps(mData, temp, 0x30);
    
    temp = _mm_dp_ps(mat.mRows[0], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xC0);
    
    temp = _mm_dp_ps(mat.mRows[1], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xD0);
    
    temp = _mm_dp_ps(mat.mRows[2], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xE0);
    
    temp = _mm_dp_ps(mat.mRows[3], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xF0);
}
    
void Vector3::TransformAsVector(const Matrix4& mat)
{
    __m128 temp = _mm_set_ss(0.0f);
    mData = _mm_insert_ps(mData, temp, 0x30);
    
    temp = _mm_dp_ps(mat.mRows[0], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xC0);
    
    temp = _mm_dp_ps(mat.mRows[1], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xD0);
    
    temp = _mm_dp_ps(mat.mRows[2], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xE0);
    
    temp = _mm_dp_ps(mat.mRows[3], mData, 0xF8);
    mData = _mm_insert_ps(mData, temp, 0xF0);
}
    
} // namespace CookieEngine
