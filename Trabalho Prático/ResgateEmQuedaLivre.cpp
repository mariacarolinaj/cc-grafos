#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef pair<int, int> coordenada;

class Pares
{
public:
    int *pai, *posicao;
    int quantidadeVertices;

    Pares(int qV)
    {
        this->quantidadeVertices = qV;
        pai = new int[qV + 1];
        posicao = new int[qV + 1];

        for (int i = 0; i <= qV; i++)
        {
            // inicializa todos os pares como posição 0
            posicao[i] = 0;
            // torna cada elemento pai de si mesmo
            pai[i] = i;
        }
    }

    int buscarPai(int vertice)
    {
        if (vertice != pai[vertice])
            pai[vertice] = buscarPai(pai[vertice]);
        return pai[vertice];
    }

    // conecta os pares
    void merge(int vertice1, int vertice2)
    {
        vertice1 = buscarPai(vertice1);
        vertice2 = buscarPai(vertice2);

        // caso o peso do vertice 1 seja maior que o do vértice 2, faz com que o pai do vértice 2 seja
        // o vértice 1, criando uma subárvore, senão faz o contrário
        if (posicao[vertice1] > posicao[vertice2])
            pai[vertice2] = vertice1;
        else
            pai[vertice1] = vertice2;

        if (posicao[vertice1] == posicao[vertice2])
            posicao[vertice2]++;
    }
};

class Grafo
{
public:
    int quantidadeVertices, quantidadeArestas;
    vector<pair<int, coordenada>> arestas;

    Grafo(int qV, int qA)
    {
        this->quantidadeVertices = qV;
        this->quantidadeArestas = qA;
    }

    void inserirAresta(int vertice1, int vertice2, double peso)
    {
        arestas.push_back({peso, {vertice1, vertice2}});
    }

    double gerarArvoreMinimaKruskal()
    {
        double pesoTotal = 0;

        // organiza arestas de acordo com seu peso, do menor para o maior
        sort(arestas.begin(), arestas.end());
        // inicializa os "sets" (conjuntos de pares de vértices conectados por uma aresta)
        Pares pares(quantidadeVertices);

        // cria iterator para passar por todos os vértices inseridos
        vector<pair<int, coordenada>>::iterator i;
        for (i = arestas.begin(); i != arestas.end(); i++)
        {
            int vertice1 = i->second.first;  // primeiro vértice do par
            int vertice2 = i->second.second; // segundo vértice do par

            int paiVertice1 = pares.buscarPai(vertice1);
            int paiVertice2 = pares.buscarPai(vertice2);

            // verifica se a aresta atual forma um ciclo com a árvore mínima atual
            if (paiVertice1 != paiVertice2)
            {
                pesoTotal += i->first;
                pares.merge(paiVertice1, paiVertice2);
            }
        }
        return pesoTotal;
    }
};

double obterDistanciaEntreCoordenadas(int coordenada1[], int coordenada2[])
{
    return sqrt((pow(coordenada1[0] - coordenada2[0], 2) + pow(coordenada1[1] - coordenada2[1], 2)));
}

int main()
{
    /* Legenda:
     * c = quantidade de casos de teste
     * n = número de pessoas do grupo (quantidade de vértices)
     * x, y = coordenadas de cada pessoa (vértice)
     */

    int c, n, x, y;

    cin >> c;

    for (int iTeste = 0; iTeste < c; iTeste++)
    {
        cin >> n;
        // a dimensão das colunas é 2 para armazenar os dados de x e y
        int coordenadasVertices[n][2];

        // a quantidade de arestas é igual a n² para poder armazenar todas as possibilidades de conexão
        // e depois avaliar quais são aquelas com menor peso
        Grafo grafo(n, pow(n, 2));

        for (int iVertice = 0; iVertice < n; iVertice++)
        {
            // realiza leitura das coordenadas do vértice atual e as armazena
            cin >> x;
            cin >> y;
            coordenadasVertices[iVertice][0] = x;
            coordenadasVertices[iVertice][1] = y;
        }

        for (int iAresta1 = 0; iAresta1 < n; iAresta1++)
        {
            for (int iAresta2 = iAresta1 + 1; iAresta2 < n; iAresta2++)
            {
                grafo.inserirAresta(iAresta1, iAresta2, obterDistanciaEntreCoordenadas(coordenadasVertices[iAresta1], coordenadasVertices[iAresta2]));
            }
        }

        // realiza a montagem da árvore geradora mínima e normaliza o resultado para devolver
        // quantos metros de teia o homem aranha gastará para salvar o grupo
        double pesoTotalArvore = grafo.gerarArvoreMinimaKruskal() / 100 + 0.01;
        cout << pesoTotalArvore << "\n";
    }

    return 0;
}
