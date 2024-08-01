/*
 * Author: Daniel Bespalov
 * ID: 213446479
 * Mail: danieldaniel2468@gmail.com
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <ostream>

namespace ariel {

    class Graph {
    private:
        unsigned int verts;
        unsigned int edges;
        std::vector<std::vector<int>> mat;

        void updateEdges();

    public:
        // Constructors
        Graph();

        // Methods
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        unsigned int getVerts() const;
        unsigned int getEdges() const;
        std::vector<std::vector<int>> getGraph() const;
        std::string printGraph() const; // Updated to return a string

        // Arithmetic Operators
        Graph operator+(const Graph& other) const;
        Graph operator-(const Graph& other) const;
        Graph operator*(const Graph& other) const;
        Graph operator*(int scalar) const;
        Graph operator/(int scalar) const;

        // Unary Arithmetic Operators
        Graph& operator++(); // Prefix increment
        Graph operator++(int); // Postfix increment
        Graph& operator--(); // Prefix decrement
        Graph operator--(int); // Postfix decrement
        
        //Unary
        Graph operator+() const;
        Graph operator-() const; 

        // Arithmetic Assignment Operators
        Graph& operator+=(const Graph& other);
        Graph& operator-=(const Graph& other);
        Graph& operator*=(const Graph& other);

        // Comparison Operators
        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;

        // Strict Containment Check
        bool isStrictlyContainedIn(const Graph& other) const;

        // Output Operator
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };

} // namespace ariel

#endif // GRAPH_HPP
