const int ALPHA = 26;
const int LEN = 1000;
unsigned int bt[ALPHA][LEN];
unsigned int xprev[LEN], x[LEN], y[LEN];
void set_bit(unsigned int *a, int i) {
    int q = i / 32;
    int p = i % 32;
    a[q] ^= (1ll << p);
}
int lcs(const string& s, const string& w) {
    int n = (int)s.size();
    int m = (int)w.size();
    for (int i = 0; i < m; i++) {
        set_bit(bt[w[i] - 'a'], i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m / 32; j++) {
            xprev[j] = x[j];
            x[j] = 0;
        }
        for (int j = 0; j <= m / 32; j++) {
            int ylst = 0;
            if (j > 0) ylst = ((y[j - 1] & (1ll << 31)) != 0);
            unsigned int ss = bt[s[i] - 'a'][j] | xprev[j];
            unsigned int t = bt[s[i] - 'a'][j] & ~xprev[j];
            unsigned int q = ss - ((t << 1) | (ylst ? 1 : 0));
            y[j] = (q & ~ss) | t;
            unsigned int sx = (bt[s[i] - 'a'][j] | xprev[j]) & ~((y[j] << 1) | (ylst ? 1 : 0));
            x[j] = sx;
        }
    }
    int ans = 0;
    for (int i = 0; i <= m / 32; i++) {
        ans += __builtin_popcount(x[i]);
        x[i] = 0; y[i] = 0;
        for (int k = 0; k < 26; k++) bt[k][i] = 0;
    }
    return ans;
}