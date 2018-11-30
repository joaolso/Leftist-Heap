#include <stdlib.h>
#include <stdio.h>

// Estrutura do No 								//
// key = valor 								    //
// ccn = minimo comprimento do caminho nulo     //
// right = ponteiro filho da direita			//
// left = pronteiro filho da esquerda			//
// pai = pai do no								//

int opp=0;
struct node * merge(struct node*, struct node*);
struct node * mergeT(struct node*, struct node*);

struct node {												// Contrucao da estrutura dos NOS
	int key, ccn;
	struct node *right, *left;
}


*temp, *root;

struct node * deletar(struct node * root){
	root=merge(root->right,root->left);
}

int visualiza(struct node *ra){							// funcao que imprime em in-Ordem
	if(ra!=NULL){											// verifica a condicao de NULL (folha da raiz)
		visualiza(ra->left);								// recurssao filho da esquerda
		printf(" |%d| ",ra->key);							// imprime na tela
		visualiza(ra->right);								// recurssao filho da direita
	}
}


int distance(struct node *m){
	if(m==NULL)
		return(-1);
	else
	return(m->ccn);
}

struct node * merge (struct node *root, struct node *newnode){
	if (root==NULL)											// condicoes de parada da recurssao
		return newnode; 
	if (newnode==NULL) 										// condicoes de para da recurssao
		return root;
	if (newnode->key < root->key){
		temp=root;
		root=newnode;
		newnode=temp;
	}
	
	root->right = merge(root->right, newnode);
	
	if (distance(root->right) > distance(root->left)){
		opp++;
		temp=root->right;
		root->right=root->left;
		root->left=temp;
	}
	if (root->right==NULL){
		root->ccn=0;
	}	
	else{
		root->ccn = 1+(root->right->ccn);
	}
	return (root);
}														
												
struct node * inserir(int valor) {
	if (root->key==0){
		root->key=valor;
	}else{													// Funcao inseri novo no, tabalha juntamente da funcao merge// retorna a funcao							
		struct node *newnode;								// Constroi o pronteiro
		newnode=(struct node *)malloc(sizeof(struct node));	// Aloca espaco na memoria
		newnode->right=NULL;								// default inicilizacao e garantia de nao coleta de lixo	
		newnode->left=NULL;									// *
		newnode->ccn=0;										// *
		newnode->key = valor;								// *
		root=merge(root, newnode);							// *
	}
	return (root);
}

int main(){

	root=(struct node *)malloc(sizeof(struct node));		//Constoi a raiz ao iniciar o programa
	root->right=NULL;
	root->left=NULL;
	root->key=0;
	root->ccn=0;
	
	while(1){
		printf("\n Escolha a opcao: \n 1.Inserir 2.Visualizar 3.Deletar(Min) 4.Sair\n");
		int valor,opc=0;
		int paratudo=0;
		scanf("%d",&opc);
			switch(opc){
			case 1:
				system("cls");
				printf("Informe o valor: ");
				scanf("%d",&valor);
				inserir(valor);
				break;
			case 2:
				visualiza(root);
				printf("\nRaiz: %d\n",root->key);
				printf("CCN Raiz: %d\n",root->ccn);
				printf("Qtd de rotacoes(filhos): %d\n", opp);
				break;
			case 3:
				root=deletar(root);
				break;
			case 4:
				paratudo=1;
				break;
			default:
				break;
			}
			if(paratudo==1)
			break;
	}
}

