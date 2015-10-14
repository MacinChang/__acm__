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
#define LL long long
#define eps 1e-8
#define INF 0x3f3f3f3f
#define MAXN 2005
//#define OPEN_FILE
using namespace std;

struct TwoSat{
    int n;
    vector<int> G[MAXN*2];
    bool mark[MAXN*2];
    int S[MAXN*2], c;

    bool dfs(int x){
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for(int i = 0; i < G[x].size(); i++){
            if(!dfs(G[x][i])) return false;
        }
        return true;
    }

    void init(int n){
        this->n = n;
        for(int i = 0; i < n * 2; i++){
            G[i].clear();
        }
        memset(mark, 0, sizeof(mark));
    }

    void add_clause(int x, int xval, int y, int yval){
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve(){
        for(int i = 0; i < n * 2; i += 2){
            if(!mark[i] && !mark[i + 1]){
                c = 0;
                if(!dfs(i)){
                    while(c > 0){
                        mark[S[--c]] = false;
                    }
                    if(!dfs(i + 1)){
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

TwoSat p;
int n, T[MAXN][2];
bool check(int diff){
    p.init(n);
    for(int i = 0; i < n; i++){
        for(int a = 0; a < 2; a++){
            for(int j = i + 1; j < n; j++){
                for(int b = 0; b < 2; b++){
                    if(abs(T[i][a] - T[j][b]) < diff){
                        p.add_clause(i, a^1, j, b^1);
                    }
                }
            }
        }
    }
    return p.solve();
}
int main()
{
#ifdef OPEN_FILE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif // OPEN_FILE
    while(~scanf("%d", &n) && n){
        int left = 0, right = 0;
        for(int i = 0; i < n; i++){
            for(int a = 0; a < 2; a++){
                scanf("%d", &T[i][a]);
                right = max(right, T[i][a]);
            }
        }
        while(left < right){
            int mid = left + (right - left + 1) / 2;
            if(check(mid)){
                left = mid;
            }
            else{
                right = mid - 1;
            }
        }
        printf("%d\n", left);
    }
}





















