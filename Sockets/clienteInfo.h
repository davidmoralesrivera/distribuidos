#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <pthread.h>
#include <time.h>
#include <cstdio>

using namespace std;

class ClienteInfo{

	private:
		int descriptorCliente;
		struct sockaddr_in clienteInfor; 
		bool estado;
		int id;
	public:
		
		ClienteInfo(int ,struct sockaddr_in);

		int getId(void);
		void setId(int);

		int getDescriptorCliente(void);
		struct sockaddr_in getClienteInfor();

		bool getEstado(void);
		void setEstado(bool);


};