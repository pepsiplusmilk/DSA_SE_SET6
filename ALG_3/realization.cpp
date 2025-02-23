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

void alg_3(vc<edge>& edges, ll n) {
  mt<std::pair<ll, ll>> mst(n, vc<std::pair<ll, ll>>(n));

  LinkCutTree lct(n); // построим V пустых деревьев

  for (const auto& edge : edges) {
    if (lct.not_bridge(edge)) {
      ll l = lct.lca(edge.u, edge.v); // Ищем lca - вершину которая ограничивает циклы

      auto maxu, us, ut = lct.max_edge(l, u);
      auto maxv, vs, vt = lct.max_edge(l, v);

      // Если ребро которое мы пытаемся добавить тяжелее всех остальных, то обрываемся
      if (edge.w >= maxu && edge.w >= maxv) {
        continue;
      }

      // Сравниваем ребро в каком пути самое большое
      ll emax, s, f;

      if (maxu > maxv) {
        emax = maxu;
        s = us, f = ut;
      } else {
        emax = maxv;
        s = vs, f = vt;
      }

      if (edge.w < emax) {
        lct.cut(s, f, edge.w); // удаляем ребро из леса деревьев
        lct.link(edge.u, edge.v); // добавляем новое более легкое ребро туда
      }
    }
  }

  return mst;
}
