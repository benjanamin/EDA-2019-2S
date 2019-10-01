#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo Nodo;

struct Nodo{
	int valor;
	Nodo* siguiente;
};
//crea un nodo
Nodo* crearNodo(int valor){
	Nodo* nodo= (Nodo*)malloc(sizeof(Nodo));
	nodo->siguiente=NULL;
	nodo->valor=valor;
	return nodo;
}
//libera la memoria
void destruirNodo(Nodo *nodo){
	free(nodo);
}
//agrega un nodo al final
Nodo* agregarNodo(Nodo* cabeza,Nodo* nodo){
	if(cabeza==NULL){
		cabeza=nodo;
		return cabeza;
	}
	else{
		Nodo* aux=cabeza;
		
		while(aux->siguiente!=NULL){
			aux=aux->siguiente;
		}
		aux->siguiente=nodo;
		return cabeza;
	}
}
int estaEnLaLista(Nodo* inicial,int valor){
	Nodo* aux=inicial;
	if(inicial!=NULL){
		while(aux->siguiente!=NULL){
			if(aux->valor==valor){
				return 1;
			}
			aux=aux->siguiente;
			
		}
		if(aux->valor==valor){
			return 1;
		}
		return 0;
	}
	else{
		return 0;
	}
}

//imprime todos los valor3es de la lista
void printear(Nodo* inicial){
	Nodo* aux= inicial;
	while(aux->siguiente!=NULL){
		printf("%d ",aux->valor);
		aux=aux->siguiente;
	}
	printf("%d",aux->valor);
}

Nodo* buscar(Nodo* cabezal,int valor){
	if(cabezal==NULL){
		return NULL;
	}
	else{
		Nodo* aux= cabezal;
		while(aux->siguiente!=NULL){
			if(aux->valor==valor){
				return aux;
			}
			aux=aux->siguiente;
		}
		if(aux->valor==valor){
			return aux;
		}
		else{
			return NULL;
		}
	}
}
int getLargo(Nodo* cabezal){
	Nodo* aux= cabezal;
	int contador=0;
	while(aux->siguiente!=NULL){
		contador+=1;
		aux=aux->siguiente;
	}
	contador+=1;
	return contador;
}

Nodo* agregarOrdenado(Nodo* cabezal,Nodo* nodo){
	if(cabezal==NULL){
		return nodo;
	}
	else{
		Nodo* aux=cabezal;
		while(aux->siguiente!=NULL){
			if(nodo->valor<cabezal->valor){
				nodo->siguiente=cabezal;
				return nodo;
			}
			else{
				if(aux->siguiente->valor>nodo->valor){
					nodo->siguiente=aux->siguiente;
					aux->siguiente=nodo;
					return cabezal;
				}
				else{
					aux=aux->siguiente;
				}
			}
		}
		aux->siguiente=nodo;
		return cabezal;
	}
}

int main(){
	Nodo* cabeza=NULL;
	Nodo* pepe=crearNodo(5);
	cabeza=agregarOrdenado(cabeza,pepe);
	cabeza=agregarOrdenado(cabeza,crearNodo(32));
	cabeza=agregarOrdenado(cabeza,crearNodo(1));
	cabeza=agregarOrdenado(cabeza,crearNodo(4));
	printear(cabeza);
	
}
