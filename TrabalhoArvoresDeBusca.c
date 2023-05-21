#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca necessária para o STRCMP (comparação de strings)
//==============================================================================
//=========================| Declarações de struct's |==========================
//==============================================================================

//INICIO DA LISTA ENCADEADA E INICIO DE RAIZES
typedef struct CabecaMusica{
	struct Musica * inicio;
	struct Musica * fim;	
	struct NodoMusica * indiceMusica;// RAIZ DAS MUSICAS
	struct NodoArtista * indiceArtista; //RAIZ DOS ARTISTAS 
}CabecaMusica;

// ELEMENTO DA LISTA ENCADEADA
typedef struct Musica{ // Elemento que estará na lista encadeada
	char nome[50];
	char artista[50];
	int ano;
	struct Musica *ante;
	struct Musica *prox;
}Musica;

//NODO DA ARVORE DE MÚSICAS
typedef struct NodoMusica{// Para fazer pesquisa por nome da música
	char nomeMusica[50];
	struct NodoMusica *esquerda;
	struct NodoMusica *direita;	
	struct Musica *alvo;	
	
}NodoMusica;

//NODO DA ARVORE DE ARTISTAS
typedef struct NodoArtista{
	char nomeArtista[50];
	struct NodoArtista * esquerda;
	struct NodoArtista * direita;
	struct Ocorrencias * listaAlvo;// Acessar a lista de musicas que o artista fez	
	
}NodoArtista;

//LISTA PARA INDEXAR MÚSICAS FEITAS PELO ARTISTA
typedef struct Ocorrencias{
	struct Musica * endereco; // PONTEIRO PARA A LISTA ENCADEADA COM A MÚSICA FEITA PELO ARTISTA
	struct Ocorrencias * prox;
	
}Ocorrencias;

//==============================================================================
//=========================| Funções para a lista encadeada |===================
//==============================================================================

//------------| Inicializar |---------------
CabecaMusica* iniciarCabeca(){
	// Inicialização padrão
	CabecaMusica *C; 
	C = (CabecaMusica *)malloc(sizeof(CabecaMusica));
	
	C->inicio = NULL;
	C->fim = NULL;
	C->indiceMusica = NULL;
	C->indiceArtista = NULL;
	
	return C;
}
//------------| Inserir |------------
Musica* inserirMusicaLista(CabecaMusica *C){
	Musica *novo = (Musica *)malloc (sizeof(Musica));
	
	printf("\n\tDigite o nome da Musica (Ate 50 caracteres): ");
	fflush(stdin);
	scanf("%s", novo->nome);
	strupr(novo->nome); // Deixar as letras em maiusculas
	
	printf("\n\tDigite o nome do Autor (Ate 50 caracteres): ");
	fflush(stdin);
	scanf("%s", novo->artista);
	strupr(novo->artista);
	
	printf("\n\tDigite o ano de lancamento: ");
	fflush(stdin);
	scanf("%d", &(novo->ano));	
	
	novo->ante = NULL;
	novo->prox = NULL;
	
	if(C->inicio == NULL){
		//A lista esta vazia!
		C->inicio = novo;
		C->fim = novo;
		
	}//if	
	else{
		//Existe algum elemento dentro, logo será inserido o novo no inicio!
		novo->prox = C->inicio;
		
		C->inicio->ante = novo;
		C->inicio = novo;
		
	}//else
	
	return novo;
	
}
//------------| Remover Item da Lista |------------
//..... Pesquisar Musica da lista ......
Musica *encontrarMusicaLista(CabecaMusica *C,char * nomeMusica){
	Musica *atual;
	atual = C->inicio;
	
	while( atual != NULL){
		if(strcmp(atual->nome,nomeMusica) == 0)
			return atual;
		
		atual = atual->prox;
	}
	
	return atual;		
}
//..... Retirar Musica da lista .....
void removerMusicaLista(CabecaMusica *C,char * nomeMusica ){
	char * nomeArtista = (char *)malloc(50 * sizeof(char)); // Nome do artista irá retornar para facilitar a busca pela arvore
	
	if(C->inicio == NULL){
		printf("\n\n\tA lista esta vazia!!\n\n");
		return NULL;
	}
	else{// Existe pelo menos um elemento
	   	Musica *musicaEncontrada;
		musicaEncontrada = encontrarMusicaLista(C, nomeMusica);
		
		if(musicaEncontrada == NULL){
			//A musica não existe
			printf("\n\tA musica pesquisada nao existe!!\n\n");
			return NULL;
			
		}
		else if((musicaEncontrada == C->inicio) && (musicaEncontrada == C->fim)){
			//A musica é a unica da lista
			C->inicio = NULL;
			C->fim = NULL;
			
		}else if(musicaEncontrada == C->inicio){
			//A musica esta no inicio da lista
			C->inicio = musicaEncontrada->prox;
			musicaEncontrada->prox->ante = NULL;
			
		}else if(musicaEncontrada == C->fim){
			//A musica esta no fim da lista
			C->fim = musicaEncontrada->ante;
			C->fim->prox = NULL;
			
		}else{
			//A musica esta no meio da lista
			musicaEncontrada->ante->prox = musicaEncontrada->prox;
			musicaEncontrada->prox->ante = musicaEncontrada->ante;
			
		}	
		
		printf("\n\t---------- Excluido com sucesso!!! ---------\n\n");
		return musicaEncontrada;
		
	}//else
}
//------------| Listar lista de musicas |------------
void imprimirLista(CabecaMusica *C){
	Musica *atual;
	atual = C->inicio;
	if(C->inicio == NULL){
		printf("\n\tA lista esta vazia!!!\n\n");
	}
	else{
		while(atual != NULL){
			printf("\n-------------------");
			printf("\n\tNome da musica:%s",atual->nome);
			printf("\n\tNome do Artista:%s",atual->artista);
			printf("\n\tAno da musica:%d\n\n",atual->ano);
			
			atual = atual->prox;
		}
	}//else 	
}
//==============================================================================
//=========================| Funções para a arvore de musicas |=================
//==============================================================================

