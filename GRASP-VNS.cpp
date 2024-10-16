#include <bits/stdc++.h>
using namespace std;

// Função auxiliar para ordenar pares de itens com base no primeiro valor (tamanho dos itens) em ordem decrescente.
int ret(pair<int,int> a, pair<int,int> b) {
    return a.first > b.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    // Entrada do número de itens (n) e capacidade máxima da caixa (c).
    cin >> n >> c;

    int r = 0;  // Número de caixas necessárias.
    vector<int> f(n);  // Vetor para armazenar os tamanhos dos itens.
    vector<bool> escolhidos(n);  // Vetor para marcar quais itens já foram escolhidos.
    int escolhas = 0;  // Contador de quantos itens já foram empacotados.

    // Leitura dos tamanhos dos itens.
    for (int i = 0; i < n; i++) {
        cin >> f[i];
        escolhidos[i] = false;  // Inicialmente, nenhum item foi escolhido.
    }

    // Enquanto nem todos os itens tiverem sido empacotados.
    while (escolhas < n) {
        int max_iterations = 100;  // Número máximo de iterações do GRASP.
        double alpha = 1;  // Parâmetro que controla a aleatoriedade no GRASP.

        int best_solution_sum = 0;  // Melhor soma de tamanhos empacotados para a caixa atual.
        vector<pair<int,int>> best_solution;  // Melhor solução encontrada em termos de itens para a caixa.

        // GRASP: fase de construção.
        for (int i = 0; i < max_iterations; i++) {
            vector<pair<int,int>> current_solution;  // Solução atual para a caixa.
            vector<int> elements = f;  // Cópia dos elementos restantes.
            int remaining_capacity = c;  // Capacidade restante da caixa.
            bool deu = true;  // Flag para verificar se é possível empacotar mais itens na caixa.

            // Tentativa de empacotar itens na caixa atual até que não haja mais capacidade.
            while (remaining_capacity > 0 && deu == true) {
                vector<pair<int,int>> rcl;  // Lista de Candidatos Restritos (RCL) que contém os itens que podem caber na caixa.

                // Preencher a RCL com itens que cabem na caixa e que ainda não foram escolhidos.
                for (int i = 0; i < elements.size(); i++) {
                    if (elements[i] <= remaining_capacity * alpha && escolhidos[i] == false) {
                        rcl.push_back(make_pair(elements[i], i));
                    }
                }

                // Se não houver itens que possam ser empacotados, sair do laço.
                if (rcl.empty()) {
                    deu = false;
                } else {
                    // Ordena os itens da RCL em ordem decrescente de tamanho.
                    sort(rcl.begin(), rcl.end(), ret);
                    srand(time(0));  // Gera semente para aleatoriedade.
                    
                    // Seleciona um item aleatoriamente da RCL.
                    int chosen_index = rand() % rcl.size();
                    current_solution.push_back(rcl[chosen_index]);  // Adiciona o item à solução atual.
                    remaining_capacity -= rcl[chosen_index].first;  // Atualiza a capacidade restante da caixa.
                    elements[rcl[chosen_index].second] = 99999999;  // Marca o item como empacotado.
                }
            }

            // Calcula a soma dos itens na solução atual.
            int sum = 0;
            for (size_t i = 0; i < current_solution.size(); ++i) {
                sum += current_solution[i].first;
            }

            // Se a soma atual for maior que a melhor soma encontrada, atualiza a melhor solução.
            if (best_solution_sum < sum) {
                best_solution_sum = sum;
                best_solution = current_solution;
            }
        }

        // Marca os itens da melhor solução como escolhidos.
        vector<bool> escc = escolhidos;
        for (pair<int,int> i : best_solution) {
            escolhas++;  // Atualiza o número de itens empacotados.
            escc[i.second] = true;  // Marca o item como escolhido.
        }

        // Fase VNS: melhoria da solução encontrada.
        int k = 0;
        while (k < 100) {  // Executa VNS até atingir o limite de iterações sem melhoria.
            int sum_f = best_solution_sum;  // Melhor soma de itens empacotados.
            vector<bool> esc = escc;  // Vetor auxiliar para itens escolhidos.
            vector<pair<int,int>> bs = best_solution;  // Solução auxiliar.

            // Para cada vizinhança, tenta trocar um item da solução por um item não empacotado.
            for (int i = 0; i < k; i++) {
                srand(time(0));
                int rn = rand() % (bs.size());  // Escolhe um item aleatoriamente da solução atual.
                srand(time(0));
                int x = rand() % n;  // Escolhe um item aleatoriamente da lista de itens.
                int op = 0;
                
                // Garante que o item escolhido ainda não foi empacotado.
                while (esc[x] == true && op < 100) {
                    srand(time(0));
                    x = rand() % n;
                    op++;
                }

                // Se o item ainda não foi escolhido, realiza a troca.
                if (esc[x] == false) {
                    esc[x] = true;  // Marca o novo item como escolhido.
                    esc[bs[rn].second] = false;  // Desmarca o item removido.
                    sum_f = sum_f - bs[rn].first + f[x];  // Atualiza a soma dos tamanhos.
                    bs[rn] = make_pair(f[x], x);  // Substitui o item na solução.
                }
            }

            // Se a nova solução for válida e melhor que a anterior, atualiza a solução.
            if (sum_f <= c && sum_f > best_solution_sum) {
                best_solution_sum = sum_f;
                best_solution = bs;
                k = 1;  // Reinicia o contador de vizinhanças.
            } else {
                k++;  // Aumenta o número de vizinhanças se não houve melhoria.
            }
        }

        r++;  // Incrementa o número de caixas usadas.

        // Atualiza os itens escolhidos com base na melhor solução.
        for (pair<int,int> a : best_solution) {
            escolhidos[a.second] = true;
        }
    }

    // Exibe o resultado final: o número de caixas utilizadas.
    cout << "Resultado:" << endl;
    cout << r << endl;

    return 0;
}
