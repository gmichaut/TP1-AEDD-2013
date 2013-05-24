#define NOMBREMAX 50

/* Estructuras */
struct Usuario {
	char nombreUsuario[NOMBREMAX];
	int password;
};

typedef struct Usuario usuario;

/* Declaro un array de 10 usuarios y lo inicializo */
usuario User[9] = {
					{"el secreto de sus ojos", 2009},
					{"un novio para mi mujer", 2008},
					{"el abrazo partido", 2004},
					{"nueve reinas", 2000},
					{"mundo grua", 1999},
					{"dias de pesca", 2012},
					{"el cielo elegido", 2012},
					{"escuela normal", 2012},
					{"un lugar en el mundo", 1992},
					{"la historia oficial", 1985}
					};

/* implementar ingreso usuario con un loop y un strcmp */
