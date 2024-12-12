// Find the first k such that (kS + I) % M is in [L, R]
// The first k : (kS + I) mod M in [L, R],
// and it's assumed that S, I, L, R in [0, M - 1], S != 0
ll solve (ll S, ll I, ll M, ll L, ll R)
{
    if (L <= I && I <= R) return 0; // I in [L, R]
    else if (S == 0) return -1;
    else
    {
        // let I become zero
        L = L + M - I, R = R + M - I;
        if (L >= M) L -= M;
        if (R >= M) R -= M;
    }
    // let S <= M / 2
    if (S > (M >> 1))
    {
        // kS mod M in [L, R], it's equivalent to k(M - S) in [M - R, M - L]
        S = M - S;
        L = M - L, R = M - R, swap(L, R);
    }
    ll k1 = L / S, k2 = R / S, m1 = L % S, m2 = R % S;
    if (m1 == 0) return k1;
    if (k2 > k1) return k1 + 1;
    ll T = (M + S - 1) / S;
    ll P = S * T % M;
    if (P == 0) return -1; // no solution
    // recursive question: kP mod S in [m1, m2]
    ll Res = solve(P, 0, S, m1, m2);
    if (Res == -1) return -1;
    // final
    ll Adv = multiDiv(Res, P, S);
    //multiDiv(Res, P, S) = (Res * P) // S, mozhno v __int128
    return Res * T - Adv + k1;
}