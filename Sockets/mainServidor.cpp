#include "servidor.h"



int main(int arg , char** args){

	Servidor servidor;

	servidor.setPuerto(atoi(args[1]));

	servidor.inicializarServidor();
	servidor.ejecutarServidor();
	
	while(1);

	return 0;
}