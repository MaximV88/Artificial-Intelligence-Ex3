//
//  Dot.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Dot.hpp"

Dot::Dot(int x, int y) :
m_x(x),
m_y(y)
{ }

int Dot::getX() const { return m_x; }

int Dot::getY() const { return m_y; }