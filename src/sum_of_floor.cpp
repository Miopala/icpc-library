//sum of floor((A * i + B) / M) [0, N), 0 <= A, B < M
ll solve(ll N, ll M, ll A, ll B) {
    assert(M > 0);
    if (B < 0) {
        ll at_least = (-B + M - 1) / M;
        return solve(N, M, A, B + at_least * M) - N * at_least;
    }
    if (A == 0) {
        return (B / M) * N;
    }
    assert(0 <= B && B < M);
    if (A >= M) {
        return solve(N, M, A % M, B) + (A / M) * ((N * (N - 1)) / 2);
    }
    ll up = (A * (N - 1) + B) / M;
    ll val = N * up;
    val -= (B / A);
    return val - solve(up + 1, A, M, A - 1 - B);
}