#include <stdio.h>
#include <stdlib.h>

typedef struct matrizGrafo {
	int vertices;
	int** adyacencias;
}MatrizGrafo;

// Función que genera una matriz cuadrada como arreglo de arreglos, dado un tamaño entero "n".
// Entrada: Número de vértices del grafo
// Salida: Estructura con el número nodos y una matriz de adyacencia que permita representar un grafo del tamaño indicado.
// Cada valor dentro de la matriz quedará inicializado como 0.
MatrizGrafo* generarMatrizGrafo(int vertices) {
	MatrizGrafo* matriz = (MatrizGrafo*)malloc(sizeof(MatrizGrafo));
	matriz->vertices = vertices;
	matriz->adyacencias = (int**)malloc(vertices * sizeof(int*));
	int i;
	for (i = 0; i < vertices; i++) {
		matriz->adyacencias[i] = (int*)calloc(vertices, sizeof(int));
	}
	return matriz;
}

// Función que lee el archivo de texto con el grafo y traspasa su información a una matriz de adyacencia.
// Entrada: Arreglo de caracteres con el nombre del archivo que posee el grafo
// Salida: Estructura con el número de nodos del grafo y su representación como matriz de adyacencia.
MatrizGrafo* abrirArchivoMatriz(char *nombreArchivo) {
	int size, nodoAdyacente, i;
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
		fscanf(archivo, "%d", &nodoAdyacente);
		aux = getc(archivo);
		if (i != (nodoAdyacente-1)) {
			matrizAdyacencia->adyacencias[i][nodoAdyacente-1] = 1;
		}
	}
	fclose(archivo);
	return matrizAdyacencia;
}

//Función para simplificar el mostrar por pantalla la matriz de adyacencia
// Entrada: Estructura que contiene el grafo a mostrar por pantalla.
void imprimirMatrizAdyacencia(MatrizGrafo* matriz) {
	int i, j;
	for (i = 0; i < matriz->vertices; i++) {
		for (j = 0; j < matriz->vertices; j++) {
			printf("%d ", matriz->adyacencias[i][j]);
		}
		printf("\n");
	}
}

// Función para verificar si dos nodos A y B son adyacentes entre si en un grafo no dirigido.
// Entradas: Struct que contiene el grafo como matriz de adyacencia, ints que representan los nodos a verificar
// Salida: Entero que indica si los nodos son adyacentes (0 = falso, 1 = verdadero)
int adyacenciaNodos(MatrizGrafo* matriz, int nodoA, int nodoB) {

	if (matriz->adyacencias[nodoA - 1][nodoB - 1] == 1) {
		return 1;
	}
	return 0;
}

// Función para contar el grado de cada nodo de un grafo.
// Entrada: Estructura con el grafo como matriz de adyacencia.
// Salida: Lista con el grado de cada nodo, siguiendo el orden de los nodos.
int* gradosGrafo(MatrizGrafo* matriz) {

	int* listaGrados = (int*) malloc(sizeof(int) * matriz->vertices);
	for (int i = 0; i < matriz->vertices; i++) {
		int grado = 0;
		for (int j = 0; j < matriz->vertices; j++) {
			if (matriz->adyacencias[i][j]) {
				grado++;
			}
		}
		listaGrados[i] = grado;
	}

	return listaGrados;
}

// Función que verifica si un grafo es K regular (que cada nodo tiene grado K)
// Entrada: Lista de enteros con los grados de los nodos de un árbol, entero con el tamaño de la lista, entero que representa K
// Salida: Entero que representa un valor de verdadero/falso
int esKRegular(int* listaGrados, int size, int k) {

	for (int i = 0; i < size; i++) {
		if (listaGrados[i] != k) {
			return 0;
		}
	}
	return 1;
}

// Función que verifica si un grafo es completo (que todos sus nodos están conectados entre si)
// Entrada: Estructura con el grafo como matriz de adyacencia.
// Salida: Entero que representa un valor de verdadero/falso.
int esCompleto(MatrizGrafo* matriz) {

	for (int i = 0; i < matriz->vertices; i++) {
		for (int j = 0; j < matriz->vertices; j++) {
			if ((i != j) && (matriz->adyacencias[i][j] != 1)) {
				return 0;
			}
		}
	}
	return 1;
}

// Función que verifica si un conjunto de nodos dado es camino dentro de un grafo.
// Entrada: Estructura con el grafo como matriz de adyacencia, lista de enteros con los nodos a verificar, entero con el tamaño de dicha lista.
// Salida: Entero que representa un valor de verdadero/falso.
int esCamino(MatrizGrafo* matriz, int* camino, int sizeCamino) {

	for (int i = 0; i < (sizeCamino - 1); i++) {
		if (matriz->adyacencias[camino[i] - 1][camino[i+1] -1] == 0) {
			return 0;
		}
	}
	return 1;
}

// Función que verifica si un camino es ciclo, verificando si el último nodo es igual al primero de la lista con el ciclo a verificar
// Entrada: Estructura con el grafo como matriz de adyacencia, lista de enteros con los nodos a verificar, entero con el tamaño de dicha lista.
// Salida: Entero que representa un valor de verdadero/falso.
int esCiclo(MatrizGrafo* matriz, int* camino, int sizeCamino) {

	if (esCamino(matriz, camino, sizeCamino)) {
		if (camino[0] == camino[sizeCamino - 1])
			return 1;
	}
	return 0;
}

