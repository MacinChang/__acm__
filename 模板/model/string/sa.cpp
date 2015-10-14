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
#define OPEN_FILE
#define MAXN 2005
using namespace std;
char str[MAXN];
int m, dn;
int s[MAXN], sa[MAXN], height[MAXN], p[MAXN], q[MAXN], c[MAXN];
int ranK[MAXN];
int f[MAXN * 2][45];

void getSa(){
	for (int i = 0; i < dn; i++){
		p[i] = s[i];
		c[s[i]]++;
	}
	for (int i = 1; i < m; i++){
		c[i] += c[i - 1];
	}
	for (int i = dn - 1; i >= 0; i--){
		sa[--c[p[i]]] = i;
	}
	for (int k = 1; k <= dn; k *= 2){
		int t = 0;
		for (int i = dn - k; i < dn; i++){
			q[t++] = i;
		}
		for (int i = 0; i < dn; i++){
			if (sa[i] >= k){
				q[t++] = sa[i] - k;
			}
		}
		for (int i = 0; i < m; i++){
			c[i] = 0;
		}
		for (int i = 0; i < dn; i++){
			c[p[q[i]]]++;
		}
		for (int i = 0; i < m; i++){
			c[i] += c[i - 1];
		}
		for (int i = dn - 1; i >= 0; i--){
			sa[--c[p[q[i]]]] = q[i];
		}

		swap(p, q);
		t = 1;
		p[sa[0]] = 0;
		for (int i = 1; i < dn; i++){
			if (q[sa[i - 1]] == q[sa[i]] && q[sa[i - 1] + k] == q[sa[i] + k]){
				p[sa[i]] = t - 1;
			}
			else{
				p[sa[i]] = t++;
			}
		}
		if (t >= dn) break;
		m = t;
	}

}

void getHeight(){
	for (int i = 0; i < dn; i++){
		ranK[sa[i]] = i;
	}
	int k = 0;
	for (int i = 0; i < dn; i++){
		if (k != 0) k--;
		int j = sa[ranK[i] - 1];
		while (s[i + k] == s[j + k]){
			k++;
		}
		height[ranK[i]] = k;
	}
}

int rmq(int x, int y){
	x = ranK[x];
	y = ranK[y];
	if (x > y){
		swap(x, y);
	}
	x++;
	int k = (int)(log((double)(y - x + 1.0)) / log(2.0));
	return  min(f[x][k], f[y - (1 << k) + 1][k]);
}

int main()
{
#ifdef OPEN_FILE
	//freopen("in.txt", "r", stdin);
	//freopen("palindromes.in", "r", stdin);
	//freopen("palindromes.out", "w", stdout);
#endif // OPEN_FILE
	while (~scanf("%s", str)){
		memset(p, 0, sizeof(p));
		memset(q, 0, sizeof(q));
		memset(c, 0, sizeof(c));
		memset(height, 0, sizeof(height));
		memset(ranK, 0, sizeof(ranK));
		memset(s, 0, sizeof(s));
		int n = strlen(str);
		for (int i = 0; i < n; i++){
			s[i] = str[i];
			s[2 * n - i] = s[i];
		}
		s[n] = 124;
		dn = n * 2 + 2;
		m = 130;
		getSa();
		getHeight();
		dn--;

		//initial rmq
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= dn * 2 + 1; i++)
			f[i][0] = height[i];
		for (int j = 1; (1 << j) <= 2 * dn + 1; j++)
		for (int i = 1; i + (1 << j) - 1 <= 2 * dn + 1; i++)
			f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);

		int ans = 0;
		int pos = 0;
		//single
		int temp = rmq(0, 2 * n);
		ans = max(ans, temp * 2 - 1);
		for (int i = 1; i < n; i++){
			//odd
			int temp = rmq(i, 2 * n - i) * 2 - 1;
			if (ans < temp){
				ans = temp;
				pos = i;
			}
			//even
			temp = rmq(i, 2 * n - i + 1) * 2;
			if (ans < temp){
				ans = temp;
				pos = i;
			}
		}
		if (ans % 2 == 0){
			for (int i = pos - ans / 2; i <= pos + ans / 2 - 1; i++){
				printf("%c", str[i]);
			}
		}
		else{
			for (int i = pos - ans / 2; i <= pos + ans / 2; i++){
				printf("%c", str[i]);
			}
		}
		printf("\n");
	}
}
