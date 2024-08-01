# מטלה 2 - גרפים והעמסת אופרטורים

# Graph Algorithms Library

## Author
Daniel Bespalov

## ID
213446479

## Mail
danieldaniel2468@gmail.com

## Overview

This repository contains implementations of graph algorithms using C++. The `Graph` class represents a graph using an adjacency matrix, and the `Algorithms` class provides various graph algorithms such as BFS, DFS, cycle detection, bipartite check, and shortest path finding.

## Features

- Graph representation using an adjacency matrix.
- Graph operations such as addition, subtraction, multiplication, and scalar division.
- Various graph algorithms including BFS, DFS, cycle detection, bipartite check, and shortest path finding.
- Operator overloading for graph comparison and arithmetic operations.
- Output graph information as a string.

## Classes

### Graph

The `Graph` class represents a graph using an adjacency matrix. It provides methods to load a graph, get the number of vertices and edges, and various overloaded operators.

#### Methods

- `void loadGraph(const std::vector<std::vector<int>>& matrix)`: Loads the graph from an adjacency matrix.
- `unsigned int getVerts() const`: Returns the number of vertices.
- `unsigned int getEdges() const`: Returns the number of edges.
- `std::vector<std::vector<int>> getGraph() const`: Returns the adjacency matrix of the graph.
- `std::string printGraph() const`: Returns a string representation of the graph.

#### Operators

- `Graph operator+(const Graph& other) const`: Adds two graphs.
- `Graph operator-(const Graph& other) const`: Subtracts one graph from another.
- `Graph operator*(const Graph& other) const`: Multiplies two graphs.
- `Graph operator/(int scalar) const`: Divides the graph by a scalar.
- `Graph& operator++()`: Prefix increment operator.
- `Graph operator++(int)`: Postfix increment operator.
- `Graph& operator--()`: Prefix decrement operator.
- `Graph operator--(int)`: Postfix decrement operator.
- `Graph operator+() const`: Unary plus operator.
- `Graph operator-() const`: Unary minus operator.
- `bool operator==(const Graph& other) const`: Checks if two graphs are equal.
- `bool operator!=(const Graph& other) const`: Checks if two graphs are not equal.
- `bool operator<(const Graph& other) const`: Checks if one graph is strictly contained in another.
- `bool operator<=(const Graph& other) const`: Checks if one graph is contained in another.
- `bool operator>(const Graph& other) const`: Checks if one graph contains another.
- `bool operator>=(const Graph& other) const`: Checks if one graph contains or is equal to another.
- `Graph& operator+=(const Graph& other)`: Adds another graph to this graph.
- `Graph& operator-=(const Graph& other)`: Subtracts another graph from this graph.
- `Graph& operator*=(const Graph& other)`: Multiplies this graph with another graph.

### Algorithms

The `Algorithms` class provides various graph algorithms including BFS, DFS, cycle detection, bipartite check, and shortest path finding.

#### Methods

- `int isConnected(const Graph& g)`: Checks if the graph is connected.
- `std::string shortestPath(const Graph& g, unsigned long start, unsigned long end)`: Finds the shortest path between two vertices using BFS.
- `int isContainsCycle(const Graph& g)`: Checks if the graph contains a cycle.
- `std::string isBipartite(const Graph& g)`: Checks if the graph is bipartite and returns the sets.
- `std::string negativeCycle(const Graph& g)`: Checks if the graph contains a negative cycle using the Bellman-Ford algorithm.

## Usage

To run this project, type 'make' in the terminal and will run the tests.


