#include "cliente.h"

Cliente::Cliente(){
	this->puertoServidor=9000;
	this->ipServidor="192.168.1.10";
	this->estado=true;
}

Cliente::Cliente(int puerto, string ip){
	this->puertoServidor=puerto;
	this->ipServidor=ip;
	this->estado=true;
}

void * Cliente::escucharServidor(void * cli){
	Cliente* cliente=(Cliente *) cli;
	char mensajeDeServidor[60];

	while(1){
		recv(cliente->getDescriptor(),(void *)&mensajeDeServidor ,60,0);
		cout<<mensajeDeServidor<<endl;
	}
}

void * Cliente::escribirServidor(void * cli){
	Cliente* cliente=(Cliente *) cli;

	int conectado=1;
	while(conectado){

		char msg[128];
		sprintf(msg,"Hola");

		int i=send(cliente->getDescriptor(),(void *)msg,sizeof(msg),0);
		sleep(1);

		if(i==-1){
			conectado=0;
			cout<<"se desconecto del servidor"<<endl;
			close(cliente->getDescriptor());
			exit(EXIT_SUCCESS);
		}
	}	
}

void Cliente::conectarServidor(){

	descriptorCliente= socket(AF_INET,SOCK_STREAM,0);

	servidorInfo.sin_family=AF_INET;

	inet_pton(AF_INET,ipServidor.c_str(),&servidorInfo.sin_addr);

	servidorInfo.sin_port=htons(puertoServidor);

	int conn=connect(descriptorCliente,(struct sockaddr *)&servidorInfo,sizeof(servidorInfo));

	if(conn!=-1){

		pthread_t hiloEscucha;
		pthread_create(&hiloEscucha,NULL,escucharServidor,(void *)this);


		pthread_t hiloEscribe;
		pthread_create(&hiloEscribe,NULL,escribirServidor,(void *)this);

		while(1);
	}else{

		cout<<"No se pudo conectar con el servidor"<<endl;
	}
}


int Cliente::getDescriptor(){
	return this->descriptorCliente;
}

void Cliente::setDescriptor(int descriptor){
	 this->descriptorCliente=descriptor;
}

bool Cliente::getEstado(){
	return this->estado;
}

void Cliente::setEstado(bool estado){
	 this->estado=estado;
}

