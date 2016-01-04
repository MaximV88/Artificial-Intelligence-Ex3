//
//  main.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include <fstream>
#include "Parse.hpp"
#include "Cluster.hpp"

int main(int argc, const char * argv[]) {

    //Read the file
    std::ifstream ifs("input.txt");
    
    //Get contents to string
    std::string formattedInput((std::istreambuf_iterator<char>(ifs) ),
                               (std::istreambuf_iterator<char>()    ));
    
    //The requested dots
    std::vector<const Dot*> dots = parse::Dots(formattedInput);
    
    //Create the clusters
    std::vector<cluster::Cluster*> clusters = cluster::Create(parse::ClusterType(formattedInput),
                                                              parse::ClusterSize(formattedInput),
                                                              dots);
    
    //Sort the results by clusters
    cluster::Sort(clusters, dots);
    
    //Print the clusters to a file
    std::ofstream output("output11.txt");
    output << parse::Format(clusters, dots);
    output.close();

    return 0;

}
