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
Nodo* crearNodo(int valor){//5c
	Nodo* nodo= (Nodo*)malloc(sizeof(Nodo));//c
	nodo->siguiente=NULL;//c
	nodo->valor=valor;//c
	nodo->cantidad=1;//c
	return nodo;//c
}
//libera la memoria
void destruirNodo(Nodo *nodo){
	free(nodo);
}
//agrega un nodo al final
Nodo* agregarNodo(Nodo* cabeza,Nodo* nodo){//(n-1)c+3c
	if(cabeza==NULL){//3c
		cabeza=nodo;
		return cabeza;
	}
	else{
		Nodo* aux=cabeza;//c
		
		while(aux->siguiente!=NULL){//n-1
			aux=aux->siguiente;//c
		}
		aux->siguiente=nodo;//c
		return cabeza;//c
	}
}
int estaEnLaLista(Nodo* inicial,int valor){//c+c+(n-1)3c +2c+c
	Nodo* aux=inicial;//c
	if(inicial!=NULL){//c
		while(aux->siguiente!=NULL){//(n-1)
			if(aux->valor==valor){//c
				return 1;//c
			}
			aux=aux->siguiente; //c
			
		}
		if(aux->valor==valor){//2c
			return 1;
		}
		return 0;//c
	}
	else{//c
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

Nodo* buscar(Nodo* cabezal,int valor){//c+(n-1)3c+2c
	if(cabezal==NULL){
		return NULL;
	}
	else{
		Nodo* aux= cabezal;//c
		while(aux->siguiente!=NULL){//n-1
			if(aux->valor==valor){//2c
				return aux;
			}
			aux=aux->siguiente;//c
		}
		if(aux->valor==valor){//2c
			return aux;
		}
		else{
			return NULL;
		}
	}
}
int getLargo(Nodo* cabezal){//2c+(n-1)c+2c
	Nodo* aux= cabezal;//c
	int contador=0;//c
	while(aux->siguiente!=NULL){//n-1
		contador+=1;//c
		aux=aux->siguiente;//c
	}
	contador+=1;//c
	return contador;//c
}
int getValor(Nodo* cabezal,int numero){//3c+2cn
	Nodo* aux= cabezal;//c
	int contador=1;//c
	while(contador!=numero){//n
		if(cabezal==NULL){//c
			return -1;//c
		}
		else{
			aux=aux->siguiente;//c
			contador+=1;//c
		}
	}
	return aux->valor;//c
}

Nodo* agregarOrdenado(Nodo* cabezal,Nodo* nodo){//6c+(n-1)4c
	if(cabezal==NULL){
		return nodo;
	}
	else{
		Nodo* aux=cabezal;//c
		while(aux->siguiente!=NULL){//n-1
			if(nodo->valor>cabezal->valor){//c
				nodo->siguiente=cabezal;//c
				return nodo;//c
			}
			else{
				if(aux->siguiente->valor<nodo->valor){//c
					nodo->siguiente=aux->siguiente;//c
					aux->siguiente=nodo;//c
					return cabezal;//c
				}
				else{
					aux=aux->siguiente;//c
				}
			}
		}
		if(nodo->valor>cabezal->valor){
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
					if(estaEnLaLista(cabezal,contador)){
						buscar(cabezal,contador)->cantidad=buscar(cabezal,contador)->cantidad+1;//(n-1)
					}
					else{
						cabezal=agregarOrdenado(cabezal,crearNodo(contador)); //n^2+nc
					}
				contador=0;
			}
		}
		return cabezal;
	}
}
double promedio(Nodo* cabezal){//6c+(n-1)3c
	int numerador=0;//c
	int denominador=0;//c
	Nodo* aux=cabezal;//c
	
	while(aux->siguiente!=NULL){//n-1
		numerador=numerador+aux->valor*aux->cantidad;//c
		denominador=denominador+aux->cantidad;//c
		aux=aux->siguiente;//c
	}
	numerador=numerador+aux->valor*aux->cantidad;//c
	denominador=denominador+aux->cantidad;//c
	return numerador/denominador;//c
}
int getMayor(Nodo *nodo){
	int mayor=0;//c
	Nodo* aux=nodo;//c
	while(aux->siguiente!=NULL){//(n-1)
		if(aux->valor>mayor){//c
			mayor=aux->valor;//c
		}
		aux=aux->siguiente;//c
	}
	if(aux->valor>mayor){//c
		mayor=aux->valor;//c
	}
	return mayor;//c
}
int getMenor(Nodo *nodo){
	int menor=999999;//c
	Nodo* aux=nodo;//c
	while(aux->siguiente!=NULL){//n-1
		if(aux->valor<menor){//c
			menor=aux->valor;//c
		}
		aux=aux->siguiente;//c
	}
	if(aux->valor<menor){//c
		menor=aux->valor;//c
	}
	return menor;//c
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
double getDesviacionEstandar(Nodo* cabezal,double promedio){//n-1
	Nodo* aux=cabezal;
	double acum=0;
	while(aux->siguiente!=NULL){//n-1
		acum=acum+(abs(aux->valor-promedio)^2);//c
		aux=aux->siguiente;//c
	}
	acum=acum+(abs(aux->valor-promedio)^2);//c
	acum=(sqrt(acum)/getLargo(cabezal));//c
	return acum;
}

Nodo* getDatosOrdenados(Nodo* cabezal){//2c+(n-1)(n-1)+n(n-1)
	 Nodo* aux=cabezal;//c
	 Nodo* aux2=NULL;//c
	 while(aux->siguiente!=NULL){//n-1
	 	for(int i=0;i<aux->cantidad;i++){//c
	 		aux2=agregarOrdenado(aux2,crearNodo(aux->valor));//n-1
		 }
		 aux=aux->siguiente;	 	
	 }
	for(int i=0;i<aux->cantidad;i++){//n
		aux2=agregarOrdenado(aux2,crearNodo(aux->valor));//n-1
	}
	return aux2;
}

Nodo* obtenerImagenes(int*** matrizImagen,int*** matrizBusqueda,Nodo* cabezal){
	
	for(int i=0;i<4;i++){//4
		cabezal=verificar(matrizImagen,matrizBusqueda,cabezal);
		matrizBusqueda=rotar90(matrizBusqueda);

	}
	
	return cabezal;
}
double mediana(Nodo* nodo){
	int largo=getLargo(nodo);
	double x=0;
	if(largo%2==0){
		return getValor(nodo,largo/2);
	}
	else{
		largo=largo/2;
		return (((getValor(nodo,(largo+0.5)))-(getValor(nodo,(largo-0.5))))/2);//2*2n
	}
}

void obtenerDatos(Nodo* nodo){
	
	FILE *fptr;
	fptr = fopen("salida.out","w");
	printear(nodo);
	Nodo* aux2=getDatosOrdenados(nodo);
	fprintf(fptr,"Mayor similitud: %d pixeles encontrado %d veces \n",getMayor(nodo),buscar(nodo,getMayor(nodo))->cantidad);
	fprintf(fptr,"Menor similitud: %d pixeles encontrado %d veces \n",getMenor(nodo),buscar(nodo,getMenor(nodo))->cantidad);
	fprintf(fptr,"Media %f pixeles\n",promedio(nodo));
	fprintf(fptr,"Mediana %f pixeles \n",mediana(aux2));
	fprintf(fptr,"Desviacion estandar: %f \n",getDesviacionEstandar(aux2,promedio(nodo)));
	
	fclose(fptr);
}



int main(){
	char* nombreImagen="imagen2.in";
	char* nombreBusqueda ="buscar2.in";
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
	int cantidad=columnaImagen*filaImagen+columnaBuscar*filaBuscar;
	cabeza=obtenerImagenes(imagen,buscar,cabeza);
  	getDatosOrdenados(cabeza);
	obtenerDatos(cabeza);
	getDatosOrdenados(cabeza);
	
	liberar(filaBuscar,buscar);
	liberar(filaImagen,imagen);
	liberarNodo(cabeza);
	printf(" termino ");
	return 0;
}
