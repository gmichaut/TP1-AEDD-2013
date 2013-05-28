/* GRUPO NRO 5
 INTEGRANTES:
 GABRIEL MICHAUT
 gmichaut@gmail.com
 */

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
#define ANYOACTUAL 2013

/* Estructura Peliculas */
struct Peliculas {
	char nombre[MAXNOMBRE];
	int anyo;
	char genero;
	int mce;
	char fac[12];
	int marcaBaja;
};

/* Sinonimo tipo de dato */
typedef struct Peliculas peliculas;

/* Estructura Salas */
struct Salas {
	char nombreSala[20];
	char generoSala;
	int capacidad;
	peliculas enCartelera[10];
	int asignadas;
};

/* Sinonimo tipo de dato */
typedef struct Salas salas;

/* Prototipo Funciones */
void inicio();
void autenticar(usuario pu[]);
void gestionPeliculas(peliculas *pp, int *indice);
void altaManual(peliculas *pp, int *indice);
void altaMasiva(peliculas *pp, int *indice);
void bajaPeli(peliculas *pp, int *indice);
void modificarPeli(peliculas *pp, int *indice);
void listado(peliculas *pp, int *indice);
void renovarCartelera(salas *ps, peliculas *pp, int *indice);
void gestionSalas(salas *ps, int *indice);
void fechaActual();
int validoFecha(char *fecha);

