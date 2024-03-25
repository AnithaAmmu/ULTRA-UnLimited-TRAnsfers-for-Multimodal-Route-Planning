#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Dijkstra.h" 

using namespace std;

struct Edge {
    int from, to, weight;
};
vector<vector<Edge>> parseDIMACS(const string & filename) {
    ifstream file(filename);
    vector<vector<Edge>> graph;
    string line;
    int n, m;
    while (getline(file, line)) {
        if (line[0] == 'p') {
            sscanf(line.c_str(), "p sp %d %d", &n, &m);
            graph.resize(n);
        } else if (line[0] == 'a') {
            int u, v, w;
            sscanf(line.c_str(), "a %d %d %d", &u, &v, &w);
            graph[u-1].push_back({u-1, v-1, w});
        }
    }
    return graph;
}


vector<pair<int, int>> generateRandomPairs(int numPairs, int numNodes) {
    vector<pair<int, int>> pairs;
    for (int i = 0; i < numPairs; ++i) {
        int src = rand() % numNodes;
        int dest = rand() % numNodes;
        pairs.push_back({src, dest});
    }
    return pairs;
}

int main() {
    srand(time(0));
    vector<vector<Edge>> graph = parseDIMACS("florida.dimacs");
    vector<pair<int, int>> randomPairs = generateRandomPairs(200, graph.size());

    double totalRuntime = 0.0;

    for (const auto& pair : randomPairs) {
        clock_t start = clock();
        dijkstra(pair.first, pair.second);
        clock_t end = clock();
        totalRuntime += double(end - start) / CLOCKS_PER_SEC;
    }

    cout << "Total runtime in seconds for 200 random Dijkstra:: " << totalRuntime << endl;

    return 0
}
