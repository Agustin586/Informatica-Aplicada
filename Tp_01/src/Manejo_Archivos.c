#include "Manejo_Archivos.h"

int Valor_aleatorio(int min,int max){
	//int valor = min+rand()/(RAND_MAX/(max-min+1)+1);
	int valor = min + rand() % (max+1 - min);


	printf("%d\n",valor);

	return valor;
}

void Cadena_aleatoria(int longitud,char destino[]){
	//Creamos la cadena aleatoria
	for (int x = 0; x < longitud; x++){
		int indiceAleatorio = Valor_aleatorio(RANGO_CARACTER_MIN,RANGO_CARACTER_MAX);	//Tomamos un caracter determinado
		destino[x] = indiceAleatorio;
	}

	return;
}

void Generar_archivo(void){
	//srand(time(NULL));

	uint16_t cant_lineas;
	FILE *archivo;

	//Realizo un nuevo archivo datos.txt
	archivo = fopen("datos.txt","w+");

	//Realizamos un promedio de valores aleatorios, ya que el primer valor siempre es igual
	for(int i=0;i<REPETICION;i++){
		cant_lineas = Valor_aleatorio(RANGO_LINEA_MIN, RANGO_LINEA_MAX);
	}
	//cant_lineas = (uint16_t) (((float)cant_lineas)/REPETICION);

	printf("cantidad de lineas: %d\n",cant_lineas);

	for(int g=0;g<cant_lineas;g++){
		//srand(time(NULL));

		int longitud = Valor_aleatorio(RANGO_CANT_CARACTERES_MIN, RANGO_CANT_CARACTERES_MAX-1); //longitud de cadena aleatoria entre 0 y 20
		char destino[longitud+1];

		//strcpy(destino,"");
		// El +1 es por el carácter nulo que marca el fin de la cadena

		Cadena_aleatoria(longitud, destino);

		fprintf(archivo, "%s\n",destino);
	}

	//Cerramos el archivo
	fclose(archivo);

	return;
}
