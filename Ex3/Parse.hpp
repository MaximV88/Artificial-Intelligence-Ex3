//
//  Parse.hpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Parse_hpp
#define Parse_hpp
#define NAMESPACE_PARSE_BEGIN namespace parse {
#define NAMESPACE_PARSE_END }
#include <vector>
#include <string>
#include "Cluster.hpp"
class Dot;

NAMESPACE_PARSE_BEGIN

/**
 * Parses the input string to a vector of dots.
 *
 * @param input The string to be parsed.
 * @return A vector of heap allocated dots.
 */
std::vector<const Dot*> Dots(const std::string& input);

/**
 * Parses the ClusterType contained in the input string.
 * Throws exception if none found.
 *
 * @param input The string to be parsed.
 * @return A CluserType enum.
 */
cluster::ClusterType ClusterType(const std::string& input);

/**
 * Parses the specified cluster size from the input string.
 *
 * @param input The string to be parsed.
 * @return Specified size of cluster.
 */
size_t ClusterSize(const std::string& input);

NAMESPACE_PARSE_END
#endif /* Parse_hpp */
