typedef pair<int, int> Pr;

class GraphUtils {
	/*
	** There are (directed, undirected) x (weighted, unweighted), (connected, disconnected, strongly connected) 
	** * (cyclic, acycli) x (positive edge, negative edge) graphs
	** These are important classifications of graph properties ^^
	** connected -> there exists a path either or from u, v or v,u;
	** disconnected -> there exist atleast 1 u,v for which no path exist for either u -> or v->u
	*/

	/*
	** Among different impl(s) of graph represented, adjacency list with list implemented as BSTs is the optimal sol
	** among others adjacency matrix, adjacency list with array or linked list as other options
	*/

	/*
	** Mathematically speaking
	** A tree basically is an undirected graph, where any pair of nodes is connected by one and only one path.
	    -> should not have cycle.
	    -> should be connnected.
	*/

	private:

		/*
		**	TRAVERSALS
		**	BFS(queue) and DFS(stack) for both directed / undirected is SAME.
		**	start with one node, vis[start] = true; ds.push(start); then follow the loop:
			while(!dataStruct.empty()){
				s= dataStruct.top()/front();
				dataStruct.pop();
				for(int i=0; i<adj[s][i].size();  i++){
					if(!vis[adj[s][i]]){
						dataStruct.push(adj[s][i]);
						vis[adj[s][i]]= true;
					}
				}
			}
		*/

		/*
		** 	BFS
		**	recursive of this will be very simple ^^, simply code inside the while, and basic checks 
		*/
		void iterativeBfs(int n, int start, vector<int> adj[], vector<int>& res) {
			// todo: check if adj is being passed as value or ref
			
			/*
			**	I think it should be ref only, 
			**	since names we give to an array are simply const pointer, pointing to 0th element
			*/

	        if (n < 1) {
	            return;
	        }
        
	        vector<bool> visited = vector<bool>(n, false);
	        queue<int> que;
	        
	        
	        que.push(0);
	        visited[0] = true;
	        while (!que.empty()) {
	            int cur = que.front();
	            que.pop();
	            
	            for (int i=0; i<adj[cur].size(); i++) {
	                if (!visited[adj[cur][i]]) {
	                    que.push(adj[cur][i]);
	                    visited[adj[cur][i]] = true;
	                }
	            }
	            
	            res.push_back(cur);
	        }
	        return;
		}

		/*
		** 	DFS (parent -> child -> child ->child) (not the other way around)
		**	recursive of this will be very simple ^^, simply code inside the while, and basic checks 
		*/
		void iterativeDfs(int n, int start, vector<int> adj[], vector<int>& res) {

	        if (n < 1) {
	            return;
	        }
        
	        vector<bool> visited = vector<bool>(n, false);
	        stack<int> st;
	        
	        st.push(0);
	        visited[0] = true;
	        while (!st.empty()) {
	            int cur = st.top();
	            st.pop();
	            
	            for (int i=0; i<adj[cur].size(); i++) {
	                if (!visited[adj[cur][i]]) {
	                    st.push(adj[cur][i]);
	                    visited[adj[cur][i]] = true;
	                }
	            }
	            
	            res.push_back(cur);
	        }
	        return;
		}

		/*
		** 	CYCLE DETECTION
		** 	this is just dfs along with keeping track of nodes which are part of current traversal
		** 	We are checking if we are reaching a node which is already part of the current traversal
		**	if thats the case cycle exists.
		** 	in undirected graph pass along the parent as well
		**	so that it can be ignored in the neighbors of children nodes
		*/
	    bool detectCycleIterative (int n, int start, vector<bool>& visited, vector<int> adj[]) {
	        stack<int> st;
	        vector<bool> inCurPath(n, false);
	        
	        visited[start] = true;
	        inCurPath[start] = true;
	        st.push(start);
	        
	        while (!st.empty()) {
	            int cur = st.top();
	            
	            bool foundNew = false;
	            for (int i=0; i<adj[cur].size(); i++) {
	                if (inCurPath[adj[cur][i]]) {
	                    return true;
	                } else if (!visited[adj[cur][i]]){
	                    foundNew = true;
	                    visited[adj[cur][i]] = true;
	                    inCurPath[adj[cur][i]] = true;
	                    st.push(adj[cur][i]);
	                    break;
	                }
	            }
	            
	            if (!foundNew) {
	                inCurPath[cur] = false;
	                st.pop();
	            }
	        }
	        return false;
	    }

