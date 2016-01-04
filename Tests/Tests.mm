//
//  Tests.m
//  Tests
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <fstream>
#import <sstream>

#import "Parse.hpp"

@interface Tests : XCTestCase

@end

@implementation Tests

using namespace cluster;

std::string read_file(const std::string& file) {
    
    //Read the file
    std::ifstream ifs(file);
    
    //Get contents to string
    return std::string((std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ));
    
}

- (void)testParsing_ClusterType {

    XCTAssertEqual(parse_type_from_file("input.txt"),  kClusterTypeSingleLink);
    XCTAssertEqual(parse_type_from_file("input2.txt"), kClusterTypeAverageLink);
    XCTAssertEqual(parse_type_from_file("input3.txt"), kClusterTypeAverageLink);
    XCTAssertEqual(parse_type_from_file("input4.txt"), kClusterTypeAverageLink);

}

ClusterType parse_type_from_file(const std::string& input) {
    
    return parse::ClusterType(read_file(input));

}

- (void)testParsing_ClusterSize {
    
    XCTAssertEqual(parse_size_from_file("input.txt"),  4);
    XCTAssertEqual(parse_size_from_file("input2.txt"), 2);
    XCTAssertEqual(parse_size_from_file("input3.txt"), 5);
    XCTAssertEqual(parse_size_from_file("input4.txt"), 5);
    
}

size_t parse_size_from_file(const std::string& input) {
    
    return parse::ClusterSize(read_file(input));
    
}

- (void)testClustering {
    
    XCTAssertEqual(formatted_result("input.txt"),  formatted_file_read("output.txt"));
    XCTAssertEqual(formatted_result("input2.txt"), formatted_file_read("output2.txt"));
    XCTAssertEqual(formatted_result("input3.txt"), formatted_file_read("output3.txt"));
    XCTAssertEqual(formatted_result("input4.txt"), formatted_file_read("output4.txt"));
    
}

std::string formatted_result(const std::string& input) {
    
    std::string contents = read_file(input);
    
    //The requested dots
    std::vector<const Dot*> dots = parse::Dots(contents);
    
    //Create the clusters
    std::vector<cluster::Cluster*> clusters = cluster::Create(parse::ClusterType(contents),
                                                              parse::ClusterSize(contents),
                                                              dots);
        
    //Sort the results by clusters
    cluster::Sort(clusters, dots);
    
    //Print the cluster to which each dot belongs
    std::stringstream test;
    test << parse::Format(clusters, dots);
    
    //Conform by removing redundant characters
    std::string output = test.str();
    output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

    return output;
    
}

std::string formatted_file_read(const std::string& input) {
    
    std::string contents = read_file(input);

    contents.erase(std::remove(contents.begin(), contents.end(), '\r'), contents.end());
    contents.erase(std::remove(contents.begin(), contents.end(), '\n'), contents.end());
    
    return contents;
    
}

@end
