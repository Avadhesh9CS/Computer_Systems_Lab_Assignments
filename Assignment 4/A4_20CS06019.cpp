/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*
A directed graph is strongly connected if there is a path between all pairs of vertices. A
strongly connected component (SCC) of a directed graph is a maximal strongly connected
subgraph.Given a directed graph, write a program that prints the number of SCCs in the graph. Also it
prints vertices in each component.
*/
#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph
class Graph{
    // No. of vertices
    int vertices;

    // No. of edges
    int edges;

    // Adjacency lists to store forward edge
    vector<int> *adj_for;
    // Adjacency list to store reversed edge
    vector<int> *adj_back;
    // Adjacency list to store edges between component
    vector<int> *component_edges;

    // Array to mark vertex is visited or not visited
    bool *discovered;

    // Stack to implement DFS
    stack<int> Stack;

    // Array containing vertex and its belonging component
    int** ver_component_list;

    // Global variable to store count of components
    int no_of_component;

    // DFS traversal of the vertices reachable from s
    // It is a private functions

    // Function to implement DFS traversal graph in forward edges graph
    void forwardOrderTraversal(int v);
    // Function to implement DFS traversal graph in reversed edges graph
    void reverseOrderTraversal(int v);
    // Function to add and print edges of component graph
    void componentEdgeAddition();

    public:
        // Constructor
        Graph(int V,int E);

        // Functions to add an edge to graph

        // It add forward edge in adjacency list of forward graph and it also add reversed edge in reversed graph
        void addEdge(int v, int w);
        // It add unique edge in component graph
        void addComponentEdge(int v, int w);

        //function to find strongly connected component and print component graph
        void SCCs();

};

// Constructor define
Graph::Graph(int V,int E){
    this->vertices  = V;
    this->edges=E;
    adj_for=new vector<int>[V];
    adj_back=new vector<int>[V];
    discovered=new bool[V];
    ver_component_list=new int*[V];
    for(int i=0;i<V;i++){
        ver_component_list[i]= new int[2];
        for(int j=0;j<2;j++){
            ver_component_list[i][j]=-1;
        }
    }
}

// Function to add forward edge in adjacency list of forward graph and it also add reversed edge in reversed
void Graph::addEdge(int u, int v){
    //(u,v) is the edge
    adj_for[u].push_back(v); //this add v in the list of adjacent of u in forward graph
    adj_back[v].push_back(u);//this add v in the list of adjacent of u in backward graph
}

// It add unique edge in component graph
void Graph::addComponentEdge(int u, int v){
    //(u,v) is the edge
    int i=0;
    for (auto x : component_edges[u])// this part check that no duplicate edge id going to be add
            if(x==v)
                    i=1;
    if(i==0)
        component_edges[u].push_back(v); //this add v in the list of adjacents of u
}


void Graph::forwardOrderTraversal(int v){
    // Mark the current node as visited and print it
    discovered[v] = true;

    // Recur for all the vertices adjacent to this vertex
    vector<int>::iterator i;
    for(i = adj_for[v].begin(); i != adj_for[v].end(); ++i)
        if(!discovered[*i])
            forwardOrderTraversal(*i);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

//this function traverse reversed graph and it traverse according to stack that is filled in forward traversal
void Graph::reverseOrderTraversal(int v){
    // Mark the current node as visited and print it
    discovered[v] = true;
    cout << v+1 << " ";
    // adding information of component invetex component list
    ver_component_list[v][0]=v;
    ver_component_list[v][1]=no_of_component;

    // Recur for all the vertices adjacent to this vertex
    vector<int>::iterator i;
    for (i = adj_back[v].begin(); i != adj_back[v].end(); ++i)
        if (!discovered[*i])
            reverseOrderTraversal(*i);
}

// Function to add and print edges of component graph and it is also responsible for printing it
void Graph::componentEdgeAddition(){
    component_edges=new vector<int>[no_of_component];
    vector<int>::iterator i;
    for(int v=0;v<vertices;v++){
        for (i = adj_for[v].begin(); i != adj_for[v].end(); ++i){
            if(ver_component_list[v][1]!=ver_component_list[*i][1]){
                          addComponentEdge(ver_component_list[v][1],ver_component_list[*i][1] );
                    }
                }
            }

    std::cout<< "\n Component Graph "<<endl;
   	for (int v = 0; v < no_of_component; ++v){
		for (auto x : component_edges[v])
            std::cout<< "Component "<<v+1<<"---> Component " << x+1;
		printf("\n");
	}
}

void Graph::SCCs(){
    no_of_component=0;

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < vertices; i++)
        if(discovered[i] == false)
            forwardOrderTraversal(i);

    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < vertices; i++)
        discovered[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false){
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (discovered[v] == false){
            std::cout << " Component "<<no_of_component+1<<": ";
            reverseOrderTraversal(v);
            no_of_component++;
            cout << endl;
        }
    }
    componentEdgeAddition();
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
	std::cout<< std::endl << "       -----OUTPUT-----" << std::endl;
	graph.SCCs();
return 0;
}
