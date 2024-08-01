/*
 * Author: Daniel Bespalov
 * ID: 213446479
 * Mail: danieldaniel2468@gmail.com
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel {

    class Algorithms {
    public:
        // Function to check if the graph is connected
        static int isConnected(const Graph& g);

        // Function to find the shortest path between two vertices
        static std::string shortestPath(const Graph& g, unsigned long start, unsigned long end);

        // Function to check if the graph contains a cycle
        static int isContainsCycle(const Graph& g);

        // Function to check if the graph is bipartite and return the sets
        static std::string isBipartite(const Graph& g);

        // Function to check if the graph contains a negative cycle
        static std::string negativeCycle(const Graph& g);

        static bool dfsCycleCheck(const Graph& g, unsigned long v, std::vector<bool>& visited, int parent);

        static bool bfsCheckBipartite(const Graph& g, unsigned long start, std::vector<int>& color, std::vector<int>& setA, std::vector<int>& setB);



    };

} // namespace ariel

#endif // ALGORITHMS_HPP
