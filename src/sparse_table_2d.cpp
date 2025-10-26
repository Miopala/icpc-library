template <class S, S (*op)(S, S), S (*e)()> struct sparse_table {
    int N, lgN;
    std::vector<std::vector<S>> d;
    std::vector<int> lgx_table;
    sparse_table() {}
    sparse_table(const std::vector<S> &sequence) : N(sequence.size()) {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; ++i) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        d.assign(lgN, std::vector<S>(N, e()));
        d[0] = sequence;
        for (int h = 1; h < lgN; ++h) {
            for (int i = 0; i + (1 << h) <= N; ++i) {
                d[h][i] = op(d[h - 1][i], d[h - 1][i + (1 << (h - 1))]);
            }
        }
    }
    S prod(int l, int r) const { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return e();
        int h = lgx_table[r - l];
        return op(d[h][l], d[h][r - (1 << h)]);
    }
};


template <class S, S (*op)(S, S), S (*e)()> struct SparseTable2D {
    int H, lgH, W;
    std::vector<std::vector<sparse_table<S, op, e>>> d;
    std::vector<int> lgx_table;
    SparseTable2D() {}
    SparseTable2D(const std::vector<std::vector<S>> &matrix) {
        H = matrix.size(), W = (matrix.size() ? matrix[0].size() : 0);
        lgx_table.resize(H + 1);
        for (int i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgH = lgx_table[H] + 1;
        d.resize(lgH);
        for (auto v : matrix) d[0].emplace_back(sparse_table<S, op, e>(v));
        for (int h = 1; h < lgH; h++) {
            for (int i = 0; i + (1 << h) <= H; ++i) {
                std::vector<S> v(W);
                for (int j = 0; j < W; ++j) {
                    v[j] = op(d[h - 1][i].d[0][j], d[h - 1][i + (1 << (h - 1))].d[0][j]);
                }
                d[h].emplace_back(sparse_table<S, op, e>(v));
            }
        }
    }
    S prod(int xl, int xr, int yl, int yr) const {
        assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);
        if (xl >= xr) return e();
        int h = lgx_table[xr - xl];
        return op(d[h][xl].prod(yl, yr), d[h][xr - (1 << h)].prod(yl, yr));
    }
};