//------------| Imprimir Musica |------------
void imprimirMusica(Musica * atual){
	printf("\n--------- Dados da musica buscada ----------");
	printf("\n\tNome da musica:%s",atual->nome);
	printf("\n\tNome do Artista:%s",atual->artista);
	printf("\n\tAno da musica:%d\n\n",atual->ano);
}
//------------| Inicializar arvores |------------
void iniciarArvores(CabecaMusica **C){
	
	(*C)->indiceMusica = NULL;
	(*C)->indiceArtista = NULL;
	
}
//------------| Gerar novo nó |------------
NodoMusica * gerarNodoMusica(char* nomeMusica, Musica *enderecoMusica){
	NodoMusica * novo = (NodoMusica *)malloc (sizeof(NodoMusica));
	
	strcpy(novo->nomeMusica,nomeMusica);
	novo->esquerda = NULL;
	novo->direita = NULL;
	novo->alvo = enderecoMusica;
	
	return novo;
	
}
//------------| Inserir nó na arvore |------------
NodoMusica * inserirNodoMusica(NodoMusica **nodo, char * nomeMusica, Musica *enderecoMusica){
	if((*nodo) == NULL){
		(*nodo) = gerarNodoMusica(nomeMusica,enderecoMusica);
		
	}else if (strcmp((*nodo)->nomeMusica, nomeMusica) <= 0){
		//Nome musica é maior ou igual
		(*nodo)->direita = inserirNodoMusica(&(*nodo)->direita,nomeMusica,enderecoMusica);
	}else{
		//Nome musica é menor
		(*nodo)->esquerda = inserirNodoMusica(&(*nodo)->esquerda,nomeMusica,enderecoMusica);
	}
	return *nodo;
	
}
//------------| Remover nó da arvore |------------
NodoMusica * removerNodoMusica(NodoMusica **nodo, char * nomeMusicaBuscada){
	
	if((*nodo) == NULL){
		// O nodo não existe na arvore
		return NULL;
	}
	else if (strcmp((*nodo)->nomeMusica, nomeMusicaBuscada) < 0){
		(*nodo)->direita = removerNodoMusica(&(*nodo)->direita,nomeMusicaBuscada);
		
	}
	else if(strcmp((*nodo)->nomeMusica, nomeMusicaBuscada) > 0){
		(*nodo)->esquerda = removerNodoMusica(&(*nodo)->esquerda,nomeMusicaBuscada);
	}
	else{
		//O nodo almejado foi encontrado
		if((*nodo)->esquerda == NULL && (*nodo)->direita == NULL){
			//O nodo em questão não possui filhos
			free(*nodo);
			(*nodo) = NULL;
			
		}
		else if((*nodo)->direita == NULL){
			//Existe um filho a ESQUERDA
			NodoMusica * temp = (*nodo);
			(*nodo) = (*nodo)->esquerda;
			free(temp);
			
		}
		else if((*nodo)->esquerda == NULL){
			//Existe um filho a DIREITA
			NodoMusica * temp = (*nodo);
			(*nodo) = (*nodo)->direita;
			free(temp);
			
		}
		else{
			//possui dois filhos
			NodoMusica * temp = (*nodo)->esquerda;
			
			while(temp->direita != NULL){
				temp = temp->direita;
			}
			
			strcpy((*nodo)->nomeMusica,temp->nomeMusica);//O nodo recebe o valor do nodo mais a direita
			strcpy(temp->nomeMusica,nomeMusicaBuscada);// O nodo mais a direita recebe o valor a ser removido
			
			(*nodo)->esquerda = removerNodoMusica(&(*nodo)->esquerda,nomeMusicaBuscada);
			
		}
	}// ELSE se o nodo foi encontrado
	
	return *nodo;
	
}
//------------| Pesquisar por NOME MUSICA |------------
Musica * buscarMusica(NodoMusica *nodo, char * nomeMusica){
	if(nodo == NULL){
		printf("\n-------------------\n\tMusica nao encontrada OU Arvore vazia\n\n");
		return NULL;
	}
	else if(strcmp(nomeMusica, nodo->nomeMusica) > 0){
		//desce pela direita
		buscarMusica((nodo->direita), nomeMusica);
		
	}
	else if(strcmp(nomeMusica, nodo->nomeMusica) < 0){
		//desce pela esquerda
		buscarMusica((nodo->esquerda), nomeMusica);
	
	}
	else {
		//Encontrou o nodo
		return nodo->alvo;// retorna o endereço da musica na lista encadeada
	}	
	
}
//==============================================================================
//=========================| Funções para a arvore de Artistas |================
//==============================================================================

