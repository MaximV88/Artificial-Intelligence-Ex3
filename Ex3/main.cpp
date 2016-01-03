//
//  main.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <fstream>
#include "Parse.hpp"

int main(int argc, const char * argv[]) {

    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs("input.txt");
    
    //Get the formatted map (reading from current location until end of file)
    std::string formattedInput((std::istreambuf_iterator<char>(ifs) ),
                               (std::istreambuf_iterator<char>()    ));
    
    std::vector<const Dot*> dots = parse::dots(formattedInput);
    
    ClusterType type = parse::clusterType(formattedInput);
    
    size_t cluster_size = parse::clusterSize(formattedInput);
    
    return 0;
}
