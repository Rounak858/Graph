#include<iostream>
using namespace std;

class DisJoint_Set
{
    vector<int> parent, size;
    // Use either UnionByRank or UnionBySize, not both in the same algorithm
public:
    DisJoint_Set(int n) 
    {
        parent.resize(n+1,0);
        size.resize(n+1,1);
        for(auto i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    int findUlParent(int node) {
        // if(node == parent[node]) return node;
        // Path Compression
        return parent[node] == node ? node : parent[node] = findUlParent(parent[node]); 
    }
    void UnionBySize(int u,int v) {
        // Time Complexity: O(4 Alfa)
        int parent_U = findUlParent(u);
        int parent_V = findUlParent(v);
        if(parent_U == parent_V) return;
        if(size[parent_U] < size[parent_V]) {
            parent[parent_U] = parent_V;
            size[parent_V] += size[parent_U];
        }
        else {
            parent[parent_V] = parent_U;
            size[parent_U] += size[parent_V];
        }
    }
};
class Solution {
public:
    int spanningTree(int n, vector<vector<int>> adj[]) {
        vector<pair<int,pair<int,int>>>edges;
        for(auto i = 0;i < n;i++) {
            for(auto it : adj[i]) {
                int adjNode = it[0];
                int weight = it[1];
                // int node = i;
                // edges.push_back({weight,{node,adjNode}});
                if (i < adjNode) // Avoid duplicate edges
                    edges.push_back({weight, {i, adjNode}});
            }
        }
        DisJoint_Set ds(n);
        sort(edges.begin(),edges.end());
        int mstwt = 0;
        for(auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            if(ds.findUlParent(u) != ds.findUlParent(v)) {
                mstwt += wt;
                ds.UnionBySize(u,v);
            }
        }
        return mstwt;
    }
};
int main() {
    // constexpr is use for compile time constant
    constexpr int V = 4 ; // number of vertices 
    
    vector<vector<int>> adj[V];

    // Undirected weighted edges: (u, v, weight)
    vector<tuple<int, int, int>> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    /*This is structured binding (available in C++17 and above)
    letting you unpack the tuple directly into variables.*/

    for (auto [u, v, wt] : edges) {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); // since the graph is undirected
    }
    // this is a tradional method for unpack the tuple
    // for (auto edge : edges) {
    //     int u = get<0>(edge);
    //     int v = get<1>(edge);
    //     int wt = get<2>(edge);
    //     adj[u].push_back({v, wt});
    //     adj[v].push_back({u, wt});
    //     // ...
    // }
    
    Solution sol;
    int mstWeight = sol.spanningTree(V, adj);
    cout << "Weight of the Minimum Spanning Tree is: " << mstWeight << endl;
    return 0;
}
