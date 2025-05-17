#include<iostream>
#include<set>
using namespace std;

class Solution {
    public:
    static vector<int>Dijkstra(int v, vector<vector<int>>adj[], int s) {
        set<pair<int,int>> st;
        vector<int>distance(v,INT_MAX);
        st.insert({0,s});
        distance[s] = 0;

        while(!st.empty()) {
            auto it = *(st.begin());
            int node = it.second;
            int dis = it.first;
            st.erase(it);

            for(auto itt : adj[node]) {
                int adjNode = itt[0];
                int edjWeight = itt[1];

                if(dis + edjWeight < distance[adjNode]) {
                    if(distance[adjNode != 1e9]) {
                        st.erase({distance[adjNode],adjNode});
                    }
                    distance[adjNode] = dis + edjWeight;
                    st.insert({distance[adjNode],adjNode});
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
    vector<int> res = obj.Dijkstra(V, adj, S);

    for (int i = 0; i < V; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}