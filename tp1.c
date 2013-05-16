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

/* Estructuras */
struct Peliculas {
	char nombre[MAXNOMBRE];
	int anyo;
	char genero;
	int mce;
	int fac;
	int marcaBaja;
};

/* Tipo de dato */
typedef struct Peliculas peliculas;

/* Prototipo Funciones */
int autenticar();
void gestionPeliculas(peliculas *pp, int *indice);
void renovarCartelera();
void gestionSalas();
void altaManual(peliculas *pp, int *indice);
void altaMasiva(peliculas *pp, int *indice);
void bajaPeli(peliculas *pp, int *indice);
void modificarPeli(peliculas *pp, int *indice);
void listado(peliculas *pp, int *indice);
int validarFecha(int *fecha);

enum genero {Accion, Comedia, Drama, Suspenso, Terror};

int main() {
	/* Array de peliculas */
	peliculas Peli[MAXPELI];
	
	/* Puntero a estructura */
	peliculas *ptrPeli;
	ptrPeli = Peli;
	
	/* Reserva espacio almacenamiento */
	ptrPeli = malloc(sizeof(Peli));
	
	/* Indice cantidad peliculas cargadas */
	int indice = 0;
	int *ptrIndice;
	ptrIndice = &indice;
	
	int opcion;
	puts(".................................................................................");
	puts(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .");
	puts("  #########   .   ######    .   ###     ##  .  ###########  .  ###     ###  .  ");
	puts("  ##          .     ##      .   ## #    ##  .  ##       ##  .  ## #   # ##  .  ");
	puts("  ##          .     ##      .   ##  #   ##  .  ##       ##  .  ##  # #  ##  .  ");
	puts("  ##          .     ##      .   ##   #  ##  .  ## ##### ##  .  ##   #   ##  .  ");
	puts("  ##          .     ##      .   ##    # ##  .  ##       ##  .  ##       ##  .  ");
	puts("  #########   .   ######    .   ##     ###  .  ##       ##  .  ##       ##  .  ");
	puts(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .");
	puts(".................................................................................");
	printf("Seleccione la operacion a realizar:\n\t1. Gestion de Peliculas\n\t2. Renovar Cartelera\n\t3. Gestion de Salas\n\t4. Salir del sistema\n-> ");
	scanf("%d",&opcion);
	switch (opcion) {
		case 1: gestionPeliculas(ptrPeli, ptrIndice);
			break;
		case 2: renovarCartelera();
			break;
		case 3: gestionSalas();
			break;
		case 4: printf("Gracias por utilizar CINAMON");
			break;
		default: printf("\nOpcion incorrecta.");
			break;
	}
}

void gestionPeliculas(peliculas *pp, int *indice) {
	int opcion;
	
	printf("Seleccione la opcion:\n\t1. Alta Manual\n\t2. Alta Masiva\n\t3. Baja\n\t4. Modificacion\n\t5. Listado\n\n\t9. Menu anterior\n-> ");
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
		case 9: printf("\nGracias por utilizar CINAMON");
			break;
		default:
			break;
	}
}

void altaManual(peliculas *pp, int *indice) {
	char opcion;
	
	/* Verifica si se alcanzo el limite de peliculas */
	if(*indice == MAXPELI)
		printf("\nNo se pueden cargar mas peliculas!\n");
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
			printf("\n\nDatos cargados:\nNombre: %sAño: %d\nGenero: %c\nMCE: %d\nFAC: %d\nMarca Baja: %d",pp[*indice].nombre, pp[*indice].anyo, pp[*indice].genero, pp[*indice].mce, pp[*indice].fac, pp[*indice].marcaBaja);
			/* Incrementa en 1 indice de peliculas cargadas */
			*indice += 1;
			printf("\n\nPelicula(s) cargadas: %d\n\n", *indice);
			printf("\nDesea cargar mas peliculas? (S)i - (N)o: ");
			scanf("%c",&opcion);
		} while (opcion == 's' || opcion == 'S');
	}
	/* vuelve al menu anterior */
	system("clear");
	gestionPeliculas(pp, indice);
}

void altaMasiva(peliculas *pp, int *indice) {
	int i, j;
	char ch;
	
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
			/* Asigna el genero */
			pp[*indice].genero = 'C';
			
			/* incremento el indice de peliculas */
			*indice += 1;
		}
	}
	
	printf("\nPelicula(s) Cargada(s): %d\n\n",*indice);
	/* vuelve al menu anterior */
	gestionPeliculas(pp, indice);
}

void bajaPeli(peliculas *pp, int *indice) {
	int i, pos;
	char nombrePeli[MAXNOMBRE];
	
	if(*indice == 0) {
		printf("\nNo hay peliculas cargadas.\n");
		getchar();
		gestionPeliculas(pp, indice);
	}
	else {
		printf("\n\t\tIngrese el nombre de la pelicula a buscar: ");
		getchar();
		fgets(nombrePeli,MAXNOMBRE,stdin);
		
		for (i = 0; i < *indice; i++) {
			if((strstr(pp[i].nombre, nombrePeli)) != NULL);
				
		}
	}
	gestionPeliculas(pp, indice);
}

void modificarPeli(peliculas *pp, int *indice) {
	
}

void listado(peliculas *pp, int *indice) {
	int i;
	
	system("clear");
	printf("--+----------------------------------------------------+------+---+-----+----------+---+\n");
	for(i = 0; i < *indice; i++) {
		printf("%d.\t%s   %d   %c   %d   %d   %d\n",i+1, pp[i].nombre, pp[i].anyo, pp[i].genero, pp[i].mce, pp[i].fac, pp[i].marcaBaja);
		printf("--+----------------------------------------------------+------+---+-----+----------+---+\n");
	}
	printf("\n");
	gestionPeliculas(pp, indice);
}

void renovarCartelera() {
	
}

void gestionSalas() {
	
}

int validarFecha(int *fecha) {
	return 0;
}

