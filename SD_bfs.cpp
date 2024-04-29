#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
class Graph{
    int vertices;
    vector<vector<int>>edges;
public:
     Graph(int n){
        vertices=n;
        cout<<"Enter number of edges"<<"\n";
        edges.resize(n);
        int m;
        cin>>m;
        while(m--){
            int a,b;cin>>a>>b;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }
    void pbfs(){
        double start_time = omp_get_wtime();
        queue<int>q;
        vector<int>vis(vertices);
        if(vertices==0)return;
        cout<<"enter start node: "<<"\n";
        int st;
        cin>>st;
        q.push(st);
        cout<<st<<"\n";
        vis[st]=1;
        while(!q.empty()){
            int node;
            #pragma omp critical
            {
                node=q.front();
                q.pop();
            }
            #pragma omp parallel for
            for(int i = 0; i < edges[node].size(); ++i){
                int n = edges[node][i];
                if(!vis[n]){
                    cout<<n<<"\n";
                    vis[n]=1;
                    #pragma omp critical
                    q.push(n);
                }
            }
        }
        cout<<"end"<<"\n";
        double end_time = omp_get_wtime();
        cout << "Parallel BFS completed in " << end_time - start_time << " seconds" << endl;
    }
    void pdfs(){
        double start_time = omp_get_wtime();
        stack<int>s;
        vector<int>vis(vertices);
        if(vertices==0)return;
        cout<<"enter start node:"<<"\n";
        int st;
        cin>>st;
        s.push(st);
        vis[st]=1;
        while(!s.empty()){
            int node;
            #pragma omp critical
            {
            node=s.top();
            s.pop();
            }
            cout<<node<<"\n";
            #pragma omp parallel for
            for(int i = 0; i < edges[node].size(); ++i){
                int n = edges[node][i];
                if(!vis[n]){
                    #pragma omp critical
                    s.push(n);
                    vis[n]=1;}
            }
        }
        cout<<"end"<<"\n";
        double end_time = omp_get_wtime();
        cout << "Parallel DFS completed in " << end_time - start_time << " seconds" << endl;
    }

    void bfs() {
        double start_time = omp_get_wtime();
        queue<int> q;
        vector<int> vis(vertices);
        if (vertices == 0) return;
        cout << "Enter start node for BFS: " << "\n";
        int st;
        cin >> st;
        q.push(st);
        cout << st << "\n";
        vis[st] = 1;
        while (!q.empty()){
            int node = q.front();
            q.pop();
            for (int i = 0; i < edges[node].size(); ++i){
                int n = edges[node][i];
                if (!vis[n]){
                    cout << n << "\n";
                    vis[n] = 1;
                    q.push(n);
                }
            }
        }
        double end_time = omp_get_wtime();
        cout << "BFS completed in " << end_time - start_time << " seconds" << endl;
    }

    void dfs() {
        double start_time = omp_get_wtime();
        stack<int> s;
        vector<int> vis(vertices);
        if (vertices == 0) return;
        cout << "Enter start node for DFS: " << "\n";
        int st;
        cin >> st;
        s.push(st);
        vis[st] = 1;
        while (!s.empty()){
            int node = s.top();
            s.pop();
            cout << node << "\n";
            for (int i = 0; i < edges[node].size(); ++i){
                int n = edges[node][i];
                if (!vis[n]){
                    s.push(n);
                    vis[n] = 1;
                }
            }
        }
        double end_time = omp_get_wtime();
        cout << "DFS completed in " << end_time - start_time << " seconds" << endl;
    }

};
int main(){
int n;
cout<<"Enter number of vertices"<<"\n";
cin>>n;
Graph g=Graph(n);
g.bfs();
g.dfs();
g.pbfs();
g.pdfs();
return 0;
}