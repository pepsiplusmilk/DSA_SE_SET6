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
  bool fl = true;
};

mt<edge> alg_1(vc<edge>& e, ll n) {
  mt<edge> mst(n, vc<edge>());

  for (const auto& edj : e) {
    mst[edj.u].push_back(edj);
    mst[edj.v].push_back(edj);
  }

  for (const auto& edj : e) {
    unlink(edj); // найдем и поставим fl в ребре в false -> O(1)

    if (!dfs(mst, edj.u, edj.v)) { // dfs -> O(V + E)
      link(edj); // Если связность была нарушена
    }
  }

  return mst;
}