	    bool detectCycleRecursively (int start, vector<bool>& visited, vector<bool>& inCurPath, vector<int> adj[]) {
	        visited[start] = true;
	        inCurPath[start] = true;

			int cur = st.top();
	        for (int i=0; i<adj[cur].size(); i++) {
                if (inCurPath[adj[cur][i]]) {
                    return true;
                } else if (!visited[adj[cur][i]]){
                	bool res = detectCycleRecursively(adj[cur][i], visited, inCurPath, adj);
                	if (res) {
                		return true;
                	}
                }
            }
        	inCurPath[cur] = false;
            return false;
	    }

        void createAdjList (vector<vector<int>>& edges, vector<int> adj[]) {
	        for (int i=0; i<edges.size(); i++) {
	            adj[edges[i][0]].push_back(edges[i][1]);
	        }
	    }

    public:
    	bool FindCycle (int n, vector<int> adj[]) {
	        if (n < 1) {
	            return true;
	        }
	        
	        vector<bool> visited(n, false);
	        
	        for (int i =0; i<n; i++) {
	            if (!visited[i]) {
	            	vector<bool> inCurPath(n, false);
	                if (detectCycle(i, visited, inCurPath, adj)) {
	                    return true;
	                }
	            }
	        }
	        
	        return false;
    	}

    	/*
		** 	for every edge from (u, v), u should come before v
		**	Hence applicable for DAGs only
		**	compute inDegrees, push those with inDegree 0 in que
		** 	there will surely be atleast one as graph is DAG
		**	run through the que, reduce indegree of the immediate neighbours and push in que if inDegree reduces to 0
    	*/
		vector<int> getTopoLogicalSort(int V, vector<int> adj[]) {
		    vector<int> res;
		    if (V < 1) {
		        return res;
		    }
		    
		    vector<int> inDegree(V, 0);
		    for (int i=0; i<V; i++) {
		        for (int j=0; j<adj[i].size(); j++) { 
		            inDegree[adj[i][j]]++;
		        }
		    }
		    
		    queue<int> que;
		    
		    for (int i=0; i<V; i++) {
		        if (inDegree[i] == 0) {
		            que.push(i);
		        }
		    }
		    
		    while (!que.empty()) {
		        int cur = que.front();
		        que.pop();
		        
		        res.push_back(cur);
		        
		        for (int i=0; i<adj[cur].size(); i++) {
		            if (inDegree[adj[cur][i]] != 0) {
		                inDegree[adj[cur][i]]--;
		                if (inDegree[adj[cur][i]] == 0) {
	    	                que.push(adj[cur][i]);
		                }
		            }
		        }
		    }
		    
		    return res;
		}

		/*
	    **	after function returns, reverse res to get result
	    */
	    void recursiveTopo(vector<vector<int>>& adj, int src, vector<bool>&visited, vector<int>& res) {
	    	if (visited[src]) {
	    		return;
	    	}

    		for (int i=0; i<adj[src].size(); i++) {
    			recursiveTopo(adj, adj[src][i], visited);
    		}

    		// we can mark this visited before loop also no issue
    		visited[src] = true;
    		res.push_back(src);
    		return;
	    }

    	/*
    	**	SHORTEST DISTANCE
    	**	For unweighted graphs, simply BFS will give shortest path for both directed/undirected graph
    	*/

