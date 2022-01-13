								_________Graph_________

In Reality, a graph will be a collection of data_type x which are connected in a specific manner (connected, disconnected || directed, undirected) 
now the adjacency list will be an unordered map <key,values> where keys= vertices on graph(x data_type) and values will be neighbouring vertices (unordered_set of data_type x)
Basically hashing is done. The visited will be an unordered_map <data_type x, bool>.

But here we are considering that the key and value both are same and are just same as indices, hence hashing with unordered_map reduces to array with index (0-n);
Disconnected graph: A graph is said as disconnected if there exist atleast one pair of nodes (u, v) such that v cannot be reached if we start from u.

A directed graph s called unilaterally connected if for every pair of nodes (u, v), atleast one of (u to v or v to u) exist. 
...........................strongly............. iff.............................., both of (u to v and v to u) exists.

---------------------------------------
Connected / Disconnected
Directed / Undirected
Weighted / Unweighted
Cyclic / Acyclic
Only positive edge / Negative also
--------------------------------------- 
Traversals(BFS, DFS, Topological sort), Cycle detection, Shortest Path -> (Dijkstras, Bellman-Ford, Floyd-Warshall), Bipartite, Disjoint Set Union method, Minimum Spanning Tree-> ( Kruskal, Prims ( Heap(min, max), priority queue ) 
---------------------------------------

BFS(queue) and DFS(stack) for both directed / undirected is same.
ek node se start kro vis[s] true krdo, DS mein push kro;
while(!DS.empty()){
	s= DS.top()/front();
	DS.pop();
	for(int i=0; i<adj[s][i].size();  i++){
		if(!vis[adj[s][i]]){
			DS.push(adj[s][i]);
			vis[adj[s][i]]= true;
		}
	}
}
--------------------------------------------------------------------------------------------------------------------------------
Topological sort is different from dfs. It is valid for only Directed Acyclic Graph(DAG),
For Connected graph, these two will be the same.
a -> b, then a should come before b for every pair of (a,b) in graph.

Jo kisi ke nhi vo sbse bde. (indegree zero ko ancestor bna do );
find nodes with zero in degree and call for dfs on them.

or do the recst method wala dfs and store the nodes in a master stack whenever flag wala conditon.
-----------------------------------------------------------------------------------------------------------------------------


Cycle Detection
// the different connected components can have a cycle for that we repeatedly call func. for all nodes which have not been visited yet.
-------------------------------------------------------------------------------------------------
for undirected graph, simple DFS of graph passing parent along with can detect cycle.

                        UNDIRECTED GRAPH

// cycle detection through dfs;
//visited ensures that a single connected component is not checked again and again.
// where reckstack is visited array of current connected component
*** 
cycle detection in undirected graph through BFS has the problem of passing the parent. what we can do is makea queue of pair of int <neighbour, parent>. 
***
int dcycle(int s, int par, bool* visited, bool* reckst, vector<int>* adj){
    if(visited[s]) return false;
    visited[s]= reckst[s]= true;
    for(int i=0; i< adj[s].size(); i++){
        if( reckst[ adj[s][i] ] && adj[s][i] != par) return true;
        if( dcycle(adj[s][i], s, visited, reckst, adj) ) return true;
    }
    return false;
}
bool isCyclic(vector<int> adj[], int V)
{
    if(!V) return false;
    bool visited[V]= {};
    for(int i=0; i<V; i++){
        if(!visited[i]){
            bool reckst[V]= {};
            if( dcycle(i, -1, visited, reckst, adj) ) return true;
        }
    }
    return false;
}
----------------------------------------------------------------------------------------------
						Directed GRAPH

cycle can be detected using recstack and flag technique where flag signifies if a node has zero neighbour or not.
stack se pop and recstack mein false only when no neighbour(sure this node cannot be part of cycle).
if a node which is present in reckstack then cycle is detected.
if a new node is found push it in stack flag ko change kro break;

visited array contains all the nodes that have been visited.
reckst shows those which are visited in the current connected graph component;
st basically is same as reckst, its used because it has the LIFO tech.

****** if a node has out degree= 0 it can form no cycle, so start retracting from that node *****

bool dcycle(int s, int V, bool* visited, bool* reckst, vector<int>* adj){
    if(visited[s]) return false;
    stack<int> st;
    st.push(s);
    while(!st.empty()){
        s= st.top();
        visited[s]= true;
        reckst[s]=true;
        
        bool flag= false;
        for(int i=0; i<adj[s].size(); i++){
            if(visited[ adj[s][i] ]  && reckst[ adj[s][i] ]) 
                    return true;
            if(!visited[ adj[s][i] ] ){
                flag=true;
                st.push( adj[s][i] );
                break;
            }
        }
        if(!flag){ 
            reckst[s]= false;
            st.pop();
        }
    }
    return false;
}

bool isCyclic(int V, vector<int> adj[] ){
    if(!V) return false;
    bool visited[V]= {};
    bool reckst[V]= {}; 
    for(int i=0; i< V; i++)
        if( dcycle(i, V, visited, reckst, adj) ) return true;
        
    return false;
}
-----------------------------------------------------------------------------------------------------------
Shortest PATH ALGO
	For unweighted graphs, simply BFS will give shortest path for both directed/undirected graph.
-----------------------------------------------------------------------------------------------------------

Weighted graphs

If negative weights are present, Dijkstras fails as it is a greedy algo and once a node is visited it assumes shortest path is found for it which may not be the case in presence of negative weights.

				Dijkstras using priority_queue time complexity O(Elog(V))
Not dfs;
take the node(min dist) from unused nodes; once taken include in taken nodes; update dist of neighbours if sum from src to weight < prev dist of node. REPEAT.
normal Dijkstras time complexity O(V^2) (without priority queue);

typedef pair<int, int>  pr;

void djk(priority_queue<pr, vector<pr> , greater<pr>>& que, int V, vector<vector<int>>& adj, bool* vis, int* dist){
    while(!que.empty() && vis[que.top().second])
        que.pop();
    if(que.empty()) return;
    int s= que.top().second;
    vis[s]= true;
    que.pop();
    
    for(int i=0; i<V; i++){
        if(!vis[i] && adj[s][i] != 0){
            dist[i]= min(dist[i], dist[s] + adj[s][i]);
            que.push({dist[i], i});
        }
    }
  
    djk(que, V, adj, vis, dist);
    return;
}

-----------------------------------------------------------------------------------------------------------
To get shortest distance of nodes from source using atmost k nodes use atleast 2 arrays, dist, dist1
while checking for relaxing of an edge check from dist i.e dist2[v]= min(dist[v], dist[u] + adj[u][v] )

For negative weights, Bellman-Ford works, but is a bit slower than Dijkstras. Bellman-Ford can be used for negative-weight-cycle.
Bellman-Ford states that if negative-weight-cycles are not present, shortest path to any node can be relaxed in atmost V-1 iterations, V being nnumber of nodes.
It assumes shortest path to contain all the vertices, i.e worst case. 

*****************       BELLMAN_FORD FOR negative-weight-cycle detection        **************************
this algo works on principle of dp, it performs v-1 iterations and claims that AFTER i iterations, min dist of vertex v using atmost i edges is evaluated.
proof by mathematical induction.  after 0: src ka 0, all other inf, after 1 iter, using 1 or 0 edges. 

after i iteration, isse accha shortest distance nhi bna skte using i or less.
****After i iterations, the dist of a node is such that no better dist(smaller) can be made using i or less  than i edges. PLease Note that the distance after i iterations may be such that it cannot be made with <=i edges.****

	int dist[v];
    memset(dist, INF, sizeof(int) * v);
    dist[0]=0;
    bool change;
    for(int k=0; k<v; k++){// v-1 iterations will give shortest distances if negative cycle not present
        change= false;
        for(int i=0; i<v; i++){ 
            for(int j=0; j<adj[i].size(); j++){
                if(dist[adj[i][j].first] > dist[i] + adj[i][j].second){
                    dist[adj[i][j].first]= dist[i] + adj[i][j].second;
                    change= true;
                }
            }
        }
        if(!change) break;
    }
    if(change) cout<< 1<< endl; // after v iterations edges are changing so cycle present.
    else cout<< 0<< endl;

 *************************************************************************************************************

                        FLoyd- Warshall 
it finds shortest path between any pair of nodes in a graph in O(V^3).
triple loop over every node, outer most being the intermediate node and inner being the src, des, respectively
update dist[i][j], if dist[i][k] + dist[k][j] < dist[i][j];

--------------------------------------------------------------------------------------------------------------

A tree basically is an undirected graph, where any pair of nodes is connected by one and only one path.
    -> should not have cycle.
    -> should be connnected.

------------------------------------------------------------------------------------------------------------------
Bipartite graphs is one in which nodes can be divided into 2 sets of nodes such that any edge connnects vertices from one set to another set only.
--------------------------------------------------------------------------------------------------------------------

Disjoint Set Union Find method 

**  root-> returns the root of the connected component, root is one which has par[a] as a;
** 	root-> while finding root of a node we update its parent as the parent of its parent, so that search for root next time is faster.
** find-> returns true if two nodes have same roots
** Union -> if belong to diff groups we set parent of root of a to root of b, if count[b] > count[a];
** count ensures that we add root of smaller group to root of bigger group and the par[a]= par[par[a]] helps to ensure least skewed data structure of parent array.

int root(int a, int* par){
    while(par[a] != a){
        par[a]= par[par[a]];
        a= par[a];
    }
    return a;
}

bool find(int a, int b, int* par){
    if(root(a, par) == root(b, par))
        return true;
    return false;
}

void Union(int a, int b, int* par, int* count){
    int root_a=root(a, par), root_b= root(b, par);
    
    if(root_a != root_b){
        if(count[root_a] >= count[root_b]){
            par[root_b]= root_a;
            count[root_a]+= count[root_b];
        }
        else{
            par[root_a]= root_b;
            count[root_b]+= count[root_a];
        }
    }
    return;
}

---------------------------------------------------------------------------------------------------------------

Heap and Priority Queue.

min heap and max heap basically works with a constraint that child and parent will have a strict order, while there is no particular order among left and right child.
min heap= parent < children.
max heap= parent > children

heapify basically uses two function one which puts parent in the correct pos, in two heapified children heap and other which iteratively calls this function in bottom up fashion.

the heap data structure is stored in a linear array of n+1 spaces, to make it 1 indexed system
0 pe kuch nhi.
    for parent node at i index, 
        left child is stored at 2*i, right child is stored in 2*i +1;
    rooot is at 1;

void max_heapify (int Arr[ ], int i, int N)// assumes children are heapified already.
{
    int left = 2*i                   //left child
    int right = 2*i +1           //right child
    if(left<= N and Arr[left] > Arr[i] )
          largest = left;
    else
         largest = i;
    if(right <= N and Arr[right] > Arr[largest] )
        largest = right;
    if(largest != i )
    {
        swap (Ar[i] , Arr[largest]);
        max_heapify (Arr, largest,N);
    } 
 }

void build_maxheap (int Arr[ ]) {
	int N= sizeof(arr)/ sizeof(arr[0]) - 1; //number of elements
    for(int i = N/2; i >0 ; i-- )
    {
        max_heapify (Arr, i) ;
    }
}

The total operation takes O(n) time. max_heapify takes log(n) time and it is called at various nodes which have different n -> r for almost n/2 times.

Heap sort // Nlog(N)
It basically heapifies the given array to get max at root ar[1];
then swaps arr[1] and arr[N];
then N= N-1;
and calls max_heapify on arr, 1, N until N ==1; // as the children are heapified already so we have to find correct pos of root only

void heap_sort(int Ar[ ])
{
    int heap_size = N;
    build_maxheap(Arr); // first heapify given array. O(n);
    for(int i = N; i>=2 ; i-- )
    {
        swap(Arr[ 1 ], Arr[ i ]); // max element will be at top take to last and reduce size of array 
        heap_size = heap_size-1;
        max_heapify(Arr, 1, heap_size); //note that heapify is called and not buid_heap because childeren are already heap, just place parent at correct place.
    }
}
--------------------------------------------------------------------------------------------------------

Priority Queue

class pri_q{
    private:
        int len;
        vector<int> pq;

    public:
        pri_q(){
            len=1;
            pq= vector<int>(1, NULL);
        }

        bool empty(){
            if(len== 1) return true;
            return false;
        }

        insert(int a){
        	pq.push_back(a);
        	int i= len;
            while(i > 1 && pq[i] > pq[i/2]){
                swap(i ,i/2);
                i= i/2;
            }
            len= len+1;
        }

        int top(){
            if(pq.size()==1) return NULL;
            return pq[1];
        }

        int pop(){
            if(pq.size()==1) return NULL;
            ans= pq[1];
            pq[1]= pq[len];
            len= len-1;
            max_heapify(1);
            return ans;
        }

        void max_heapify(int i){
            int left= 2*i;
            int right= 2*i+1;
            int largest= i;

            if(left<=len && pq[left] > pq[largest])
                largest= left;
            if(right<=len && pq[right] > pq[largest])
                largest= right;
            
            if(largest != i){
                swap(largest, i);
                max_heapify(largest);
            }
        }

        void swap(int i, int j){
            int temp= pq[i];
            pq[i]= pq[j];
            pq[j]=temp;
        }
};

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
	