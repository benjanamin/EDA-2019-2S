#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int filaImagen;
int columnaImagen;
int filaBuscar;
int columnaBuscar;
int*** leer(char* Nombre){
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
void liberar(int m,int*** arreglo){
	for(int i=0;i<m;i++){
		free(arreglo[i]);
	}
	free(arreglo);
}
void printMatriz(int*** matriz,int m,int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d,%d,%d ",matriz[i][j][0],matriz[i][j][1],matriz[i][j][2]);
		}
		printf("\n");
	}
}


int*** rotar90(int*** matriz){
	int m=filaBuscar;
	int n=columnaBuscar;
	int*** matrizRotada=(int ***)malloc(n * sizeof(int **)); 
    // a cada columna le asigna otro array
    for (int i = 0; i < n; i++) {
        matrizRotada[i] = (int **)malloc(m * sizeof(int*));
        for(int j=0;j<m;j++){
        	matrizRotada[i][j]=(int *)malloc(3* sizeof(int *));
		}
    }
    for(int i=m-1;i>=0;i--){
    	for(int j=0;j<n;j++){
    		for(int k=0;k<3;k++){
    			matrizRotada[j][m-i-1][k]=matriz[i][j][k];
			}
		}
	}
	filaBuscar=n;
	columnaBuscar=m;
    return matrizRotada;
}
int sonIguales(int*** matriz1,int*** matriz2,int m,int n, int mInicial , int nInicial){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(matriz1[i+mInicial][j+nInicial][0]!=matriz2[i][j][0]||matriz1[i+mInicial][j+nInicial][1]!=matriz2[i][j][1]||matriz1[i+mInicial][j+nInicial][2]!=matriz2[i][j][2]){
				return 0;
			} 
		}
	}
	return 1;
}
int verificar(int*** matrizImagen,int*** matrizBuscar){
	int distanciaFila=filaImagen-filaBuscar;
	int distanciaColumna=columnaImagen-columnaBuscar;
	int contador=0;
	
	if(distanciaFila<0||distanciaColumna<0){
		return 0;
	}
	else{
		for(int i=0;i<=distanciaFila;i++){
			for(int j=0;j<=distanciaColumna;j++){
				if(sonIguales(matrizImagen,matrizBuscar,filaBuscar,columnaBuscar,i,j)==1){
					contador+=1;
				}
			}
		}
		return contador;
	}
}
void obtenerImagenes(int*** matrizImagen,int*** matrizBusqueda){
	for(int i=0;i<4;i++){
		printf("Cantidad para rotacion %d: %d \n",i*90,verificar(matrizImagen,matrizBusqueda));
		matrizBusqueda=rotar90(matrizBusqueda);
	}
}

int main(){
	FILE *fp;
	fp = fopen("imagen2.in", "r"); // read mode
	fscanf(fp,"%d %d",&columnaImagen,&filaImagen);//se lee el tamaño de la matriz
	fclose(fp);
	fp = fopen("buscar2.in", "r"); // read mode
	fscanf(fp,"%d %d",&columnaBuscar,&filaBuscar);//se lee el tamaño de la matriz
	fclose(fp);
	int*** imagen=leer("imagen2.in");
	int*** buscar=leer("buscar2.in");
	obtenerImagenes(imagen,buscar);
	liberar(filaBuscar,buscar);
	liberar(filaImagen,imagen);
	
	printf("termino");
	
	return 0;
}
