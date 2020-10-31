#include <bits/stdc++.h>
using namespace std;

class Grafo
{
public:
    int quantidadeVertices;
    list<int> *matrizAdjacencias;

    Grafo(int qV)
    {
        this->quantidadeVertices = qV;
        matrizAdjacencias = new list<int>[qV];
    }

    void inserirAresta(int vertice1, int vertice2)
    {
        matrizAdjacencias[vertice1].push_back(vertice2);
    }

    bool verificarSeVerticeFazParteDoCaminho(int vertice1, int vertice2, bool *verticeFazParteDoCaminho)
    {
        verticeFazParteDoCaminho[vertice1] = true;

        // cria iterator para passar por todos os vértices inseridos
        list<int>::iterator i;
        if (vertice1 == vertice2)
        {
            return true;
        }
        for (i = matrizAdjacencias[vertice1].begin(); i != matrizAdjacencias[vertice1].end(); i++)
        {
            if (!verticeFazParteDoCaminho[*i])
                if (verificarSeVerticeFazParteDoCaminho(*i, vertice2, verticeFazParteDoCaminho))
                    return true;
        }
        return false;
    }

    bool verificarSePossuiCaminho(int vertice1, int vertice2)
    {
        bool *verticeFazParteDoCaminho = new bool[quantidadeVertices];
        for (int iVertice = 0; iVertice < quantidadeVertices; iVertice++)
        {
            verticeFazParteDoCaminho[iVertice] = false;
        }
        if (vertice1 == vertice2 || verificarSeVerticeFazParteDoCaminho(vertice1, vertice2, verticeFazParteDoCaminho))
        {
            return true;
        }

        return false;
    }
};

int main(void)
{
    /* Legenda:
     * n = quantidade de vértices
     * m = quantidade de arestas
     */

    int n, m, vertice1, vertice2;

    cin >> n; // qtd vertices
    cin >> m; // qtd arestas

    Grafo grafo(n);

    for (int iAresta = 0; iAresta < m; iAresta++)
    {
        cin >> vertice1;
        cin >> vertice2;

        // retira 1 de cada vértice para fins de normalização ao incluir as arestas no grafo
        grafo.inserirAresta(vertice1 - 1, vertice2 - 1);
    }

    bool possuiCaminhoEntreTodosOsParesDeVertice = true;

    // verifica cada par de arestas para saber se existe ao menos um caminho entre eles;
    // caso não tenha, então o vértice não é semi-fortemente conectado - e não é uma bolada
    for (int iV1 = 0; iV1 < m && possuiCaminhoEntreTodosOsParesDeVertice; iV1++)
    {
        for (int iV2 = 0; iV2 < m && possuiCaminhoEntreTodosOsParesDeVertice; iV2++)
        {
            possuiCaminhoEntreTodosOsParesDeVertice = grafo.verificarSePossuiCaminho(iV1, iV2) || grafo.verificarSePossuiCaminho(iV2, iV1);
        }
    }

    if (possuiCaminhoEntreTodosOsParesDeVertice)
    {
        cout << "Bolada";
    }
    else
    {
        cout << "Nao bolada";
    }

    return 0;
}