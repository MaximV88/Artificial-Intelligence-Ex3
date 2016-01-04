//
//  Cluster.cpp
//  Ex3
//
//  Created by Maxim Vainshtein on 03/01/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "Cluster.hpp"
#include "Dot.hpp"
#include <stdexcept>
#import <sstream>

//Internal usage
NAMESPACE_CLUSTER_BEGIN

/**
 * Creates a cluster per each dot in the input.
 *
 * @param dots The dots to issue clusters from.
 * @return A vector containing the clusters.
 */
std::vector<Cluster*> ClusterByIndividualDots(std::vector<const Dot *> dots);

/**
 * Creates clusters by single linkage.
 *
 * @param size The number of clusters to create.
 * @param dots The input coordinates to cluster.
 * @return A vector containing the resulting clusters.
 */
std::vector<Cluster*> ClusterBySingleLinkage(size_t size, std::vector<const Dot *> dots);

/**
 * Creates clusters by average linkage.
 *
 * @param size The number of clusters to create.
 * @param dots The input coordinates to cluster.
 * @return A vector containing the resulting clusters.
 */
std::vector<Cluster*> ClusterByAverageLinkage(size_t size, std::vector<const Dot *> dots);

/**
 * Creates clusters by complete linkage.
 *
 * @param size The number of clusters to create.
 * @param dots The input coordinates to cluster.
 * @return A vector containing the resulting clusters.
 */
std::vector<Cluster*> ClusterByCompleteLinkage(size_t size, std::vector<const Dot *> dots);

NAMESPACE_CLUSTER_END

std::vector<cluster::Cluster*> cluster::ClusterByIndividualDots(std::vector<const Dot*> dots) {
    
    std::vector<Cluster*> clusters;
    
    //Create a cluster for every dot and push to vector
    for (std::vector<const Dot*>::const_iterator dot = dots.begin() ;
         dot != dots.end() ;
         dot++) {
        
        clusters.push_back(new Cluster(*dot));
        
    }
    
    return clusters;
    
}

std::vector<cluster::Cluster*> cluster::ClusterBySingleLinkage(size_t size, std::vector<const Dot *> dots) {
    
    /*
     * Start by finding the nearest pair of clusters in the current clustering.
     * Afterwards, merge the two clusters together, and iterate once more.
     * Iteration will be complete after N-K steps where N is number of 
     * dots and K is number of clusters.
     */
    
    std::vector<Cluster*> clusters = ClusterByIndividualDots(dots);
    
    //N-K repeats
    size_t repeats = dots.size() - size;
    
    while (repeats) {
        
        //Find the most similar pairs of clusters in the current clustering
        float min_distance = 0;
        bool found_minimum = false;
        Cluster* lhs = NULL;
        Cluster* rhs = NULL;
        
        for (std::vector<Cluster*>::const_iterator clusterA = clusters.begin() ;
             clusterA != clusters.end() ;
             clusterA++) {
            
            for (std::vector<Cluster*>::const_iterator clusterB = clusters.begin() ;
                 clusterB != clusters.end() ;
                 clusterB++) {
                
                //Skip checking cluster on itself
                if (clusterA == clusterB) continue;
                
                
                //If havnt found a cluster yet the following distance will be minimum
                if (!found_minimum) {
                    
                    min_distance = (*clusterA)->NearestNeighbourDistance(**clusterB);
                    found_minimum = true;
                    lhs = *clusterA;
                    rhs = *clusterB;
                    
                }
                else {
                    
                    //If the clusters have a smaller distance than previously, update variables
                    float current_minimum_distance = (*clusterA)->NearestNeighbourDistance(**clusterB);
                    if (current_minimum_distance < min_distance) {
                        
                        min_distance = current_minimum_distance;
                        lhs = *clusterA;
                        rhs = *clusterB;
                        
                    }
                    
                }
                
            }
            
        }
        
        //Now lhs, rhs point to the clusters that have the minimum distance - so we merge them
        lhs->Merge(*rhs);
        
        //Remove the previous cluster from memory
        clusters.erase(std::remove(clusters.begin(), clusters.end(), rhs), clusters.end());
        
        --repeats;
        
    }
    
    return clusters;
    
}

std::vector<cluster::Cluster*> cluster::ClusterByAverageLinkage(size_t size, std::vector<const Dot *> dots) {
    
    return std::vector<Cluster*>();
    
}

std::vector<cluster::Cluster*> cluster::ClusterByCompleteLinkage(size_t size, std::vector<const Dot *> dots) {
    
    return std::vector<cluster::Cluster*>();
    
}