/*
// Función que verifica si un camino es ciclo, verificando si desde el último elemento se puede llegar al primero
int esCiclo(MatrizGrafo* matriz, int* camino, int sizeCamino) {

	if (esCamino(matriz, camino, sizeCamino)) {
		if (matriz->adyacencias[camino[0] - 1][camino[sizeCamino - 1] - 1] == 1)
			return 1;
	}
	return 0;
}
*/
// Es posible fusionar ambas funciones previas, para que respondan a ambos casos

// Función que verifica si un conjunto de nodos es clique (que entre ellos formen un grafo completo interno).
// Entrada: Estructura con el grafo como matriz de adyacencia, lista de enteros con los nodos a verificar, entero con el tamaño de dicha lista.
// Salida: Entero que representa un valor de verdadero/falso.
int esClique(MatrizGrafo* matriz, int* conjunto, int sizeConjunto) {

	for (int i = 0; i < sizeConjunto; i++) {
		for (int j = 0; j < sizeConjunto - 1; j++)
			if ((i != j) && (matriz->adyacencias[conjunto[i] - 1][conjunto[j] -1] == 0)) {
				return 0;
			}
	}
	return 1;
}

// Función que verifica si un conjunto de nodos es conjunto independiente (que entre ellos no exista ninguna conexión).
// Entrada: Estructura con el grafo como matriz de adyacencia, lista de enteros con los nodos a verificar, entero con el tamaño de dicha lista.
// Salida: Entero que representa un valor de verdadero/falso.
int esConjuntoIndependiente(MatrizGrafo* matriz, int* conjunto, int sizeConjunto) {

	for (int i = 0; i < sizeConjunto; i++) {
		for (int j = 0; j < sizeConjunto - 1; j++)
			if ((i != j) && (matriz->adyacencias[conjunto[i] - 1][conjunto[j] -1] == 1)) {
				return 0;
			}
	}
	return 1;
}

int main() {

	// Llamado abrirArchivoMatriz
	MatrizGrafo* matrizAdyacencia = abrirArchivoMatriz("ejemplo.txt");
	if (matrizAdyacencia == NULL) {
		printf("Archivo no encontrado.");
		return -1;
	}
	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(matrizAdyacencia);
	printf("----------\n");

	// Llamado adyacenciaNodos

	// VARIAR PARA PROBAR ADYACENCIA NODOS
	int nodoA = 1;
	int nodoB = 3;
	if (adyacenciaNodos(matrizAdyacencia, nodoA, nodoB)) {
		printf("Los nodos %d y %d son adyacentes\n", nodoA, nodoB);
	}
	else {
		printf("Los nodos %d y %d no son adyacentes\n", nodoA, nodoB);
	}

	// Llamado gradosGrafo
	int* listaGrados = gradosGrafo(matrizAdyacencia);
	for(int i = 0; i < matrizAdyacencia->vertices; i++) {
		printf("El nodo %d tiene grado %d\n", i+1, listaGrados[i]);
	}

	// Llamado esKRegular
	int k = 2;
	if (esKRegular(listaGrados, matrizAdyacencia->vertices, k)) {
		printf("El grafo es %d-regular\n", k);
	}
	else {
		printf("El grafo no es %d-regular\n", k);
	}
	free(listaGrados);

	// Llamado esCompleto
	if (esCompleto(matrizAdyacencia))
		printf("El grafo es completo\n");
	else
		printf("El grafo no es completo\n");

	// Llamado esCamino

	// VARIAR PARA PROBAR ESCAMINO, ESCICLO, ESCLIQUE Y ESCONJUNTOINDEPENDIENTE
	// ASEGURESE DE COMPLETAR camino[] SEGUN EL TAMAÑO QUE USTED DECIDA 
	int sizeCamino = 3;
	int* camino = (int*) malloc(sizeof(int) * sizeCamino);
	camino[0] = 1;
	camino[1] = 2;
	camino[2] = 7;
	
	printf("La secuencia [");
	for (int  i = 0; i < sizeCamino; i++) {
		if (i != (sizeCamino - 1))
			printf("%d, ", camino[i]);
		else
			printf("%d]", camino[i]);
	}
	if (esCamino(matrizAdyacencia, camino, sizeCamino))
		printf(" es camino.\n");
	else
		printf(" no es camino.\n");

	// Llamado esCiclo
	printf("La secuencia [");
	for (int  i = 0; i < sizeCamino; i++) {
		if (i != (sizeCamino - 1))
			printf("%d, ", camino[i]);
		else
			printf("%d]", camino[i]);
	}
	if (esCiclo(matrizAdyacencia, camino, sizeCamino))
		printf(" es ciclo.\n");
	else
		printf(" no es ciclo.\n");

	// Llamado esClique
	printf("El conjunto [");
	for (int  i = 0; i < sizeCamino; i++) {
		if (i != (sizeCamino - 1))
			printf("%d, ", camino[i]);
		else
			printf("%d]", camino[i]);
	}
	if (esClique(matrizAdyacencia, camino, sizeCamino))
		printf(" es clique.\n");
	else
		printf(" no es clique.\n");

	// Llamado esConjuntoIndependiente
	printf("El conjunto [");
	for (int  i = 0; i < sizeCamino; i++) {
		if (i != (sizeCamino - 1))
			printf("%d, ", camino[i]);
		else
			printf("%d]", camino[i]);
	}
	if (esConjuntoIndependiente(matrizAdyacencia, camino, sizeCamino))
		printf(" es conjunto independiente.\n");
	else
		printf(" no es conjunto independiente.\n");
	free(camino);

	return 0;
}