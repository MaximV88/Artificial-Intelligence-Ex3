//
//  Dot.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Dot.hpp"
#include <math.h>

Dot::Dot(float x, float y) :
m_x(x),
m_y(y)
{ }

bool Dot::operator==(const Dot &dot) const {
    
    return (m_x == dot.m_x && m_y == dot.m_y);
    
}

float Dot::distance(const Dot &dot) const {
    
    return sqrtf(powf(m_x - dot.m_x, 2) + powf(m_y - dot.m_y, 2));
    
}
