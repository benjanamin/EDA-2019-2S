#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Lista Lista;
typedef struct Nodo Nodo;
int filaImagen;
int columnaImagen;
int filaBuscar;
int columnaBuscar;

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
	Nodo* aux=inicial->cabeza;
	if(inicial!=NULL){
		while(aux->siguiente!=NULL){
			if(aux->valor==valor){
				return 1;
			}
			aux=aux->siguiente;
			
		}
		return 0;
	}
	else{
		return 0;
	}
}
int obtenerTamano(Lista* lista){
	Nodo* aux=lista->cabeza;
	int contador=0;
	if(lista==NULL){
		return 0;
	}
	else{
		contador+=1;
		while(aux->siguiente!=NULL){
			contador+=1;
			aux=aux->siguiente;
		}
	}
	return contador;
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
	return aux;;
}
//Cuenta cuantas veces esta la matrizBuscar en matrizImagen
int verificar(int*** matrizImagen,int*** matrizBuscar){//n^2*(n^2+nc+c)=n
	int distanciaFila=filaImagen-filaBuscar;//c
	int distanciaColumna=columnaImagen-columnaBuscar;//c
	int contador=0;//c
	
	if(distanciaFila<0||distanciaColumna<0){//c
		return 0;
	}
	else{
		for(int i=0;i<=distanciaFila;i++){//n
			for(int j=0;j<=distanciaColumna;j++){//n
				if(sonIguales(matrizImagen,matrizBuscar,filaBuscar,columnaBuscar,i,j)==1){// n^2+nc+c
					contador+=1;//c
				}
			}
		}
		return contador;
	}
}
void obtenerImagenes(int*** matrizImagen,int*** matrizBusqueda){
	for(int i=0;i<4;i++){//4
		printf("Cantidad para rotacion %d: %d \n",i*90,verificar(matrizImagen,matrizBusqueda));
		matrizBusqueda=rotar90(matrizBusqueda);
	}
}

int main(){
	char* nombreImagen="imagen.in";
	char* nombreBusqueda ="buscar.in";
	FILE *fp;
	fp = fopen(nombreImagen, "r"); // read mode
	fscanf(fp,"%d %d",&columnaImagen,&filaImagen);//se lee el tamaño de la matriz
	fclose(fp);
	fp = fopen(nombreBusqueda, "r"); // read mode
	fscanf(fp,"%d %d",&columnaBuscar,&filaBuscar);//se lee el tamaño de la matriz
	fclose(fp);
	int*** imagen=leer(nombreImagen);
	int*** buscar=leer(nombreBusqueda);
	obtenerImagenes(imagen,buscar);
	liberar(filaBuscar,buscar);
	liberar(filaImagen,imagen);

	
	return 0;
}
