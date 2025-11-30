#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

int dijkstra(int st,int en,vector<vector<pii>>&adj,int V)
{
    const int INF=1e9;
    vector<int>dist(V+1,INF),parent(V+1,-1);
    dist[st]=0;
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    pq.push({0,st});

    while(!pq.empty())
    {
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u])continue;
        for(auto &edge:adj[u])
        {
            int v=edge.first,w=edge.second;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                parent[v]=u;
                pq.push({dist[v],v});
            }
        }
    }
    if(dist[en]==INF)return -1;

    cout<<"Path\n";
    vector<int>path;
    for(int v=en;v!=-1;v=parent[v])path.push_back(v);
    reverse(path.begin(),path.end());

    for(int i=0;i<path.size();i++)
    {
        if(i+1<path.size())cout<<path[i]<<"-> ";
        else cout<<path[i];
    }
    cout<<"\n";
    return dist[en];
}

int main()
{
    int n,m;
    cout<<"enter vertices and edges:\n";
    cin>>n>>m;
    vector<vector<pii>> adj(n+1);
    cout<<"Enter u v w:\n";
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    int st,en;
    cout<<"enter start and end:\n";
    cin>>st>>en;

    int ans=dijkstra(st,en,adj,n);
    if(ans==-1)cout<<"No path exists\n";
    else cout<<"shortest distance = "<<ans<<"\n";
}
