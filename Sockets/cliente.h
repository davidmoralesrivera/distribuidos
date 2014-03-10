#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>
#include <vector>

using namespace std;

class Cliente{

	private:
		int descriptorCliente;
		struct sockaddr_in servidorInfo;
		int puertoServidor;
		string ipServidor;
		int tiempoVida;
		bool estado;


	public:

		Cliente(void);
		Cliente(int, string, int);

		void conectarServidor(void);
		//static void * actualizarTiempo(void *);
		static void * tiempoCliente(void*);
		static void * contarFrases(void *);

		int getTiempoVida(void);
		void setTiempoVida(int);	

		int getDescriptor(void);
		void setDescriptor(int);

		bool getEstado(void);
		void setEstado(bool);
};
