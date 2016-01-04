//
//  main.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <fstream>
#include <iostream>
#include "Parse.hpp"
#include "Cluster.hpp"

int main(int argc, const char * argv[]) {

    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs("input.txt");
    
    //Get the formatted map (reading from current location until end of file)
    std::string formattedInput((std::istreambuf_iterator<char>(ifs) ),
                               (std::istreambuf_iterator<char>()    ));
    
    //The requested dots
    std::vector<const Dot*> dots = parse::Dots(formattedInput);
    
    //Create the clusters
    std::vector<cluster::Cluster*> clusters = cluster::Create(parse::ClusterType(formattedInput),
                                                              parse::ClusterSize(formattedInput),
                                                              dots);
    
    cluster::RandomizeOrder(clusters);
    
    //Sort the results by clusters
    cluster::Sort(clusters, dots);
    
    //Print the cluster to which each dot belongs
    std::cout << cluster::Format(clusters, dots);
    
    return 0;

}
