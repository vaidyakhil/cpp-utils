/*
**  THIS MONOLITH NEEDS TO BE DEPRECATED
*/

Buy n Sell stock problems:
    121: only one transaction allowed, so while traversing, maintain a variable (buy)which stores minimum prices till then, 
        if a val less than it comes, update it, else update profit= max(prices[i]-buy, profit)

    122: Multiple transactions allowed without any fee, so basically 
        if we sell our bought stock on the adjacent high price + initialize update buy to this price and if get lower than that update buy.
            if(prices.size() == 0) return 0;
            int n= prices.size();
            int profit= 0, buy=prices[0];
            for(int i= 1; i<n; i++){
                if(prices[i] > buy)
                    profit+= prices[i] - buy;
                buy= prices[i]; // this occurs every time
            }
            return profit;

    123: Very good problem

        int maxProfit(vector<int>& prices) {
        int n= prices.size();
        if(n == 0) return 0;
        int buy= prices[0], profit[n]={};
        for(int i=1; i<n; i++){
            if(buy > prices[i]){
                buy= prices[i];
                profit[i]= profit[i-1];
            }
            else{
                profit[i]= max(profit[i-1], prices[i] - buy);
            }
        }
        //first make a profit array which stores profit that can be made by making only one transactions till ith day. UPTO THIS
        int sell= prices[n-1], master= profit[n-1];
        for(int i= n-1; i>=0; i--){
            if(sell - prices[i] + profit[i] > master)
                master= sell - prices[i] + profit[i];
            else if( sell < prices[i])
                sell= prices[i];
        }
        return master; // Then make a master profit var, and update it by selling another share at the best price from right till i.
        
    }

// less than more than compare operators compare strings in LEXICOGRAPHIC order

// dp-29 longest common substring, the above procedure will not work, since we want continous part (SUBSTRING). so for that fill up a dp[i][j] which stores LONGEST COMMON SUBSTRING IN S1 and  S2, INCLUDING i th of S1 and j th of S2. SO if char does not match store zero if match store 1 + [i-1][j-1]; DONT KNOW RECURSIVE.   
 dp-27 and optimum binary tree?????????
// some problem may require making pair of var(s), sorting according to one, and dp on other type. (BOX STACKING)

