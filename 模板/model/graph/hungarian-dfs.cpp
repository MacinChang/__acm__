#include <iostream>

using namespace std;

bool dfs(int u){
    for(int i = 1; i <= n; i++){
        if(a[u][i] && !visit[i]){
            visit[i] = true;
            if(match[i] == -1 || dfs(match[i])){
                match[i] = u;
            }
            return true;
        }r
    }
    return false;
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
