
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
