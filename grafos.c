#include <stdio.h>
#include <stdlib.h>
//definições importantes: UM GRAFO PODERADO É UM GRAÇO QUE POSSUI "PESOS" EM SUAS LIGAÇÕES(VERTICES), OU SEJA, PARA FAZER UM GPS
//SE TORNA NECESSARIO TER PESOS NAS ARESTAS PARA QUE REPRESENTE AS DISTANCIAS DE CADA VERTICE, OU CADA CIDADE (GENERALIZANDO)
// UM GRAFO DIGRAFO É UM GRAFO QUE TANTO VAI COMO VOLTA, OU SEJA, UM QUE VÁ DE A->B E B->
//o grafo a seguir foi baseado em matrizes, na ideia de linhas e colunas, no caso existem a coluna de vertices e as demais ligações(arestas
// sao as outras colunas, tendo seu peso e suas respectivas informações.

//comentarios para facilitar a apresentação
//
typedef struct grafo Grafo;
    struct grafo{
            int ponderado; //verifica se é um grafo ponderado, ou seja se as arestas possuem peso, no caso do GPS o peso é a distancia entre cada aresta
            int nr_vertices; // a quantidade de vertices que o grafo possui
            int grau_max; // o grau maximo que voce vai ter para cada vertice, cada vertice vai ter
            int **arestas; // UMA MATRIZ DE ARESTAS, que a primeira coluna é os vertices e as outras colunas é a quantidade de conexoes que cada vertice possui, no caso as arestas
            float** peso; // distancia entre as arestas
            int *grau; //
    };
 //função para criar um grafo com a quantidade de "nos", o grau maximo de cada nos e verifica se ele é ponderado
    Grafo* cria_grafo(int nr_vertices, int grau_max, int ponderado){
            Grafo* gr=(Grafo*)malloc(sizeof(struct grafo));
            if(gr != NULL){
                int i;
                int j;
                gr->nr_vertices = nr_vertices;
                gr->grau_max=grau_max;
                gr->ponderado=(ponderado != 0)?1:0;
                gr->grau=(int*)calloc(nr_vertices,sizeof(int)); //criando vetor de grau
                gr->arestas=(int**)malloc(nr_vertices*sizeof(int*)); // alocando a quantidade necessaria de memoria para alocar as arestas
                for(i=0;i<nr_vertices; i++){ //criando a matriz de arestas
                    gr->arestas[i]=(int*)malloc(grau_max*sizeof(int)); //para cada vertice, esta cirando a quantidade de arestas possives que no caso é ilimitado
                    if(gr->ponderado){ // se for um grafo ponderado ele tambem aloca um espaço para adicionar o peso
                        gr->peso=(float**)malloc(nr_vertices*sizeof(float*));
                        for(j=0;j<nr_vertices; j++){ //criando a matriz de arestas
                            gr->peso[j]=(float*)malloc(grau_max*sizeof(float)); //para cada vertice, esta cirando a quantidade de arestas possives que no caso é ilimitado, incluido o peso nessa informação
                        }

                    }
            }
            }
            printf("GRAFO CRIADO COM SUCESSO!\n");
            return gr;
        }


    int insereAresta(Grafo *gr, int origem, int destino,int eh_digrafo, float peso){
                //rotina para ver se a aresta a ser inserida no grafo
                    if(gr==NULL){
                        return 0;   //se o grafo for vazio ele retorna 0
                    }
                    if(origem<0 || origem > gr->nr_vertices){
                        return 0; //se a origem for menor que zero ou maior que o tamanho do grago criado ,e ele vai retornar 0
                    }
                    if(destino <0 || destino >   gr->nr_vertices){
                        return 0; //se o desitno for menor que zero ou maior que o tamanho do grago criado ,e ele vai retornar 0
                    }

                    gr->arestas[origem][gr->grau[origem]]= destino; // ou seja, nesta linha a matriz do grafo, a coluna que r
                                            //epresenta como origem, vai receber o seu primeiro endereçamento, que no caso é um destino

                    //se for ponderado(NO CASO, PARA FAZER O GPS) ele vai alocar o peso na variavel definida
                    if(gr->ponderado){
                        gr->peso[origem][gr->grau[origem]]= peso;
                    }
                    //por fim, como a cada criação de uma aresta ele anda um no grau, no caso tendo que adcionar uma variavel a mais naquela linha de arestas
                    gr->grau[origem]++;

                        //se ele for digrafo, faz-se uma chamada recursiva para ligar "B->A"
                    if(eh_digrafo){
                        insereAresta(gr, destino,origem,1,peso);
                    }
                    printf("VERTICE INSERIDO COM SUCESSO.\n");
                return 1;

    }


   int menor_distancia(float *dist, int *visitado, int numero_vertices){ //procura o vertice que ainda nao foi vistado de menor distancia
    int i, menor= -1, primeiro= 1; // variaveis auxiliares
    // essa função procura um vertice que ainda nao tenha sido visitado com a menor distancia
    for(i=0;i<numero_vertices;i++){//percorrendo todo o grafo e os verticies
            if(dist[i] >= 0 && visitado[i] == 0){
                    if(primeiro){
                        menor= i;
                        primeiro = 0;
                    } //vereficia se é o primeiro vertice a ser visitado
                    else{
                        if(dist[menor] > dist[i]){ // faz uma comparação da distancia atual com a distancia menor anterior encontrada
                            menor= i; // se a distancia atual for menor do que a menor anterior, a menor vira a atual
                        }
                    }

            } //verifica  se o vertice ainda nao foi visitado

    }
 return menor; //retornando a menor distancia
    }
