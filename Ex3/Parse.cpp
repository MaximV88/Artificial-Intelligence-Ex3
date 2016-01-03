//
//  Parse.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Parse.hpp"
#include "Dot.hpp"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

//Internal functions
NAMESPACE_PARSE_BEGIN

/**
 * Clear the input string from any escape characters.
 *
 * @param An editable string.
 */
void purify(std::string& input) {
    
    input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

}

NAMESPACE_PARSE_END

using namespace parse;


std::vector<const Dot*> parse::dots(const std::string &input) {
    
    using namespace std;
    
    /*
     * The format is simple, starts with reading an int, proceeds to
     * another ',' and reads another int until reaching end of line. Continue
     * until end of string.
     */
    
    stringstream sstream(input);

    //Get starting position for parsing
    string line;
    while (std::getline(sstream, line)) {
        
        //Check if the line contains a ',' character that indicates its a coordinate
        if (line.find(",") != std::string::npos)
            break;
        
    }
    
    //Stores all of the found dots
    std::vector<const Dot*> storage;
    
    while (std::getline(sstream, line)) {
        
        //Clean the line from escape character
        parse::purify(line);
        
        size_t seperator = line.find_first_of(",");
        string rawX = line.substr(0, seperator);
        string rawY = line.substr(seperator + 1);

        int x, y;
        
        //Parse string to int
        istringstream(rawX) >> x;
        istringstream(rawY) >> y;
        
        storage.push_back(new Dot(x, y));
        
    }

    return storage;
    
}

ClusterType parse::clusterType(const std::string &input) {
    
    using namespace std;
    
    /*
     * Iterate on all of the lines until one
     * that matches the possibilities is 
     * found. Throw exception is not found.
     */
    
    stringstream sstream(input);
    
    string line;
    while (std::getline(sstream, line)) {
        
        //Clear the line from any escape characters
        parse::purify(line);

        if (line.find("single link") != std::string::npos)
            return ClusterTypeSingleLink;
        else if (line.find("average link") != std::string::npos)
            return ClusterTypeAverageLink;
        
    }
    
    //None found
    throw std::runtime_error("The input does not contain a cluster type.");
    
}

size_t parse::clusterSize(const std::string &input) {
    
    using namespace std;
    
    /*
     * Iterate over all of the lines and find a line
     * that contains only a number.
     */
    
    stringstream sstream(input);

    string line;
    while (std::getline(sstream, line)) {
        
        //Clear the line from any escape characters
        parse::purify(line);
        
        //Check if line has only a number
        bool invariant = false;
        for (string::const_iterator iter = line.begin() ; iter != line.end() ; iter++)
            if (!std::isdigit(*iter)) {

                invariant = true;
                break;
                
            }
        
        //Skip non valid lines
        if (invariant) continue;
        
        size_t size;
        
        //Parse string to int
        istringstream(line) >> size;
        
        return size;
        
    }
    
    //None found
    throw std::runtime_error("The input does not contain cluster size.");
    
}
