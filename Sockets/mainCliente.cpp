#include "cliente.h"
#include <stdlib.h>
int main(int argc, char ** argv){
	Cliente *cliente = new Cliente(atoi(argv[1]),argv[2]);
	
	cliente->conectarServidor();
	return 0;
}