//usei o algoritmo de Dijkstra
    void gps_caminhodef(Grafo *gr, int inicio, int *ant, float *dist, int destino){//passa o grafo como aprametro, de onde quer sair, o anterior de onde ele visitou e a distancia total.
          int i,j, cont,n_vertices, ind , *visitado, u; //variaveis auxiliares

          cont=n_vertices = gr->nr_vertices;
          visitado = (int*)malloc(n_vertices* sizeof(int)); //alocando um vetor para saber quem ja foi visitado
                    for(i=0; i< n_vertices; i++){ //inicializando as variaveis pois nenhum verticie foi visitado
                        ant[i] = -1; // nao existe nenhum anterior a ele
                        dist[i]= -1; // nao existe ainda nenhuma distaincia
                        visitado[i]= 0; // e nenhuma vertice foi visitado
                    }
                    dist[inicio]= 0;//a distancia do vertice inicial a ele mesmo, é 0
                    while(cont > 0) { //enquanto houver vertice p percorrer, descobrir a menor distancia entre eles
                        u = menor_distancia(dist,visitado, n_vertices);
                                    if(u== (-1) ){
                                        break; // se existir um verticie com uma menor distancia -1 , ele para , pq nao é possivel realizar isto
                                                }
                        visitado[u] = 1; //marcando o vertice de menor distanccia como visitado
                        cont -- ;

                                for(i=0; i< gr->grau[u]; i++){ //indo atras de todos os vizinhos do vertice de menor caminho
                                        ind = gr->arestas[u][i]; // variavel axiliar recebendo aresta que em tese tem o menor caminho
                                        //se o vertice ainda nao foi visitado ele recebe a distancia do atual, com a distancoa do anterior
                            if(dist[ind]< 0){
                                 dist[ind] = dist[u] + gr->peso[u][i]; // de acordo com a locação de matriz
                                 if(ant[i] == destino){
                                 printf("%f\n", (dist[u] + gr->peso[u][i]));
                                }
                                 ant[ind] = u; //como esta dentro do laço o vertice anterior recebe o u
                        //se nao for o primeiro vertice a ser visitado , ele vai verificar se a distancia menor atual é menor do que a distancia velha
                            }else{
                                if(dist[ind] > dist[u] + gr->peso[u][i]){
                                    dist[ind]= dist[u] + gr->peso[u][i];
                                   if(ant[i] == destino){
                                      printf("%f\n", (dist[u] + gr->peso[u][i]));
                                      }
                                    ant[ind]= u;
                                    }
                                }
                                }
                    }
                        free(visitado);//decrementa o contador até que nao existam mais vertices
    }


int main(){
    Grafo *gr;
    int quant_nos;
    int no_origem;
    int no_origemaux;
    int no_destino;
    int destino;

    int nao_ehdigrafo= 0;
    int ehpodenrado= 1;
    float distancia;


                        printf("\nQuantos vertices o grafo tem que ter ?\n");
                        scanf("%d",&quant_nos);
                        fflush(stdin);
                         //priemira chamada da função para  criar um grafo
                         gr = cria_grafo(quant_nos,quant_nos,ehpodenrado);
                            printf("Qual o destino que voce deseja ir ? \n");
                            scanf("%d", &destino);

                        while(1){
                                printf("\nDigite o vertice de origem que deseja informar: \n");
                                scanf("%d", &no_origemaux);
                                fflush(stdin);
                                if(no_origemaux != (-1)){
                                    no_origem = no_origemaux;
                                    }
                                    else{
                                        printf("VOCE ENCERROU A ALOCAÇÃO DE ARESTAS \n");
                                        break;
                                    }
                            printf("Digite o vertice de destino que deseja informar: \n");
                                scanf("%d",&no_destino);
                                fflush(stdin);
                            printf("Digite a distancia entre esses dois vertices: \n");
                                scanf("%f",&distancia);

                                insereAresta(gr,no_origem,no_destino,0,distancia);
                                  fflush(stdin);

                            //chama a função
                        }

                        int vis[quant_nos]; // cria um vetor para
                        float dist[quant_nos];
                        gps_caminhodef(gr,1,vis,dist,destino);
                        system("pause");


    return 0;

}
