//
//  Matrix4.cpp
//  CookieEngine
//
//  Created by Amos Byon on 3/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#include "Matrix4.h"
#include "Vector3.h"

namespace CookieEngine {
    
    float identity[4][4] = {1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};
    const Matrix4 Matrix4::Identity(identity);
    
    void Matrix4::CreateTranslation(const CookieEngine::Vector3& translation)
    {
        mRows[0] = _mm_setr_ps(1.0f, 0.0f, 0.0f, translation.GetX());
        mRows[1] = _mm_setr_ps(0.0f, 1.0f, 0.0f, translation.GetY());
        mRows[2] = _mm_setr_ps(0.0f, 0.0f, 1.0f, translation.GetZ());
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    void Matrix4::CreateLookAt(const CookieEngine::Vector3& vEye,
                               const CookieEngine::Vector3& vAt,
                               const CookieEngine::Vector3& vUp)
    {
        Vector3 zAxis = vAt;
        zAxis.Sub(vEye);
        zAxis.Normalize();
        
        Vector3 xAxis = Cross(vUp, zAxis);
        xAxis.Normalize();
        
        Vector3 yAxis = Cross(zAxis, xAxis);
        
        mRows[0] = _mm_setr_ps(xAxis.GetX(), xAxis.GetY(), xAxis.GetZ(), -1.0f * xAxis.Dot(vEye));
        mRows[1] = _mm_setr_ps(yAxis.GetX(), yAxis.GetY(), yAxis.GetZ(), -1.0f * yAxis.Dot(vEye));
        mRows[2] = _mm_setr_ps(zAxis.GetX(), zAxis.GetY(), zAxis.GetZ(), -1.0f * zAxis.Dot(vEye));
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        
    }
    
    void Matrix4::CreatePerspective(float fovy, float fAspectRatio, float fNear, float fFar)
    {
        float yScale = tanf(1.57079633f - (fovy/2));
        float xScale = yScale / fAspectRatio;
        
        mRows[0] = _mm_setr_ps(xScale, 0.0f, 0.0f, 0.0f);
        mRows[1] = _mm_setr_ps(0.0f, yScale, 0.0f, 0.0f);
        mRows[2] = _mm_setr_ps(0.0f, 0.0f, fFar/(fFar-fNear), -fNear*fFar/(fFar-fNear));
        mRows[3] = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
    }
} // namespace CookieEngine
