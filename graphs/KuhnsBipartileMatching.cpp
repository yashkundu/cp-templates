/**
*    author:  lazyhash(yashkundu)
*    created: 05 Feb, 2023 | 18:31:42
*    O(n*m) O(V*E) worst case - O(n^3)
*    
**/
#include <iostream>
#include <vector>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 

int n, k;
vector<vector<int>> g;
vector<int> mt(k);
vector<bool> used(n), used1(n);

// either saturates the vertex by finding augmenting path
// or the vertex can't be saturated
// iterating over the vertices on left and mapping from right to left in bipartile graph
// it returns true if it succeeds in finding an augmenting path
// if no augmenting path can be find then it is the maximum matching
// iterating over left set (two sets in bipartile graph) and mapping from right to left
bool try_kuhn(int v) {
    if(used[v]) return false;
    used[v] = true;
    for(int u: g[v]) {
        if(mt[u]==-1 || try_kuhn(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // a random heuristic to find an initital mapping for the graph
    // for random graphs, it provides a huge time boost
    // if this is not implemeted then used1 is not needed because then any vertex on left which is not iterated won't be mapped by any vertex in right but in this case it can be initially mapped so used1 is needed
    // n vertices in left and k vertices in right

    // not needed if time not optimised
    mt.assign(k, -1);
    for(int i=0;i<n;i++) {
        for(int u: g[i]) {
            if(mt[u]==-1) {
                mt[u] = i;
                used1[i] = true;
                break;
            }
        }
    }

    for(int i=0;i<n;i++) {
        if(used1[i]) continue;
        used.assign(n, false);
        try_kuhn(i);
    }

    // -------------------------------------------------------------------------
    // without the initial unnecessary heuristic

    mt.assign(k, -1);
    for(int i=0;i<n;i++) {
        used.assign(n, false);
        try_kuhn(i);
    }
 
    
    return 0;
}
