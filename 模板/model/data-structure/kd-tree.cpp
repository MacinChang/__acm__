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
#define MAXN 100005
using namespace std;
int sum[MAXN * 3], add[MAXN * 3];
void pushup(int t){
	sum[t] = sum[t << 1] + sum[t << 1 | 1];
}
void pushdown(int t, int x){
	if (add[t]){
		add[t << 1] += add[t];
		add[t << 1 | 1] += add[t];
		sum[t << 1] += ((x + 1) >> 1)* add[t];
		sum[t << 1 | 1] += (x >> 1) * add[t];
		add[t] = 0;
	}
}
void update(int L, int R, int t, int p, int q, int x){
	if (p <= L && q >= R){
		sum[t] += (R - L + 1) * x;
		add[t] += x;
		return;
	}

	pushdown(t, R - L + 1);
	int mid = (L + R) >> 1;
	if (p <= mid){
		update(L, mid, t << 1, p, q, x);
	}
	if (q > mid){
		update(mid + 1, R, t << 1 | 1, p, q, x);
	}
	pushup(t);
}
int query(int L, int R, int t, int p, int q){
	if (p <= L && q >= R){
		return sum[t];
	}
	pushdown(t, R - L + 1);
	int mid = (L + R) >> 1;
	int res = 0;
	if (p <= mid)
		res += query(L, mid, t << 1, p, q);
	}
	if (q > mid){
		res += query(mid + 1, R, t << 1 | 1, p, q);
	}
	return  res;
}
void build(int L, int R, int t){
	if (L == R){
		sum[t] = 1;
		return;
	}
	int mid = (L + R) >> 1;
	build(L, mid, t << 1);
	build(mid + 1, R, t << 1 | 1);
	sum[t] = sum[t << 1] + sum[t << 1 | 1];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif // OPEN_FILE
	int n;
	while (~scanf("%d", &n) && n){
		memset(sum, 0, sizeof(sum));
		memset(add, 0, sizeof(add));
		int x, y;
		for (int i = 1; i <= n; i++){
			scanf("%d%d", &x, &y);
			update(1, n, 1, x, y, 1);
		}
		for (int i = 1; i < n; i++){
			printf("%d ", query(1, n, 1, i, i));
		}
		printf("%d\n", query(1, n, 1, n, n));
	}
}
