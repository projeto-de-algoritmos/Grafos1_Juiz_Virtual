#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ii = pair<int,int>;

    void printGraph(const vector<int> graph[], int numVertices) {
        for (int u = 0; u < numVertices; ++u) {
            cout << "Vértice " << u << " :" << endl;
            for (int v : graph[u]) {
                cout << "   Vértice " << v  << endl;
            }
        }
    }
    
    int bfs(const vector<int>graph[], int first, int size,vector<int>& status, vector<int>& candies, vector<vector<int>>& keys) {
        vector<bool> visited(size, false);
        
        queue<int> queue;
        queue.push(first);
        visited[first] = true;
        int total = 0;


        //see that exist key 

        while (!queue.empty()) {
            
            int u = queue.front();
            queue.pop();

            if(status[u]==1){
                //see that exist key 
                for (int i = 0; i < keys[u].size(); i++){
                    status[i] = 1;
                }

                total += candies[u];
                
                for (int v : graph[u]) {
                //cout << "Visitando vértice " << u << " olhando: " << v << endl;
                    if (!visited[v]) {
                        queue.push(v);
                        visited[v] = true;
                    }
                }
            } 
        }

        return total;
    }


    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        
        //graph
        
        int a,total;
        vector<int> graph[status.size()+1];

        for (int i = 0; i < containedBoxes.size(); ++i) {
            for(int j = 0; j < containedBoxes[i].size(); ++j){
                a = containedBoxes[i][j];
                graph[i].push_back(a);
            }
        }

        //printGraph(graph, 3);
    
        for(int i: initialBoxes){
            total = bfs(graph, initialBoxes[i], graph->size(),status,candies,keys);
        }
        return total;
    }

};

// Main para testar (A main não vai no leetcode)
int main() {
    Solution solution;

    // Exemplo de entrada de teste
    vector<int> status = {1, 0, 1, 0};  // Status das caixas
    vector<int> candies = {7, 5, 4, 100};  // Quantidade de doces nas caixas
    vector<vector<int>> keys = {{}, {}, {1}, {}};  // Chaves que cada caixa contém
    vector<vector<int>> containedBoxes = {{1,2}, {3}, {}, {}, {}};  // Caixas que cada caixa contém
    vector<int> initialBoxes = {0};  // Caixas iniciais

    int result = solution.maxCandies(status, candies, keys, containedBoxes, initialBoxes);

    cout << "Máximo de doces que você pode coletar: " << result << endl;

    return 0;
}