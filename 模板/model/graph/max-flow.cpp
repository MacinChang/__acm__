#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#define INF 0x3f3f3f3f
#define OPEN_FILE
#define MAXN 626
using namespace std;

int n;
int win[MAXN], remain[MAXN][MAXN];
struct Edge{
    int from, to, cap, flow;
    //Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f){};
};
bool comp(const Edge& a, const Edge& b){
    return (a.from < b.from || (a.from == b.from && a.to < b.to));
}
struct Dinic{
    int n, m, i, s, t;
    Edge e;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int d[MAXN], cur[MAXN];
    bool vis[MAXN];
    void init(int n){
        this->n = n;
        for (i = 0; i <= n; i++){
            G[i].clear();
        }
        edges.clear();
    }
    void AddEdge(int from, int to, int cap){
        edges.push_back(Edge{ from, to, cap, 0 });
        edges.push_back(Edge{ to, from, 0, 0 });
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool BFS(){
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty()){
            int x = Q.front();
            Q.pop();
            for (i = 0; i < G[x].size(); i++){
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow){
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a){
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++){
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0){
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    int MaxFlow(int s, int t, int need){
        int flow = 0;
        this->s = s;
        this->t = t;
        while (BFS()){
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
            if (flow > need) return flow;
        }
        return flow;
    }
    bool checkFull(int s){
        for (int i = 0; i < G[s].size(); i++){
            if (edges[G[s][i]].flow != edges[G[s][i]].cap){
                return false;
            }
        }
        return  true;
    }
};

int main()
{
#ifdef OPEN_FILE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif // OPEN_FILE
    int T, x;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++){
        scanf("%d", &n);
        memset(win, 0, sizeof(win));
        for (int i = 1; i <= n; i++){
            scanf("%d%d", &win[i], &x);
        }
        memset(remain, 0, sizeof(remain));
        int p = 0;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                scanf("%d", &x);
                if (i == j) continue;
                remain[i][0] += x;
                if (remain[i][j] == 0 && remain[j][i] == 0){
                    remain[i][j] = x;
                    ++p;
                }
            }
        }
        int s = 0, t = n + p + 1, q;
        bool flag, first;
        Dinic ex;
        first = false;
        for (int k = 1; k <= n; k++){
            ex.init(n * n);
            flag = false;
            q = 1;
            int total = win[k] + remain[k][0];
            for (int i = 1; i <= n; i++){
                for (int j = i + 1; j <= n; j++){
                    if (!remain[i][j]) continue;
                    ex.AddEdge(s, q, remain[i][j]);
                    ex.AddEdge(q, p + i, INF);
                    ex.AddEdge(q, p + j, INF);
                    q++;
                }
                if (total - win[i] < 0) {
                    flag = true;
                    break;
                }
                ex.AddEdge(p + i, t, total - win[i]);
            }
            if (flag){
                continue;
            }
            ex.MaxFlow(s, t, INF);
            if (ex.checkFull(0)){
                if (first){
                    printf(" ");
                }
                printf("%d", k);
                first = true;
            }
        }
        printf("\n");
    }
}