/   [/ dp-21 building bridges max( min(LIS1, LIS2), min(LDS1, LDS2)) is NON SENSICAL!!!!!!! we must first sort pair(North-x, South-x) according to one and then find LIS in other of them. 

//THE EGG DROP PROBLEM!! the divide and conquer technique is not the optimum and that dp is being used to find the optimal floor to start from!, i.e it wont be mid floor.

    //since the number of eggs if broken(niche jaayega) or not broken(upr jaayega) will not be same in divide and conquere the problem won't be log2(n) simply
    //so we use dp to find optimum floor from where to start, so that we calc floor num in minimum attempts.

// 0-1 knapsack do recursion nth element and W weight ke sath, if w[n] > W leave it else return  max of (val[n] + n-1 wala with w= w- w[n]) and (n-1 wala with w). 

//ncr 0c0 1 declare kro;

//matrix multiplication-> at any time we will be multipling 2 matrices, so just travesrse between beg and end to find diffret points of divisions of multiplication
    // e.g AB CD, A  (B CD), A  (BC D) etc.

// in coin change and cutting rod problem, both can be done in simillar fashion, first fill all amounts that can be made from coin[0], then by coin[1] an so on.
// to do so, find number of ways amount- coin[i] can be made and. BASE CASE n(0)= 1; nahi toh repetition avoid krna tough.
//  in cutting rod, take max of cache[i] and cache[i - len[j]];

int main(){
    int t; cin>> t;
    while(t--){
        int n; cin>> n;
        int coin[n];
        for(int i=0; i<n; i++)
            cin>>coin[i];
        int m; cin>>m;
        
        int cache[m+1]= {};
        cache[0]= 1;
        for(int i=0; i< n; i++){
            for(int j= coin[i]; j<=m; j++){
                if(cache[ j - coin[i] ])
                    cache[j]+= cache[ j - coin[i] ];
            }
        }
        cout<< cache[m]<< endl;
    }
    return 0;
}

// edit distance, 
    //we match the letter, if it matches then min steps equals the steps required upto previous letter.
    //if it doesnt match we try all, 1+ delete(n-1, m), replace(n-1, m-1), insert(n, m-1).

// Dynamic Programming

// interviewbit flip Arrays
if(A.empty() || !A.length()) return vector<int >({});//{}
    int i=0, n= A.size();
    for(; i<n; i++)
        if(A[i] == '0' )
            break;
    if(i == n) return vector<int >({});
    int  g_l=i, g_r=i, g_len=1;
    int l= i, r= i;
    int len= 0;
    for(int r= i; r<n; r++){
        len+= ( A[r] == '0' ? 1 : -1);
        if( len <0){
            l= r+1;
            len=0;
        }
        if( len > g_r - g_l +1){
            cout<< r<<"\t";
            g_r= r;
            g_l= l;
            g_len= g_r - g_l +1;
        }
    }
    return vector<int>({g_l+1, g_r+1});
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// rotating an array right by k steps; keep in mind that n numbers have to be swapped, rth will go to (r+k)%n. the loop hole is when updating r u might get to an already updated pos. 
// hence use of beg;
void rotate(vector<int>& nums, int k) {
        if(nums.empty() || nums.size() <=1 || !k) return;
        int n=nums.size();
        k= k%n; if(!k) return;
        int i=n, pos= 0;
        int temp2= nums[(pos+k)%n];
        int temp1= nums[pos];
        int beg=0;
        while(i){
            nums[(pos+k)%n]= temp1;
            temp1= temp2;
            pos= (pos+k)%n;
            if(pos == beg){
                pos=beg+1;
                beg= pos;
                temp1= nums[pos];
            }
            temp2= nums[(pos+k)%n];
            i--;
        }
    }

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// sieve of eratosthenes
// (Marks down non prime numbers by multiples of prime numbers starting from 2, increment count whenever a non zero number is encountered)
// IF USING SEIVE, USE BOOL VECTOR IN PLACE OF ARRAY TO AVOID SEGSEV.
int Solution::isPrime(int A){
    if(A < 2) return 0;
    vector<bool> num(A+1, true);
    long long int i=2;
    while(i <= sqrt(A) ){
        if(num[i]){
            long long int j= i*i;
            while(j <= A){
                num[j]= false;
                j+=i;
            }
        }
        i++;
    }
    return num[A]; 
}

--------------------------------------------------------------------
// Standard Rank in Permutation of given string.

#define mod 1000003
long long int fact(int n){
    if(n < 2) return 1;
    return (n%mod * fact(n-1)%mod)%mod ;
}

int Solution::findRank(string A) {
    if(A.empty() || A.size()<=1 ) return 1;
    long long int n= A.length();
    int rank=0;
    for(int i=0; i<n; i++){
        int count=0;
        for(int j= i+1; j<n; j++){
            if(A[j] < A[i])
                count++;
        }
        rank+= ((count%mod) * fact(n-i-1))%mod;
    }
    return (rank+1)%mod;
}

**************************************************************************************************************

// Snake and Ladder
// DON NOT UPDATE VIS[ adj[s][i]] as if done it will disallow the updation of dist[s] even if better possible.
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define MAX 1000
void bfs(int s, int* dist, vector<int>* adj, bool* vis){
    queue<int> q;
    q.push(s);
    vis[s]= true;
    while(!q.empty()){
        s= q.front();
        vis[s]= true;
        q.pop();
        for(int i=0; i<adj[s].size(); i++){
            if(!vis[ adj[s][i] ]){
                q.push(adj[s][i]);
                if(adj[s].size() == 1 && s!= 29){
                    dist[ adj[s][i] ]= min( dist[ adj[s][i] ], dist[s] );
                else 
                    dist[ adj[s][i] ]=  min( dist[ adj[s][i] ], 1 + dist[s] );
            }
        }
    }    
}

int main(){
    int t; cin>>t; 
    while(t--){
        int n; cin>>n;
        vector<int> adj[31];
        for(int i= 1; i<31; i++)
            for(int j=1; j<=6 && i+j<=30; j++)
                adj[i].push_back(i+j);
        for(int i=0; i<n; i++){
            int x, y;
            cin>>x; cin>>y;
            adj[x].clear();
            adj[x].push_back(y);
        }
        bool vis[31]= {};
        int dist[31];
        for(int i=1; i<31; i++)
            dist[i]= MAX;
        cout<< dist[30] << endl;
    }
    return 0;
}

*************************************************************************************************
Question 3: Given a directed graph where every edge has weight as either 1 or 2, find the shortest path from a given source vertex ???s??? to a given destination vertex ???t???. Expected time complexity is O(V+E).
If we apply Dijkstra???s shortest path algorithm, we can get a shortest path in O(E + VLogV) time. How to do it in O(V+E) time? The idea is to use BFS . One important observation about BFS is, the path used in BFS always has least number of edges between any two vertices. So if all edges are of same weight, we can use BFS to find the shortest path. For this problem, we can modify the graph and split all edges of weight 2 into two edges of weight 1 each. In the modified graph, we can use BFS to find the shortest path. How is this approach O(V+E)? In worst case, all edges are of weight 2 and we need to do O(E) operations to split all edges, so the time complexity becomes O(E) + O(V+E) which is O(V+E).

Question 1: Given a directed weighted graph. You are also given the shortest path from a source vertex ???s??? to a destination vertex ???t???.  If weight of every edge is increased by 10 units, does the shortest path remain same in the modified graph?
The shortest path may change. The reason is, there may be different number of edges in different paths from s to t. For example, let shortest path be of weight 15 and has 5 edges. Let there be another path with 2 edges and total weight 25. The weight of the shortest path is increased by 5*10 and becomes 15 + 50. Weight of the other path is increased by 2*10 and becomes 25 + 20. So the shortest path changes to the other path with weight as 45

*************************************************************************************************

Word Wrap Problem | DP-19

*****************************************************************************

Minimum Cost For Tickets
In a country popular for train travel, you have planned some train travelling one year in advance.  The days of the year that you will travel is given as an array days.  
Each day is an integer from 1 to 365.

Train tickets are sold in 3 different ways:

a 1-day pass is sold for costs[0] dollars;
a 7-day pass is sold for costs[1] dollars;
a 30-day pass is sold for costs[2] dollars.
The passes allow that many days of consecutive travel.  For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

Return the minimum number of dollars you need to travel every day in the given list of days.

// when u know that greedy from start will not work because conditions in future may get better if would have chosen other option before, why not start greedy from back.

int mincostTickets(vector<int>& days, vector<int>& costs) {
        if(days.empty()) return 0;
        int last= days.back() + 30;
        vector<int> cache(last+1, 0);
        for(int i= days.size()-1; i>=0; i--){
            
            cache[ days[i] ] = min({cache[days[i]+1] + costs[0], 
                                   cache[days[i]+7] + costs[1],
                                   cache[days[i]+30] + costs[2]});
            if(i == 0) continue;
            int j= days[i]-1;
            while(j > days[i-1]){
                cache[j]= cache[days[i]];
                j--;
            }
        }
        return cache[days[0]];
    }


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Given an array divide it into M number of contionous subarrays such that the max(sum of individual sub arrays) is minimum.
// when the array is divided into 1 sub array, max of sub arrays is sum of parent array.
// when array is divided into n sub arrays, max of sub arrays is max of parent array.
//now if we vary this max of sub arrays from max(parent) to sum(parent) we will find some where the number of sub arrays == M;
// Binary search is used in this process.
// version of mid= l + (h-l)/2; and npart() > M then l= mid+1; is used because if multiple sums give same M then we choose leftmost wala 

// npages calculates the number of sub arrays created if max is equal to mx; 
int npages(long long int mx, vector<int>& pages){
    long long int sum=0;
    int count= 1;
    for(auto p: pages){
        if( sum+p > mx){
            count++;
            sum=0;
        }
        sum+=p;
    }
    return count;
}
int Solution::books(vector<int> &A, int B) {
    int n= A.size();
    if(n < B) return -1;
    long long int l= A[0], h=0;
    for(int i=0; i<n; i++){
        l= max(l, (long long)A[i]);
        h+= A[i];
    }
    while(l < h){
        long long int mid= l + (h-l)/2;
        if(npages(mid, A) > B)
            l= mid+1;
        else 
            h= mid;
    }
    return l;
}


Write a program to find the n-th ugly number.
Ugly numbers are positive integers which are divisible by a or b or c

#define MAX 2000000001
class Solution {
public:
    int nthUglyNumber(int n, int A, int B, int C) {
        long long int a= (long long)A, b= (long long)B, c= (long long)C;
        long long int ab= a*b/__gcd(a,b), bc= b*c/__gcd(b,c), ca= c*a/__gcd(c,a);
        long long int abc= a*bc/ __gcd(a, bc);
        long long int l= 1, h= MAX;
        while(l<h){
            long long int mid= l + (h - l)/2 ;
            long long int m=  mid/a + mid/b + mid/c - mid/ab - mid/bc - mid/ca + mid/abc; 
            if(m < n)
                l= mid+1;
            else 
                h=mid;
        }
        return l;
    }
};

875
1011
668
719
---------------------------------------------------------------------------------------------------------------------------------------

class Trie{
    private:
        Trie* neighbour[N];
        bool end_key;
    public: 
        Trie(){
            for(int i=0; i<N; i++)
                neighbour[i]= NULL;
            end_key= false;
        }
        void insert(string key){
            int n=key.size();
            Trie* iter= this;
            for(int i=0; i<n; i++){
                if(iter->neighbour[ key[i] - 97] == NULL)
                    iter->neighbour[ key[i] - 97]= new Trie();
                iter= iter->neighbour[ key[i] - 97];
            }
            iter->end_key= true;
        }
        bool search(string key){
            int n=key.size();
            Trie* iter= this;
            for(int i=0; i<n; i++){
                if(iter->neighbour[key[i] -97] == NULL)
                    return false;
                iter= iter->neighbour[key[i] -97];
            }
            return iter->end_key;
        }
};
----------------------------------------------------------------------------------------------------

Modular Exponentiation: // does exponentialtion in log n time.
    mod_exp(int x, int n, int d){
        bool flag= false;
        if(x <0){
            if(n%2 == 1)
                flag= true;
            x= -x;
        }
        long long int res= 1;
        while(n>0){
            if(n%2 == 1)
                res= ((res%d)*(x%d))%d;
            n= n/2;
            x= ((x%d)*(x%d))%d;
        }
        return (flag ? d - res%d : res%d);
    }


Lucas Theorem gives a way to calculate nCr%p where p is a prime number in O(p^2 * logp(n)). So it is useful when p is not very large.
write n and r in base p.
then calculate ni C ri using dp solution, where ni, ri are coeffecients of pi in there respective representation.
ni= n%p, ri= r%p;
now do n= n/p, r= r/p;
repeat.

sliding window que(s): either window size increases or the window slides for maximum  size of something.

// infix to postfix
#include<bits/stdc++.h>
using namespace std;
int  pres(char n){
    if(n == '^') return 3;
    if(n == '*' || n == '/') return 2;
    if(n == '-' || n == '+') return 1;
    return -1;
}    
int main(){
    int t; cin>>t;
    while(t--){
        stack<char> st;
        string ans, txt;
        cin>>txt;
        for(int i=0; i<txt.length(); i++){
            if((txt[i] - 'a' < 26 && txt[i] - 'a' >= 0)
               || (txt[i] - 'A' >= 0 && txt[i] - 'A' < 26)){
                ans+= txt[i];
            }
            else if( txt[i] == '(' ){
                st.push( '(' );
            }
            else if(txt[i] == ')'){
                while(!st.empty() && st.top() != '(' ){
                    char temp= st.top();
                    ans+= temp;
                    st.pop();
                }
                if(!st.empty())
                    st.pop();
            }
            else if(st.empty() || st.top() == '(' || pres(txt[i]) > pres(st.top()) ){
                st.push(txt[i]);
            }
            else{
                while(!st.empty() && st.top() != '(' && pres(txt[i]) <= pres(st.top()) ){
                    ans+=st.top();
                    st.pop();
                }
                st.push(txt[i]);
            } 
        }
        while(!st.empty()){
            ans+= st.top(); st.pop();
        }
        cout<<ans<<endl;
    }
    return 0;
}

NEXT Permutation
    find index where A[i] < A[i+1], then find A[j] such that A[j] > A[i] and closest from the back; swap them and then sort A+i+1, A+n
