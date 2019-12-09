// Kuan Lyu CSR //
// 12/8/2019 //

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class CSR {

public:
    vector <uint32_t> StartIndex;
    vector <uint32_t> adjacency;
    vector <double> weight;

public:
    static constexpr double inf = std::numeric_limits<double>::infinity();

    CSR(uint32_t a, uint32_t b, uint32_t c) {
        StartIndex.reserve(a);
        adjacency.reserve(b);
        weight.reserve(c);
    }

    bool isAdjacent(uint32_t from, uint32_t to) {
        for (uint32_t i = StartIndex[from]; i < StartIndex[from + 1]; i++) {
            if (adjacency[i] == to)
                return true;
        }
        return false;
    }

    template <typename T>
    void allAdjacent(uint32_t from, uint32_t to, T f) {
        for (uint32_t i = StartIndex[from]; i < StartIndex[from + 1]; i++)
            f(from, to);
    }

    void DFS(uint32_t from) const {

        vector <uint32_t> visited;
        visited.reserve(StartIndex.size() - 1);
        for (auto& x: visited)
            x = false;

        stack <uint32_t> stack;
        stack.push(from);
        visited[from] = true;

        while (not stack.empty()) {
            uint32_t cur = stack.top();
            cout << char(cur + 'a');
            stack.pop();
            for (uint32_t i = StartIndex[cur]; i < StartIndex[cur + 1]; i++) {
                if (not visited[adjacency[i]]) {
                    stack.push(adjacency[i]);
                    visited[adjacency[i]] = true;
                }
            }
        }
    }

    void BFS(uint32_t from) const {
        queue <uint32_t> queue;
        queue.push(from);
        vector <uint32_t> visited;
        visited.reserve(StartIndex.size() - 1);
        for (auto& x: visited)
            x = false;
        visited[from] = true;
        while (not queue.empty()) {
            uint32_t cur = queue.front();
            cout << char(cur + 'a');
            queue.pop();
            for (uint32_t i = StartIndex[cur]; i < StartIndex[cur + 1]; i++) {
                if (not visited[adjacency[i]]) {
                    queue.push(adjacency[i]);
                    visited[adjacency[i]] = true;
                }
            }
        }
    }

    void floydWarshall() {
        uint32_t numOfV = StartIndex.size() - 1;
        auto *cost = new double[numOfV * numOfV]{inf};
        for (uint32_t i = 0; i < numOfV * numOfV; i++)
            cost[i] = inf;
        for (uint32_t i = 0; i < numOfV; i++)
            for (uint32_t j = 0; j < numOfV; j++) {
                if (i == j)
                    cost[i * numOfV + j] = 0;
            }

        for (uint32_t i = 0; i < numOfV; i++)
            for (uint32_t j = StartIndex[i]; j < StartIndex[i + 1]; j++)
                cost[i * numOfV + adjacency[j]] = weight[j];


        for (uint32_t k = 0; k < numOfV; k++)
            for (uint32_t i = 0; i < numOfV; i++)
                for (uint32_t j = 0; j < numOfV; j++)
                    if (cost[i * numOfV + j] > cost[i * numOfV + k] + cost[k * numOfV + j])
                        cost[i * numOfV + j] = cost[i * numOfV + k] + cost[k * numOfV + j];

        for (uint32_t i = 0; i < numOfV; i++) {
            for (uint32_t j = 0; j < numOfV; j++)
                cout << cost[i * numOfV + j] << " ";
            cout << endl;
        }
    }
};


int main() {
    CSR graph(7, 14, 14);
    graph.StartIndex = {0, 2, 5, 8, 10, 13, 14};
    graph.adjacency = {1, 3, 0, 2, 4, 1, 4, 5, 0, 4, 1, 3, 2, 2};
    graph.weight = {2, 6, 2, 4, 2, 4, 3, 1, 6, 1, 2, 1, 3, 1};
    //graph.DFS(0);
    cout << endl;
    graph.BFS(0);
    cout << endl;
    graph.floydWarshall();
}