NodoArtista * buscarArtista(NodoArtista *nodo, char * nomeArtista){
	if(nodo == NULL){
		return NULL;
	}
	else if(strcmp(nomeArtista, nodo->nomeArtista) == 0){
		//Encontrou o nodo
		return nodo;// retorna o endereço do artista buscado
		
	}
	else if(strcmp(nomeArtista, nodo->nomeArtista) < 0){
		//desce pela esquerda
		buscarArtista(nodo->esquerda, nomeArtista);
	
	}
	else {
		//desce pela direita
		buscarArtista(nodo->direita, nomeArtista);
		
	}
}
//------------| Buscar musica especifica no PORTIFOLIO do artista |------------
Ocorrencias * buscarOcorrencias(Ocorrencias *inicio,char * nomeMusica){
	Ocorrencias *atual;
	
	atual = inicio;
	
	while(atual != NULL && strcmp(nomeMusica,atual->endereco->nome) != 0){
		
		atual = atual->prox;
	}
	
	if(atual == NULL){
		printf("\n\tMusica nao encontrada!!!");	
	}

	return atual;
	
}
//------------| Gerar nodo Artista |------------
NodoArtista* gerarNodoArtista(Musica * enderecoMusica){

	NodoArtista * novo = (NodoArtista *)malloc(sizeof(NodoArtista));
	strcpy(novo->nomeArtista,enderecoMusica->artista);
	novo->esquerda = NULL;
	novo->direita = NULL;
	
	Ocorrencias * novaOcorrencia= (Ocorrencias *)malloc(sizeof(Ocorrencias));
	novo->listaAlvo = novaOcorrencia;
	novo->listaAlvo->endereco = enderecoMusica;
	novo->listaAlvo->prox = NULL;
	
	return novo;
	
}

//------------| Inserir Artista |------------
NodoArtista * inserirArtista(NodoArtista *nodo, Musica *enderecoMusica){
	
	if(nodo == NULL){	
		nodo = gerarNodoArtista(enderecoMusica);

	}
	else if(strcmp(enderecoMusica->artista, nodo->nomeArtista ) >= 0){
		//desce pela direita
		nodo->direita = inserirArtista(nodo->direita, enderecoMusica);
		
	}
	else if(strcmp(enderecoMusica->artista,nodo->nomeArtista) < 0){
		//desce pela esquerda
		nodo->esquerda = inserirArtista(nodo->esquerda, enderecoMusica);
	
	}
	
	return nodo;   		
}

