//
//  Dot.hpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Dot_hpp
#define Dot_hpp

/**
 * Represents a Dot. The coordinates are
 * immutable by requirment.
 */
class Dot {
public:

    /**
     * Constructor.
     *
     * @param x The X coordinate.
     * @param y The Y coordiante.
     */
    Dot(int x, int y);
    
    /**
     * Returns the X coordinate.
     * 
     * @return X coordinate.
     */
    int getX() const;
    
    /**
     * Returns the Y coordinate.
     *
     * @return Y coordinate.
     */
    int getY() const;
    
private:
    
    ///Stores the X coordinate
    int m_x;
    
    ///Stores the Y coordinate
    int m_y;
    
};

#endif /* Dot_hpp */
