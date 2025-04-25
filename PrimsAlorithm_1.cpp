#include<iostream>
using namespace std;

class Solution{
    // minimam spaning tree
    public:
    int spanningTree(int v, vector<vector<int>>adj[]) {
        // min-heap procedure
        priority_queue
            <pair<int,int>,
            vector<pair<int,int>>, 
            greater<pair<int,int>>
        >pq;
        vector<int>visited(v,0);
        int sum = 0;
        pq.push({0,0});
        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int weight = it.first;
            if(visited[node] == 1) continue;
            visited[node] = 1;
            sum += weight;
            for(auto it : adj[node]){
                int adjNode = it[0];
                int edW = it[1];
                if(!visited[adjNode]) {
                    pq.push({edW,adjNode});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> edges = {{0,1,2}, {0,2,1}, {1,2,1}, {2,3,2}, {3,4,1}, {4,2,2}};
    vector<vector<int>>adj[V];
    for(auto it : edges) {
        vector<int>tenp (2);
        tenp[0] = it[1];
        tenp[1] = it[2];
        adj[it[0]].push_back(tenp);
        tenp[0] = it[0];
        tenp[1] = it[2];
        adj[it[1]].push_back(tenp);
    }
    Solution s;
    int sum = s.spanningTree(V,adj);
    cout << "The sum of all the edges weight: " <<sum <<endl;
    return 0;
}