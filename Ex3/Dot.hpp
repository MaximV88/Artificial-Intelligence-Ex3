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
     * Checks if the dot is in the same location.
     *
     * @param dot A dot to compare to.
     * @return True if in same location, false otherwise.
     */
    bool operator==(const Dot& dot) const;
    
    /**
     * Returns the euclidian distance between the current
     * and the input dots.
     *
     * @param dot The dot to find the distance to.
     * @return The distance.
     */
    float distance(const Dot& dot) const;
    
private:
    
    ///Stores the X coordinate
    int m_x;
    
    ///Stores the Y coordinate
    int m_y;
    
};

#endif /* Dot_hpp */
