#include "Manejo_Archivos.h"

int Valor_aleatorio(int min,int max){
	int valor = min + rand() % (max+1 - min);

	return valor;
}

void Simbolo_aleatorio(char *simbolo){
	//Creamos el simbolo aleatorio
	*simbolo = Valor_aleatorio(RANGO_CARACTER_MIN,RANGO_CARACTER_MAX-1);	//Tomamos un caracter determinado

	return;
}

void Generar_archivo(Tarchivo_dato *archivo){
	uint16_t cant_lineas;

	//Realizo un nuevo archivo datos.txt
	archivo->archivo_ = fopen(archivo->nombre_archivo,"w");

	//Generamos un bucle para los valores aleatorios
	//esto lo hacemos dado que "se vuelve mas aleatorio de esta forma" sino siempre serían valores parecidos
	for(int i=0;i<REPETICION;i++){
		cant_lineas = Valor_aleatorio(RANGO_LINEA_MIN, RANGO_LINEA_MAX);
	}

	//Generamos los caracteres de cada linea
	for(int g=0;g<cant_lineas;g++){
		int longitud = Valor_aleatorio(RANGO_CANT_CARACTERES_MIN, RANGO_CANT_CARACTERES_MAX); //longitud de cadena aleatoria entre 0 y 20

		for(int i=0;i<longitud;i++){
			char simbolo;

			Simbolo_aleatorio(&simbolo);
			fputc(simbolo,archivo->archivo_);
		}
		fputc('\n',archivo->archivo_);
	}

	//Cerramos el archivo
	fclose(archivo->archivo_);

	return;
}

//Esta función se realiza una vez para poder inicializar ciertas cosas
void CantidadTotal_Lineas_archivo(Tarchivo_dato *archivo){
	//Tipo de apertura como lectura
	if((archivo->archivo_ = fopen(archivo->nombre_archivo,"r")) == NULL)	printf("No puedo abrirse el archivo");

	/*
	 * Esta parte se encarga de leer la cantidad de lineas totales que posee
	 * el archivo.
	 * */

	//Lee hasta el final del archivo
	while(1){
		char caracter=fgetc(archivo->archivo_);

		if(caracter == '\n')	archivo -> total_lineas+=1;	//Cuenta la cantidad total de lineas

		if(caracter == EOF)	break;
	}

	//Suma la linea que no contiene el \n
	archivo -> total_lineas ++;

	//Imprime por pantalla la cantidad de lineas
	printf("Total lineas: %d\n",archivo -> total_lineas);

	//Vuelve al comienzo del archivo
	rewind(archivo -> archivo_);

	//Toma la posición en la que se encuentra el puntero al archivo. Esto lo hacemos dado que luego
	//queremos ubircarnos a partir de esa posición.
	archivo -> pos_final = ftell(archivo->archivo_);

	fclose(archivo->archivo_);

	return;
}


void Linea_archivo(Tarchivo_dato *archivo){
	char letra;

	if((archivo->archivo_ = fopen(archivo->nombre_archivo,"r")) == NULL) printf("No puedo abrirse correctamente");

	//Iniciliazamos el contador de caracteres en la linea
	archivo -> cont_cart = 1;

	//Leemos la primera letra donde comienza la siguiente linea
	fseek(archivo->archivo_,archivo->pos_final,SEEK_SET);
	letra = fgetc(archivo->archivo_);

	//Asignamos memoria a un puntero y le guardamos la letra leida
	archivo -> linea_leida = (char *) malloc(sizeof(char *));
	archivo -> linea_leida[0] = letra;

	while(letra != '\n'){
		//Leemos el sig caracter
		letra = fgetc(archivo -> archivo_);

		if(letra != '\n'){
			archivo -> linea_leida = (char *) realloc(archivo -> linea_leida,(archivo -> cont_cart)+1*sizeof(char *));
			archivo -> linea_leida[archivo -> cont_cart] = letra;
			archivo -> cont_cart++;
		}
	}

	archivo -> linea_leida[archivo -> cont_cart] = '\0';
	archivo -> pos_final = ftell(archivo->archivo_);

	fclose(archivo->archivo_);

	return;
}

void Procesar_LineaArchivo(Tarchivo_dato *archivo,TLE_lista *lista){
	//Ahora debemos crear un nodo para cada linea
	if(Insertar_en_ListaVacia(lista, archivo -> linea_leida[0]));
	else{
		for(int i=1;i<archivo->cont_cart;i++){
			Insertar_en_FinLista(lista, lista -> final, archivo -> linea_leida[i]);
		}
	}

	return;
}
