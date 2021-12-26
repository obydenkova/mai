#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

#define MAXINT 2147483647

enum PathElement {
    MinusOne, DivByTwo, DivByThree
};

std::string PathElementToString(PathElement elem) {
    if (elem == MinusOne) {
        return "-1";
    }
    if (elem == DivByTwo) {
        return "/2";
    }
    if (elem == DivByThree) {
        return "/3";
    }
    throw std::logic_error("Unknown element");
}

int GoToNextPathElement(int n, PathElement elem) {
    if (elem == MinusOne) {
        return n - 1;
    }
    if (elem == DivByTwo) {
        return n / 2;
    }
    if (elem == DivByThree) {
        return n / 3;
    }
    throw std::logic_error("Unknown element");
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> dp(n + 1);
    std::vector<PathElement> path(n + 1);
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        int min_one = dp[i - 1];
        int div_by_2 = (i % 2 == 0 ? dp[i / 2] : MAXINT);
        int div_by_3 = (i % 3 == 0 ? dp[i / 3] : MAXINT);

        dp[i] = std::min(min_one, std::min(div_by_2, div_by_3));
        if (dp[i] == min_one) {
            path[i] = MinusOne;
        } else if (dp[i] == div_by_2) {
            path[i] = DivByTwo;
        } else {
            path[i] = DivByThree;
        }
        dp[i] += i;
    }
    std::cout << dp[n] << "\n";
    int index = n;
    while (index != 1) {
        std::cout << PathElementToString(path[index]) << " ";
        index = GoToNextPathElement(index, path[index]);
    }
    std::cout << "\n";
    return 0;
}
