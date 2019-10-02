#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct Nodo Nodo;
int filaImagen;
int columnaImagen;
int filaBuscar;
int columnaBuscar;

struct Nodo{
	int valor;
	int cantidad;
	Nodo* siguiente;
};
//crea un nodo
Nodo* crearNodo(int valor){
	Nodo* nodo= (Nodo*)malloc(sizeof(Nodo));
	nodo->siguiente=NULL;
	nodo->valor=valor;
	nodo->cantidad=1;
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
int getValor(Nodo* cabezal,int numero){
	Nodo* aux= cabezal;
	int contador=1;
	while(contador!=numero){
		if(cabezal==NULL){
			return 0;
		}
		else{
			aux=aux->siguiente;
			contador+=1;
		}
	}
	return aux->valor;
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
		if(nodo->valor<cabezal->valor){
				nodo->siguiente=cabezal;
				return nodo;
			}
		aux->siguiente=nodo;
		return cabezal;
	}
}

int*** leer(char* Nombre){//se encarga de leer la matriz, primero lee el ancho y luego la altura para asi crear una matriz
	int m,n=0;
	FILE *fp;
	fp = fopen(Nombre, "r"); // read mode
    if (fp == NULL)
    {
    	FILE *fptr;
		fprintf(fptr,"ERROR, NO SE ENCUENTRA EL ARCHIVO");
		fclose(fptr);
    	exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d %d",&n,&m);//se lee el tamaño de la matriz
    int*** matriz=(int ***)malloc(m * sizeof(int **)); 
    // a cada columna le asigna otro array
    for (int i = 0; i < m; i++) {
        matriz[i] = (int **)malloc(n * sizeof(int *));
        for(int j=0;j<n;j++){
        	matriz[i][j]=(int *)malloc(3* sizeof(int *));
		}
    }
    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		fscanf(fp,"%d,%d,%d ",&matriz[i][j][0],&matriz[i][j][1],&matriz[i][j][2]);	
		}
	}
    fclose(fp);
    return matriz;   
}
void liberar(int m,int*** arreglo){//libera la memoria del array
	for(int i=0;i<m;i++){
		free(arreglo[i]);
	}
	free(arreglo);
}
void printMatriz(int*** matriz,int m,int n){// imprime la matriz
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d,%d,%d ",matriz[i][j][0],matriz[i][j][1],matriz[i][j][2]);
		}
		printf("\n");
	}
}

// intercambia las posiciones para asi rotar las imagenes
int*** rotar90(int*** matriz){//n*c+n^2*c+n(n-1)3c
	int m=filaBuscar;//c
	int n=columnaBuscar;//c
	int*** matrizRotada=(int ***)malloc(n * sizeof(int **)); //c
    // a cada columna le asigna otro array
    for (int i = 0; i < n; i++) {//n
        matrizRotada[i] = (int **)malloc(m * sizeof(int*));//c
        for(int j=0;j<m;j++){//n
        	matrizRotada[i][j]=(int *)malloc(3* sizeof(int *));//c
		}
    }
    for(int i=m-1;i>=0;i--){//n-1
    	for(int j=0;j<n;j++){//n
    		for(int k=0;k<3;k++){//3
    			matrizRotada[j][m-i-1][k]=matriz[i][j][k];//c
			}
		}
	}
	filaBuscar=n;
	columnaBuscar=m;
    return matrizRotada;
}
//compara si 2 matrices son iguales
int sonIguales(int*** matriz1,int*** matriz2,int m,int n, int mInicial , int nInicial){//n^2+nc
	int aux=0;
	for(int i=0;i<m;i++){//n
		for(int j=0;j<n;j++){//n
			if(matriz1[i+mInicial][j+nInicial][0]==matriz2[i][j][0]&&matriz1[i+mInicial][j+nInicial][1]==matriz2[i][j][1]&&matriz1[i+mInicial][j+nInicial][2]==matriz2[i][j][2]){
				aux+=1;
			} 
		}
	}

	return aux;
}
//Cuenta cuantas veces esta la matrizBuscar en matrizImagen
Nodo* verificar(int*** matrizImagen,int*** matrizBuscar,Nodo* cabezal){//n^2*(n^2+nc+c)=n
	int distanciaFila=filaImagen-filaBuscar;//c
	int distanciaColumna=columnaImagen-columnaBuscar;//c
	int contador=0;//c
	
	if(distanciaFila<0||distanciaColumna<0){//c
		return cabezal;
	}
	else{
		for(int i=0;i<=distanciaFila;i++){//n
			for(int j=0;j<=distanciaColumna;j++){//n
				contador=sonIguales(matrizImagen,matrizBuscar,filaBuscar,columnaBuscar,i,j);
				if(contador!=0){
					if(estaEnLaLista(cabezal,contador)){
						buscar(cabezal,contador)->cantidad=buscar(cabezal,contador)->cantidad+1;
					}
					else{
						cabezal=agregarOrdenado(cabezal,crearNodo(contador)); 
					}
				}
				contador=0;
			}
		}
		return cabezal;
	}
}
Nodo* obtenerImagenes(int*** matrizImagen,int*** matrizBusqueda,Nodo* cabezal){
	//for(int i=0;i<4;i++){//4
		cabezal=verificar(matrizImagen,matrizBusqueda,cabezal);
	//	matrizBusqueda=rotar90(matrizBusqueda);
	//}
	return cabezal;
}

