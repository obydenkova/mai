#include <iostream>
#include <vector>

#define NON_SET_COMPONENT -1


using Graph = std::vector<std::vector<int>>;

void dfs(int u, const Graph& g, std::vector<int>& components, int cur_comp) {
    components[u] = cur_comp;
    for (int v : g[u]) {
        if (components[v] == NON_SET_COMPONENT) {
            dfs(v, g, components, cur_comp);
        }
    }
}

int main() {
    int n,m;
    std::cin >> n >> m;
    Graph g(n);
    std::vector<int> comp_number(n,NON_SET_COMPONENT);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        a--;
        b--;
        g[b].push_back(a);
        g[a].push_back(b);
    }

    int cur_comp = 0;
    for (int i = 0; i < n; ++i) {
        if (comp_number[i] == NON_SET_COMPONENT) {
            dfs(i, g, comp_number, cur_comp);
            cur_comp++;
        }
    }

    std::vector<std::vector<int>> result(cur_comp);
    for (int i = 0; i < comp_number.size(); ++i) {
        result[comp_number[i]].push_back(i);
    }
    for (int i = 0; i < result.size(); ++i) {
        for (int v : result[i]) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
