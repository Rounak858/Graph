#include<iostream>
using namespace std;

class Solution {
    public:
    static vector<int> dijkstra(int v, vector<vector<int>>adj[] ,int s) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<int>distance(v,INT_MAX);
        // for(int i = 0; i < v; i++) distance[i] = 1e9;

        distance[s] = 0;
        pq.emplace(0,s);

        while(!pq.empty()) {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for(auto it : adj[node]) {
                int edgeWeight = it[1];
                int adjNode = it[0];
                if(dis + edgeWeight < distance[adjNode]) {
                    distance[adjNode] = dis + edgeWeight;
                    pq.emplace(distance[adjNode],adjNode);
                }
            }
        }
        return distance;
    }
};

int main()
{
    // Time Complexity = O(Elog(V)) {E  = number of edges, and V = number of nodes}
    // Space Complexity = O(|E| + |V|) {E  = number of edges, and V = number of nodes}
    constexpr int V = 3, S = 2;
    vector<vector<int>> adj[V];
    vector<vector<int>> edges;
    vector<int> v1{1, 1}, v2{2, 6}, v3{2, 3}, v4{0, 1}, v5{1, 3}, v6{0, 6};
    adj[0].push_back(v1);
    adj[0].push_back(v2);
    adj[1].push_back(v3);
    adj[1].push_back(v4);
    adj[2].push_back(v5);
    adj[2].push_back(v6);

    Solution obj;
    vector<int> res = obj.dijkstra(V, adj, S);

    for (int i = 0; i < V; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}