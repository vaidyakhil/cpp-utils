/*
** To be deprecated
*/

--------------------------------------- 
Traversals->BFS, DFS, Topological sort, 
Cycle detection, 
Shortest Path -> (Dijkstras, Bellman-Ford, Floyd-Warshall), 
Bipartite, Disjoint Set Union method,
Minimum Spanning Tree-> ( Kruskal, Prims ( Heap(min, max), priority queue ) 
--------------------------------------------------------------------------------------------------------------------------

						Directed GRAPH


------------------------------------------------------------------------------------------------------------------
Bipartite graphs is one in which nodes can be divided into 2 sets of nodes such that any edge connnects vertices from one set to another set only.
------------------------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------

//Prim's algorithm..
** takes adjacency list of pairs {weight, destination}, if a vertex is not yet visited it is added to a priority queue, which arranges minimum weight edge at the top.
** if edges involving same vertex, are in the q, automatically one with the smallest weight will be used and vis[v]= True;
typedef pair<long long int, int> pr; //will store {weight, destination};

int mst(vector<pr>* adj, int n){
    bool vis[n+1]= {};
    long long sum= 0;
    priority_queue <pr, vector<pr>, greater<pr>> q;
    q.push( {0, 1} );
    
    while(!q.empty()){
        
        if(vis[ q.top().second]){
            q.pop();
            continue;
        }
        
        sum+= q.top().first;
        int s= q.top().second;
        vis[s]= true;
        q.pop();
        for(int i=0; i<adj[s].size(); i++){
            if(vis[ adj[s][i].second ]) continue;
            q.push(adj[s][i]);
        }
    }
    return sum;
}

// kruskal's algo
//get vector of {w, {x, y}}, sort it. ( O(nlog(n)) );
// start adding edges if x and y belong to different group, update sum, update parent of x and y using root, find and Union functions;

// Prim's algo
// get adjacency list of {w, dest.};
// make priority que of min heap form, and add these pairs in it. if (!vis[que.top()]) add the weight of que.top() and vis[dest]= true; the start adding pairs of neighbours of  que.top().

------------------------------------------------------------------------------------------------------------------


Euclerian Path :
	we can traverse whole undirected graph with each EDGE visited only once.
	For this the number of nodes with odd degree must be ==2 or 0;
	2: it has Euclerian Path from node1 to node 2 vise- versa.
	0: Euclerian Cycle is present. start and end node are same

---------------------------------------------------------------------------------------------------------------------------------------

If an array is represented as graph and we make an edge from ith node to jth node such that os of A[i] is j in sorted array than the resultant graph will have number of cycles of different sizes.


------------------------------------------------------------------------------------------------------------------

KosaRaju's Algo to find the strongly connected components of a directed graph
Do the topological sort of original graph
and then mirror the original graph and do simple dfs in the topo of orignal graph. 
The dfs gives separate strongly connected graph.
------------------------------------------------------------------------------------------------------------------'

Rotten tomatoes (Graph) without using STL:
	#include<iostream>
#define INF 10000000
using namespace std;

int const MAX= 10000;
class Queue{
    int *que;
    int size, fr, bk;
    public: 
        Queue();
        Queue(int);
        bool empty();
        int  front();
        void push(int);
        void pop();
        ~Queue();
};

Queue:: Queue(){
    size= MAX;
    que= new int[size];
    fr= 0;
    bk= -1;
}
Queue::Queue(int size){
    this->size= size;
    que= new int[size];
    fr= 0; 
    bk=-1;
}
bool Queue::empty(){
    return (bk < fr);
}

int Queue::front(){
    if(empty()) return -1;
    return que[fr];
}
void Queue::push(int mem){
    bk++;
    if(bk > size)
        return;
    que[bk]= mem;
}

void Queue::pop(){
    if(empty())
        return;
    fr++;
}
Queue::~Queue(){
    delete[] que;
}

bool check(int i, int j, int r, int c){
    return (i >= 0 && i<r && j>=0 && j<c);
}

void bfs(int(* adj)[100] , int src, int r, int c){
    bool vis[r][c]= {};
    Queue que;
    que.push(src);
    vis[src/c][src%c]= true;
    while(!que.empty()){
        src= que.front();
        int i= src/c, j= src%c;
        if(check(i-1, j, r, c) && adj[i-1][j] != -1 && !vis[i-1][j]){
            vis[i-1][j]= true;
            if(adj[i-1][j] > 1 + adj[i][j]){
                adj[i-1][j] = 1 + adj[i][j];
                que.push(src - c);
            }
        }
        if(check(i+1, j, r, c) && adj[i+1][j] != -1 && !vis[i+1][j]){
            vis[i+1][j]= true;
            if(adj[i+1][j] > 1 + adj[i][j]){
                adj[i+1][j] = 1 + adj[i][j];
                que.push(src + c);
            }
        }
        if(check(i, j-1, r, c) && adj[i][j-1] != -1 && !vis[i][j-1]){
            vis[i][j-1]= true;
            if(adj[i][j-1] > 1 + adj[i][j]){
                adj[i][j-1] = 1 + adj[i][j];
                que.push(src - 1);
            }
        }
        if(check(i, j+1, r, c) && adj[i][j+1] != -1 && !vis[i][j+1]){
            vis[i][j+1]= true;
            if(adj[i][j+1] > 1 + adj[i][j]){
                adj[i][j+1] = 1 + adj[i][j];
                que.push(src + 1);
            }
        }
        que.pop();
    }
    return;
}


int main(){
    int t; cin>>t;
    while(t--){ 
        int r, c; cin>>r>>c;
        int adj[100][100];
        int origin[r*c];
        for(auto &i: origin)
            i= -1;
        int count= -1;
        for(int i=0; i<r*c; i++){
            cin>>adj[i/c][i%c];
            if(adj[i/c][i%c] == 0)
                adj[i/c][i%c]= -1;
            else if(adj[i/c][i%c] == 1)
                adj[i/c][i%c]= INF;
            else{
                adj[i/c][i%c]= 0;
                count++;
                origin[count]= i;
                
            }
        }
        while(count>=0){
            bfs(adj, origin[count], r, c);
            count--;
        }
            
        bool flag= true;
        int maxm= 0;
        for(int i=0; i<r*c; i++){
            if(adj[i/c][i%c] == INF){
                flag= false;
                break;
            }
            maxm= max(maxm, adj[i/c][i%c]);
        }
        if(flag)
            cout<<maxm<<endl;
        else
            cout<< -1<<endl;
    }
    return 0;
}
	