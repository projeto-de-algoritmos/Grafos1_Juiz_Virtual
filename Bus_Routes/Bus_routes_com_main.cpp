#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        
        int tam = routes.size();
        
        // Ordena as routes para facilitar a busca binária.
        for (int i = 0; i < tam; i++) {
            sort(routes[i].begin(), routes[i].end());
        }
        
        set<int> origens, targets;
        
        // Encontra as routes que contêm a source e o target.
        for (int i = 0; i < tam; i++) {
            if (binary_search(routes[i].begin(), routes[i].end(), source)) {
                origens.insert(i);
            }
            if (binary_search(routes[i].begin(), routes[i].end(), target)) {
                targets.insert(i);
            }
        }
        
        vector<vector<int>> adj(tam);
        
        // Cria um grafo onde os nós são as routes e as arestas são as interseções de paradas.
        for (int i = 0; i < tam; i++) {
            for (int j = i + 1; j < tam; j++) {
                vector<int> v(routes[i].size() + routes[j].size());
                auto it = set_intersection(routes[i].begin(), routes[i].end(), routes[j].begin(), routes[j].end(), v.begin());
                if (it != v.begin()) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        queue<int> fila;
        vector<bool> visitado(tam, false);

        // Adiciona as routes que contêm a source à fila.
        for (int sourceRota : origens) {
            fila.push(sourceRota);
            visitado[sourceRota] = true;
        }

        int onibus = 0;

        while (!fila.empty()) {
            int tamanho = fila.size();
            onibus++;
            for (int i = 0; i < tamanho; i++) {
                int rota = fila.front();
                if (targets.count(rota)) {
                    return onibus;
                }
                fila.pop();
                for (int proximaRota : adj[rota]) {
                    if (!visitado[proximaRota]) {
                        fila.push(proximaRota);
                        visitado[proximaRota] = true;
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    // Input no formato especificado
    vector<vector<int>> routes = {{1,2,7},{3,6,7}};
    int source = 1;
    int target = 6;

    Solution sol;
    int resultado = sol.numBusesToDestination(routes, source, target);

    if (resultado == -1) {
        cout << "Não é possível chegar ao destino a partir da origem." << endl;
    } else {
        cout << "Menor quantidade de onibus necessaria: " << resultado << endl;
    }

    return 0;
}