double promedio(Nodo* cabezal){
	int numerador=0;
	int denominador=0;
	Nodo* aux=cabezal;
	
	while(aux->siguiente!=NULL){
		numerador=numerador+aux->valor*aux->cantidad;
		denominador=denominador+aux->cantidad;
		aux=aux->siguiente;
	}
	numerador=numerador+aux->valor*aux->cantidad;
	denominador=denominador+aux->cantidad;
	return numerador/denominador;
}
int getMayor(Nodo *nodo){
	int mayor=0;
	Nodo* aux=nodo;
	while(aux->siguiente!=NULL){
		if(aux->valor>mayor){
			mayor=aux->valor;
		}
		aux=aux->siguiente;
	}
	if(aux->valor>mayor){
		mayor=aux->valor;
	}
	return mayor;
}
int getMenor(Nodo *nodo){
	int menor=999999;
	Nodo* aux=nodo;
	while(aux->siguiente!=NULL){
		if(aux->valor<menor){
			menor=aux->valor;
		}
		aux=aux->siguiente;
	}
	if(aux->valor<menor){
		menor=aux->valor;
	}
	return menor;
}

void liberarNodo(Nodo* cabezal){
	Nodo* aux=cabezal;
	while(aux->siguiente!=NULL){
		aux=aux->siguiente;
		free(cabezal);
		cabezal=aux;
	}
	free(aux);
}
double getDesviacionEstandar(Nodo* cabezal,double promedio){
	Nodo* aux=cabezal;
	double acum=0;
	while(aux->siguiente!=NULL){
		acum=acum+(abs(aux->valor-promedio)^2);
		aux=aux->siguiente;
	}
	acum=acum+(abs(aux->valor-promedio)^2);
	acum=(sqrt(acum)/getLargo(cabezal));
	return acum;
}

void getDatosOrdenados(Nodo* cabezal){
	printf("promedio= %f \n",promedio(cabezal));
	 Nodo* aux=cabezal;
	 Nodo* aux2=NULL;
	 while(aux->siguiente!=NULL){
	 	for(int i=0;i<aux->cantidad;i++){
	 		aux2=agregarOrdenado(aux2,crearNodo(aux->valor));
		 }
		 aux=aux->siguiente;	 	
	 }
	for(int i=0;i<aux->cantidad;i++){
		aux2=agregarOrdenado(aux2,crearNodo(aux->valor));
	}
	liberarNodo(aux2);
}


int main(){
	char* nombreImagen="imagen.in";
	char* nombreBusqueda ="buscar.in";
	FILE *fp;
	Nodo* cabeza=NULL;
	fp = fopen(nombreImagen, "r"); // read mode
	fscanf(fp,"%d %d",&columnaImagen,&filaImagen);//se lee el tamaño de la matriz
	fclose(fp);
	fp = fopen(nombreBusqueda, "r"); // read mode
	fscanf(fp,"%d %d",&columnaBuscar,&filaBuscar);//se lee el tamaño de la matriz
	fclose(fp);
	int*** imagen=leer(nombreImagen);
	int*** buscar=leer(nombreBusqueda);
	cabeza=obtenerImagenes(imagen,buscar,cabeza);
	liberar(filaBuscar,buscar);
	liberar(filaImagen,imagen);
	getDatosOrdenados(cabeza);
	liberarNodo(cabeza);
	printf(" termino ");
	
	return 0;
}
