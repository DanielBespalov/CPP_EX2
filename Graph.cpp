/*
 * Author: Daniel Bespalov
 * ID: 213446479
 * Mail: danieldaniel2468@gmail.com
 */

#include <iostream>
#include <stdexcept>
#include "Graph.hpp"
#include <sstream>  

namespace ariel {

    // Constructor
    Graph::Graph() : edges(0), verts(0), mat() {}

    // Load graph from adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){
        if (matrix.size() != matrix[0].size()) throw std::invalid_argument("Adjacency matrix must be square.");
        for (unsigned long i = 0; i < matrix.size(); i++) {
            if (matrix[i][i] != 0) throw std::invalid_argument("The main diagonal must be 0");
        }

        verts = matrix.size();
        mat = matrix;

        int count = 0;
        for (unsigned long i = 0; i < matrix.size(); i++) {
            for (unsigned long j = 0; j < matrix.size(); j++) {
                if (mat[i][j] != 0)
                    count++;
            }
        }

        edges = static_cast<unsigned int>(count);
    }

    // Get number of vertices
    unsigned int Graph::getVerts() const {
        return verts;
    }

    // Get number of edges
    unsigned int Graph::getEdges() const {
        return edges;
    }

    // Get adjacency matrix
    std::vector<std::vector<int>> Graph::getGraph() const {
        return mat;
    }

    // Print graph
    std::string Graph::printGraph() const {
        std::ostringstream oss;
        for (const auto& row : mat) {
            oss << "[";
            for (size_t i = 0; i < row.size(); ++i) {
                oss << row[i];
                if (i != row.size() - 1) {
                    oss << ", ";
                }
            }
            oss << "]\n";
        }
        return oss.str();
    }   

    // Overload arithmetic operators
    Graph Graph::operator+(const Graph& other) const {
        if (verts != other.verts) throw std::invalid_argument("Graphs must be of the same size.");
        Graph result = *this;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                result.mat[i][j] += other.mat[i][j];
            }
        }
        result.updateEdges();
        return result;
    }

    Graph& Graph::operator+=(const Graph& other) {
        if (verts != other.verts) throw std::invalid_argument("Graphs must be of the same size.");
        *this = *this + other;
        return *this;
    }

    Graph& Graph::operator-=(const Graph& other) {
        *this = *this - other;
        return *this;
    }

    Graph& Graph::operator*=(const Graph& other) {
        if (verts != other.verts) {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        *this = *this * other;
        return *this;
    }

    Graph Graph::operator-(const Graph& other) const {
        if (verts != other.verts) throw std::invalid_argument("Graphs must be of the same size.");
        Graph result = *this;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                result.mat[i][j] -= other.mat[i][j];
            }
        }
        result.updateEdges();
        return result;
    }

    Graph& Graph::operator++() {
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                if (mat[i][j] != 0) mat[i][j]++;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int) {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph& Graph::operator--() {
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                if (mat[i][j] != 0) mat[i][j]--;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int) {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    Graph Graph::operator*(int scalar) const {
        Graph result = *this;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                result.mat[i][j] *= scalar;
            }
        }
        result.updateEdges();
        return result;
    }

    Graph Graph::operator*(const Graph& other) const {
    if (verts != other.verts) {
        throw std::invalid_argument("Graphs must be of the same size.");
    }

    Graph result;
    result.verts = verts;
    result.mat.resize(verts, std::vector<int>(verts, 0));

    for (unsigned long i = 0; i < verts; ++i) {
        for (unsigned long j = 0; j < verts; ++j) {
            for (unsigned long k = 0; k < verts; ++k) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }

    result.updateEdges();
    return result;
}

    Graph Graph::operator/(int scalar) const {
        if (scalar == 0) throw std::invalid_argument("Division by zero.");
        Graph result = *this;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                result.mat[i][j] /= scalar;
            }
        }
        result.updateEdges();
        return result;
    }

    //Unary Operators
    Graph Graph::operator+() const {
        return *this; // Return a copy of the current graph
    }

    Graph Graph::operator-() const {
        Graph result(*this); // Create a copy of the current graph
        for (unsigned long i = 0; i < result.mat.size(); ++i) {
            for (unsigned long j = 0; j < result.mat[i].size(); ++j) {
                result.mat[i][j] = -result.mat[i][j]; // Negate the weight of each edge
            }
        }
        return result;
    }

    // Helper function to check if this graph is strictly contained within another graph
    bool Graph::isStrictlyContainedIn(const Graph& other) const {
        if (verts != other.verts) return false;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                if (mat[i][j] != 0 && other.mat[i][j] == 0) return false;
                if (mat[i][j] > other.mat[i][j]) return false;
            }
        }
        return true;
    }

    // Comparison operators
    bool Graph::operator==(const Graph& other) const {
        if (verts != other.verts) {
            return false;
        }

        // Check if both graphs have the same edges with identical weights
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                if (mat[i][j] != other.mat[i][j]) {
                    return false;
                }
            }
        }
        
        // If all vertices and edges are identical, the graphs are equal
        return true;
    }

    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph& other) const {
        if (isStrictlyContainedIn(other)) return true;
        if (edges < other.edges) return true;
        if (edges == other.edges && verts < other.verts) return true;
        return false;
    }

    bool Graph::operator<=(const Graph& other) const {
        return *this < other || *this == other;
    }

    bool Graph::operator>(const Graph& other) const {
        return other < *this;
    }

    bool Graph::operator>=(const Graph& other) const {
        return *this > other || *this == other;
    }

    // Output operator
    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        os << "Graph with " << graph.verts << " vertices and " << graph.edges << " edges\n";
        for (const auto& row : graph.mat) {
            for (const auto& elem : row) {
                os << elem << " ";
            }
            os << "\n";
        }
        return os;
    }

    // Update edges count based on the adjacency matrix
    void Graph::updateEdges() {
        int count = 0;
        for (unsigned long i = 0; i < verts; ++i) {
            for (unsigned long j = 0; j < verts; ++j) {
                if (mat[i][j] != 0) {
                    count++;
                }
            }
        }
        edges = static_cast<unsigned int>(count);
    }

    
}
