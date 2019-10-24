#include <stdio.h>
#include <stdlib.h>
typedef struct matrizGrafo MatrizGrafo;

struct matrizGrafo {
	int vertices;
	int** adyacencias;
};





// Función que genera una matriz cuadrada como arreglo de arreglos, dado un tamaño entero "n".
// Entrada: Número de vértices del grafo
// Salida: Estructura con el numero nodos y una matriz de adyacencia que permita representar un grafo del tamaño indicado.
// Cada valor dentro de la matriz quedara inicializado como -1.

MatrizGrafo* generarMatrizGrafo(int vertices) {
	MatrizGrafo* matriz = (MatrizGrafo*)malloc(sizeof(MatrizGrafo));
	matriz->vertices = vertices;
	matriz->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i;
	for (i = 0; i < vertices; i++) {
		matriz->adyacencias[i] = (int*)calloc(vertices, sizeof(int));
	}
	for(i =0;i<vertices;i++){
		for(int j=0; j<vertices;j++){
			matriz->adyacencias[i][j]=-1;
		}
	}
	return matriz;
}


MatrizGrafo* abrirArchivoMatriz(char *nombreArchivo) {
	int size, nodoAdyacente, i,costo;
	char aux = 0;
	FILE *archivo;
	archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL) {
		return NULL;
	}
	fscanf(archivo, "%d", &size);
	MatrizGrafo* matrizAdyacencia = generarMatrizGrafo(size);
	i = -1;
	aux = getc(archivo);
	while (aux != EOF) {
		if (aux != ' ') {
			while (aux == '\r' || aux == '\n') {
				if (aux == '\r') {
					aux = getc(archivo);
				}
				aux = getc(archivo);
				i++;
			}
			fseek(archivo, -1, SEEK_CUR);
		}
		fscanf(archivo, "%d,%d", &nodoAdyacente,&costo);
		aux = getc(archivo);
		if (i != (nodoAdyacente-1)) {
			matrizAdyacencia->adyacencias[i][nodoAdyacente-1] = costo;
		}
	}
	fclose(archivo);
	return matrizAdyacencia;
	
}

void mayorGrado(MatrizGrafo* matriz){//n*n + nc +c
	int largo= matriz->vertices;
	int aux=0;
	int contador=0;
	int mayor=0;
	for(int i=0;i<largo;i++){
		contador=0;
		for(int j=0;j<largo;j++){
			if(matriz->adyacencias[i][j]!=-1){
				contador+=1;
			}
		}
		if(contador>aux){
			aux=contador;
			mayor=i+1;
		}
	}
	printf("el mayor es el nodo %d con %d vertices \n",mayor,aux);
}
int top(int* cola,int largo){
	return cola[largo-1];
}

int* push(int* cola,int* largo,int numero){
	int* aux= (int*)malloc(sizeof(int)*(*largo+1));
	if(*largo<=0){
		aux[0]=numero;
		*largo=*largo+1;
		return aux;
	}
	else{
		for(int i=0;i<*largo;i++){
			aux[i]=cola[i];
		}
		aux[*largo]=numero;
		*largo=*largo+1;
		return aux;
	}
}
int* pop(int* cola,int* largo){
	if(*largo<=1){
		*largo=0;
		return (int*)malloc(sizeof(int));
	}
	else{
		int* aux= (int*)malloc(sizeof(int)*(*largo-1));
		*largo=*largo-1;
		for(int i=0;i<*largo;i++){
			aux[i]=cola[i];
		}
		return aux;
	}
}

void printPrevio(int destino,int* previo){
	
	if(previo[destino]!=-1){
		printPrevio(previo[destino],previo);
	}
	printf("%d \n",destino+1);
	
	
	
}

void dijkstra(MatrizGrafo* matriz,int inicio,int fin){
	inicio=inicio-1;
	fin=fin-1;
	int j;
	if(inicio==fin){
		printf("termine");
		return;
	}
	else{
		int* cola= (int*) malloc(sizeof(int));
		int largo=0;
		int* visitado=(int*)malloc(sizeof(int)*matriz->vertices);
		int* distancia=(int*)malloc(sizeof(int)*matriz->vertices);
		int* previo=(int*)malloc(sizeof(int)*matriz->vertices);
		for(int i=0;i<matriz->vertices;i++){
			visitado[i]=0;
			distancia[i]=999999999;
			previo[i]=-1;
		}
		cola=push(cola,&largo,inicio);
		distancia[inicio]=0;
		previo[inicio]=-1;
		printf("%d \n",cola[0]);
		while(largo!=0){
			int actual= top(cola,largo);
			cola=pop(cola,&largo);
			if(visitado[actual]){
				continue;
			}
			visitado[actual]=1;
			for(int i=0;i<matriz->vertices;i++){
				int peso;
				if(matriz->adyacencias[actual][i]!=-1){
					peso=matriz->adyacencias[actual][i];
					if(!visitado[i]){
						if(distancia[actual]+peso<distancia[i]){
							distancia[i]=distancia[actual]+peso;
							previo[i]=actual;
							cola=push(cola,&largo,i);
						}
					}
				}
			}
		}
		
		printPrevio(fin,previo);
		printf("f \n");
	}
	
	
	
}

int main(){
	char* archivo= "archivoPrueba.txt";
	MatrizGrafo* matriz;
	matriz=abrirArchivoMatriz(archivo);
	printf("%d \n",matriz->adyacencias[1][2]);
	mayorGrado(matriz);
	dijkstra(matriz,1,6);
	printf("finish");
	return 0;
}