//------------| Inserir Musica na arvore de artistas |------------
NodoArtista* inserirMusicaArtistas(NodoArtista *raiz,Musica* enderecoMusica){
	
	if(raiz == NULL){
		//A arvore esta vazia
		raiz = gerarNodoArtista(enderecoMusica);
		
	}
	else{
		//Existe algo na arvore
		NodoArtista *artista = buscarArtista(raiz,enderecoMusica->artista);
		if(artista == NULL){
			//O artista ainda não existe
			raiz = inserirArtista(raiz,enderecoMusica);
			
		}
		else{
			// O artista ja existe
			Ocorrencias *novo = (Ocorrencias * )malloc(sizeof(Ocorrencias));
			novo->endereco = enderecoMusica;
			novo->prox = NULL;
			
			Ocorrencias *prov = artista->listaAlvo;
			artista->listaAlvo = novo;
			novo->prox = prov; 
				
		}
	}
	
	return raiz;
	
}
//------------| Remover Artista |-------------------
NodoArtista * removerNodoArtista(NodoArtista *nodo, char* nomeArtistaBuscado){
	
	if((nodo) == NULL){
		// O nodo não existe na arvore
		return NULL;
	}
	else if (strcmp(nodo->nomeArtista, nomeArtistaBuscado) < 0){
		nodo->direita = removerNodoMusica(nodo->direita,nomeArtistaBuscado);
		
	}
	else if(strcmp(nodo->nomeArtista, nomeArtistaBuscado) > 0){
		nodo->esquerda = removerNodoMusica(nodo->esquerda,nomeArtistaBuscado);
	}
	else{
		//O nodo almejado foi encontrado
		if(nodo->esquerda == NULL && nodo->direita == NULL){
			//O nodo em questão não possui filhos
			free (nodo);
			nodo = NULL;
			
		}
		else if(nodo->direita == NULL){
			//Existe um filho a ESQUERDA
			NodoMusica * temp = nodo;
			nodo = nodo->esquerda;
			free(temp);
			
		}
		else if(nodo->esquerda == NULL){
			//Existe um filho a DIREITA
			NodoMusica * temp = nodo;
			nodo = nodo->direita;
			free(temp);
			
		}
		else{
			//possui dois filhos
			NodoArtista * temp = nodo->esquerda;
			
			while(temp->direita != NULL){
				temp = temp->direita;
			}
			
			strcpy(nodo->nomeArtista,temp->nomeArtista);//O nodo recebe o valor do nodo mais a direita
			strcpy(temp->nomeArtista,nomeArtistaBuscado);// O nodo mais a direita recebe o valor a ser removido
			
			nodo->esquerda = removerNodoMusica(nodo->esquerda,nomeArtistaBuscado);
			
		}
	}// ELSE
	
	return nodo;
	
}

//------------| Remover musica da arvore de artistas|------------
NodoArtista* removerMusicaDoArtista(NodoArtista *nodo,Musica * musica){
	
	NodoArtista *artista;
	artista = buscarArtista(nodo,musica->artista);
	
	Ocorrencias *musicaParaRemover;
	musicaParaRemover = buscarOcorrencias(artista->listaAlvo,musica->nome);
	
	Ocorrencias *atual = artista->listaAlvo;//Atual recebe o inicio da lista
	
	if(atual == musicaParaRemover){
		//A musica esta no inicio da lista
		artista->listaAlvo = musicaParaRemover->prox;
		free(musicaParaRemover);
		
	}
	else{
		//A musica esta no meio
		while(atual->prox != musicaParaRemover){
			atual = atual->prox;
		}
		atual->prox = atual->prox->prox;
		free(musicaParaRemover);
		
	}
	if(artista->listaAlvo == NULL){
		//Todas as musicas do artista foram removidas
		nodo = removerNodoArtista(nodo,artista->nomeArtista);
		
	}
	return nodo;
}
//------------| Imprimir Mesmo ano |-------------
void imprimirAnos(CabecaMusica *C, int ano){
	Musica* atual;
	int cont = 0; 
	atual = C->inicio;
	
	while(atual != NULL){
		if(atual->ano == ano){
			imprimirMusica(atual);
			cont++;	
		}
		atual = atual->prox;
		
	}
	if(cont == 0){
		printf("\n\tNao existem musicas com esse ano de lancamento!!!");
	}
}
//------------| Imprimir Ocorrencias|------------
void imprimirOcorrencias(Ocorrencias * inicio){
	Ocorrencias *atual;
	atual = inicio;
	printf("\n\tAs musicas encontradas por esse artista foram: ");
	while(atual != NULL){
		printf("\n\tNome da musica:%s",atual->endereco->nome);
		printf("\n\tAno da musica:%d\n\n",atual->endereco->ano);
		
		atual = atual->prox;
	}
}
//------------| Imprimir Arvoredo|------------
void imprimirArvore(NodoArtista *raiz){
	if(raiz != NULL){
		imprimirArvore(raiz->esquerda);	
		printf("\n\tNome: %s", raiz->nomeArtista);
		imprimirOcorrencias(raiz->listaAlvo);
		imprimirArvore(raiz->direita);
	}
}

