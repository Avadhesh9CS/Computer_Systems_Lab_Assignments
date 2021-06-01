/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*Write a C/C++ program for Kruskal’s algorithm.*/

#include<iostream>
using namespace std;
/********************************* DATA STRUCTURE CREATION *******************************/
//This class is used as a data structure of Edge
class Edge{
    public:
        int end_point_one,end_pint_two,weight;
};

//This class is used as a data structure of Graph
class Graph{
    public:
        int V,E;
        Edge* edges;
};

//This class is used as a data structure of Disjoint Set
class DisjointSet{
    public:
        int leader,rank;
};


//Method to create Graph
Graph* creatGraph(int v,int e){
    Graph* graph=new Graph;
    graph->V=v;
    graph->E=e;
    graph->edges= new Edge[e];
    return graph;
}

/********************************* QUICK SORT FUNCTION *******************************/

//It is used to swap the position of edge
void swap(Edge* a, Edge* b){
    Edge t =*a;
    *a = *b;
    *b = t;
}

//This method use to partition the array in quick sort
int partition (Graph* g, int low, int high){
    int pivot=g->edges[high].weight;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++){
        // If current element is smaller than the pivot
        if (g->edges[j].weight< pivot){
            i++;
            swap(&g->edges[i], &g->edges[j]);
        }
    }
    swap(&g->edges[i + 1], &g->edges[high]);
    return (i + 1);
}


//Function for quick Sort
// It is used for sorting edges
void sort(Graph* g,int low,int high){
    if(low<high){
        int pi = partition(g, low, high);
        sort(g,low,pi-1);
        sort(g,pi+1,high);
    }
}

/********************************* DISJOINT SET FUNCTIONS *******************************/

// Function to create disjoint set
DisjointSet* MakeSet(int V){
    DisjointSet* dset =new DisjointSet[V];
    for(int i=0;i<V;i++){
        dset[i].leader=i;
        dset[i].rank=0;
    }
 return dset;
}

// Function to Find leader of disjoint Set
int Find(DisjointSet* dset,int x){
    while (x!=dset[x].leader){
        x =dset[x].leader;
    }
return x;
}

//Function to return Union of two set by rank
void Union(DisjointSet*dset,int x,int y){
    int r=Find(dset,x);
    int s=Find(dset,y);
    if(r==s){
        return;
    }else if(dset[r].rank>dset[s].rank){
            dset[s].leader=r;
    }else{
            dset[r].leader=s;
    }
    if(dset[r].rank==dset[s].rank){
        dset[s].rank=dset[s].rank+1;
    }
}


/********************************KKRUSKAL"S ALGORITHM *******************************/
void Kruskalalgorithm(Graph* g){
    int V=g->V,E=g->E,e=0,i=0;
    Edge result[V];

    // sorting of edge in increasing order
    sort(g,0,E-1);

    //Creating disjoint sets where each vertex is only member in the set
    DisjointSet* dset=MakeSet(V);

    //picking lowest weight edge and storing in result graph such that it form tree
    while(e<V-1 && i <E){
        Edge next_edge=g->edges[i++];
        int x=Find(dset,next_edge.end_point_one);
        int y=Find(dset,next_edge.end_pint_two);
        if(x!=y){
            result[e++]=next_edge;
            Union(dset,x,y);
        }
    }

    std::cout<< std::endl << "       -----OUTPUT-----" << std::endl;
    cout<<endl<<"--------------------MST edges--------------------------"<<endl;
    int mcost=0;
    for(int i=0;i<V-1;i++){
        cout<<result[i].end_point_one<<" "<<result[i].end_pint_two<<" "<<result[i].weight<<endl;
        mcost+=result[i].weight;
    }
    cout<<endl<<"---------------------MST Cost-------------------------"<<endl;
    cout<<"Cost of spanning Tree: "<<mcost;
}

//Driver Code
int main(){
    int vertices,edges;
    cout<<"Enter no of vertices: ";
    cin>>vertices;
    cout<<"Enter no of edges: ";
    cin>>edges;
    Graph* g=creatGraph(vertices,edges);
    cout<<"Enter endpoint1, endpoint2 and weight of each edge:"<<endl;
    for(int i=0;i<edges;i++){
        cin>>g->edges[i].end_point_one>>g->edges[i].end_pint_two>>g->edges[i].weight;
    }
    Kruskalalgorithm(g);
    return 0;
}
