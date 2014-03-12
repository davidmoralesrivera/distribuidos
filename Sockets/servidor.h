 

#include "clienteInfo.h"

#define maxClientes 100




class Servidor{


	private:
		int descriptorSer;
		int idBind;
		int puerto;
		struct sockaddr_in servidorInfo; 
		vector<ClienteInfo *> clientesDescriptor;

		bool state;
	public:
		
		//constructores
		Servidor(void);
		Servidor(int);

		// metodos

		void inicializarServidor(void);
		void aceptarClientes(void);
		void cerrarServidor(void);	
		static void * comenzarServidor(void *);
		void ejecutarServidor(void);
		
		//set

		void setDescriptorServidor(int);
		void setIdBin(int);
		void setPuerto(int);
		void setServidorInfo(struct sockaddr_in);

		//get

		int getDescriptorServidor(void);
		int getIdBin(void);
		int getPuerto(void);
		struct sockaddr_in getServidorInfo(void);
		vector<ClienteInfo *> getClientes(void);

}; 
