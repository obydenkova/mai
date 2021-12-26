#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using Graph = std::vector<std::unordered_set<size_t>>;

enum Color {
    White, Grey, Black
};

bool CheckForCycle(size_t cur, const Graph& g, std::vector<Color>& colors) {
    colors[cur] = Grey;
    for (size_t i : g[cur]) {
        if ((colors[i] == White && CheckForCycle(i, g, colors)) || colors[i] == Grey) {
            return true;
        }
    }
    colors[cur] = Black;
    return false;
}

void TopSort(size_t cur, const Graph& g, std::vector<bool>& used, std::vector<size_t>& result) {
    if (used[cur]) {
        return;
    }
    used[cur] = true;
    for (size_t i : g[cur]) {
        TopSort(i, g, used, result);
    }
    result.push_back(cur);
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    Graph graph(n);
    for (size_t i = 0; i < m; ++i) {
        long long a,b;
        std::cin >> a >> b;
        graph[a - 1].insert(b - 1);
    }

    bool cycle = false;
    std::vector<Color> colors(n, White);
    for (size_t i = 0; i < graph.size(); ++i) {
        cycle = cycle || CheckForCycle(i, graph, colors);
    }

    if (cycle) {
        std::cout << -1 << "\n";
        return 0;
    }

    std::vector<bool> used(n,false);
    std::vector<size_t> result;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (!used[i]) {
            TopSort(i, graph, used, result);
        }
    }

    for (std::vector<size_t>::const_reverse_iterator it = result.crbegin(); it != result.crend(); ++it) {
        std::cout << *it + 1 << " ";
    }
    std::cout << "\n";

    return 0;
}
