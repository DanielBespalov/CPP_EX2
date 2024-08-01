#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]\n");

    ariel::Graph g4 = g1 + g3;
    CHECK(g4.printGraph() == "[0, 3, 1]\n[3, 0, 4]\n[1, 4, 0]\n");

    ariel::Graph g5 = g2 + g3;
    CHECK(g5.printGraph() == "[0, 3, 2]\n[3, 0, 5]\n[2, 5, 0]\n");

    vector<vector<int>> g7 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0 , 1 , 0}};
    
    ariel::Graph g8;
    g8.loadGraph(g7);

    CHECK_THROWS(g8 + g1);
    CHECK_THROWS(g8 += g1);

    g1+=g3;
    CHECK(g1.printGraph() == "[0, 3, 1]\n[3, 0, 4]\n[1, 4, 0]\n");
    
    g5++;
    CHECK(g5.printGraph() == "[0, 4, 3]\n[4, 0, 6]\n[3, 6, 0]\n");
   
    ariel::Graph g9 = +g3;
    CHECK(g9.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]\n");
}

TEST_CASE("Test graph dedction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 3, 7},
        {3, 0, 5},
        {7, 5, 0}};
    g2.loadGraph(weightedGraph);
    
    ariel::Graph g3 = g2 - g1;
    CHECK(g3.printGraph() == "[0, 2, 7]\n[2, 0, 4]\n[7, 4, 0]\n");

    ariel::Graph g4 = g3 - g1;
    CHECK(g4.printGraph() == "[0, 1, 7]\n[1, 0, 3]\n[7, 3, 0]\n");

    vector<vector<int>> g7 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0 , 1 , 0}};
    
    ariel::Graph g8;
    g8.loadGraph(g7);

    CHECK_THROWS(g8 - g1);
    CHECK_THROWS(g8 -= g1);

    g3-=g1;
    CHECK(g3.printGraph() == "[0, 1, 7]\n[1, 0, 3]\n[7, 3, 0]\n");

    g4--;
    CHECK(g4.printGraph() == "[0, 0, 6]\n[0, 0, 2]\n[6, 2, 0]\n");

    ariel::Graph g5 = -g3;
    CHECK(g5.printGraph() == "[0, -1, -7]\n[-1, 0, -3]\n[-7, -3, 0]\n");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    
    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]\n");

    g4 *= g1;
    CHECK(g4.printGraph() == "[0, 3, 0]\n[3, 2, 3]\n[0, 3, 0]\n");

    g4 = g4 * 3;
    CHECK(g4.printGraph() == "[0, 9, 0]\n[9, 6, 9]\n[0, 9, 0]\n");

    vector<vector<int>> g7 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0 , 1 , 0}};
    
    ariel::Graph g8;
    g8.loadGraph(g7);

    CHECK_THROWS(g4*=g8);
    CHECK_THROWS(g4 * g8);


}

TEST_CASE("Test graph compring")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 5},
        {1, 5, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 5},
        {1, 5, 0}};
    g2.loadGraph(weightedGraph);
    CHECK((g1 != g2) == true);
    CHECK((g1 < g2) == true);
    CHECK((g1 >= g2) == false);
    CHECK((g1 > g2) == false);
    CHECK((g1 == g2) == false);
    CHECK((g1 <= g2) == true);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0}};
    g3.loadGraph(graph2);
    CHECK((g1 < g3) == true);
    CHECK((g1 >= g3) == false);
    CHECK((g1 > g3) == false);
    CHECK((g1 == g3) == false);
    CHECK((g1 != g3) == true);
    CHECK((g1 <= g3) == true);



}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3= {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph4 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, -1},
        {0, 0, 0, -1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph6= {
        {0, 1, 1 ,0 ,0},
        {1, 0, 1 ,0 ,0},
        {1, 1, 0 ,0 ,0},
        {0 ,0 ,0 ,0 ,-9},
        {0 ,0 ,0 ,-9 ,0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == false);

     vector<vector<int>> graph5= {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
}

TEST_CASE("Test negative cycles"){
    ariel::Graph g;

    // Negative cycle
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, -5},
        {2, -5, 0}};

    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found");

    // Not contained negative cycle
 	vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, -3, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, -10, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph2));

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4, 5},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph3));

    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph4));

	vector<vector<int>> graph5 = {
        {0, 1, 2, 0, 1},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 0, 4},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph5));
}



//TEST_CASE("")