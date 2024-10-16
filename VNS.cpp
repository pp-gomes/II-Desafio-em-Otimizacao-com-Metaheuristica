#include<bits/stdc++.h>

using namespace std;

// Função auxiliar para ordenar em ordem decrescente. Utilizada na ordenação da lista F (inicial).
int ret(int a, int b) {
    return a > b;
}

int main(){
    // Desativando a sincronização padrão para melhorar a performance de entrada e saída.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    // Entrada do número de itens (n) e a capacidade máxima de cada caixa (c).
    cin >> n >> c;

    // Array para armazenar os tamanhos dos itens.
    vector<int>f(n);
    // Leitura dos tamanhos dos itens.
    for(int i = 0; i < n; i++){
        cin >> f[i];
    }

    // Ordenar o vector f em ordem decrescente pelo tamanho dos itens.
    sort(f.begin(), f.end(), ret);

    int k = 0;  // Variável de controle do laço de VNS .
    int r = n;  // Número inicial de caixas, começa assumindo que cada item terá sua própria caixa.

    // Loop principal da metaheurística VNS, executado até que o critério de parada seja atingido.
    while(k < 10000) {
        int x = r; // `x` armazena o número atual de caixas no início da iteração.

        // Estrutura de busca em diferentes vizinhanças, controlada pela variável `k`.
        for(int i = 0; i < k; i++) {
            srand(time(0)); // Geração de uma nova semente para o gerador de números aleatórios.

            // Seleção aleatória de um item para tentar combinar com outro.
            // O item escolhido será da faixa de índices entre 0 e `r-2`, onde `r` é o número atual de caixas.
            int t = rand() % (r - 2);

            // Verifica se o item selecionado `f[t]` pode ser combinado com o último item `f[r-1]` dentro da capacidade `c`.
            if(f[t] + f[r-1] <= c) {
                // Se sim, combina os dois itens (adiciona o tamanho do último item ao item `t`).
                f[t] += f[r-1];

                // Reduz o número de caixas, pois o último item foi combinado.
                r--;
            }
        }

        // Se o número de caixas não mudou nesta iteração, incrementa `k` (significa que não houve melhoria).
        if(x == r) {
            k++;
        } else {
            // Se houve uma mudança no número de caixas (ou seja, foi encontrada uma melhor combinação), reinicia `k`.
            k = 1;
        }
    }

    // Exibe o número de caixas resultantes após o processo.
    cout << "Resultado:" << endl;
    cout << r << endl;

    return 0;
}
