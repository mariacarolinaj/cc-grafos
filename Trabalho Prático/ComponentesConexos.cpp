#include <iostream>
#include <list>
using namespace std;

class Grafo
{
public:
    int quantidadeVertices;
    list<int> *matrizAdjacencias;

    Grafo(int qV)
    {
        this->quantidadeVertices = qV;
        this->matrizAdjacencias = new list<int>[qV];
    }

    void listarComponentesConectados()
    {
        int quantidadeComponentes = 0;
        bool *matrizAuxiliar = new bool[quantidadeVertices];
        for (int v = 0; v < quantidadeVertices; v++)
            matrizAuxiliar[v] = false;

        for (int iVertice = 0; iVertice < quantidadeVertices; iVertice++)
        {
            if (matrizAuxiliar[iVertice] == false)
            {
                buscaEmProfundidadeAdjacencias(iVertice, matrizAuxiliar);
                cout << "\n";
                quantidadeComponentes++;
            }
        }
        cout << quantidadeComponentes << " connected components\n\n";
    }

    void buscaEmProfundidadeAdjacencias(int indiceVertice, bool matrizAuxiliar[])
    {
        matrizAuxiliar[indiceVertice] = true;
        cout << (char)(indiceVertice + 97) << ",";

        // procura pelos vértices adjuntos ao atual recursivamente, imprimindo-os até que não encontre
        // mais nenhum item na matriz auxiliar
        list<int>::iterator i;
        for (i = matrizAdjacencias[indiceVertice].begin(); i != matrizAdjacencias[indiceVertice].end(); ++i)
            if (!matrizAuxiliar[*i])
                buscaEmProfundidadeAdjacencias(*i, matrizAuxiliar);
    }

    void incluirAresta(char vertice1, char vertice2)
    {
        // normaliza posição dos vértices a partir da conversão do char
        // ocorre o decremento -97 para que a letra a = 0, b = 1 e etc

        int indiceVertice1 = ((int)vertice1) - 97;
        int indiceVertice2 = ((int)vertice2) - 97;

        matrizAdjacencias[indiceVertice1].push_back(indiceVertice2);
        matrizAdjacencias[indiceVertice2].push_back(indiceVertice1);
    }
};

int main()
{
    int quantidadeTestes, quantidadeVertices, quantidadeArestas;

    cin >> quantidadeTestes;

    for (int iTeste = 0; iTeste < quantidadeTestes; iTeste++)
    {
        cin >> quantidadeVertices;
        cin >> quantidadeArestas;

        Grafo grafo(quantidadeVertices);

        for (int iAresta = 0; iAresta < quantidadeArestas; iAresta++)
        {
            char vertice1, vertice2;
            cin >> vertice1;
            cin >> vertice2;

            grafo.incluirAresta(vertice1, vertice2);
        }
        cout << "Case #" << (iTeste + 1) << ":\n";
        grafo.listarComponentesConectados();
    }
    return 0;
}
