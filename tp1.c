#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "admin.h"

#define randomize (srand(time(NULL)))
#define random(num) (rand()%(num))
#define MAXSALA 1500
#define MAXPELI 20
#define MAXNOMBRE 50

/* Estructura Peliculas */
struct Peliculas {
	char nombre[MAXNOMBRE];
	int anyo;
	char genero;
	int mce;
	int fac;
	int marcaBaja;
};

/* Sinonimo tipo de dato */
typedef struct Peliculas peliculas;

/* Estructura Salas */
struct Salas {
	char nombreSala[20];
	char generoSala;
	int capacidad;
	peliculas vigentes[10];
};

/* Sinonimo tipo de dato */
typedef struct Salas salas;

/* Prototipo Funciones */
int autenticar();
int validarFecha(int *fecha);
void inicio();
void gestionPeliculas(peliculas *pp, int *indice);
void altaManual(peliculas *pp, int *indice);
void altaMasiva(peliculas *pp, int *indice);
void bajaPeli(peliculas *pp, int *indice);
void modificarPeli(peliculas *pp, int *indice);
void listado(peliculas *pp, int *indice);
void renovarCartelera(salas *ps);
void gestionSalas();

int main() {
	/* Array de estructuras */
	peliculas Peli[MAXPELI];
	salas Sala[3];
	
	/* Puntero a estructura */
	peliculas *ptrPeli;
	ptrPeli = Peli;
	
	salas *ptrSala;
	ptrSala = Sala;
	
	/* Reserva espacio almacenamiento */
	ptrPeli = malloc(sizeof(Peli)*2);
	ptrSala = malloc(sizeof(Sala)*2);
	
	/* Indice cantidad peliculas cargadas */
	int indice = 0;
	int *ptrIndice;
	ptrIndice = &indice;
	
	int opcion;
	inicio();
	printf("Seleccione la operacion a realizar:\n\t1. Gestion de Peliculas\n\t2. Renovar Cartelera\n\t3. Gestion de Salas\n\t4. Salir del sistema\n-> ");
	scanf("%d",&opcion);
	switch (opcion) {
		case 1: gestionPeliculas(ptrPeli, ptrIndice);
			break;
		case 2: renovarCartelera(ptrSala);
			break;
		case 3: gestionSalas();
			break;
		case 4: printf("\n---------------------------------------------------------------------------------------------------------\n");
				printf("\n                                 GRACIAS POR UTILIZAR CINAMON\n\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
			break;
		default: printf("\nOpcion incorrecta.");
			break;
	}
	free(ptrPeli);
	free(ptrSala);
}

void gestionPeliculas(peliculas *pp, int *indice) {
	int opcion;
	
	inicio();
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\n       1. Alta Manual | 2. Alta Masiva | 3. Baja | 4. Modificacion | 5. Listado | 9. Menu anterior\n\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("-> ");
	scanf("%d",&opcion);
	switch (opcion) {
		case 1: altaManual(pp, indice);
			break;
		case 2: altaMasiva(pp, indice);
			break;
		case 3: bajaPeli(pp, indice);
			break;
		case 4: modificarPeli(pp, indice);
			break;
		case 5: listado(pp, indice);
			break;
		case 9: 
			break;
		default:
			break;
	}
}

void altaManual(peliculas *pp, int *indice) {
	char opcion;
	
	/* Verifica si se alcanzo el limite de peliculas */
	if(*indice == MAXPELI){
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                               NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
	}
	else {
		do {
			getchar(); /* consume el \n */
			printf("Ingrese el nombre de la pelicula: ");
			fgets(pp[*indice].nombre,MAXNOMBRE,stdin);
			printf("\nIngrese el anyo de la pelicula: ");
			scanf("%d",&pp[*indice].anyo);
			printf("\nIngrese el genero:\n\tA-a: Accion\n\tC-c: Comedia\n\tD-d: Drama\n\tS-s: Suspenso\n\tT-t: Terror\n\t:");
			getchar();
			scanf("%c",&pp[*indice].genero);
			printf("\nIngrese la cantidad de expectadores que se esperan: ");
			getchar();
			scanf("%d",&pp[*indice].mce);
			printf("\nIngrese la fecha de asignacion en cartelera en formato ddmmaaaa: ");
			scanf("%d",&pp[*indice].fac);
			getchar();
			pp[*indice].marcaBaja = 0;
			printf("\n%s   %d   %c   %d   %d   %d\n",pp[*indice].nombre, pp[*indice].anyo, pp[*indice].genero, pp[*indice].mce, pp[*indice].fac, pp[*indice].marcaBaja);
			/* Incrementa en 1 indice de peliculas cargadas */
			*indice += 1;
			printf("\n\nPelicula(s) cargadas: %d\n\n", *indice);
			printf("\nDesea cargar mas peliculas? (S)i - (N)o: ");
			scanf("%c",&opcion);
		} while (opcion == 's' || opcion == 'S');
	}
	/* vuelve al menu anterior */
	gestionPeliculas(pp, indice);
}

void altaMasiva(peliculas *pp, int *indice) {
	int i, j, dia, mes, anyo;
	char ch, gen[] = {'A','C','D','S','T'};
	
	randomize;
	
	if(*indice == MAXPELI)
		printf("\nNo se pueden cargar mas peliculas!\n");
	else {
		for (i = *indice; i < MAXPELI; i++) {
			for(j = 0; j < MAXNOMBRE; j++){
				/* Genera 50 caracteres aleatorios a-z */
				ch = 'a' + rand() % (('z'-'a') + 1);
				pp[*indice].nombre[j] = ch;
			}
			/* Genera Años entre 1900 y 2013 */
			pp[*indice].anyo = 1900 + (rand() % (int)(2013 - 1900 + 1));
			/* Genera MCE */
			pp[*indice].mce = random(MAXSALA+1);
			/* Inicializa FAC en blanco */
			pp[*indice].fac = 23112013;
			/* Asigna el genero aleatorio */
			pp[*indice].genero = gen[random(5)];
			/* Se asigna marcaBaja en 0. significa que estan vigentes */
			pp[*indice].marcaBaja = 0;
			/* incremento el indice de peliculas */
			*indice += 1;
		}
	}
	system("clear");
	inicio();
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\n                                     CANTIDAD PELICULAS CARGADAS: %d\n\n",*indice);
	printf("---------------------------------------------------------------------------------------------------------\n");
	/* vuelve al menu anterior */
	gestionPeliculas(pp, indice);
}

void bajaPeli(peliculas *pp, int *indice) {
	int i, j, num, aux, bandera, pos[MAXPELI];
	char opcion, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		printf("\nNo hay peliculas cargadas.\n");
		getchar();
		gestionPeliculas(pp, indice);
	}
	else {
		printf("\nIngrese el nombre o parte del nombre de la pelicula a buscar: ");
		getchar();
		
		scanf("%s", nombrePeli);
		i = j = 0;
		while(i < *indice){
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr == NULL)
				bandera = -1;
			else {
				printf("\n%d. %s ",j+1, pp[i].nombre);
				printf("|| %d ", pp[i].anyo);
				printf("|| %d ", pp[i].genero);
				printf("|| %d ", pp[i].mce);
				printf("|| %d ", pp[i].fac);
				printf("|| %d\n", pp[i].marcaBaja);
				printf("---------------------------------------------------------------------------------------------------------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
	}
	/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
	if(bandera == -1){
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                     NO SE ENCONTRO NINGUNA PELICULA\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		bajaPeli(pp, indice);
	}
	else {
		do {
		printf("\nIngrese el num de pelicula a dar de baja: ");
		scanf("%d",&num);
		} while(num < 0 || num >= j+1);
				
		getchar();
		printf("\nCONFIRMA LOS CAMBIOS? (S)i - (N)o: ");
		scanf("%c",&opcion);
		
		switch (opcion) {
			case 'S':
			case 's':
				aux = pos[num-1];
				pp[aux].marcaBaja = 1;
				printf("\nSE HA DADO DE BAJA LA SIGUIENTE PELICULA:\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("\n%d. %s ",aux+1, pp[aux].nombre);
				printf("|| %d ", pp[aux].anyo);
				printf("|| %c ", pp[aux].genero);
				printf("|| %d ", pp[aux].mce);
				printf("|| %d ", pp[aux].fac);
				printf("|| %d\n", pp[aux].marcaBaja);
				printf("---------------------------------------------------------------------------------------------------------\n");
				break;
			case 'N':
			case 'n':
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("\n                                        NO SE REALIZARON CAMBIOS\n\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				break;
		}
	}
	
	gestionPeliculas(pp, indice);
}

void modificarPeli(peliculas *pp, int *indice) {
	int i, j, num, aux, bandera, opcion, n_anyo, n_mce, pos[MAXPELI];
	char n_genero, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                         NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		getchar();
		gestionPeliculas(pp, indice);
	}
	else {
		getchar();
		printf("\nIngrese el nombre o parte del nombre de la pelicula a buscar: ");
		
		scanf("%s", nombrePeli);
		i = j = 0;
		while(i < *indice){
			/* Compara la subcadena con el nombre de pelicula */
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr == NULL)
				bandera = -1;
			else {
				printf("\n%d. %s ",j+1, pp[i].nombre);
				printf("|| %d ", pp[i].anyo);
				printf("|| %c ", pp[i].genero);
				printf("|| %d ", pp[i].mce);
				printf("|| %d ", pp[i].fac);
				printf("|| %d\n", pp[i].marcaBaja);
				printf("---------------------------------------------------------------------------------------------------------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
	}
	/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
	if(bandera == -1){
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                     NO SE ENCONTRO NINGUNA PELICULA\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		modificarPeli(pp, indice);
	}
	else {
		do {
		printf("\nIngrese el num de pelicula a modificar: ");
		scanf("%d",&num);
		} while(num < 0 || num >= j+1);
		
		/* Almacena la posicion de la pelicula de la estructura */
		aux = pos[num-1];
		
		do {
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nPELICULA A MODIFICAR: %s\n\n", pp[aux].nombre);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nSeleccione la modificacion a realizar:\n1. Año\n2. Genero\n3. MCE\n9. Volver al menu anterior\n-> ");
			scanf("%d", &opcion);
			switch (opcion) {
				case 1: do {
							getchar();
							printf("\nIngrese el nuevo año: ");
							scanf("%d",&n_anyo);
						} while(n_anyo < 1900 || n_anyo > 2013);
						pp[aux].anyo = n_anyo;
					break;
				case 2: getchar();
						printf("\nIngrese el nuevo genero: ");
						scanf("%c",&n_genero);
						pp[aux].genero = n_genero;
					break;
				case 3: do {
							getchar();
							printf("\nIngrese el nuevo MCE: ");
							scanf("%d",&n_mce);
						} while(n_mce < 0 || n_mce > MAXSALA);
						pp[aux].mce = n_mce;
					break;
				case 9: gestionPeliculas(pp, indice);
			}
		} while(opcion > 3 || opcion < 0);
	}
	
	printf("\nSE HA MODIFICADO LA SIGUIENTE PELICULA:\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("%d. %s ",aux+1, pp[aux].nombre);
	printf("|| %d ", pp[aux].anyo);
	printf("|| %c ", pp[aux].genero);
	printf("|| %d ", pp[aux].mce);
	printf("|| %d ", pp[aux].fac);
	printf("|| %d\n", pp[aux].marcaBaja);
	printf("---------------------------------------------------------------------------------------------------------\n");
	
	gestionPeliculas(pp, indice);
}

void listado(peliculas *pp, int *indice) {
	int i;
	
	printf("---------------------------------------------------------------------------------------------------------\n");
	for(i = 0; i < *indice; i++) {
		printf("%d.\t%s   %d   %c   %d   %d   %d\n",i+1, pp[i].nombre, pp[i].anyo, pp[i].genero, pp[i].mce, pp[i].fac, pp[i].marcaBaja);
		printf("---------------------------------------------------------------------------------------------------------\n");
	}
	printf("\n");
	gestionPeliculas(pp, indice);
}

void renovarCartelera(salas *ps) {
	/* Implementar vector en el cual las posiciones del tipo de pelicula se vayan eliminando a medida que se asignan a las salas */
	int i, j, h, genSala, indiceGen = 4;
	char gen[] = {'A','C','D','S','T'};
	
	/* Inicializo las salas con su respectiva capacidad*/
	strcpy(ps[0].nombreSala, "Aleandro");
	ps[0].capacidad = 1500;
	strcpy(ps[1].nombreSala, "Zorrilla");
	ps[1].capacidad = 200;
	strcpy(ps[2].nombreSala, "Nu");
	ps[2].capacidad = 525;
	strcpy(ps[3].nombreSala, "Eve");
	ps[3].capacidad = 525;

	for(i = 0; i < 4; i++){
		getchar();
		printf("\n---------------------------------------------------------------------------------------------------------\n");
		printf("\nSELECCIONE EL GENERO PARA LA SALA \"%s\":\t (A)ccion - (C)omedia - (D)rama - (S)uspenso - (T)error\n\n", ps[i].nombreSala);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("GENEROS DISPONIBLES: ");
		
		for(j = 0; j <= indiceGen; j++)
			printf("| %d. %c ", j+1, gen[j]);
		
		printf("\nIngrese el numero correspondiente: ");
		scanf("%d",&genSala);
		
		ps[i].generoSala = gen[genSala-1];
		
		for(h = genSala-1; h <= indiceGen; h++)
				gen[h] = gen[h+1];
		printf("\nGENERO SALA %s: %c", ps[i].nombreSala, ps[i].generoSala);
		indiceGen--;
	}
}

void gestionSalas() {
	
}

int validarFecha(int *fecha) {
	return 0;
}

void inicio() {
	puts(".........................................................................................................");
	puts(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .");
	puts("  #########   .   ######    .  ###     ##  .  ###########  .  ###     ###  .  ######### .  ###     ## .");
	puts("  ##          .     ##      .  ## #    ##  .  ##       ##  .  ## #   # ##  .  #       # .  ## #    ## .");
	puts("  ##          .     ##      .  ##  #   ##  .  ##       ##  .  ##  # #  ##  .  #       # .  ##  #   ## .");
	puts("  ##          .     ##      .  ##   #  ##  .  ## ##### ##  .  ##   #   ##  .  #       # .  ##   #  ## .");
	puts("  ##          .     ##      .  ##    # ##  .  ##       ##  .  ##       ##  .  #       # .  ##    # ## .");
	puts("  #########   .   ######    .  ##     ###  .  ##       ##  .  ##       ##  .  ######### .  ##     ### .");
	puts(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .");
	puts(".........................................................................................................");
}