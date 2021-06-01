/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*
Write a C/C++ program for Breadth-First Traversal in a directed unweighted graph.
*/

#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph using adjacency list representation
class Graph{
    // No. of vertices
    int vertices;

    // No. of edges
    int edges;

    // Adjacency lists
    vector<int> *adj;

    // Arrray to mark vertex is visited or not visited
    bool *discovered;

    // BFS traversal of the vertices reachable from s
    // It is a private function
    void BFS(int s);

    public:
        // Constructor
        Graph(int V,int E);

        // function to add an edge to graph
        void addEdge(int v, int w);

        //function to implement Breadth first Traversal
        void BFT();
};

// Constructor define
Graph::Graph(int V,int E){
    this->vertices = V;
    this->edges=E;
    adj=new vector<int>[V];
    discovered=new bool[V];
}

// A function to add an edge (u,v) in an directed graph.
void Graph::addEdge(int u, int v)
{
     //this add v in the list of adjacents of u
    adj[u].push_back(v);
}

void Graph::BFS(int s){
    // Create a queue for BFS
    list<int> queue;
    // Mark the current node as visited and enqueue it
    discovered[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent vertices of a vertex s
    vector<int>::iterator i;

    while(!queue.empty()){
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s+1 << " -> ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!discovered[*i]) {
                discovered[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

void Graph::BFT(){
    for (int i = 0; i < vertices; i++){
        if (!discovered[i])
            BFS(i);
    }
    cout <<"end";
}

// Driver code
int main(){
    int ver,ed,u,v;
    std::cout << "Enter no of vertices: ";
	std::cin >>ver ;
	std::cout << "Enter no of edges: ";
	std::cin >> ed;
	Graph graph(ver,ed);
	std::cout << "Enter directed edges:" << std::endl;
	for(int i=0;i<ed;i++){
        std::cin >>u>>v;
        graph.addEdge(u-1,v-1);
	}
	graph.BFT();
	return 0;
}
