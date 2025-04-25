#include<iostream>
#include <list>
using namespace std;

class Solution{
    public:
    vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m,vector<pair<pair<int, int>, int>> &g) {
        unordered_map<int,list<pair<int,int>>>adj;
        for (size_t i = 0; i < g.size(); i++)
        {
            auto u = g[i].first.first;
            auto v = g[i].first.second;
            auto w = g[i].second;
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }
        // priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        // pq.push({0,1});
        // vector<int>key(n+1, INT_MAX),parent(n+1,-1),visited(n+1,0);
        // parent[1] = -1;
        // while(pq.size()) {
        //     int w = pq.top().first;
        //     int node = pq.top().second;
        //     visited[node] = 1;
        //     pq.pop();
        //     for(auto it : adj[node]) {
        //         int adjNode = it.first;
        //         int edW = it.second;
        //         if(visited[adjNode] == 0 && edW < key[adjNode]) {
        //             key[adjNode] = edW;
        //             parent[adjNode] = node;
        //             pq.push({edW,adjNode});
        //         }
        //     }
        // }
        vector<int>key(n+1);
        vector<int>mst(n+1);
        vector<int>parent(n+1);
        for(int i = 0;i<=n;i++) {
            key[i] = INT_MAX;
            parent[i] = -1;
            mst[i] = false;
        }
        // Let's start the algo
        key[1] = 0;
        parent[1] = -1;
        for(int i = 1;i < n; i++) {
            int mini = INT_MAX;
            int u;
            for(int v = 1;v <= n; v ++) {
                // find the min node
                if(mst[v] == false && key[v] < mini) {
                    u = v;
                    mini = key[v];
                }
            }
            // mark min node as a true
            mst[u] = true;
            // check adjacent nodes
            for(auto it : adj[u]) {
                int v = it.first;
                int w = it.second;
                if(mst[v] == false && w < key[v]) {
                    parent[v] = u;
                    key[v] = w;
                }
            }
        }
        vector<pair<pair<int, int>, int>>result;
        for(int i = 2; i <= n; i++) {
            result.push_back({{parent[i],i},key[i]});
        }
        return result;
    }
};

int main() {
    // Example usage:
    int n = 5, m = 6;
    vector<pair<pair<int, int>, int>> g = {
        {{1, 2}, 2},
        {{1, 3}, 1},
        {{2, 3}, 1},
        {{3, 4}, 2},
        {{4, 5}, 1},
        {{5, 3}, 2}
    };
    
    Solution sol;
    vector<pair<pair<int, int>, int>> mst = sol.calculatePrimsMST(n, m, g);
    
    for (auto edge : mst) {
        cout << edge.first.first << " - " << edge.first.second << " : " << edge.second << endl;
    }
    
    return 0;
}