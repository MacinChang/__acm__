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
#define INF 0x3f3f3f3f
//#define OPEN_FILE
#define MAXN 10005
#define MAXM 30005
using namespace std;

int euler[MAXM], deep[MAXM], pos[MAXN];
int f[20][MAXN];
vector<int>G[MAXN];
bool vis[MAXN];
int top;
int cnt[MAXN];
void dfs(int t, int x)
{
	if (pos[x] == -1)
		pos[x] = top;
	deep[top] = t;
	euler[top++] = x;

	for (int i = 0; i < G[x].size(); i++)
	{
		dfs(t + 1, G[x][i]);
		deep[top] = t;
		euler[top++] = x;
	}
}

void rmq(int n)
{
	for (int i = 1; i <= n; i++)
		f[0][i] = deep[i];
	for (int j = 1; j <= (int)(log((double)n) / log(2.0)); j++){
		for (int i = 1; i <= n - (1 << j) + 1; i++){
			f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
		}
	}
}

int get(int x, int y)
{
	if (x > y){
		swap(x, y);
	}
	int k = (int)(log((double)(y - x + 1.0)) / log(2.0));
	int temp = min(f[k][x], f[k][y - (1 << k) + 1]);
	for (int i = x; i <= y; i++)
	if (deep[i] == temp)
		return euler[i];
}

int main()
{
#ifdef OPEN_FILE
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif // OPEN_FILE
	int n;
	int a, num, b;
	int root;
	int m, x, y;
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++){
		scanf("%d", &n);
		top = 1;
		memset(pos, -1, sizeof(pos));
		memset(cnt, 0, sizeof(cnt));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++)
			G[i].clear();
		for (int i = 1; i < n; i++)
		{
			scanf("%d %d", &x, &y);
			vis[y] = true;
			G[x].push_back(y);
		}

		for (int i = 1; i <= n; i++){
			if (!vis[i]){
				root = i;
				break;
			}
		}
		dfs(0, root);
		rmq(2 * n - 1);
		scanf("%d %d", &x, &y);
		printf("%d\n", get(pos[x], pos[y]));
	}
	return 0;
}
