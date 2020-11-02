#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

class Grafo
{
public:
    int quantidadeVertices;
    list<pair<int, int>> *matrizAdjacencias;

    Grafo(int qV)
    {
        this->quantidadeVertices = qV;
        this->matrizAdjacencias = new list<pair<int, int>>[qV];
    }

    void incluirAresta(int vertice1, int vertice2, int peso)
    {
        matrizAdjacencias[vertice1].push_back(make_pair(vertice2, peso));
        matrizAdjacencias[vertice2].push_back(make_pair(vertice1, peso));
    }

    void removerAresta(int vertice1, int vertice2, int peso)
    {
        this->matrizAdjacencias[vertice1].remove(make_pair(vertice2, peso));
        this->matrizAdjacencias[vertice2].remove(make_pair(vertice1, peso));
    }

    int obterMenorCaminho(int origem, int destino)
    {
        // armazena a menor distância do vértice de origem até todos os outros vértices
        int distancia[quantidadeVertices];
        // armazena os vértices que já foram visitados
        int verticesVisitados[quantidadeVertices];
        // fila de prioridade para armazenar de forma organizada os pesos entre os vértices
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridadeVertices;

        // inicializa os vetores de distância e vértices visitados
        for (int iV = 0; iV < quantidadeVertices; iV++)
        {
            distancia[iV] = INF;
            verticesVisitados[iV] = false;
        }

        // inicializa o primeiro vértice, relativo à distância da origem até ela própria (que será 0)
        distancia[origem] = 0;
        filaPrioridadeVertices.push(make_pair(distancia[origem], origem));

        // vetor para remover as arestas que já foram visitadas, já que só poderão ser usadas uma vez
        int arestasRemovidas[3][10000];
        int quantidadeArestasRemovidas = 0;

        while (!filaPrioridadeVertices.empty())
        {
            pair<int, int> parAtual = filaPrioridadeVertices.top(); // pega sempre o pair do topo da fila
            int verticeAtual = parAtual.second;
            filaPrioridadeVertices.pop(); // remove da fila o par que está sendo usado no cálculo

            // se o vértice ainda não tiver sido visitado, inicia o cálculo da menor rota
            if (verticesVisitados[verticeAtual] == false)
            {
                verticesVisitados[verticeAtual] = true; // marca como visitado o vértice atual

                // cria iterator para percorrer todas as adjacências do vértice atual
                list<pair<int, int>>::iterator i;

                // loop para percorrer todas as adjacências do vértice atual
                for (i = matrizAdjacencias[verticeAtual].begin(); i != matrizAdjacencias[verticeAtual].end(); i++)
                {
                    int verticeAdjacente = i->first;
                    int peso = i->second;

                    // se a distância do vértice adjacente for maior que a distância do vértice atual + o peso
                    // do adjacente, faz com que a distância do vértice adjacente seja substituida pelo vértice
                    // atual + seu peso
                    if (distancia[verticeAdjacente] > (distancia[verticeAtual] + peso))
                    {
                        distancia[verticeAdjacente] = distancia[verticeAtual] + peso;
                        filaPrioridadeVertices.push(make_pair(distancia[verticeAdjacente], verticeAdjacente));
                        // se estiver calculando a distância relativa ao destino informado no parâmetro, inclui os dados
                        // da aresta atual nas arestas a serem removidas posteriormente
                        if (verticeAdjacente == destino)
                        {
                            arestasRemovidas[0][quantidadeArestasRemovidas] = verticeAtual;
                            arestasRemovidas[1][quantidadeArestasRemovidas] = verticeAdjacente;
                            arestasRemovidas[2][quantidadeArestasRemovidas] = peso;
                            quantidadeArestasRemovidas++;
                        }
                    }
                }
            }
        }

        // remove as arestas que foram utilizadas no cálculo do menor caminho até o destino da matriz de
        // adjacências para que não sejam mais usadas posteriormente
        for (int iAresta = 0; iAresta < quantidadeArestasRemovidas; iAresta++)
        {
            // 0 = vértice 1; 1 = vértice 2; 2 = peso da aresta
            removerAresta(arestasRemovidas[0][iAresta], arestasRemovidas[1][iAresta], arestasRemovidas[2][iAresta]);
        }

        return distancia[destino];
    }
};

int main()
{
    /* Legenda:
     * n = quantidade de cidades das rotas de voo
     * m = quantidade de rotas de voo disponíveis
     * a = cidade origem da rota de voo atual
     * b = cidade destino da rota de voo atual
     * c = custo da passagem da rota atual, de a até b
     * d = número de amigos que precisam viajar
     * k = número de assentos livres em cada rota de voo
     */

    int n, m, a, b, c, d, k;

    int instanciaAtual = 0;

    bool existePlanejamentoPossivel = true; // verifica se será possível alocar todos os amigos no voo

    while (existePlanejamentoPossivel)
    {
        cin >> n;
        cin >> m;

        Grafo g(n); // vertices = n, arestas = m

        for (int i = 0; i < m; i++)
        {
            cin >> a;
            cin >> b;
            cin >> c;

            g.incluirAresta(a - 1, b - 1, c);
        }

        cin >> d;
        cin >> k;

        int custoTotal = 0;

        while (d > 0) // enquanto houverem amigos para alocar em uma rota de voo,
        {             // é calculada uma nova rota para os que ainda faltam
            if (d > k)
            {
                custoTotal += g.obterMenorCaminho(0, n - 1) * (d - k); // caso hajam mais amigos que lugares em um voo
            }
            else
            {
                custoTotal += g.obterMenorCaminho(0, n - 1) * d; // caso hajam lugares disponíveis para todos
            }

            d -= k; // caso o número de assentos for menor que o de amigos, remove da quantidade total
                    // de amigos a quantidade que já embarcou para que seja recalculada uma nova rota
                    // com a quantidade de pessoas que ainda resta.

            // se custo < 0, ocorreu erro ao calcular a distância (falta de arestas), impossibilitando
            // alocação de todos os amigos; se maior que 10^15, excede a quantidade limite de dinheiro disponível
            if (custoTotal < 0 || custoTotal > pow(10, 15))
            {
                existePlanejamentoPossivel = false;
            }
        }

        cout << "Instancia " << ++instanciaAtual << "\n\n";

        if (existePlanejamentoPossivel)
        {
            cout << custoTotal << "\n\n\n\n";
        }
        else
        {
            cout << "impossivel\n\n\n\n";
        }
    }

    return 0;
}