//------------| MENU DE OPÇÕES |------------
void menu(CabecaMusica *C){
	int seletor = 1;
	char* nomeArtista = (char*)calloc(50,sizeof(char));
	char* nomeArtistaBuscado = (char*)calloc(50,sizeof(char));
	char* nomeMusicaBuscada = (char*)calloc(50,sizeof(char));
	int ano;
	Musica *musicaRemovida;
	NodoArtista * artistaEncontrado;
	Musica* enderecoMusica;
	Musica* copia = (Musica *)malloc(sizeof(Musica));
	
	//Inicializações
	C = iniciarCabeca();
	
	while(seletor){
		printf("\n\t0 - Sair");
		printf("\n\t1 - Inserir Musica");
		printf("\n\t2 - Listar");
		printf("\n\t3 - Pesquisar musicas por nome do artista");
		printf("\n\t4 - Pesquisar por nome da Musica");
		printf("\n\t5 - Listar musicas por ano");
		printf("\n\t6 - Excluir por nome da Musica");	
		printf("\n\tDigite a opcao desejada: ");
		fflush(stdin);
		scanf("%d",&seletor);
		
		switch (seletor){
			
			case 0:
				printf("\n\tPrograma encerrado!!");
				break;
			case 1://Inserir Musica (lista encadeada, Arvore de musicas e Arvores de artistas)
				enderecoMusica = inserirMusicaLista(C);
				inserirNodoMusica(&(C->indiceMusica),enderecoMusica->nome,enderecoMusica);
				C->indiceArtista = inserirMusicaArtistas(C->indiceArtista,enderecoMusica);
				
				//imprimirArvore(C->indiceArtista);
				break;
			case 2://Listar todas as musicas da lista encadeade
				imprimirLista(C);
				break;
			case 3:
				printf("\n\tInsira o nome do artista para pesquisar: ");
				fflush(stdin);
				scanf("%s",nomeArtistaBuscado);
				strupr(nomeArtistaBuscado);
				artistaEncontrado = buscarArtista(C->indiceArtista,nomeArtistaBuscado);
				if(artistaEncontrado != NULL){
					imprimirOcorrencias(artistaEncontrado->listaAlvo);  	
					
				}
				//imprimirArvore(C->indiceArtista);
				break;
			case 4:
				printf("\n\tInsira o nome da musica para pesquisar: ");
				scanf("%s",nomeMusicaBuscada);
				strupr(nomeMusicaBuscada);
				
				enderecoMusica = buscarMusica(C->indiceMusica, nomeMusicaBuscada);
				if(enderecoMusica != NULL){
					imprimirMusica(enderecoMusica);
				}
				else{
					printf("\n\tMusica nao encontrada!!!");
				}
				break;
			case 5:
				printf("\n\tInsira o ano que deseja pesquisar: ");
				fflush(stdin);
				scanf("%d",&ano);
				imprimirAnos(C,ano);
				
				break;   	
			case 6://Excluir por nome da Musica
				printf("\n\tInsira o nome da musica para remover: ");
				scanf("%s",nomeMusicaBuscada);
				strupr(nomeMusicaBuscada);
				musicaRemovida = buscarMusica(C->indiceMusica,nomeMusicaBuscada);
				
				if(musicaRemovida != NULL){
					*copia = *musicaRemovida;
					removerMusicaLista(C,nomeMusicaBuscada);
					C->indiceMusica = removerNodoMusica(&(C->indiceMusica),nomeMusicaBuscada);
					C->indiceArtista = removerMusicaDoArtista(C->indiceArtista,copia);
				}
				else{
					printf("\n\tMusica nao encontrada!!!");
					
				}
				break;
			
			default:
				printf("\n\tValor invalido!!\n\n");
				break;
		}
	}//while
		
}
int main(){
	CabecaMusica *C = NULL;
	
	menu(C);
	
	return 0;
}