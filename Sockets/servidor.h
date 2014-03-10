 

#include "clienteInfo.h"

#define maxClientes 20




class Servidor{


	private:
		int descriptorSer;
		int idBind;
		int puerto;
		struct sockaddr_in servidorInfo; 
		vector<ClienteInfo *> clientesDescriptor;

		bool state;
		//vector<pthread_t> clientesHilos;
		//vector<struct sockaddr> clientesDescriptor;

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

		void migrarCodigo(void);
		//void tiempos(void);
		void frases(void);
		int buscarCliente(string);
		
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
