class AlgosV2 {
private:
	int _dsu_getRoot(int a, vector<int>& par, vector<int>& count) {
		while (par[a] != a) {
			count[par[a]]-= count[a];
			par[a] = par[par[a]];
			count[par[a]]+= count[a];
			a = par[a];
		}
		return a;
	}

	public:
		/*
		**	DISJOINT SET UNION
		**  _dsu_getRoot-> returns the root of the connected component, root is one which has par[a] as a;
		** 	root-> while finding root of a node we update its parent as the parent of its parent, 
		**	so that search for root next time is faster.
		**	dsu_find-> returns true if two nodes have same roots
		** 	Union -> if belong to diff groups we set parent of root of a to root of b, if count[b] > count[a];
		** 	count ensures that we add root of smaller group to root of bigger group and the par[a]= par[par[a]] helps to ensure least skewed data structure of parent array.
		*/

		bool dsu_find(int a, int b, vector<int>& par, vector<int>& count){
		    return _dsu_getRoot(a, par, count) == _dsu_getRoot(b, par, count);
		}

		void dsu_union(int a, int b, vector<int>& par, vector<int>& count){
		    int root_a=root(a, par), root_b= root(b, par);
		    
		    if(root_a != root_b) {
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


		/*
		**	Monotonous Stack problems:
		**	IMP ones being: rain water trapping and area in histogram
		**	In mono stack problems what we do is we push an element in stack if some condition is met,
		**	else we start poping elements untill condition is met,
		**	meanwhile calculate the possible res using the elements that are getting popped
		** 	since these elements we won't encounter again.
		** 	In this way mono stack approach sometimes results in O(n) time complexity
		**	for eg. see problem_solutions::trap for rain water problem
		*/


} 
