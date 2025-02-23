#include <vector>
#include <set>
#include <cmath>

using ll = long long;
using ld = long double;
const ll inf = 1e18;

template<typename T>
using vc = std::vector<T>;

template<typename T>
using mt = vc<vc<T>>;

struct edge {
  ll u, v, w;

  edge(ll _u, ll _v, ll _w) : u(_u), v(_v), w(_w) {};
};

struct dsu {
private:
  vc<ll> p, r;

public:
  explicit dsu(ll n) {
    p.resize(n, 0);
    r.resize(n, 0);
  }

  void make(ll v) {
    p[v] = v;
  }

  ll find(ll v) {
    if (v == p[v]) {
      return v;
    }

    return p[v] = find(p[v]);
  }

  void unite(ll v, ll u) {
    v = find(v);
    u = find(u);

    if (v != u) {
      if (r[v] < r[u]) {
        std::swap(v, u);
      }

      p[u] = v;

      if (r[v] == r[u]) {
        ++r[v];
      }
    }
  }
};

//edges - случайно сгенерированная последовательность ребер
mt<std::pair<ll, ll>> alg_2(vc<edge>& edges, ll n) {
  mt<std::pair<ll, ll>> mst(n, vc<std::pair<ll, ll>>());

  dsu comps(n);

  for (ll i = 0; i < n; ++i) {
    comps.make(i);
  }

  for (const auto&[u, v, w] : edges) {
    if (comps.find(u) != comps.find(v)) {
      comps.unite(v, u);
      mst[u].emplace_back(v, w);
      mst[v].emplace_back(u, w);
    }
  }
}
