#include <iostream>

using namespace std;

int main()
{
    /*
     * Legenda:
     * t = quantidade de casos de teste
     * n = número de vértices
     * m = número de arestas do grafo original
     * p = número de arestas a serem inseridas
     * k = número de cores do grafo
     */

    int t, n, m, p, k;

    // Le o numero de casos
    cin >> t;

    // Para cada caso
    for (int iTeste = 0; iTeste < t; iTeste++)
    {
        bool grafoValido = true;

        cin >> n;
        cin >> m;
        cin >> p;
        cin >> k;

        // Inicializa vetor de cores e matriz de adjacencia
        int cor[n];
        bool matrizAdjacencias[n][n];

        // incializa o vetor de cores com o valor 0 (padroniza)
        for (int iCor = 0; iCor < n; iCor++)
        {
            cor[iCor] = 0;
        }

        // inicializa a matriz de adjacências dos vértices como false, de forma que não sejam
        // identificada nenhuma adjacência até que sejam lidos os pares de vértices
        for (int iX = 0; iX < n; iX++)
        {
            for (int iY = 0; iY < n; iY++)
            {
                matrizAdjacencias[iX][iY] = false;
            }
        }

        // realiza a leitura e identifica a cor de cada i-ésimo vértice do grafo
        for (int i = 0; i < n; i++)
        {
            cin >> cor[i];
        }

        // realiza a leitura dos pares de aresta que serão inseridos e verifica se é possível
        // conectar os dois vértices indicados (dada a cor de cada um, que não pode ser igual ao outro)
        for (int iAresta = 0; iAresta < m && grafoValido; iAresta++)
        {
            int vertice1, vertice2;

            cin >> vertice1;
            cin >> vertice2;

            // realiza a normalização devido ao índice, por se tratar de vetor iniciado em 0, e não em 1
            vertice1--;
            vertice2--;

            if (cor[vertice1] == cor[vertice2])
            {
                // invalida o grafo devido ao fato de que como os vértices possuem a mesma cor,
                // não podem ser conectados
                grafoValido = false;
            }
            else
            {
                // realiza a conexão dos dois vértices informados na matriz de adjacências,
                // indicando que ela foi realizada com sucesso, e a aresta que acaba de ser
                // inserida não invalida o grafo (já que as cores dos vértices são diferentes)
                matrizAdjacencias[vertice1][vertice2] = true;
                matrizAdjacencias[vertice2][vertice1] = true;
            }
        }

        // se até essa etapa o grafo ainda for válido, continua a análise
        if (grafoValido)
        {
            for (int j = 0; j < n && grafoValido; j++)
            {
                int quantidadeConexoes = 0;

                for (int k = 0; k < n; k++)
                {
                    // se as cores de ambos os vértices for diferente, não houver previamente uma aresta os
                    // conectando e ainda houverem arestas a serem inseridas (p > 0), realiza a conexão
                    if (cor[j] != cor[k] && !matrizAdjacencias[j][k] && p > 0)
                    {
                        // insere as p arestas informadas que seriam posteriormente inseridas no grafo,
                        // preenchendo a matriz de adjacências de ambos os vértices
                        matrizAdjacencias[j][k] = true;
                        matrizAdjacencias[k][j] = true;
                        p--;
                    }

                    // caso exista uma aresta conectando ambos os vértices, incrementa o contador
                    // de conexões existentes no grafo
                    if (matrizAdjacencias[j][k])
                    {
                        quantidadeConexoes++;
                    }
                }

                // verifica se a quantidade de conexões é maior que 0, de forma a saber se o grafo
                // é ou não conexo (possui apenas um componente); caso não seja conexo, o invalida
                grafoValido = quantidadeConexoes > 0;
            }

            // se todas as arestas "adicionais" forem inseridas com sucesso (p == 0) e o grafo continuar
            // válido ao final do processo, retorna mensagem de sucesso na tela
            if (p == 0 && grafoValido)
            {
                cout << "Y\n\n";
            }
            else
            {
                cout << "N\n\n";
            }
        }
        else // grafo inválido nas primeiras etapas de avaliação
        {
            cout << "N\n\n";
        }
    }

    return 0;
}