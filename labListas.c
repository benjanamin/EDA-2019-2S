#include <stdio.h>
#include <stdlib.h>
typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Lista{
	Nodo *cabeza;
};
struct Nodo{
	int valor;
	Nodo* siguiente;
};

Nodo* crearNodo(int valor){
	Nodo* nodo= (Nodo*)malloc(sizeof(Nodo));
	nodo->siguiente=NULL;
	nodo->valor=valor;
	return nodo;
}

void destruirNodo(Nodo *nodo){
	free(nodo);
}
void insertarPrincipio(Lista* inicial,int valor){
	if(inicial->cabeza==NULL){
		Nodo* nodo=crearNodo(valor);
		inicial->cabeza->siguiente=nodo;
	}
	else{
		Nodo* nodo= crearNodo(valor);
		nodo->siguiente=inicial->cabeza;
		inicial->cabeza=nodo;
	}
}
void insertarFinal(Lista* inicial,int valor){
	Nodo* nodo=crearNodo(valor);
	if(inicial->cabeza!=NULL){
		
		Nodo* aux= inicial->cabeza;
		while(aux->siguiente!=NULL){
			aux=aux->siguiente;
		}
		aux->siguiente=nodo;
	}
	else{
		inicial->cabeza=nodo;
	}
}
void insertarOrdenado(Lista* inicial,int valor){
	Nodo* nodo=crearNodo(valor);
	Nodo* aux= inicial->cabeza;
	Nodo* aux2=aux;
	if(inicial->cabeza==NULL){
		inicial->cabeza=nodo;
	}
	else{
		while(aux->siguiente!=NULL){
			if(aux->valor>valor){
				nodo->siguiente=aux;
			}
			else{
				
			}
			aux=aux->siguiente;
		}
	}
}
void printear(Lista* inicial){
	Nodo* aux= inicial->cabeza;
	while(aux->siguiente!=NULL){
		printf("%d ",aux->valor);
		aux=aux->siguiente;
	}
	printf("%d",aux->valor);
}
void insertarDespuesDeN(Lista* inicial,int valor,int despuesDe){
	Nodo* nodo=crearNodo(valor);
	Nodo* aux= inicial->cabeza;
	if(inicial->cabeza==NULL){
		inicial->cabeza=nodo;
	}
	else{
		while(aux->valor!=despuesDe){
			if(aux->siguiente!=NULL){
				aux=aux->siguiente;
			}
			else{
				break;
			}
		}
		nodo->siguiente=aux->siguiente;
		aux->siguiente=nodo;
	}
}

int estaEnLaLista(Lista* inicial,int valor){
	
	if(inicial->cabeza==NULL){
		
		return 0;
	}
	
	else{
		printf("%d",inicial->cabeza);
		printf("holo");
		Nodo* aux=inicial->cabeza;
		while(aux->siguiente!=NULL){
			if(aux->valor==valor){
				return 1;
			}
			aux=aux->siguiente;
			
		}
		return 0;
	}
}
int obtenerTamano(Lista* lista){
	printf("entre");
	int contador=0;
	if(lista->cabeza==NULL){
		return 0;
	}
	else{
		Nodo* aux=lista->cabeza;
		contador+=1;
		while(aux->siguiente!=NULL){
			contador+=1;
			aux=aux->siguiente;
		}
	}
	return contador;
}
/*void insertarEnN(Lista* inicial,int valor,int contador){
	int contadorAux=0;
	Nodo* nodo=crearNodo(valor);
	Nodo* aux= inicial->cabeza;
	if(inicial->cabeza==NULL){
		inicial->cabeza=nodo;
	}
	else{
		while(aux->siguiente!=NULL){
			if(contador==contadorAux+1){
		
			}
			aux->siguiente
		}
		nodo->siguiente=aux->siguiente;
		aux->siguiente=nodo;
	}
}*/

void darVuelta(Lista* lista){
	Nodo* aux=lista->cabeza;
	Nodo* aux2=NULL;
	while(aux2->siguiente!=NULL){
		
	}
}
int main(){
	Lista* lista=(Lista*)malloc(sizeof(Lista));

	Nodo* pepe=crearNodo(1);
	lista->cabeza=pepe;
	insertarPrincipio(lista,0);
	insertarFinal(lista,2);
	insertarFinal(lista,3);
	insertarDespuesDeN(lista,32,5);
	insertarPrincipio(lista,41);
	printear(lista);
	printf(" %d ",lista->cabeza->valor);
	free(pepe);
	printf("\n");
	
	
	
	return 0;
}
