/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// LAB Test 1


#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph
class Graph{
    // No. of vertices
    int vertices;

    // Arrray to mark vertex is visited or not visited
    bool *discovered;

    // Vertex parent and in-out time maintaing table
    /* Each column index in this table signifies
            0 index for node no
            1 index for parent node
    */
    int** ver_in_out;

    // DFS traversal of the vertices reachable from s
    // It is a private function
    void DFS(int s,char c,Graph graph2);
    void DFS(int v);

    public:
        // Adjacency lists
        vector<int> *adj;
        //cross edges
        vector<int> *crossedge;
        //color array
        char* color;

        // Constructor
        Graph(int V);

        // function to add an edge to graph
        void addEdge(int v, int w);

        // Function to print the output
        void printAdjancyList(char c);
        void printAdjancyList();

        //function to implement Depth first Traversal
        void DFT(char c,Graph graph2);
        void DFT();
};

// Constructor define
Graph::Graph(int V){
    this->vertices  = V;
    adj=new vector<int>[V];
    crossedge=new vector<int>[V];
    color=new char[V];
    discovered=new bool[V];
    ver_in_out=new int*[V];
    for(int i=0;i<V;i++){
        ver_in_out[i]= new int[4];
        for(int j=0;j<2;j++){
            ver_in_out[i][j]=-1;
        }
    }
}
void Graph::addEdge(int u, int v){
    //(u,v) is the undirected edge
    adj[u].push_back(v);
    adj[v].push_back(u);
}
// Function to perform DFS
void Graph::DFS(int v,char c,Graph graph2){
    // set node no
    ver_in_out[v][0]=v;
	// mark vertex as discovered
	discovered[v] = true;

	for (int a : adj[v]){
        if (!discovered[a] && color[a]==c){
            //set node's parent
            graph2.addEdge(v,a);
            ver_in_out[a][1]=v;
            DFS(a,c,graph2);
        }
        else{
            int test=1;
            for (auto x:crossedge[v]){
                if(x==a){
                    test=0;
                }
            }
            if(color[a]==c && ver_in_out[v][1]!=a && test==1){
                // store edge (v,a) and mark edge type as cross edge
                int parent=v;
                crossedge[v].push_back(a);
                crossedge[a].push_back(v);
                while(parent!=a && parent!=-1){
                      cout<<parent<<"["<<c<<"] ";
                      parent=ver_in_out[parent][1];
                }
                cout<<parent<<"["<<c<<"] "<<endl;
            }
        }
	}
}
void Graph::DFT(char c,Graph graph2){
    for (int i = 0; i < vertices; i++){
        if (!discovered[i] && color[i]==c)
            DFS(i,c,graph2);
    }
}

void Graph::DFS(int v){
    // set node no
    ver_in_out[v][0]=v;
	// mark vertex as discovered
	discovered[v] = true;

	for (int a : adj[v]){
        if (!discovered[a]){
            //set node's parent
            ver_in_out[a][1]=v;
            DFS(a);
        }
        else{
            int test=1;
            for (auto x:crossedge[v]){
                if(x==a){
                    test=0;
                }
            }
            if(ver_in_out[v][1]!=a && test==1){
            // store edge (v,a) and mark edge type as cross edge
                int parent=v;
                crossedge[v].push_back(a);
                crossedge[a].push_back(v);
                while(parent!=a && parent!=-1){
                      cout<<parent<<"["<<color[parent]<<"] ";
                      parent=ver_in_out[parent][1];
                }
                cout<<parent<<"["<<color[parent]<<"] "<<endl;
            }
        }
	}
}

void Graph::DFT(){
    for (int i = 0; i < vertices; i++){
        if (!discovered[i])
            DFS(i);
    }
}
void Graph::printAdjancyList(){
    for (int v = 0; v < vertices; ++v){
		std::cout<< "\n ["<<color[v]<<"] "<<v;
		for (auto x:adj[v])
            std::cout<< "-> " << x;
	}
}
void Graph::printAdjancyList(char c){
    for (int v = 0; v < vertices; ++v){
            if(color[v]==c){
                std::cout<< "\n ["<<color[v]<<"] "<<v;
                for (auto x : adj[v])
                    if(color[x]==c)
                        std::cout<< "-> " << x;
            }
        }
}
//Driver code
int main(){
    int u,v,vertices;
    cout<<"Enter no of vertices ";
    cin>>vertices;
    Graph graph(vertices);
    cout<<"Enter color string ";
    for(int i=0;i<vertices;i++){
        cin>>graph.color[i];
    }
    std::cout << "-----Enter edges:-----" << std::endl;
	while(true){
        std::cin >>u;
        if(u==-1){
            break;
        }
        std::cin >>v;
        graph.addEdge(u,v);
	}
    std::cout<< std::endl << "       ===========OUTPUT==========" << std::endl;
    std::cout<<endl<< "-------------Graph Adjacency list-------------";
	graph.printAdjancyList();

	std::cout<<endl<<endl<< "-------------Red Adjacency list-------------";
	graph.printAdjancyList('r');

	std::cout<<endl<<endl<< "-------------Blue Adjacency list-------------";
	graph.printAdjancyList('b');

	Graph graph2(vertices);
	graph2.color=graph.color;
	cout<<endl<<endl<<"-------------Red cycles-------------"<<endl;
	graph.DFT('r',graph2);

	cout<<endl<<endl<<"-------------Blue cycles-------------"<<endl;
	graph.DFT('b',graph2);

	// Add Green Edge
	for (int v = 0; v < vertices; ++v){
        for (auto x : graph.adj[v]){
            if(graph.color[v]=='r' && graph.color[x]=='b'){
                graph2.addEdge(v,x);
            }
        }
	}

	std::cout<<endl<<endl<< "-------------Red-Blue Adjacency list-------------";
	graph2.printAdjancyList();

	cout<<endl<<endl<<"-------------Red-Blue cycles-------------"<<endl;
	graph2.DFT();

}

