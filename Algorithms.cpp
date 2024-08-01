/*
 * Author: Daniel Bespalov
 * ID: 213446479
 * Mail: danieldaniel2468@gmail.com
 */

#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <limits>
#include <climits>
#include "Algorithms.hpp"
#include <sstream>
#include <algorithm>

namespace ariel {

// Helper function to perform BFS from a given start node
void bfs(const Graph& g, unsigned long start, std::vector<bool>& visited, std::vector<int>& dist, std::vector<int>& prev) {
    std::queue<unsigned long> q;
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        unsigned long node = q.front();
        q.pop();

        for (unsigned long i = 0; i < g.getVerts(); ++i) {
            if (g.getGraph()[node][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                dist[i] = dist[node] + 1;
                prev[i] = node;
            }
        }
    }
}

// Helper function to perform Bellman-Ford algorithm for shortest paths and negative cycle detection
bool bellmanFord(const Graph& g, std::vector<int>& dist) {
    unsigned int V = g.getVerts();
    dist[0] = 0;

    // Relax all edges V-1 times
    for (unsigned long i = 0; i < V - 1; ++i) {
        for (unsigned long u = 0; u < V; ++u) {
            for (unsigned long v = 0; v < V; ++v) {
                if (g.getGraph()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getGraph()[u][v] < dist[v]) {
                    dist[v] = dist[u] + g.getGraph()[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (unsigned long u = 0; u < V; ++u) {
        for (unsigned long v = 0; v < V; ++v) {
            if (g.getGraph()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getGraph()[u][v] < dist[v]) {
                return true;
            }
        }
    }

    return false;
}

// Function to check if the graph is connected
int Algorithms::isConnected(const Graph& g) {
    unsigned int v = g.getVerts();
    std::vector<bool> visited(v, false);
    std::vector<int> dist(v, INT_MAX);
    std::vector<int> prev(v, -1);

    bfs(g, 0, visited, dist, prev);

    for (bool v : visited) {
        if (!v) return 0;
    }
    return 1;
}

// Function to find the shortest path between two vertices using BFS
std::string Algorithms::shortestPath(const Graph& g, unsigned long start, unsigned long end) {
    unsigned int v = g.getVerts();
    std::vector<int> dist(v, INT_MAX);  // Distance vector
    std::vector<int> prev(v, -1);       // Previous vertex vector
    std::vector<bool> visited(v, false);

    bfs(g, start, visited, dist, prev);

    // If there is no path to the end vertex
    if (dist[end] == INT_MAX) {
        return "-1";
    }

    // Construct the shortest path
    std::vector<int> path;
    for (unsigned int at = end; at != -1; at = (unsigned int)prev[at]) {
        path.push_back((int)at);
    }
    std::reverse(path.begin(), path.end());

    std::ostringstream oss;
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) {
            oss << "->";
        }
        oss << path[i];
    }

    return oss.str();
}

// Helper function to perform DFS for cycle check
bool Algorithms::dfsCycleCheck(const Graph& g, unsigned long v, std::vector<bool>& visited, int parent) {
    visited[v] = true;

    for (unsigned long i = 0; i < g.getVerts(); ++i) {
        if (g.getGraph()[v][i] != 0) {
            if (!visited[i]) {
                if (dfsCycleCheck(g, i, visited, v)) return true;
            } else if (i != parent) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if the graph contains a cycle
int Algorithms::isContainsCycle(const Graph& g) {
    unsigned int v = (unsigned int)g.getVerts();
    std::vector<bool> visited(v, false);

    for (unsigned long i = 0; i < v; ++i) {
        if (!visited[i]) {
            if (dfsCycleCheck(g, i, visited, -1)) {
                return 1; // Cycle found
            }
        }
    }

    return 0; // No cycle found
}

// Helper function to perform BFS for bipartite check and building sets
bool Algorithms::bfsCheckBipartite(const Graph& g, unsigned long start, std::vector<int>& color, std::vector<int>& setA, std::vector<int>& setB) {
    std::queue<unsigned long> q;
    q.push(start);
    color[start] = 1; // Start with color 1 for set A
    setA.push_back(start);

    while (!q.empty()) {
        unsigned long node = q.front();
        q.pop();

        // Visit all adjacent vertices of the current node
        for (unsigned long i = 0; i < g.getVerts(); ++i) {
            if (g.getGraph()[node][i] != 0) { // If there is an edge
                if (color[i] == -1) { // If the node has not been colored
                    color[i] = 1 - color[node]; // Assign opposite color
                    q.push(i);
                    if (color[i] == 1) {
                        setA.push_back(i);
                    } else {
                        setB.push_back(i);
                    }
                } else if (color[i] == color[node]) { // Check for conflict
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to check if the graph is bipartite and return the sets
std::string Algorithms::isBipartite(const Graph& g) {
    unsigned int numVertices = g.getVerts();
    std::vector<int> colors(numVertices, -1); // Initialize colors for each vertex
    std::vector<int> setA, setB; // To store the two sets

    // Start BFS from each uncolored vertex
    for (unsigned long i = 0; i < numVertices; ++i) {
        if (colors[i] == -1) {
            if (!bfsCheckBipartite(g, i, colors, setA, setB)) {
                return "0"; // Not bipartite
            }
        }
    }

    // If the graph is bipartite, build a result string showing the two groups
    std::ostringstream result;
    result << "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        if (i != 0) result << ", ";
        result << setA[i];
    }

    result << "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        if (i != 0) result << ", ";
        result << setB[i];
    }
    result << "}";

    return result.str();
}

// Function to check if the graph contains a negative cycle using the Bellman-Ford algorithm
std::string Algorithms::negativeCycle(const Graph& g) {
    unsigned int V = g.getVerts();
    std::vector<int> dist(V, INT_MAX);

    if (bellmanFord(g, dist)) {
        return "Negative cycle found";
    }

    return "No negative cycle found";
}

} // namespace ariel
