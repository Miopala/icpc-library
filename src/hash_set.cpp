const int MAX_N = 4e5 + 5;
int n, k;
 
const int MOD_A = 1e9 + 7;
const int P_A = 1e6;
const int MOD_B = 1e9 + 321;
const int P_B = 1e6;
 
int powA[MAX_N];
int powB[MAX_N];
 
struct Hash
{
    int va = 0;
    int vb = 0;
 
    void add(int pos)
    {
        va = (va + powA[pos]) % MOD_A;
        vb = (vb + powB[pos]) % MOD_B;
    }
    void sub(int pos)
    {
        va = (va - powA[pos] + MOD_A) % MOD_A;
        vb = (vb - powB[pos] + MOD_B) % MOD_B;
    }
 
    Hash operator+(Hash &other)
    {
        return Hash({
        (va + other.va) % MOD_A,
        (vb + other.vb) % MOD_B
        });
    }
 
    long long compress()
    {
        return (long long)va | ((long long)vb << 32LL);
    }
};
 
Hash minusHash;
 
void precompute()
{
    powA[0] = 1;
    powB[0] = 1;
    for(int i = 1; i < MAX_N; ++i)
    {
        powA[i] = (powA[i - 1] * P_A) % MOD_A;
        powB[i] = (powB[i - 1] * P_B) % MOD_B;
    }
 
    for(int i = 1; i < k; ++i) 
        minusHash.sub(i);
}
 
Hash extendHash(Hash h, int val)
{
    if(val == 0) return h + minusHash;
    h.add(val);
    return h;
}
 
Hash prefixHash[MAX_N];