/**
 * @file ford_fulkerson.cpp
 */
 /**
*   @authors Manasa SK - 2020A7PS0223H  
*   @authors Ayush Agrawal - 2020A7PS0160H
*   @authors Vedant Mathur - 2020A7PS2047H
*   @authors Dhairya Agrawal - 2020A7PS0130H
 */
//  Ford Fulkerson Algorithm brief
/**
  *  @brief The Ford Fulkerson Algorithm is used to find the maximum flow in a flow network.   
*/
#include<bits/stdc++.h>
using namespace std;

double algoTime;

void print(vector<vector<pair<int, pair<int, int>>>> &G){
    /**
        * @brief This function prints the graph G
        * @param vector<vector<pair<int, pair<int, int>>>> G
    */
    for(int i = 0; i<G.size(); i++){
        cout << i << " -> ";
        for(int j = 0; j<G[i].size(); j++){
            cout << G[i][j].first << " " << G[i][j].second.first << " " << G[i][j].second.second << ", ";
        }
        cout << endl;
    }
}

void printResidual(vector<vector<pair<int, pair<int, bool>>>> &rG){
    /**
        * @brief This function prints the residual graph rG
        * @param vector<vector<pair<int, pair<int, bool>>>> rG
    */
    for(int i = 0; i<rG.size(); i++){
        cout << i << " -> ";
        for(int j = 0; j<rG[i].size(); j++){
            cout << rG[i][j].first << " " << rG[i][j].second.first << " " << rG[i][j].second.second << ", ";
        }
        cout << endl;
    }
}

vector<int> parent;
vector<vector<pair<int, pair<int, bool>>>> generateResidual(vector<vector<pair<int, pair<int, int>>>> &G){
    /**
     * @brief This function generates the residual graph from the graph G
     * @param vector<vector<pair<int, pair<int, int>>>> G
     */
    
    vector<vector<pair<int, pair<int, bool>>>> rG(G.size());
    for(int i = 0; i<G.size(); i++){
        for(int j = 0; j<G[i].size(); j++){
            int v = G[i][j].first;
            int f = G[i][j].second.first;
            int c = G[i][j].second.second;
            if(c-f > 0)
                rG[i].push_back({v, {c-f, false}});
            if(f > 0)
                rG[v].push_back({i, {f, true}});
        }
    }
    return rG;
}

bool bfs(vector<vector<pair<int, pair<int, bool>>>> &rG, int s, int t){
    /**
     * @brief This function performs a bfs on the residual graph rG
     * @param vector<vector<pair<int, pair<int, bool>>>> rG
     * @param int s
     * @param int t
     */

    parent.assign(rG.size(), -1);
    vector<bool> visited(rG.size(), false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(u==t)
            break;
        for(int i = 0; i<rG[u].size(); i++){
            int v = rG[u][i].first;
            int f = rG[u][i].second.first;
            if(!visited[v] && f > 0){
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

void decrease(vector<vector<pair<int, pair<int, int>>>> &G, int u, int v, int bottleneck){
    /**
     * @brief This function decreases the flow in the graph G
     * @param vector<vector<pair<int, pair<int, int>>>> G
     * @param int u
     * @param int v
     * @param int bottleneck
     */

    for(int i = 0; i<G[u].size(); i++){
        if(G[u][i].first == v){
            G[u][i].second.first -= bottleneck;
            break;
        }
    }
}

void increase(vector<vector<pair<int, pair<int, int>>>> &G, int u, int v, int bottleneck){
    /**
     * @brief This function increases the flow in the graph G
     * @param vector<vector<pair<int, pair<int, int>>>> G
     * @param int u
     * @param int v
     * @param int bottleneck
     */

    for(int i = 0; i<G[u].size(); i++){
        if(G[u][i].first == v){
            G[u][i].second.first += bottleneck;
            break;
        }
    }
}

int ford_fulkerson(vector<vector<pair<int, pair<int, int>>>> &G, int s, int t){
    /**
     * @brief This function implements the Ford Fulkerson Algorithm
     * @param vector<vector<pair<int, pair<int, int>>>> G
     * @param int s
     * @param int t
     */

    int n = G.size();
    vector<vector<pair<int, pair<int, bool>>>> rG = generateResidual(G);
    while(true){
        // printResidual(rG);
        if(!bfs(rG, s, t))
            break;
        // for(int i = 0; i<n; i++)
        //     cout<<parent[i]<< " ";
        // cout<<endl;
        int bottleneck = INT_MAX;
        for(int i = t; i!=s; i = parent[i]){
            int u = parent[i];
            for(int j = 0; j<rG[u].size(); j++){
                if(rG[u][j].first == i){
                    bottleneck = min(bottleneck, rG[u][j].second.first);
                    break;
                }
            }
        }
        // cout<<bottleneck<<endl;
        // printResidual(rG);
        for(int i = t; i!=s; i = parent[i]){
            int u = parent[i];
            for(int j = 0; j<rG[u].size(); j++){
                if(rG[u][j].first == i){
                    if(rG[u][j].second.second){
                        decrease(G, i, u, bottleneck);
                    }else{
                        increase(G, u, i, bottleneck);
                    }
                }
            }
        }
        rG = generateResidual(G);
    }
    int max_flow = 0;
    for(int i = 0; i<G[s].size(); i++){
        max_flow += G[s][i].second.first;
    }
    return max_flow;
}

void bipartite()
{
    /**
     * @brief This function implements the Ford Fulkerson Algorithm on a bipartite graph
     */
    freopen("input1(bpm).txt", "r", stdin);
    int n, m,k;
    cin >> n >> m >> k; 
    vector<vector<pair<int, pair<int, int>>>> G(n+ m + 2);
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back({n+v, {0, 1}});
    }
    for(int i = 0; i<n; i++)
        G[0].push_back({i+1, {0, 1}});
    for(int i = 0; i<m; i++)
        G[n+i+1].push_back({n+m+1, {0, 1}});
    
    auto start_time = std::chrono::high_resolution_clock::now();
    cout << ford_fulkerson(G, 0, n+m+1) << endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    algoTime = elapsed_time.count();
    // freopen("output1.txt", "a", stdout);
    // cout<<n<<", "<<algoTime<<endl;
}

void normal()
{
    /**
     * @brief This function implements the Ford Fulkerson Algorithm on a normal graph
     */
    freopen("input1.txt", "r", stdin);
    int n, m,s,t;
    cin >> n >> m>>s>>t;
    vector<vector<pair<int, pair<int, int>>>> G(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, {0, w}});
    }
    // print(G);
    auto start_time = std::chrono::high_resolution_clock::now();
    cout << ford_fulkerson(G, s, t) << endl;
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;
    algoTime = elapsed_time.count();
    freopen("output1.txt", "a", stdout);
    cout<<n<<", "<<algoTime<<endl;
}

int main()
{
    /** 
        * @brief Main function
        * First it takes the input from the file input.txt
        * Then it calls the ford_fulkerson function
        * Then it prints the maximum flow
        * @returns 0 on exit

    */
    // normal();
    bipartite();
    return 0;
}