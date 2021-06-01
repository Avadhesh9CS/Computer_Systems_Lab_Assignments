/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*
Given a directed unweighted graph, write a code for depth first traversal.
For each vertex, print  start time  (st)  and  finish  time  (fin).
Also,  print  the  edges  and  their  types  as  Tree  edge, Back Edge, Forward Edge and Cross Edge.
*/
#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph
class Graph{
    // No. of vertices
    int vertices;

    // No. of edges
    int edges;

    // Adjacency lists
    vector<int> *adj;

    // Arrray to mark vertex is visited or not visited
    bool *discovered;

    // Global variable to store time of visited node
    int time;

    // Vertex parent and in-out time maintaing table
    /* Each column index in this table signifies
            0 index for node no
            1 index for parent node
            2 index for in time of node in stack
            3 index for out time of node in stack */
    int** ver_in_out;

    /*Edges type maintaing table
      Edge type is stored as->
        1 tree edge
        2 forward edge
        3 back edge
        4 cross edge*/
    int** ed_type;

    // Global variable to store count of visited edge
    int k;

    // DFS traversal of the vertices reachable from s
    // It is a private function
    void DFS(int s);

    public:
        // Constructor
        Graph(int V,int E);

        // function to add an edge to graph
        void addEdge(int v, int w);

        // Function to print the output
        void printOutput();

        //function to implement Depth first Traversal
        void DFT();
};

// Constructor define
Graph::Graph(int V,int E){
    this->vertices  = V;
    this->edges=E;
    adj=new vector<int>[V];
    discovered=new bool[V];
    ver_in_out=new int*[V];
    for(int i=0;i<V;i++){
        ver_in_out[i]= new int[4];
        for(int j=0;j<4;j++){
            ver_in_out[i][j]=-1;
        }
    }
    ed_type=new int*[E];
    for(int i=0;i<E;i++){
        ed_type[i]= new int[3];
        for(int j=0;j<3;j++){
            ed_type[i][j]=-1;
        }
    }
}

// A function to add an edge in an directed graph.
void Graph::addEdge(int u, int v)
{
    //(u,v) is the edge
    adj[u].push_back(v); //this add v in the list of adjacents of u
}

void Graph::printOutput(){
    std::cout<< "\n Adjacency list of given graph" <<std::endl;
	for (int v = 0; v < vertices; ++v){
		std::cout<< "\n Adjacency list of vertex "<< v+1 << "\n head ";
		for (auto x : adj[v])
		std::cout<< "-> " << x+1;
		printf("\n");
	}
	std::cout <<std::endl<<"Vertices in and out timming"<<std::endl;
	std::cout <<"  Vertex  (start time , finish Time)"<<std::endl;
	for (int i=0;i<vertices;i++){
	    std::cout <<"    "<<ver_in_out[i][0]+1<<"       ("<<ver_in_out[i][2]<<","<<ver_in_out[i][3]<<")"<<std::endl;
	}

    std::cout <<std::endl<<"Edge and its type"<<std::endl;
	for (int i=0;i<edges;i++){
	    //1 tree edge
        //2 forward edge
        //3 back edge
        //4 cross edge
        if(ed_type[i][2]==1){
            std::cout<<ed_type[i][0]+1<<" -> "<<ed_type[i][1]+1<<" Tree Edge"<<std::endl;
        }
        else if(ed_type[i][2]==2){
            std::cout<<ed_type[i][0]+1<<" -> "<<ed_type[i][1]+1<<" Forward Edge"<<std::endl;
        }
        else if(ed_type[i][2]==3){
            std::cout<<ed_type[i][0]+1<<" -> "<<ed_type[i][1]+1<<" Back Edge"<<std::endl;
        }
        else{
            std::cout<<ed_type[i][0]+1<<" -> "<<ed_type[i][1]+1<<" Cross Edge"<<std::endl;
        }

	}
}

// Function to perform DFS
void Graph::DFS(int v){
    // set node no
    ver_in_out[v][0]=v;
	// set arrival time of vertex v
	ver_in_out[v][2]=time;
	time++;
	// mark vertex as discovered
	discovered[v] = true;

	for (int a : adj[v]){
        if (!discovered[a]){
            //set node's parent
            ver_in_out[a][1]=v;
            // store edge (v,a)
            ed_type[k][0]=v;
            ed_type[k][1]=a;
            // store edge type as Tree edge
            ed_type[k][2]=1;
            k++;
            DFS(a);
        }
        else{
            // store edge (v,a) and mark edge type as others
            ed_type[k][0]=v;
            ed_type[k][1]=a;
            k++;
        }
	}
	// set departure time of vertex v
	ver_in_out[v][3] =time;
	time++;
}

// Function to perform Depth fiest Traversal and assign type to rest of the edge
void Graph::DFT(){
    k=0;
    time=1;
    //DFT loope
    for (int i = 0; i < vertices; i++){
        if (!discovered[i])
            DFS(i);
    }
    // assign type to rest of the edge
    for(int p=0;p<edges;p++){
        if(ed_type[p][2]!=1){
            int stu,stv,finu,finv;
            //(u,v) is the edge u is parent and v is child
            stu=ver_in_out[ed_type[p][0]][2];//start time of u
            finu=ver_in_out[ed_type[p][0]][3];//finish time of u
            stv=ver_in_out[ed_type[p][1]][2];//start time of v
            finv=ver_in_out[ed_type[p][1]][3];//finish time of v
            //(u, v) is a Back edge: st(v) < st(u) < fin(u) < fin(v)
            if(stv<stu && stu <finu && finu<finv){
                ed_type[p][2]=3;
            }
            //(u, v) is a Cross edge: st(v) < fin(v) < st(u) < fin(u)
            else if(stv < finv && finv <stu && stu<finu){
                ed_type[p][2]=4;
            }
            //(u, v) is a Forward edge: u is NOT a parent of v in DFS tree and st(u)<st(v)<fin(v)<fin(u)
            else{
                ed_type[p][2]=2;
            }
        }
    }
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
	graph.DFT();
	std::cout<< std::endl << "       -----OUTPUT-----" << std::endl;
	graph.printOutput();
return 0;
}
