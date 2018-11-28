#include <stdlib.h>
#include <stdio.h>

// Estrutura do No 								//
// key = valor 								    //
// ccn = minimo comprimento do caminho nulo     //
// right = ponteiro filho da direita			//
// left = pronteiro filho da esquerda			//
// pai = pai do no								//

struct node {												// Contrucao da estrutura dos NOS
	int key, ccn;
	struct node *right, *left, *prnt;
}

*temp, *root;

void visualiza(struct node *ra){							// funcao que imprime em in-Ordem
	if(ra!=NULL){											// verifica a condicao de NULL (folha da raiz)
		visualiza(ra->left);								// recurssao filho da esquerda
		printf("\t%d: ",ra->key);							// imprime na tela
		visualiza(ra->right);								// recurssao filho da direita
	}
}

int distancia(struct node *d){								// funcao que verifica os ccn
	if(d==NULL)												
		return(-1);
	else
	return(d->ccn);
}


struct node * merge (struct node *root,struct node *newnode){
	if (root==NULL)											// condicoes de parada da recurssao
		return newnode; 
	if (newnode==NULL) 										// condicoes de para da recurssao
		return root;
	if (root->key < newnode->key){ 							// faz a troca de sub-arvores
		temp=root;
		root=newnode;
		root=temp;											// troca de valor com raiz e temp
	}													
	root->right=merge(root->right,newnode);					// recurssao, ele so sai da recursao quando barrar nas condicoes do if e sacar fora
	
	if(distancia(root->right)>distancia(root->left)){		// troca de irmaos quando ccn da direita e maior que o da esquerda			
		temp=root->right;									// troca filho da direita para temp
		root->right=root->left;								// troca filho da direita pelo da esquerda
		root->left=temp;									// troca filho da esquerda pelo temp
	}
	
	if(root->right==NULL)									// verifica se a um ccn proximo
		root->ccn=0;										// atribui valor do ccn
	else
		root->ccn=1+(root->right->ccn);							// nicremeta cc se nao for null incrementa +1
	return(root);											// retorna a raiz
}

struct node * inserir(struct node *root, int valor) {		// Funcao inseri novo no, tabalha juntamente da funcao merge
	if (root->key==0){										// verifica se ja existe uma raiz se tiver valor 0 ele ja foi criada
		root->key = valor;									// atribui o valor a raiz
		return(root);										// retorna a funcao
	}else {								
		struct node *newnode;								// Constroi o pronteiro
		newnode=(struct node *)malloc(sizeof(struct node));	// Aloca espaco na memoria
		newnode->right=NULL;								// default inicilizacao e garantia de nao coleta de lixo	
		newnode->left=NULL;									//
		newnode->ccn=0;										//
		newnode->prnt=NULL;									//
		newnode->key = valor;								//
		root=merge(root, newnode);							//
	}
}

int main(){
	root=(struct node *)malloc(sizeof(struct node));		//Constoi a raiz ao iniciar o programa
	root->right=NULL;
	root->left=NULL;
	root->key=0;
	root->ccn=0;
	root->prnt=NULL;

	
	while(1){
		printf("\n Escolha a opcao: \n 1.Inserir 2.Visualizar 3.Sair\n");
		int valor,opc=0;
		int paratudo=0;
		scanf("%d",&opc);
			switch(opc){
			case 1:
				printf("Informe o valor: ");
				scanf("%d",&valor);
				inserir(root,valor);
				break;
			case 2:
				visualiza(root);
				break;
			case 3:
				paratudo=1;
				break;
			default:
				break;
			}
			
			if(paratudo==1)
			break;
	}
}

