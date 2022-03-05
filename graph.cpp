/*
**  THIS MONOLITH NEEDS TO BE DEPRECATED
*/

--------------------------------------- 
Traversals->BFS, DFS, Topological sort, 
Cycle detection, 
Shortest Path -> (Dijkstras, Bellman-Ford, Floyd-Warshall), 
Bipartite, Disjoint Set Union method,
Minimum Spanning Tree-> ( Kruskal, Prims ( Heap(min, max), priority queue ) 
--------------------------------------------------------------------------------------------------------------------------

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
