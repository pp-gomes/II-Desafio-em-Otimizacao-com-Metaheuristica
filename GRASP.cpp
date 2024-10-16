#include <bits/stdc++.h>

using namespace std;

// Função auxiliar para ordenar os pares com base no primeiro valor (tamanho dos elementos)
// em ordem decrescente. Utilizada na ordenação da lista de candidatos restritos (RCL).
int ret(pair<int,int> a, pair<int,int> b) {
    return a.first > b.first;
}

int main() {
    // Desativar a sincronização padrão para melhorar a velocidade de entrada e saída.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    // Entrada de dados: n = número de elementos, c = capacidade máxima de cada caixa.
    cin >> n >> c;

    // Vetor que armazenará os tamanhos dos elementos (itens a serem empacotados).
    vector<int> f(n);
    // Entrada dos elementos.
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    // Parâmetros do algoritmo GRASP.
    int max_iterations = 1000; // Número máximo de iterações da metaheurística.
    double alpha = 1; // Parâmetro para controle do fator aleatório.

    int r = INT_MAX; // Variável para armazenar o menor número de caixas obtido.

    // Início do laço GRASP, repetido para cada iteração.
    for(int i = 0; i < max_iterations; i++) {
        // Cópia dos elementos (lista de itens) para serem empacotados.
        vector<int> elements = f;
        int bins = 0; // Contador do número de caixas usadas.

        // Enquanto ainda houver elementos a serem empacotados.
        while (!elements.empty()) {
            vector<pair<int,int>> current_solution; // Solução atual (caixa sendo preenchida).
            int remaining_capacity = c; // Capacidade restante da caixa atual.
            bool feasible = true; // Flag para indicar se ainda é possível empacotar mais itens na caixa atual.

            // Enquanto houver espaço na caixa e for possível empacotar.
            while (remaining_capacity > 0 && feasible) {
                vector<pair<int,int>> rcl; // Lista de Candidatos Restritos (RCL), contendo os itens que cabem na caixa.

                // Adicionar à RCL todos os itens que podem caber na caixa (com fator alpha).
                for (int i = 0; i < elements.size(); i++) {
                    if (elements[i] <= remaining_capacity * alpha) {
                        rcl.push_back(make_pair(elements[i], i));
                    }
                }

                // Se a RCL está vazia, não é mais possível empacotar na caixa atual.
                if (rcl.empty()) {
                    feasible = false;
                } else {
                    // Ordenar a RCL em ordem decrescente pelo tamanho dos itens.
                    sort(rcl.begin(), rcl.end(), ret);
                    srand(time(0)); // Semente para aleatoriedade.
                    
                    // Escolher um item aleatoriamente da RCL.
                    int chosen_index = rand() % rcl.size();
                    // Adicionar o item escolhido à solução atual.
                    current_solution.push_back(rcl[chosen_index]);
                    // Reduzir a capacidade restante da caixa.
                    remaining_capacity -= rcl[chosen_index].first;
                    // Marcar o item como "empacotado" alterando seu valor para 99999999.
                    elements[rcl[chosen_index].second] = 99999999;
                }
            }

            // Remover todos os itens já empacotados (marcados como 99999999).
            elements.erase(remove(elements.begin(), elements.end(), 99999999), elements.end());

            bins++; // Incrementa o número de caixas usadas.
        }

        // Se o número de caixas usadas nesta iteração é menor do que o melhor já encontrado, atualiza o resultado.
        if (bins < r) {
            r = bins; // Atualiza o menor número de caixas.
        }
    }

    // Exibe o menor número de caixas encontrado após todas as iterações.
    cout << "Resultado:" << endl;
    cout << r << endl;

    return 0;
}
