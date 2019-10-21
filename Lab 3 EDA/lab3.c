#include <stdio.h>
#include <stdlib.h>

typedef struct matrizGrafo {
	int vertices;
	int** adyacencias;
}MatrizGrafo;


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

int main(){
	char* archivo= "archivoPrueba.txt";
	MatrizGrafo* matriz;
	matriz=abrirArchivoMatriz(archivo);
	printf("%d \n",matriz->adyacencias[0][3]);
	mayorGrado(matriz);
	printf("finish");
	return 0;
}
