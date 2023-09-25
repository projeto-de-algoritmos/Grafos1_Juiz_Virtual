#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>>getAncestors(int n, vector<vector<int>>&edges) {
        // Armazena um vetor de lista de adjacência, onde cada nó possui uma lista de nós para os quais aponta.
        vector<int> lista_adjacencia[n];

        // Armazena o grau de entrada de cada nó.
        vector<int> grau_entrada(n);

        // Cria a lista de adjacência e atualiza os graus de entrada.
        for (int i = 0; i <edges.size(); ++i) {
            lista_adjacencia[edges[i][0]].push_back(edges[i][1]);
            grau_entrada[edges[i][1]]++;
        }

        // Fila para a travessia BFS.
        queue<int> fila;

        // Adiciona todos os nós com grau de entrada igual a 0, pois eles atuam como nós de origem.
        for (int i = 0; i < n; ++i) {
            if (grau_entrada[i] == 0)
                fila.push(i);
        }

        set<int> conjunto[n]; // Para evitar repetição de nós pais.

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            for (auto it : lista_adjacencia[atual]) {
                // Insere o nó pai imediato em cada filho do nó atual.
                conjunto[it].insert(atual);

                // Adiciona todos os ancestrais do nó atual.
                for (auto it2 : conjunto[atual])
                    conjunto[it].insert(it2);

                // Adiciona à fila se o grau de entrada for igual a 0.
                grau_entrada[it]--;
                if (grau_entrada[it] == 0)
                    fila.push(it);
            }
        }

        // Para armazenar a resposta.
        vector<vector<int>> resposta(n, vector<int>());

        // Adiciona os ancestrais de cada nó ao vetor de resposta final.
        for (int i = 0; i < n; ++i)
            resposta[i] = vector<int>(conjunto[i].begin(), conjunto[i].end());

        return resposta;
    }
};
