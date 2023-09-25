#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int a;
        int total = 0;
        int n = status.size();
        vector<int> graph[n];
        vector<bool> visited(n, false), keyFound(n, false), collected(n,false);

        //graph
        for (int i = 0; i < containedBoxes.size(); ++i) {
            for(int j = 0; j < containedBoxes[i].size(); ++j){
                a = containedBoxes[i][j];
                graph[i].push_back(a);
            }
        }

        //bfs
        if(initialBoxes.size()>=0){
            for(int i = 0; i < initialBoxes.size(); ++i){
                queue<int> queue;
                queue.push(initialBoxes[i]);

                visited[initialBoxes[i]] = true;

                while (!queue.empty()) {
                    
                    int u = queue.front();
                    queue.pop();

                    if(status[u]==1 || keyFound[u]==true){

                        //see that exist key inside
                        for (int i = 0; i < keys[u].size(); ++i){
                            int vectorKey = keys[u][i];
                            keyFound[vectorKey] = true;

                            //We will put box the were already found back in the queue to look inside, now we have the key
                            if(collected[vectorKey]==false && visited[vectorKey]==true){ 
                                queue.push(vectorKey);
                            }
                        }
                        
                        if(collected[u]==false) {
                            total += candies[u];
                            collected[u] = true;
                        }

                        //looking at neighbors
                        for (int v : graph[u]) {
                            if (!visited[v]) {
                                queue.push(v);
                                visited[v] = true;
                            }
                        }

                    } 
                }
            }
        }
        return total;
    }
};

// Main para testar (A main não vai no leetcode)
int main() {
    Solution solution;

    //output = 23185
    vector<int> status = {1,1,0,1,1,0,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,0,0};  // Status das caixas
    vector<int> candies = {732,320,543,300,814,568,947,685,142,111,805,233,813,306,55,1,290,944,36,592,150,596,372,299,644,445,605,202,64,807,753,731,552,766,119,862,453,136,43,572,801,518,936,408,515,215,492,738,154};  // Quantidade de doces nas caixas
    vector<vector<int>> keys = {{42,2,24,8,39,16,46},{20,39,46,21,32,31,43,16,12,23,3},{21,14,30,2,11,13,27,37,4,48},{16,17,15,6},{31,14,3,32,35,19,42,43,44,29,25,41},{7,39,2,3,40,28,37,35,43,22,6,23,48,10,21,11},{27,1,37,3,45,32,30,26,16,2,35,19,31,47,5,14},{28,35,23,17,6},{6,39,34,22},{44,29,36,31,40,22,9,11,17,25,1,14,41},{39,37,11,36,17,42,13,12,7,9,43,41},{23,16,32,37},{36,39,21,41},{15,27,5,42},{11,5,18,48,25,47,17,0,41,26,9,29},{18,36,40,35,12,33,11,5,44,14,46,7},{48,22,11,33,14},{44,12,3,31,25,15,18,28,42,43},{36,9,0,42},{1,22,3,24,9,11,43,8,35,5,41,29,40},{15,47,32,28,33,31,4,43},{1,11,6,37,28},{46,20,47,32,26,15,11,40},{33,45,26,40,12,3,16,18,10,28,5},{14,6,4,46,34,9,33,24,30,12,37},{45,24,18,31,32,39,26,27},{29,0,32,15,7,48,36,26,33,31,18,39,23,34,44},{25,16,42,31,41,35,26,10,3,1,4,29},{8,11,5,40,9,18,10,16,26,30,19,2,14,4},{},{0,20,17,47,41,36,23,42,15,13,27},{7,15,44,38,41,42,26,19,5,47},{},{37,22},{21,24,15,48,33,6,39,11},{23,7,3,29,10,40,1,16,6,8,27},{27,29,25,26,46,15,16},{33,40,10,38,13,19,17,23,32,39,7},{35,3,39,18},{47,11,27,23,35,26,43,4,22,38,44,31,1,0},{},{18,43,46,9,15,3,42,31,13,4,12,39,22},{42,45,47,18,26,41,38,9,0,35,8,16,29,36,31},{3,20,29,12,46,41,23,4,9,27},{19,33},{32,18},{17,28,7,35,6,22,4,43},{41,31,20,28,35,32,24,23,0,33,18,39,29,30,16},{43,47,46}};
    vector<vector<int>> containedBoxes = {{14},{},{26},{4,47},{},{6},{39,43,46},{30},{},{},{0,3},{},{},{},{},{27},{},{},{},{},{12},{},{},{41},{},{31},{20,29},{13,35},{18},{10,40},{},{38},{},{},{19},{5},{},{},{11},{1},{15},{},{},{},{24},{},{},{},{}};  // Caixas que cada caixa contém
    vector<int> initialBoxes = {2,7,8,9,16,17,21,22,23,25,28,32,33,34,36,37,42,44,45,48};
    
    int result = solution.maxCandies(status, candies, keys, containedBoxes, initialBoxes);

    cout << "Máximo de doces que você pode coletar: " << result << endl;

    //output = 1
    vector<int> status2 = {1, 1, 1};  // Status das caixas
    vector<int> candies2 = {100, 1, 100};  // Quantidade de doces nas caixas
    vector<vector<int>> keys2 = {{}, {0,2}, {}};  // Chaves que cada caixa contém
    vector<vector<int>> containedBoxes2 = {{}, {}, {}, {}, {}};  // Caixas que cada caixa contém
    vector<int> initialBoxes2 = {1};  // Caixas iniciais
    
    int result2 = solution.maxCandies(status2, candies2, keys2, containedBoxes2, initialBoxes2);

    cout << "Máximo de doces que você pode coletar: " << result2 << endl;

    return 0;
}
