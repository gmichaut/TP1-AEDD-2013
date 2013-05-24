/* Estructuras */
struct Usuario {
	char nombreUsuario[50];
	int password;
};

typedef struct Usuario usuario;

/* Declaro un array de 10 usuarios */
usuario User[10];

/* implementar ingreso usuario con un loop y un strcmp */