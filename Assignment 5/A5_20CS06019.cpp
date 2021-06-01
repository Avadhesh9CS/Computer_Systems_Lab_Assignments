/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph
class Graph{
    // No. of vertices
    int vertices;

    // No. of edges
    int edges;

    // Adjacency lists to store undirected graph edges
    vector<int> *adj;

    // Array to mark vertex is visited or not visited
    bool *discovered;
   void BFS(int e,int s,int k);
    vector<int> *output;
    public:
        // Constructor
        Graph(int V,int E);
        void addEdge(int u,int v);
        void printOutput(int x,int y,int dis);
};
Graph::Graph(int V,int E){
    this->vertices  = V;
    this->edges=E;
    adj=new vector<int>[V];
    output=new vector<int>[2];
}

void Graph::addEdge(int u, int v){
    //(u,v) is the edge
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void Graph::BFS(int e,int s,int k){
    discovered=new bool[vertices];
    list<int> queue;
    int j,present=0,next=0;
    vector<int>::iterator i;
    discovered[s] = true;
    present=1;
    queue.push_back(s);
    while(!queue.empty()){
    s = queue.front();
    if(present==0){
        present=next;
        k--;
        next=0;
    }
    queue.pop_front();
    for (i = adj[s].begin(); i != adj[s].end(); ++i) {
        if (!discovered[*i]) {
            discovered[*i] = true;
             next++;
            if(k==0){
              output[e].push_back(*i);
              //cout<<*i<<" ";
           }
           if(k!=0){
            queue.push_back(*i);
           }
            }
        }
        present--;
    }
}
void Graph::printOutput(int x,int y,int dis){
    int t=0;
    BFS(0,x,dis);
    BFS(1,y,dis);
    vector<int>::iterator r;
   /* for(int j=0;j<2;j++){
            cout<<endl;
        for (r = output[j].begin(); r != output[j].end(); ++r) {
            cout<<*r<<" ";
        }
    }*/
    vector<int> v(output[0].size() + output[1].size());
    vector<int>::iterator it, st;

    it = set_intersection(output[0].begin(),
                          output[0].end(),
                          output[1].begin(),
                          output[1].end(),
                          v.begin());
     for (st = v.begin(); st != it; ++st){
        t=1;
        cout << *st << " ";
     }
     if(t==0){
        cout<<"-1";
     }
}
int main(){
    int ver,ed,u,v,dis,x,y;
    std::cout << "Enter no of vertices: ";
	std::cin >>ver ;
	std::cout << "Enter no of edges: ";
	std::cin >> ed;
	Graph graph(ver,ed);
	std::cout << "Enter edges:" << std::endl;
	for(int i=0;i<ed;i++){
        std::cin >>u>>v;
        graph.addEdge(u,v);
	}
	std::cout << "Enter the distance: ";
	std::cin >>dis ;
	std::cout << "Enter two elements x and y: ";
	std::cin >>x>>y;
	std::cout<< std::endl << "       -----OUTPUT-----" <<endl;
	graph.printOutput(x,y,dis-1);
return 0;
}
