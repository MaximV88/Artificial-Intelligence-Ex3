//
//  Tests.m
//  Tests
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <fstream>
#import "Parse.hpp"

@interface Tests : XCTestCase

@end

@implementation Tests

- (void)testParsing_ClusterType {

    XCTAssertEqual(parse_type_from_file("input.txt"), ClusterTypeSingleLink);
    XCTAssertEqual(parse_type_from_file("input2.txt"), ClusterTypeAverageLink);
    XCTAssertEqual(parse_type_from_file("input3.txt"), ClusterTypeAverageLink);
    XCTAssertEqual(parse_type_from_file("input4.txt"), ClusterTypeAverageLink);

}

ClusterType parse_type_from_file(const std::string& input) {
    
    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs(input);
    
    //Get the formatted map (reading from current location until end of file)
    std::string formattedInput((std::istreambuf_iterator<char>(ifs) ),
                               (std::istreambuf_iterator<char>()    ));
    
    return parse::clusterType(formattedInput);

}

- (void)testParsing_ClusterSize {
    
    XCTAssertEqual(parse_size_from_file("input.txt"), 4);
    XCTAssertEqual(parse_size_from_file("input2.txt"), 2);
    XCTAssertEqual(parse_size_from_file("input3.txt"), 5);
    XCTAssertEqual(parse_size_from_file("input4.txt"), 5);
    
}

size_t parse_size_from_file(const std::string& input) {
    
    //Read the file to seperate the contents of map and algorithm
    std::ifstream ifs(input);
    
    //Get the formatted map (reading from current location until end of file)
    std::string formattedInput((std::istreambuf_iterator<char>(ifs) ),
                               (std::istreambuf_iterator<char>()    ));
    
    return parse::clusterSize(formattedInput);
    
}

@end
