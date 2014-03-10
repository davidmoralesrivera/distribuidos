#include "cliente.h"
#include <stdlib.h>
int main(int argc, char ** argv){
	//cout<<argv[1]<<" "<<argv[2]<<endl;	
	Cliente *cliente = new Cliente(atoi(argv[1]),argv[2],atoi(argv[3]));
	
	cliente->conectarServidor();
	return 0;
}
