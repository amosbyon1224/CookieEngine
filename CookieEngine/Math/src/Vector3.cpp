//
//  Vector3.cpp
//  CookieEngine
//
//  Created by Amos Byon on 2/12/16.
//  Copyright (c) 2016 Amos Byon. All rights reserved.
//

#include "Vector3.h"

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
    
} // namespace CookieEngine