		/*
    	**	Floyd-Warshall
    	**	find sd b/w every pair of nodes on a given weighted graph
    	**	T-> O(n3), S->O(n2)
    	*/
    	void floydWarshall(vector<vector<int>>& adj) {
	    	/*
	    	**	adj[i][j] == -1 if no {i, j} does not exist in edges]
	    	** 	adj[i][j] = dist(i -> j)
	    	** 	directed/ undirected weighted graph (can have negative weights as well)
			*/
			
			int n = adj.size();
    		vector<vector<int>> dist(n, vector<int>(n, -1));
		    
		    for (i = 0; i < V; i++)
    			for (j = 0; j < V; j++)
        			dist[i][j] = graph[i][j];

			for (int k=0; k<n; k++) {
				// take every possible node k as intermediate node for src, dest nodes i, j
				for (int i=0; i<n; i++) {
					for (int j=0; j<n; j++) {
						if (dist[i][k] != -1 && dist[k][j] != -1) {
							dist[i][j] = dist[i][j] == -1 ? dist[i][k] + dist[k][j] 
								: min(dist[i][j], dist[i][k] + dist[k][j]);
						}
					}
				}
			}
    	}


    	/*
    	**	Dijkstra's algo is a greedy algo:
    	**	gets u shortest dist of all nodes from src
    	**	we constantly optimize the dist of the node which is currently the shortest.
    	**	we add neighbours to a minimal heap, pick the nearest one and mark it visited
    	** 	and update its distance 
    	**	edges cannot have -ve weights.
    	**	Dijkstras using priority_queue time complexity O(Elog(V)
    	**	Normal Dijkstras time complexity O(V^2) (without priority queue);
    	**	edges: (ui, vi, wi), to make adjacency matrix
    	**	dist is the adjacency matrix (n x n)
    	*/
	    void dijkstra(vector<vector<int>>& edges, int src, vector<vector<int>>& dist) {
	        int n = dist.size();
	        vector<bool> visited(n
	        	, false);
	        for (int i=0; i<edges.size(); i++) {
	            dist[edges[i][0]][edges[i][1]] = edges[i][2];
	        }
	        
	        priority_queue<Pr, vector<Pr>, greater<Pr>> pq;
	        pq.push({ 0, src });
	        while (!pq.empty()) { 
	            int curDist = pq.top().first;
	            int curNode = pq.top().second;
	            pq.pop();
	            if (visited[curNode]) {
	                continue;   
	            }
	            visited[curNode] = true;
	            dist[src][curNode] = curDist;
	            for (int i=1; i<n; i++) {
	                if (visited[i] == false && dist[curNode][i] != -1) {
	                    pq.push({dist[curNode][i] + curDist, i});
	                }
	            }
	        }
	        return;
	    }

    	/*
    	**	Bellman Ford's algo is a dynamic programming algo:
    	**	gets u shortest dist of all nodes from src
    	** 	works with negative edge (if no negative edge cycle is detected)
    	** 	Logic behind is: 
    	**	->	given a graph with v nodes, shortest path to every node will have <= v-1 edges.
    		->	first relax sd for all nodes with 0 edges, then 1 then 2 etc..
    		->	0th iteration relaxes src' sd to src => 0
    		->	AT ith ITERATION, THIS ALGO GIVES SD TO A NODE FROM SRC BY USING MAXM i EDGES.

		** 	VERY IMPORTANT:
		**	use 1D dp when all you want is SDs for the given graph, src
			->	After i iterations, the dist of a node is such that 
			no better dist(smaller) can be made using <= i edges.
			->	Please Note that the distance after i iterations may be such that it cannot be made with <=i edges

		**	use 2D dp when we want SD to node using k edges from src, (k x v)(before every i, dp[i][src] = 0)
    	*/
	    void bellManFord(int v, int src, vector<vector<int>>& edges, vector<vector<int>>& dist) {
	    	vector<int> dist(v, INT_MAX);
		    dist[src]=0;
		    bool change;
		    for(int k=0; k<v; k++) {// v-1 iterations will give shortest distances if negative cycle not present
		        change= false;
		        for(int i=0; i<edges.size(); i++){
		        	int intermediate = edges[i][0];
		        	int dest = edges[i][1];
		        	int edgeLen = edges[i][2];
		        	if (dist[intermediate] != INT_MAX) {
		        		int newLen = dist[intermediate] + edgeLen;
		        		if ( newLen < dist[dest]) {
		        			dist[dest] = newLen;
		        			change= true;
		        		}
		        	}
		        }
		        if(!change) break;
		    }

		    if (change) {
		    	// negative edge cycle detected
		    	dist = vector<int>();
		    	return;
		    }
		    return;
	    }
}