#include<iostream>
using namespace std;

class DisJoint_Set
{
    vector<int>rank, parent, size;
    //don't use both of this (UnionByRank or UnionBySize) 
public:
    DisJoint_Set(int n) 
    {
        rank.resize(n+1,0);
        parent.resize(n+1,0);
        size.resize(n+1,1);
        for(auto i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    int findUlParent(int node) {
        if(node == parent[node]) return node;
        // Path Compression
        return parent[node] = findUlParent(parent[node]); 
    }
    void UnionByRank(int u,int v) {
        // Time Complexity: O(4 Alfa) 
        int ulp_u = findUlParent(u);
        int ulp_v = findUlParent(v);
        if(ulp_u == ulp_v) return;
        if(rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_u] > rank[ulp_v]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void UnionBySize(int u,int v) {
        // Time Complexity: O(4 Alfa)
        int ulp_u = findUlParent(u);
        int ulp_v = findUlParent(v);
        if(ulp_u == ulp_v) return;
        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
int main() {
    DisJoint_Set ds(7);
    ds.UnionBySize(1,2);
    ds.UnionBySize(2,3);
    ds.UnionBySize(4,5);
    ds.UnionBySize(6,7);
    ds.UnionBySize(5,6);
    if(ds.findUlParent(3) == ds.findUlParent(7)) cout<<"Same"<<endl;
    else cout<<"Not Same"<<endl;
    ds.UnionBySize(3,7);
    if(ds.findUlParent(3) == ds.findUlParent(7)) cout<<"Same"<<endl;
    else cout<<"Not Same"<<endl;
    return 0;
}