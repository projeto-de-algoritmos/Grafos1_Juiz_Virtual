#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // -1 = não visitado, 0 = blue, 1 = red)
    bool isBipartite(const vector<vector<int>>& graph, int n) {
        vector<int> colors(n, -1);

        for (int i = 1; i < n; ++i) {
            if (colors[i] == -1) { 
                queue<int> q;
                q.push(i); 
                colors[i] = 0;

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    for (int v : graph[u]) {
                        if (colors[v] == -1) { 
                            colors[v] = 1 - colors[u]; 
                            q.push(v);
                        } else if (colors[v] == colors[u]) {
                            return false; 
                        }
                    }
                }

            }
    }

    return true; 
}

    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

        vector<int> adj[n+1];
        for(auto i:dislikes){
            int u=i[0];
            int v=i[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if(dislikes.empty()) return true;

        vector<vector<int>> graph1(n+1);
        int haters = dislikes.size();

        for(auto it:dislikes){
            graph1[it[0]].push_back(it[1]);
            graph1[it[1]].push_back(it[0]);
        }

        return isBipartite(graph1, n);
    }
};

// Exemplo de uso (a main não vai no leetcode)
int main() {
    Solution solution;
    int n = 4;
    vector<vector<int>> dislikes = {{1, 2}, {1, 3}, {2, 4}};

    if (solution.possibleBipartition(n, dislikes)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}