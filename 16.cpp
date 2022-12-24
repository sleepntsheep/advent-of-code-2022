#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <set>
#include <cassert>
#include <bitset>

int nsi(std::string s) {
    return ((s[0] - 'A') * 26) + (s[1] - 'A');
}

std::string isn(int i) {
    std::string s;
    s += 'A' + i / 26;
    s += 'A' + i % 26;
    return s;
}

using Visit = std::bitset<676>;

class Cave {
    public:
        std::map<std::pair<int, int>, int> distance;
        std::map<int, int> flow;
        std::vector<int> nodes;

        std::pair<int, Visit> get_flow(int node, int time_left, Visit visited = 0) {

            for (int i = 0; i < 676; i++) {
                if (visited[i]) continue;
                if (time_left < distance[{node, i}] + 1)
                    visited[i] = 1;
            }

            auto f = 0;
            Visit fv = visited;
            for (int next = 0; next < 676; next++) {
                if (visited[next]) continue;
                if (flow[next] == 0) continue;
                auto nt = time_left - distance[{node, next}] - 1;
                visited.set(next);
                auto p = get_flow(next, nt, visited);
                auto nf = p.first + flow[next] * nt;
                if (nf > f) {
                    f = nf;
                    fv = p.second;
                }
                visited.reset(next);
            }

            return {f, fv};
        }

        void simplify_distance() {
            for (const auto i : nodes) {
                for (const auto j : nodes) {
                    for (const auto k : nodes) {
                        if (distance[{i, j}] == 0) {
                            distance[{i, j}] = 1e9;
                        }
                    }
                }
            }

            for (const auto i : nodes)
                distance[{i, i}] = 0;

            for (const auto i : nodes) {
                for (const auto j : nodes) {
                    for (const auto k : nodes) {
                        distance[{j, k}] = std::min(distance[{j, k}],
                                distance[{j, i}] + distance[{i, k}]);
                    }
                }
            }
        }

        void parse(const std::vector<std::string> &input) {
            for (const auto &line : input) {
                int f = 0, read = 0;
                char us[3], discard[10];
                if (sscanf(line.c_str(), "Valve %s has flow rate=%d; %s %s to %s%n",
                        us, &f, discard, discard, discard, &read) != 5) {
                    break;
                }

                auto u = nsi(us);

                flow[u] = f;
                nodes.push_back(u);

                std::string word;
                std::stringstream ss(line.substr(read)); while (ss >> word) {
                    auto v = nsi(word.substr(0, 2));
                    distance[{u, v}] = 1;
                    nodes.push_back(v);
                }
            }
            std::sort(nodes.begin(), nodes.end());
            auto it = std::unique(nodes.begin(), nodes.end());
            nodes.resize(std::distance(nodes.begin(), it));
        }

    private:
};

int main() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) input.push_back(line);

    Cave cave;
    cave.parse(input);
    cave.simplify_distance();

    std::cout << cave.get_flow(nsi("AA"), 30).first << " ";

    return 0;
}

