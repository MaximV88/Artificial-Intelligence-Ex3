//
//  Cluster.hpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#ifndef Cluster_hpp
#define Cluster_hpp
#include <vector>
class Dot;

#define NAMESPACE_CLUSTER_BEGIN namespace cluster {
#define NAMESPACE_CLUSTER_END }

NAMESPACE_CLUSTER_BEGIN
class Cluster;

enum ClusterType {
    
    kClusterTypeSingleLink,
    kClusterTypeAverageLink,
    kClusterTypeFurthestLink
    
};

/**
 * Creates clusters based on input parameters (type, size and data).
 *
 * @param type The type of clustering to apply.
 * @param size Number of clusters to create.
 * @param dots The dot collection to cluster.
 */
std::vector<cluster::Cluster*> Create(ClusterType type, size_t size, std::vector<const Dot*> dots);

/**
 * Sorts the clusters array using the order of the dots.
 * The first will be that which contains the first dot and so forth.
 *
 * @param clusters The clusters to sort.
 * @param dots The dots to sort the clusters by.
 */
void Sort(std::vector<cluster::Cluster*>& clusters, const std::vector<const Dot*>& dots);

/**
 * Randomizes the ordering of the clusters.
 * Used to test sorting under different initial conditions.
 *
 * @param clusters The clusters to randomize.
 */
void RandomizeOrder(std::vector<cluster::Cluster*>& clusters);

/**
 * Creates a formatted string for output.
 *
 * @param clusters The clusters to index numbers to.
 * @param dots The dots which determine the output's content.
 * @return A string containing a formatted output as in instructions.
 */
std::string Format(const std::vector<cluster::Cluster*>& clusters, const std::vector<const Dot*>& dots);

/**
 * Represents a cluster, contains dots and can
 * calculate distances to other clusters via
 * different methods, and merge with other clusters.
 */
class Cluster {
public:
    
    /**
     * Checks if the cluster contains a specific dot.
     * 
     * @param dot The dot to find.
     * @return True if dot is in the cluster, false otherwise.
     */
    bool Contains(const Dot& dot) const;
    
    /**
     * Calculates the minimum distance between elements of each cluster.
     * (Also called single linkage clustering)
     *
     * @param rhs The cluster to compute the distance against.
     * @return The calculated distance.
     */
    float NearestNeighbourDistance(const Cluster& rhs) const;
    
    /**
     * Calculates the mean distance between elements of each cluster.
     * (Also called average linkage clustering)
     *
     * @param rhs The cluster to compute the distance against.
     * @return The calculated distance.
     */
    float AverageNeighbourDistance(const Cluster& rhs) const;

    /**
     * Calculates the maximum distance between elements of each cluster.
     * (Also called complete-linkage clustering)
     *
     * @param rhs The cluster to compute the distance against.
     * @return The calculated distance.
     */
    float FurthestNeighbourDistance(const Cluster& rhs) const;

    /**
     * Merges the input dots from parameter to itself.
     *
     * @param rhs The cluster to merge the dots from.
     */
    void Merge(const Cluster& rhs);
    
    /**
     * Constructor.
     *
     * @param dots The dots which the cluster contains.
     */
     Cluster(std::vector<const Dot*> dots);
    
    /**
     * Constructor.
     *
     * @param dot A dot which the cluster will be made of.
     */
    Cluster(const Dot* dot);
    
private:
    
    ///Stores the dots that the cluster holds.
    std::vector<const Dot*> m_dots;
    
};

NAMESPACE_CLUSTER_END
#endif /* Cluster_hpp */
