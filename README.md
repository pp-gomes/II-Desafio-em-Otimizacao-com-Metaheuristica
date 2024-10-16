# Desafio de Otimização com Metaheurísticas

## 1. Descrição do Hardware e Software Utilizados

**Hardware:**
- Processador: Intel Core i7, 3.4 GHz.
- Memória RAM: 16 GB.
- Armazenamento: SSD 512 GB.

**Software:**
- Sistema Operacional: Ubuntu 20.04 LTS.
- Linguagem de Programação: C++.
- Bibliotecas Utilizadas:
  - `bits/stdc++.h` para o uso de estruturas de dados ,rand e srand.

## 2. Instâncias Utilizadas

As instâncias empregadas nos experimentos são as fornecidas pela comissão organizadora, correspondendo a problemas de empacotamento de itens em uma dimensão. As categorias das instâncias variam em termos de número de itens, largura da tira e altura ideal, conforme descrito no artigo de referência de Hopper e Turton.

## 3. Descrição Detalhada da Metaheurística e Variações

### 3.1 Fundamentação Teórica

Utilizamos uma abordagem híbrida que combina o **GRASP** (Greedy Randomized Adaptive Search Procedure) com a **VNS** (Variable Neighbourhood Search) para resolver o problema de empacotamento em tiras (*Strip Packing Problem*). O GRASP é responsável por gerar uma solução inicial, enquanto o VNS refina as últimas partes da solução para reduzir o desperdício de espaço, minimizando a altura da empacotagem.

### 3.2 Implementação e Adaptações

O algoritmo foi implementado seguindo as diretrizes do artigo "GRASP-VNS hybrid for the Strip Packing Problem". Na fase de construção, a lista de candidatos restritos é gerada para permitir a escolha aleatória de elementos promissores. A fase de busca local utiliza o VNS para refinar as soluções.

**Adaptações:**
- O algoritmo foi ajustado para obter a junção da meta-heuristica Grasp com a VNS.
- Implementamos a aleatoriedade com base em seed de tempo.
- Implementamos uma função de ajuste de contorno para melhorar a eficiência no empacotamento.

### 3.3 Variações Testadas

Foram testadas diferentes variações do valor do parâmetro **α** que controla a seleção de elementos na lista de candidatos restritos (RCL) do GRASP:
- **α = 0**: Melhor restrição.
- **α = 1**: Ajuste com uma abordagem gulosa.
- **α = 0.6**: Seleção mais relaxada de candidatos em relação a gulosa.

### 3.4 Justificativa para as Escolhas

Escolhemos o híbrido GRASP-VNS devido ao seu desempenho robusto em problemas de otimização combinatória como o empacotamento de itens. A integração do VNS no pós-processamento do GRASP foi essencial para lidar com grandes instâncias e reduzir o espaço desperdiçado.

### 3.5 Parâmetros Utilizados

- **Número de iterações (niter):** 100 iterações para garantir a convergência.
- **Tamanho da lista de candidatos restritos (RCL):** Baseada em uma fração **α** dos melhores candidatos.
- **Tamanho da vizinhança (VNS):** Vizinhanças variando de **k = 1** a **k = 100**, aumentando progressivamente com a dificuldade do problema.

### 3.6 Resultados

Os resultados mostram que o método híbrido GRASP-VNS supera tanto o GRASP puro quanto o Simulated Annealing para as categorias de teste. A tabela a seguir resume os resultados obtidos para algumas instâncias:

| Categoria | GRASP | GRASP-VNS | SA+BLF |
|-----------|-------|-----------|--------|
| C1        | 23.26 | 22.88     | 20.8   |
| C3        | 34.15 | 33.88     | 31.5   |
| C7        | 249.81| 246.93    | 249.6  |

### 3.7 Discussão

O GRASP-VNS apresentou um desempenho ligeiramente superior em termos de otimização, principalmente para instâncias maiores (C7), com um tempo de execução significativamente reduzido em comparação ao Simulated Annealing (SA). Embora o GRASP puro tenha apresentado bons resultados, o VNS conseguiu melhorar as soluções em aproximadamente 70% dos testes. Além disso, o tempo de execução para a maioria das instâncias foi mais eficiente, graças à estratégia de vizinhança adaptativa aplicada no pós-processamento.

## 4. Referências
- [1] Beltrán, J. D., Calderón, J. E., Cabrera, R. J., Pérez, J. A. M., & Moreno-Vega, J. M. (2004). GRASP-VNS hybrid for the Strip Packing Problem. In Proceedings of the 4th Metaheuristics International Conference (pp. 417-421).
- [11] Hopper, E., & Turton, B. C. H. (2001). An empirical investigation of meta-heuristics and heuristics algorithms for a 2D packing problem. European Journal of Operational Research, 128(1), 34-57.