int main() {
	/* Array de estructuras */
	peliculas Peli[MAXPELI];
	salas Sala[3];
	
	/* Puntero a estructura */
	peliculas *ptrPeli;
	ptrPeli = Peli;
	
	salas *ptrSala;
	ptrSala = Sala;
	
	usuario *ptrUser;
	ptrUser = User;
	
	/* Reserva espacio almacenamiento puntero */
	ptrPeli = malloc(sizeof(Peli)*2);
	ptrSala = malloc(sizeof(Sala)*2);
	ptrUser = malloc(sizeof(User));
	
	/* Indice cantidad peliculas cargadas */
	int indice = 0;
	int *ptrIndice;
	ptrIndice = &indice;
	
	/* Autenticamos el usuario */
	autenticar(User);
	
	int opcion;
	inicio();
	do {
		system("clear");
		inicio();
		printf("\ninicio\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n       1. Gestion de Peliculas | 2. Renovar Cartelera | 3. Gestion de Salas | 4. Salir del Sistema\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("-> ");
		scanf("%d",&opcion);
		switch (opcion) {
			case 1: gestionPeliculas(ptrPeli, ptrIndice);
				break;
			case 2: renovarCartelera(ptrSala, ptrPeli, ptrIndice);
				break;
			case 3: gestionSalas(ptrSala, ptrIndice);
				break;
			case 4:
                system("clear");
                inicio();
                printf("\nsalir\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("\n                                     GRACIAS POR UTILIZAR CINAMON\n\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
				break;
			default:
                system("clear");
                inicio();
                printf("\ninicio\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("\n                                          OPCION INCORRECTA\n\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
				break;
		}
	} while(opcion != 4);
	
	/* Libera espacio reservado en memoria */
	free(ptrPeli);
	free(ptrSala);
	free(ptrUser);
	return 0;
}

void gestionPeliculas(peliculas *pp, int *indice) {
	int opcion;
	
	system("clear");
	inicio();
	do {
		getchar();
		fflush(stdin);
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas\n");
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
                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("\n                                          OPCION INCORRECTA\n\n");
                printf("---------------------------------------------------------------------------------------------------------\n");
				break;
		}
	} while(opcion != 9);
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void altaManual(peliculas *pp, int *indice) {
	char opcion, n_genero, nombrePeli[MAXNOMBRE];
	
	/* Verifica si se alcanzo el limite de peliculas */
	if(*indice == MAXPELI){
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> alta manual\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                   NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
		do {
			getchar();
			fflush(stdin);
			system("clear");
			inicio();
			printf("\ninicio >> gestion de peliculas >> alta manual\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("INGRESE EL NOMBRE DE LA PELICULA: ");
			fgets(nombrePeli,MAXNOMBRE,stdin);
            strncpy(pp[*indice].nombre, nombrePeli, strlen(nombrePeli)-1);
			printf("---------------------------------------------------------------------------------------------------------\n");
			do {
				printf("INGRESE EL AÑO DE ESTRENO: ");
				scanf("%d",&pp[*indice].anyo);
			} while((pp[*indice].anyo > ANYOACTUAL) || (pp[*indice].anyo < 1900));
			printf("---------------------------------------------------------------------------------------------------------\n");
			do {
				fflush(stdin);
				getchar();
				printf("SELECCIONE EL GENERO (A)ccion - (C)omedia - (D)rama - (S)uspenso - (T)error : ");
				scanf("%c",&n_genero);
				switch (n_genero) {
					case 'A':
					case 'a':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'C':
					case 'c':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'D':
					case 'd':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'S':
					case 's':
						pp[*indice].genero = toupper(n_genero);
						break;
					case 'T':
					case 't':
						pp[*indice].genero = toupper(n_genero);
						break;
					default: n_genero = -1;
						break;
				}
			} while(n_genero == -1);
			printf("---------------------------------------------------------------------------------------------------------\n");
			do {
				printf("INGRESE LA CANTIDAD EXPECTADORES QUE SE ESPERAN: ");
				getchar();
				scanf("%d",&pp[*indice].mce);
			} while((pp[*indice].mce > MAXSALA) || (pp[*indice].mce < 0));
			printf("---------------------------------------------------------------------------------------------------------\n");
			
			/* Pelicula se carga con estado "Vigente" */
			pp[*indice].marcaBaja = 0;
			
			/* Incrementa en 1 indice de peliculas cargadas */
			*indice += 1;
			
			system("clear");
			inicio();
			printf("\ninicio >> gestion de peliculas >> alta manual\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\n                                    CANTIDAD PELICULAS CARGADAS: %d\n\n", *indice);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("DESEA CARGAR MAS PELICULAS? (S)i - (N)o: ");
			scanf("%c",&opcion);
		} while (opcion == 's' || opcion == 'S');
	}
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void altaMasiva(peliculas *pp, int *indice) {
	int i, j;
	char ch, gen[] = {'A','C','D','S','T'};
	
	randomize;
	
	if(*indice == MAXPELI){
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> alta masiva\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                    NO SE PUEDEN CARGAR MAS PELICULAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
		for (i = *indice; i < MAXPELI; i++) {
			for(j = 0; j < MAXNOMBRE; j++){
				/* Genera 50 caracteres aleatorios a-z */
				ch = 'a' + rand() % (('z'-'a') + 1);
				pp[*indice].nombre[j] = ch;
			}
			/* Genera Años entre 1900 y 2013 */
			pp[*indice].anyo = 1900 + (rand() % (int)(ANYOACTUAL - 1900 + 1));
			
			/* Genera MCE */
			pp[*indice].mce = random(MAXSALA+1);
			
			/* Inicializa FAC en blanco */
			strcpy(pp[*indice].fac, "");
			
			/* Asigna el genero aleatorio */
			pp[*indice].genero = gen[random(5)];
			
			/* Se asigna marcaBaja en 0. significa que estan vigentes */
			pp[*indice].marcaBaja = 0;
			
			/* incremento el indice de peliculas */
			*indice += 1;
		}
        
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> alta masiva\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                    CANTIDAD PELICULAS CARGADAS: %d\n\n",*indice);
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void bajaPeli(peliculas *pp, int *indice) {
	/* marcaBaja = 0 : Pelicula Vigente
     marcaBaja = 1 : Pelicula VIGENTE */
	
	int i, j, h, num, aux, bandera = -1, pos[MAXPELI];
	char opcion, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
		inicio();
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                       NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
        
		system("clear");
		inicio();
		
		printf("\ninicio >> gestion de peliculas >> baja\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("INGRESE EL NOMBRE O PARTE DEL NOMBRE A BUSCAR: ");
		getchar();
		
		scanf("%s", nombrePeli);
		i = j = 0;
		printf("\n");
        printf("\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
		printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
        while(i < *indice){
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr != NULL) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", pp[i].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (h = 0; h < (MAXNOMBRE - strlen(pp[i].nombre)); h++)
                    printf(" ");
                printf(" | %d ", pp[i].anyo);
                printf("|   %c   ", pp[i].genero);
                if (pp[i].mce < 100)
                    printf("|  %d   ", pp[i].mce);
                else if (pp[i].mce < 1000)
                    printf("|  %d  ", pp[i].mce);
                else
                    printf("|  %d ", pp[i].mce);
                
                if(strlen(pp[i].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[i].fac);
                printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : " VIGENTE"));
                printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
        
		/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
		if(bandera != 0){
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\n                                     NO SE ENCONTRO NINGUNA PELICULA\n\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
			getchar();
		}
		else {
			do {
                printf("\nIngrese el num de pelicula a dar de baja: ");
                scanf("%d",&num);
			} while(num < 0 || num >= j+1);
            
			do {
				getchar();
				printf("\nCONFIRMA LOS CAMBIOS? (S)i - (N)o: ");
				scanf("%c",&opcion);
                
				switch (opcion) {
					case 'S':
					case 's':
						aux = pos[num-1];
						pp[aux].marcaBaja = 1;
						system("clear");
						inicio();
						printf("\nSE HA DADO DE BAJA LA SIGUIENTE PELICULA:\n");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
                        printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
                        if (aux < 9)
                            printf("%d.  ",aux+1);
                        else
                            printf("%d. ",aux+1);
                        printf("%s", pp[aux].nombre);
                        /* Formatea el nombre para mostrar en tabla */
                        for (j = 0; j < (MAXNOMBRE - strlen(pp[aux].nombre)); j++)
                            printf(" ");
                        printf(" | %d ", pp[aux].anyo);
                        printf("|   %c   ", pp[aux].genero);
                        if (pp[aux].mce < 100)
                            printf("|  %d   ", pp[aux].mce);
                        else if (pp[aux].mce < 1000)
                            printf("|  %d  ", pp[aux].mce);
                        else
                            printf("|  %d ", pp[aux].mce);
                        
                        if(strlen(pp[aux].fac) == 0)
                            printf("|            ");
                        else
                            printf("| %s ", pp[aux].fac);
                        printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : "VIGENTE"));
                        printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
						printf("\nPRESIONE ENTER PARA CONTINUAR..");
						getchar();
						break;
					case 'N':
					case 'n':
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("\n                                        NO SE REALIZARON CAMBIOS\n\n");
						printf("---------------------------------------------------------------------------------------------------------\n");
						printf("\nPRESIONE ENTER PARA CONTINUAR..");
						getchar();
						break;
					default: opcion = -1;
						break;
				}
			} while(opcion == -1);
		}
	}
	
	/* Vuelve bandera a su estado inicial */
	bandera = -1;
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void modificarPeli(peliculas *pp, int *indice) {
	int i, j, k, num, aux, bandera = -1, opcion, n_anyo, n_mce, pos[MAXPELI];
	char n_genero, nombrePeli[MAXNOMBRE];
	char *ptr;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
		inicio();
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                       NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	else {
		getchar();
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> modificar\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nIngrese el nombre o parte del nombre de la pelicula a buscar: ");
		
		scanf("%s", nombrePeli);
		printf("\n");
        printf("\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
		printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
		i = j = 0;
		while(i < *indice){
			/* Compara la subcadena con el nombre de pelicula */
			ptr = strstr(pp[i].nombre, nombrePeli);
			/* Verifica que la busqueda haya arrojado resultados */
			if(ptr != NULL) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", pp[i].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (k = 0; k < (MAXNOMBRE - strlen(pp[i].nombre)); k++)
                    printf(" ");
                printf(" | %d ", pp[i].anyo);
                printf("|   %c   ", pp[i].genero);
                if (pp[i].mce < 100)
                    printf("|  %d   ", pp[i].mce);
                else if (pp[i].mce < 1000)
                    printf("|  %d  ", pp[i].mce);
                else
                    printf("|  %d ", pp[i].mce);
                
                if(strlen(pp[i].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[i].fac);
                printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : " VIGENTE"));
                printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
				pos[j] = i;
				j++;
				bandera = 0;
			}
			i++;
		}
		printf("CANTIDAD PELICULAS ENCONTRADAS: %d\n",j);
        
		/* Si no encuentra peliculas muestra msj y vuelve al menu anterior */
		if(bandera != 0) {
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\n                                     NO SE ENCONTRO NINGUNA PELICULA\n\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
			getchar();
		}
		else {
			do {
                printf("\nIngrese el num de pelicula a modificar: ");
                scanf("%d",&num);
			} while(num < 0 || num >= j+1);
			
			/* Almacena la posicion de la pelicula de la estructura */
			aux = pos[num-1];
			
			do {
				fflush(stdin);
				system("clear");
				inicio();
				printf("\nPELICULA A MODIFICAR:\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
                printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
                if (aux < 9)
                    printf("%d.  ",aux+1);
                else
                    printf("%d. ",aux+1);
                printf("%s", pp[aux].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (k = 0; k < (MAXNOMBRE - strlen(pp[aux].nombre)); k++)
                    printf(" ");
                printf(" | %d ", pp[aux].anyo);
                printf("|   %c   ", pp[aux].genero);
                if (pp[aux].mce < 100)
                    printf("|  %d   ", pp[aux].mce);
                else if (pp[aux].mce < 1000)
                    printf("|  %d  ", pp[aux].mce);
                else
                    printf("|  %d ", pp[aux].mce);
                
                if(strlen(pp[aux].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", pp[aux].fac);
                printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : " VIGENTE"));
                printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
				printf("\n\nSELECCIONE LA MODIFICACION A REALIZAR:\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("                      1. Año | 2. Género | 3. MCE | 4. Volvel al menú anterior\n");
				printf("---------------------------------------------------------------------------------------------------------\n");
				printf("-> ");
				scanf("%d", &opcion);
				switch (opcion) {
					case 1: do {
                        getchar();
                        printf("\nIngrese el nuevo año: ");
                        scanf("%d",&n_anyo);
                    } while(n_anyo < 1900 || n_anyo > ANYOACTUAL);
                        pp[aux].anyo = n_anyo;
						break;
					case 2:	do {
                        fflush(stdin);
                        getchar();
                        printf("\nIngrese el nuevo genero: ");
                        scanf("%c",&n_genero);
                        switch (n_genero) {
                            case 'A':
                            case 'a':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'C':
                            case 'c':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'D':
                            case 'd':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'S':
                            case 's':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            case 'T':
                            case 't':
                                pp[aux].genero = toupper(n_genero);
                                break;
                            default: n_genero = -1;
                                break;
                        }
                    } while(n_genero == -1);
						break;
					case 3: do {
                        getchar();
                        printf("\nIngrese el nuevo MCE: ");
                        scanf("%d",&n_mce);
                    } while(n_mce < 0 || n_mce > MAXSALA);
                        pp[aux].mce = n_mce;
						break;
					case 4:
						break;
					default: opcion = -1;
						break;
				}
			} while(opcion == -1);
            
            system("clear");
            inicio();
            printf("\nSE HA MODIFICADO LA SIGUIENTE PELICULA:\n");
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("\nNOMBRE PELICULA                                          AÑO   GENERO    MCE        FAC           ESTADO\n");
            printf("--+----------------------------------------------------+------+-------+-------+-------------+---------------\n");
            if (aux < 9)
                printf("%d.  ",aux+1);
            else
                printf("%d. ",aux+1);
			printf("%s", pp[aux].nombre);
            /* Formatea el nombre para mostrar en tabla */
            for (j = 0; j < (MAXNOMBRE - strlen(pp[aux].nombre)); j++)
                printf(" ");
            printf(" | %d ", pp[aux].anyo);
            printf("|   %c   ", pp[aux].genero);
            if (pp[aux].mce < 100)
                printf("|  %d   ", pp[aux].mce);
            else if (pp[aux].mce < 1000)
                printf("|  %d  ", pp[aux].mce);
            else
                printf("|  %d ", pp[aux].mce);
            
            if(strlen(pp[aux].fac) == 0)
                printf("|            ");
            else
                printf("| %s ", pp[aux].fac);
            printf("| %s\n", ((pp[aux].marcaBaja)?"DADA DE BAJA" : "VIGENTE"));
            printf("--+----------------------------------------------------+------+-------+-------+-------------+---------------\n");
            printf("\nPRESIONE ENTER PARA CONTINUAR..");
            getchar();
		}
	}
	/* Vuelve bandera a su estado inicial */
	bandera = -1;
	
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
}

void listado(peliculas *pp, int *indice) {
	int i, j;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> listado\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                       NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
	}
	else {
		system("clear");
		inicio();
		printf("\ninicio >> gestion de peliculas >> listado\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
        printf("\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
		printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
		for(i = 0; i < *indice; i++) {
            if (i < 9)
                printf("%d.  ",i+1);
            else
                printf("%d. ",i+1);
			printf("%s", pp[i].nombre);
            /* Formatea el nombre para mostrar en tabla */
            for (j = 0; j < (MAXNOMBRE - strlen(pp[i].nombre)); j++)
                printf(" ");
            printf(" | %d ", pp[i].anyo);
            printf("|   %c   ", pp[i].genero);
            
            if (pp[i].mce < 100)
                printf("|  %d   ", pp[i].mce);
            else if (pp[i].mce < 1000)
                printf("|  %d  ", pp[i].mce);
            else
                printf("|  %d ", pp[i].mce);
            
            if(strlen(pp[i].fac) == 0)
                printf("|            ");
            else
                printf("| %s ", pp[i].fac);
            printf("| %s\n", ((pp[i].marcaBaja)?"DADA DE BAJA" : "  VIGENTE"));
            printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
		}
		printf("\n");
	}
	/* Limpia buffer y vuelve al menu anterior */
	printf("PRESIONE ENTER PARA CONTINUAR..");
	getchar();
	fflush(stdin);
}

void renovarCartelera(salas *ps, peliculas *pp, int *indice) {
	int i, j, k, h, n, genSala, fechaOK = 0, indiceGen = 4;
	char gen[] = {'A','C','D','S','T'};
	char fechahoy[12];
	
	fechaActual(fechahoy);
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
		inicio();
		printf("\ninicio >> renovar cartelera\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                         NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
		
	}
	else {
		
		/* Inicializo las salas con su respectivo nombre y capacidad*/
		strcpy(ps[0].nombreSala, "Aleandro");
		ps[0].capacidad = 1500;
		strcpy(ps[1].nombreSala, "Zorrilla");
		ps[1].capacidad = 200;
		strcpy(ps[2].nombreSala, "Nu");
		ps[2].capacidad = 525;
		strcpy(ps[3].nombreSala, "Eve");
		ps[3].capacidad = 525;
		
		for(i = 0; i < 4; i++){
			fflush(stdin);
			getchar();
			system("clear");
			inicio();
			printf("\ninicio >> renovar cartelera\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nSELECCIONE EL GENERO PARA LA SALA \"%s\":\t (A)ccion - (C)omedia - (D)rama - (S)uspenso - (T)error\n\n", ps[i].nombreSala);
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("GENEROS DISPONIBLES: ");
			
			/* Muestra los generos disponibles */
			for(j = 0; j <= indiceGen; j++)
				printf("| %d. %c ", j+1, gen[j]);
			
			/* Verifica que el numero ingresado este dentro del rango */
			do {
				printf("\nIngrese el numero correspondiente: ");
				scanf("%d",&genSala);
			} while((genSala > j) || (genSala < 0));
			
			/* Asigna e imprime el genero seleccionado a la sala */
			ps[i].generoSala = gen[genSala-1];
			
			/* Elimina de la lista de generos disponibles al genero seleccionado */
			for(k = genSala-1; k <= indiceGen; k++)
				gen[k] = gen[k+1];
			
			/* Busca y asigna las peliculas a la sala de acuerdo al genero seleccionado */
			for(h = 0, n = 0; h < *indice; h++){
				
				/* Verifica la FAC con la fecha actual. En caso de haber pasado mas de 7 dias da el OK. -2604 y 8897 num magicos que indican dif 7 dias */
				if((validoFecha(pp[h].fac) - validoFecha(fechahoy) >= -2604) || (validoFecha(pp[h].fac) - validoFecha(fechahoy) <= 8897))
					fechaOK = 1;
				
				/* Verifica los criterios para que la pelicula pueda ser asignada a la sala */
				if((pp[h].genero == ps[i].generoSala) && (pp[h].mce <= ps[i].capacidad) && (pp[h].marcaBaja == 0) && fechaOK == 1) {
					strcpy(ps[i].enCartelera[n].nombre, pp[h].nombre);
					strcpy(ps[i].enCartelera[n].fac, fechahoy);
					strcpy(pp[h].fac, fechahoy);
					ps[i].enCartelera[n].anyo = pp[h].anyo;
                    ps[i].enCartelera[n].mce = pp[h].mce;
					ps[i].enCartelera[n].genero = pp[h].genero;
					ps[i].asignadas = n+1;
					n++;
				}
			}
			indiceGen--;
		}
	}
	
	fechaOK = 0;
	/* Limpia buffer y vuelve al menu anterior */
	fflush(stdin);
	getchar();
}

void gestionSalas(salas *ps, int *indice) {
	int i, j, h;
	
	/* Verifica que haya peliculas cargadas */
	if(*indice == 0) {
		system("clear");
		inicio();
		printf("\ninicio >> gestion de salas\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\n                                         NO HAY PELICULAS CARGADAS\n\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	
	else {
		/* Muestra el listado de peliculas asignadas a las correspondientes salas */
		system("clear");
		inicio();
		printf("\ninicio >> gestion de salas\n");
		printf("---------------------------------------------------------------------------------------------------------\n");
		for(i = 0; i < 4; i++){
			printf("\nPELICULAS ASIGNADAS A LA SALA \"%s\" (%d) - GENERO: %c", ps[i].nombreSala, ps[i].asignadas, ps[i].generoSala);
			printf("\n\n    NOMBRE PELICULA                                      AÑO   GENERO    MCE        FAC        ESTADO\n");
            printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
			for(j = 0; j < ps[i].asignadas; j++) {
				if (j < 9)
                    printf("%d.  ",j+1);
                else
                    printf("%d. ",j+1);
                printf("%s", ps[i].enCartelera[j].nombre);
                /* Formatea el nombre para mostrar en tabla */
                for (h = 0; h < (MAXNOMBRE - strlen(ps[i].enCartelera[j].nombre)); h++)
                    printf(" ");
                printf(" | %d ", ps[i].enCartelera[j].anyo);
                printf("|   %c   ", ps[i].enCartelera[j].genero);
                if (ps[i].enCartelera[j].mce < 100)
                    printf("|  %d   ", ps[i].enCartelera[j].mce);
                else if (ps[i].enCartelera[j].mce < 1000)
                    printf("|  %d  ", ps[i].enCartelera[j].mce);
                else
                    printf("|  %d ", ps[i].enCartelera[j].mce);
                
                if(strlen(ps[i].enCartelera[j].fac) == 0)
                    printf("|            ");
                else
                    printf("| %s ", ps[i].enCartelera[j].fac);
                printf("| %s\n", ((ps[i].enCartelera[j].marcaBaja)?"DADA DE BAJA" : " VIGENTE"));
                printf("--+----------------------------------------------------+------+-------+-------+------------+-------------\n");
            }
			printf("\n\n");
        }
		printf("\nPRESIONE ENTER PARA CONTINUAR..");
		getchar();
	}
	getchar();
}

void autenticar(usuario pu[]) {
	int i, pass, userOK = 0, auth, pos;
	char usuario[MAXNOMBRE];
	
	do {
		system("clear");
		puts("\n\n");
		puts("                                                      **");
		puts("                                         *** ****  ********");
		puts("                                        *       ****      **");
		puts("                                       **        **        *");
		puts("                                       **        **        *");
		puts("                                        *       ***        *");
		puts("                                         **   ********  ***   **");
		puts("                                         **           ** *** **");
		puts("                                         **            *     **");
		puts("                                         **                  **");
		puts("                                         **                  **");
		puts("                                          *            * **  **");
		puts("                                              *   *          **");
		puts("                                             *** * *");
		puts("                                             **  ** *");
		puts("                                            *    * **");
		puts("                                           * *   *  **");
		puts("                                          * *    *  * *");
		puts("                                           *     *   * *");
		puts("\n                                         BIENVENIDO A CINAMON");
		fflush(stdin);
		
		printf("\n\n                                         USUARIO: ");
		fgets(usuario,50,stdin);
		
		for(i= 0; i < 10; i++) {
			auth = strcmp(pu[i].nombreUsuario, usuario);
			/* Valida el usuario */
			if(auth == 0) {
				pos = i;
				userOK = 1;
			}
		}
		
		fflush(stdin);
		printf("                                         CONTRASEÑA: ");
		scanf("%d",&pass);
		
		/* Verifica que el usuario y contraseña coincidan */
		if((pu[pos].password == pass) && userOK == 1)
			auth = 1;
		
		else {
			auth = 0;
			printf("\n---------------------------------------------------------------------------------------------------------\n");
			printf("\n                                    USUARIO O CONTRASEÑA INCORRECTOS\n\n");
			printf("---------------------------------------------------------------------------------------------------------\n");
			printf("\nPRESIONE ENTER PARA CONTINUAR..");
			getchar();
		}
		getchar();
	} while (auth == 0);
	
	printf("\n---------------------------------------------------------------------------------------------------------\n");
	printf("\n                                         INGRESO SATISFACTORIO\n\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\nPRESIONE ENTER PARA CONTINUAR..");
	getchar();
}

void fechaActual(char *fecha) {
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	strftime(fecha,12,"%d/%m/%Y",tlocal);
}

int validoFecha(char *fecha) {
    int a = (int)strtol(fecha, &fecha, 10);
    int m = (int)strtol(++fecha, &fecha, 10);
    int d = (int)strtol(++fecha, &fecha, 10);
    return (a*12+m)*31+d;
}

void inicio() {
	char ltime[12];
	fechaActual(ltime);
	printf("%s\n",ltime);
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
