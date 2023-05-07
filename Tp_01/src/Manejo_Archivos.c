#include "Manejo_Archivos.h"

int Valor_aleatorio(int min,int max){
	//int valor = min+rand()/(RAND_MAX/(max-min+1)+1);
	int valor = min + rand() % (max+1 - min);

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

	//printf("cantidad de lineas: %d\n",cant_lineas);

	for(int g=0;g<cant_lineas;g++){
		int longitud = Valor_aleatorio(RANGO_CANT_CARACTERES_MIN, RANGO_CANT_CARACTERES_MAX-1); //longitud de cadena aleatoria entre 0 y 20
		char destino[longitud+1];

		Cadena_aleatoria(longitud, destino);

		fprintf(archivo, "%s\n",destino);
	}

	//Cerramos el archivo
	fclose(archivo);

	return;
}

//Esta función se realiza una vez para poder inicializar ciertas cosas
void LeerLinea_archivo(Tarchivo_dato *archivo){
	//FILE *archivo;

	archivo -> lineas_procesadas = 0;
	archivo -> total_lineas = 0;

	archivo -> archivo_ = fopen(archivo -> nombre_archivo,"r");

	//Lee la cantidad de lineas totales
	//uint16_t total_lineas=0;
	char caracter;

	caracter = fgetc(archivo -> archivo_);

	while(caracter != EOF){
		if(caracter == '\n')	archivo -> total_lineas++;
		caracter = fgetc(archivo -> archivo_);
	}

	printf("\nTotal lineas: %d\n",archivo -> total_lineas);

	rewind(archivo -> archivo_);
	archivo -> pos_final = ftell(archivo->archivo_);	//Toma la posicion inicial del archivo

	//Lee la primera linea entera y la guarda en un vector dinámico


	//Envia la posición del vector para luego procesarlo

	//fclose(archivo->archivo_);

	return;
}


void Linea_archivo(Tarchivo_dato *archivo){
	char letra;

	//Mostramos en que linea nos encontramos leyendo
	printf("\nLinea:%d\n",archivo->lineas_procesadas+1);

	//Iniciliazamos el contador de caracteres en la linea
	archivo -> cont_cart = 1;

	//Leemos la primera letra donde comienza la siguiente linea
	fseek(archivo->archivo_,archivo->pos_final,SEEK_SET);
	letra = fgetc(archivo -> archivo_);

	//Asignamos memoria a un puntero y le guardamos la letra leida
	archivo -> linea_leida = (char*) malloc(sizeof(char));
	archivo -> linea_leida[0] = letra;

	//Aumentamos la cantidad de bytes leidos
	archivo -> pos_final++;

	while(letra != '\n'){
		//Leemos el sig caracter
		letra = fgetc(archivo -> archivo_);

		//Aumentamos la cantidad de bytes leidos
		archivo -> pos_final++;
		archivo -> cont_cart++;

		archivo -> linea_leida = (char*) realloc(archivo -> linea_leida,(archivo -> cont_cart)*sizeof(char));
		archivo -> linea_leida[(archivo -> cont_cart)-1] = letra;
	}

	archivo -> linea_leida[archivo -> cont_cart] = '\0';
	archivo -> pos_final = ftell(archivo->archivo_);

	printf("Leyo una linea\n");
	printf("%s",archivo -> linea_leida);

	//free(archivo -> linea_leida);	//Todavia no debemos librerar la memoria dado que la debemos procesar en otro estado
}

void Procesar_LineaArchivo(Tarchivo_dato *archivo,TLE_lista *lista){
	//Ahora debemos crear un nodo para cada linea
	if(Insertar_en_ListaVacia(lista, archivo -> linea_leida[0]));
	else{
		for(int i=1;i<archivo->cont_cart;i++){
		//		Insertar_en_FinLista(lista, lista -> final, prueba[i]);
		//	}
		Insertar_en_FinLista(lista, lista -> final, archivo -> linea_leida[i]);
		}
	}

	Imprimir_Lista(lista);

	Destruir_Lista(lista);

	//Indica que ya proceso la linea seleccionada
	archivo -> lineas_procesadas++;

	//Aca debemos liberar la memoria una vez que fue procesada la información
	free(archivo -> linea_leida);
}
