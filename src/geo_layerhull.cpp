#include <bits/stdc++.h>

using namespace std;
using Point = complex<int>;
using ll = long long;

ll cross(Point a, Point b) { return 1LL * a.real() * b.imag() - 1LL * b.real() * a.imag(); }
ll det(Point a, Point b, Point c) { return cross(b - a, c - a); }


namespace std {
  bool operator<(const Point& a, const Point& b) {
    return make_pair(a.real(), a.imag()) < 
      make_pair(b.real(), b.imag());
  }
}

struct DynHull {
  struct Node { int bl, br, l, r, lc, rc; };
  vector<Node> T = {{-1, -1, -1, -1, 0, 0}};
  vector<Point> P;
  int root = 0;

  DynHull(vector<Point> P) : P(P), root(build(0, P.size())) {}

  bool leaf(int x) { 
    return T[x].l == T[x].r; 
  }
  int combine(int lc, int rc, int ret = -1) {
    if (!lc || !rc) return lc + rc; 
    if (ret == -1 || ret == lc || ret == rc) 
      ret = T.size(), T.push_back({});
    T[ret] = {-1, -1, T[lc].l, T[rc].r, lc, rc};

    while (!leaf(lc) || !leaf(rc)) {
      int a = T[lc].bl, b = T[lc].br, 
          c = T[rc].bl, d = T[rc].br;
      if (a != b && det(P[a], P[b], P[c]) > 0) {
        lc = T[lc].lc;
      } else if (c != d && det(P[b], P[c], P[d]) > 0) {
        rc = T[rc].rc;
      } else if (a == b) {
        rc = T[rc].lc;
      } else if (c == d) {
        lc = T[lc].rc;
      } else {
        auto s1 = det(P[a], P[b], P[c]);
        auto s2 = det(P[a], P[b], P[d]);
        assert(s1 >= s2);
        auto xc = P[c].real(), xd = P[d].real(), 
             xm = P[T[rc].l].real();
        if (s1 == s2 || s1 * xd - s2 * xc < (s1 - s2) * xm) { 
          lc = T[lc].rc;
        } else {
          rc = T[rc].lc;
        }
      }
    }
    T[ret].bl = T[lc].l; T[ret].br = T[rc].l;
    return ret;
  }
  void hull(int x, int l, int r, vector<int>& ret) {
    if (!x || l > r) return;
    if (leaf(x)) { ret.push_back(l); return; }
    hull(T[x].lc, l, min(r, T[x].bl), ret);
    hull(T[x].rc, max(l, T[x].br), r, ret);
  }
  int erase(int x, int pos) {
    if (!x || T[x].l > pos || T[x].r < pos) return x;
    return leaf(x) ? 0 : combine(
        erase(T[x].lc, pos), erase(T[x].rc, pos), x);
  }
  int build(int l, int r) {
    if (r - l == 1) {
      T.push_back({l, l, l, l, 0, 0});
      return T.size() - 1;
    }
    int m = (l + r) / 2;
    return combine(build(l, m), build(m, r));
  }

  void Erase(int x) { root = erase(root, x); }
  vector<int> Hull() { 
    vector<int> ret; 
    hull(root, T[root].l, T[root].r, ret); 
    return ret; 
  }
};

int main() {
  int n; cin >> n;
  vector<pair<Point, int>> pts(n);
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    pts[i] = make_pair(Point{x, y}, i);
  }
  sort(pts.begin(), pts.end());
  vector<Point> P(n);
  vector<int> remap(n);
  for (int i = 0; i < n; ++i) {
    remap[i] = pts[i].second;
    P[i] = pts[i].first;
  }
  auto LH = DynHull(P);
  for (int i = 0; i < n; ++i) P[i] = -P[i];
  reverse(P.begin(), P.end());
  auto UH = DynHull(P);

  vector<int> layer(n, -1);
  for (int i = 0; ; ++i) {
    vector<int> all;
    for (auto x : LH.Hull()) all.push_back(x);
    for (auto x : UH.Hull()) all.push_back(n - x - 1);
    if (all.empty()) break;
    for (auto x : all) {
      LH.Erase(x); UH.Erase(n - x - 1);
      layer[remap[x]] = i;
    }
  }
  
  for (int i = 0; i < n; ++i)
    cout << layer[i] + 1 << '\n';

  return 0;
}