std::vector<cluster::Cluster*> cluster::Create(cluster::ClusterType type, size_t size, std::vector<const Dot *> dots) {
    
    switch (type) {
        case cluster::kClusterTypeSingleLink:   return cluster::ClusterBySingleLinkage(size, dots);
        case cluster::kClusterTypeAverageLink:  return cluster::ClusterByAverageLinkage(size, dots);
        case cluster::kClusterTypeFurthestLink: return cluster::ClusterByCompleteLinkage(size, dots);
    }
    
    throw std::runtime_error("An unknown cluster type was requested.");
    
}

void cluster::Sort(std::vector<cluster::Cluster *>& clusters, const std::vector<const Dot *>& dots) {
    
    //Place each cluster that a dot was found for in a decreasing manner
    size_t index = 0;
    
    for (std::vector<const Dot*>::const_iterator dot = dots.begin() ;
         dot != dots.end() ;
         dot++) {
        
        for (std::vector<cluster::Cluster*>::iterator cluster = clusters.begin() + index ;
             cluster != clusters.end() ;
             cluster++) {
            
            /*
             * Once a cluster that contains the dot has been found, move it to the last top
             * position and increment towards the next reordering.
             */
            
            if ((*cluster)->Contains(**dot)) {
                
                std::iter_swap(clusters.begin() + index, cluster);
                ++index;
                
            }
            
        }
        
    }
    
}

void cluster::RandomizeOrder(std::vector<cluster::Cluster *> &clusters) {

    std::random_shuffle(clusters.begin(), clusters.end());
    
}

std::string cluster::Format(const std::vector<cluster::Cluster *> &clusters, const std::vector<const Dot *> &dots) {
    
    std::stringstream sstream;
    
    //Print the cluster to which each dot belongs
    for (std::vector<const Dot*>::const_iterator dot = dots.begin() ; dot != dots.end() ; dot++)
        for (std::vector<cluster::Cluster*>::const_iterator cluster = clusters.begin() ; cluster != clusters.end() ; cluster++) {
            
            //Check if the dot is in the current cluster and continue to next dot if so
            if ((*cluster)->Contains(**dot)) {
                
                sstream << cluster - clusters.begin() + 1 << '\n';
                break;
                
            }
            
        }
    
    return sstream.str();
    
}

#pragma mark - Cluster class methods

bool cluster::Cluster::Contains(const Dot &dot) const {
    
    for (std::vector<const Dot*>::const_iterator iter = m_dots.begin() ;
         iter != m_dots.end() ;
         iter++) {
        
        //Check for evey dot if it's contained in the cluster
        if ((**iter) == dot)
            return true;
        
    }
    
    //No dots were found
    return false;
    
}

float cluster::Cluster::NearestNeighbourDistance(const cluster::Cluster &rhs) const {

    /*
     * Dmin(Ci, Cj) = min for every x in Ci, y in Cj so that || x - y ||^2.
     *
     * This measures the dissimilarity between 2 groups of data points.
     * The minimum distance will measure similarity between both clusters
     * by their closest distance. Often goes by name of "single linkage".
     */
    
    float min_distance = 0;
    bool found_minimum = false;
    
    //Iterate over each dot and find the closest one in the input cluster
    for (std::vector<const Dot*>::const_iterator dot = m_dots.begin() ;
         dot != m_dots.end() ;
         dot++) {
        
        for (std::vector<const Dot*>::const_iterator foreign_dot = rhs.m_dots.begin() ;
             foreign_dot != rhs.m_dots.end() ;
             foreign_dot++) {
            
            //There must be an initial value to compare other distances to
            if (!found_minimum) {
                
                min_distance = (*dot)->distance(**foreign_dot);
                found_minimum = true;
                
            }
            else {
                
                //Replace minimal distance if a smaller one is found
                float distance = (*dot)->distance(**foreign_dot);
                if (distance < min_distance)
                    min_distance = distance;
                
            }
            
        }
        
    }
    
    return min_distance;
    
}

float cluster::Cluster::AverageNeighbourDistance(const cluster::Cluster &rhs) const {
    
    return 0;
    
}

float cluster::Cluster::FurthestNeighbourDistance(const cluster::Cluster &rhs) const {
    
    /* 
     * "Complete linkage" - maximum distance between every pair of points.
     * Unlike single linkage, this gives dissimilarity to clusters that are close everywhere.
     *
     * Dmax(Ci, Cj) = max for every x in Ci, y in Cj so that || x - y ||^2.
     */
    
    return 0;
    
}

void cluster::Cluster::Merge(const cluster::Cluster &rhs) {
    
    //Just add the dots from the incoming cluster
    m_dots.insert(m_dots.end(), rhs.m_dots.begin(), rhs.m_dots.end());
    
}

cluster::Cluster::Cluster(std::vector<const Dot*> dots) :
m_dots(dots)
{ }

cluster::Cluster::Cluster(const Dot* dot) {

    m_dots.push_back(dot);

}
