#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    int name,f,g,h,x,y,parent;
    Node(int name): name(name){
        cout<<"\nEnter coordinates x and y for the node-"<<name<<" :";
        cin>>x>>y;
        g = INT_MAX;
    }


    Node(int name,int x,int y): name(name), x(x), y(y){
        g = INT_MAX;
    }

    friend class Graph;

};


bool operator<(const Node& lhs, const Node& rhs)
{
    return lhs.f < rhs.f;
}
 

class Graph {
    int size;
    vector<vector<int>> adjacency_matrix;
public:
    vector<Node> nodes;

    Graph(const int size) : size(size) {
        int a,b;
    
        adjacency_matrix = vector<vector<int>>(size, vector<int>(size,0));
        for(int i=0; i<size; i++){
            nodes.push_back(Node(i));
        }
        do{
            cout<<"\nEnter two nodes to connect them ";
            cin>>a;
            if(a==-1)break;
            cin>>b;
            adjacency_matrix[a][b] = euclidean(nodes[a], nodes[b]);
            adjacency_matrix[b][a] =  adjacency_matrix[a][b];
        } while(1);
    }

    int euclidean(Node& a, Node& b){
        return round(sqrt ( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) ));
    }

    void print_adjacency_matrix(){
        cout<<"\nAdjacency Matrix:\n";
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                cout<<adjacency_matrix[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl; 
        for(int i=0; i<size; i++){
            for(int j=0; j<i; j++){
                if(adjacency_matrix[i][j] != 0)
                    cout<<i<<"-"<<j<<": weight "<<euclidean(nodes[i],nodes[j])<<endl;
            }
        }
    }

    void a_star(int source, int destination){
        vector<int> closed;
        vector<Node> open;
        int cost=0;

        for(int i = 0; i < size; i++){
            nodes[i].h = euclidean(nodes[i], nodes[destination]);
            cout<<"\nFor Node-"<<i<<" h="<<nodes[i].h;
        }
        nodes[source].g = 0;
        nodes[source].f = nodes[source].g + nodes[source].h;
        nodes[source].parent = -1;
        
        open.push_back(nodes[source]);

        while(open.size()){
            auto selectedNode = min_element(open.begin(),open.end(), 
                []( const Node &a, const Node &b )
                {
                    return a.f < b.f;
                }
            );
            int curr = selectedNode->name;
            open.erase(selectedNode);
            if(curr == nodes[destination].name){
                cost = nodes[curr].g;
                break;
            }
            cout<<"\n\nInserted Node "<<curr<<" into Closed List with f="<<nodes[curr].f<<endl; 
            closed.push_back(curr);
            for(int i = 0; i < size; i++) {
                if(adjacency_matrix[curr][i] != 0 && i!=curr  && find(closed.begin(),closed.end(), i)==closed.end()){
                    auto itr = find_if(open.begin(),open.end(), [&i](const Node& obj) {return obj.name == i;});
                    if(itr!=open.end()){
                        itr->g = nodes[curr].g + euclidean(*itr, nodes[curr]);
                        itr->f = itr->g + itr->h;
                        cout<<"\nUpdated Node"<<itr->name<<" in Open List with g="<<itr->g; 
                        itr->parent = curr;
                    }
                    else{
                        nodes[i].g = nodes[curr].g + euclidean(nodes[i], nodes[curr]);
                        nodes[i].f = nodes[i].g + nodes[i].h;
                        cout<<"\nInserted Node"<<i<<" into Open list with g="<<nodes[i].g; 
                        nodes[i].parent = curr;
                        open.push_back(nodes[i]);
                    }
                }
            }
        }

        
        cout<<"\n\nPath found with total cost: "<< cost << endl;
        stack<int> path;
        int parent = nodes[destination].parent;
        while(parent != -1 && path.size()<=size){
            path.push(parent);
            parent = nodes[parent].parent;
        }

        while(!path.empty()){
            cout<<path.top()<<" - ";
            path.pop();
        }
        cout<<destination<<endl;
    }
};

/*
     N1(0,1) _N3(0,4){2}
 {3}/   |    \      |  \
   /    |     \     |  N5(1,6)
  /    {5}  {4}\   {4}  /{3}
N0(3,0) |       \   |  /
 {2}\   |         N4(4,5)
    N2(5,1) __/
                {4}
6 3 0  0 1  5 1  0 4  4 5  1 6 
0 1  0 2  1 2  1 3  1 4  2 4  3 4  3 5  4 5 -1 0 5
*/

int main() {
    int vertices,a,b;
    cout<<"Enter the number of vertices in the graph: ";
    cin>>vertices;
    Graph graph(vertices);
    graph.print_adjacency_matrix();
    do{
        cout<<"\nEnter the start node and end node \nor -1 to exit ";
        cin>>a;
        if(a==-1) 
            break;
        cin>>b;
        graph.a_star(a,b);
    }while(1);
    return 0;
}

/*  PS C:\c++ course> g++ .\LP2_astar.cpp
PS C:\c++ course> .\a.exe
Enter the number of vertices in the graph: 6
Enter coordinates x and y for the node-0 :3 0
Enter coordinates x and y for the node-1 :0 1
Enter coordinates x and y for the node-2 :5 1
Enter coordinates x and y for the node-3 :0 4
Enter coordinates x and y for the node-4 :4 5
Enter coordinates x and y for the node-5 :1 6
Enter two nodes to connect them 0 1
Enter two nodes to connect them 0 2
Enter two nodes to connect them 1 2
Enter two nodes to connect them 1 3
Enter two nodes to connect them 1 4
Enter two nodes to connect them 2 4
Enter two nodes to connect them 3 4
Enter two nodes to connect them 3 5
Enter two nodes to connect them 4 5
Enter two nodes to connect them -1
Adjacency Matrix:
0 3 2 0 0 0
3 0 5 3 6 0
2 5 0 0 4 0
0 3 0 0 4 2
0 6 4 4 0 3
0 0 0 2 3 0
