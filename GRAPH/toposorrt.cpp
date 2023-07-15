#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Data structure to store a graph edge
struct Edge {
    char src, dest;
};

// A class to represent a graph object
class Graph {
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<char>> adjList;

    // construct another vector for storing in-degree of the vertices
    vector<int> indegree;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // find the maximum vertex
        char maxVertex = 'a';
        for (auto &edge : edges) {
            maxVertex = max(maxVertex, max(edge.src, edge.dest));
        }

        // resize the adjacency list and in-degree vectors
        adjList.resize(maxVertex - 'a' + 1);
        indegree.resize(maxVertex - 'a' + 1);

        // add edges to the directed graph
        for (auto &edge : edges) {
            adjList[edge.src - 'a'].push_back(edge.dest);
            indegree[edge.dest - 'a']++;
        }
    }
};

// Utility function to print contents of a given list
void printPath(list<char> list) {
    while (!list.empty()) {
        cout << list.front() << ' ';
        list.pop_front();
    }
    cout << endl;
}
void findAllTopologicalOrderings(Graph &graph, auto &path, auto &discovered, int n) {
    for (char v = 'a'; v <= 'z'; v++) {
        int index = v - 'a';
        if (index >= 0 && index < graph.adjList.size() && graph.indegree[index] == 0 && !discovered[index]) {
            for (char u : graph.adjList[index]) {
                int uIndex = u - 'a';
                if (uIndex >= 0 && uIndex < graph.adjList.size()) {
                    graph.indegree[uIndex]--;
                }
            }

            path.push_back(v);
            discovered[index] = true;

            findAllTopologicalOrderings(graph, path, discovered, n);

            for (char u : graph.adjList[index]) {
                int uIndex = u - 'a';
                if (uIndex >= 0 && uIndex < graph.adjList.size()) {
                    graph.indegree[uIndex]++;
                }
            }

            path.pop_back();
            discovered[index] = false;
        }
    }

    if (path.size() == n) {
        printPath(path);
    }
}


// Print all topological orderings of a given DAG
void printAllTopologicalOrders(Graph &graph) {
    int n = graph.adjList.size();
    vector<bool> discovered(n);
    list<char> path;
    findAllTopologicalOrderings(graph, path, discovered, n);
}

int main() {
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
       {'a', 'b'},
        {'d', 'b'},
        {'d', 'e'},
        {'g', 'e'},
        {'g', 'h'},
        {'e', 'f'},
        {'b', 'c'},
        {'b', 'f'},
        {'b', 'h'}
    };

    // build a graph from the given edges
    Graph graph(edges);

    // print all topological orderings of the graph
    printAllTopologicalOrders(graph);

    return 0;
}
// {5, 11},
// {7, 11},
// {7, 8},
// {3, 8},
// {3, 10},
// {8, 9},
// {11, 2},
// {11, 9},
// {11, 10}

// replace - a by 5, b by 11, c by 2 , d by 7, e by 8, f by 9, g by 3, h by 10 
// a d b c g e f h 
// a d b c g e h f
// a d b c g h e f
// a d b g c e f h
// a d b g c e h f
// a d b g c h e f
// a d b g e c f h
// a d b g e c h f
// a d b g e f c h
// a d b g e f h c
// a d b g e h c f
// a d b g e h f c
// a d b g h c e f
// a d b g h e c f
// a d b g h e f c
// a d g b c e f h
// a d g b c e h f
// a d g b c h e f
// a d g b e c f h
// a d g b e c h f
// a d g b e f c h 
// a d g b e f h c
// a d g b e h c f
// a d g b e h f c
// a d g b h c e f
// a d g b h e c f
// a d g b h e f c
// a d g e b c f h
// a d g e b c h f
// a d g e b f c h
// a d g e b f h c
// a d g e b h c f
// a d g e b h f c
// a g d b c e f h
// a g d b c e h f
// a g d b c h e f
// a g d b e c f h
// a g d b e c h f
// a g d b e f c h
// a g d b e f h c 
// a g d b e h c f
// a g d b e h f c
// a g d b h c e f
// a g d b h e c f
// a g d b h e f c
// a g d e b c f h
// a g d e b c h f
// a g d e b f c h
// a g d e b f h c
// a g d e b h c f
// a g d e b h f c
// d a b c g e f h
// d a b c g e h f
// d a b c g h e f
// d a b g c e f h
// d a b g c e h f
// d a b g c h e f
// d a b g e c f h
// d a b g e c h f
// d a b g e f c h
// d a b g e f h c
// d a b g e h c f
// d a b g e h f c 
// d a b g h c e f
// d a b g h e c f
// d a b g h e f c
// d a g b c e f h
// d a g b c e h f
// d a g b c h e f
// d a g b e c f h
// d a g b e c h f
// d a g b e f c h
// d a g b e f h c
// d a g b e h c f
// d a g b e h f c
// d a g b h c e f
// d a g b h e c f
// d a g b h e f c
// d a g e b c f h
// d a g e b c h f
// d a g e b f c h
// d a g e b f h c 
// d a g e b h c f
// d a g e b h f c
// d g a b c e f h
// d g a b c e h f
// d g a b c h e f
// d g a b e c f h
// d g a b e c h f
// d g a b e f c h
// d g a b e f h c
// d g a b e h c f
// d g a b e h f c
// d g a b h c e f
// d g a b h e c f
// d g a b h e f c
// d g a e b c f h
// d g a e b c h f
// d g a e b f c h
// d g a e b f h c
// d g a e b h c f
// d g a e b h f c
// d g e a b c f h
// d g e a b c h f
// d g e a b f c h 
// d g e a b f h c
// d g e a b h c f
// d g e a b h f c
// g a d b c e f h
// g a d b c e h f
// g a d b c h e f
// g a d b e c f h
// g a d b e c h f 
// g a d b e f c h
// g a d b e f h c
// g a d b e h c f
// g a d b e h f c
// g a d b h c e f
// g a d b h e c f
// g a d b h e f c
// g a d e b c f h 
// g a d e b c h f 
// g a d e b f c h
// g a d e b f h c
// g a d e b h c f 
// g a d e b h f c
// g d a b c e f h
// g d a b c e h f
// g d a b c h e f
// g d a b e c f h
// g d a b e c h f 
// g d a b e f c h
// g d a b e f h c
// g d a b e h c f
// g d a b e h f c
// g d a b h c e f 
// g d a b h e c f
// g d a b h e f c
// g d a e b c f h
// g d a e b c h f
// g d a e b f c h
// g d a e b f h c 
// g d a e b h c f
// g d a e b h f c
// g d e a b c f h
// g d e a b c h f 
// g d e a b f c h
// g d e a b f h c
// g d e a b h c f
// g d e a b h f c