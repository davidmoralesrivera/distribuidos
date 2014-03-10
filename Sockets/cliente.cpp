#include "cliente.h"

clock_t inicial;


Cliente::Cliente(){
 
	this->puertoServidor=9000;
	this->ipServidor="192.168.1.10";
	this->tiempoVida=120;
	this->estado=true;
}

Cliente::Cliente(int puerto, string ip, int tiempo){
	this->puertoServidor=puerto;
	this->ipServidor=ip;
	this->tiempoVida=tiempo;
	this->estado=true;
}

void * Cliente::tiempoCliente(void * cli){
	Cliente* cliente=(Cliente *) cli;
	double time=0;
	while(time<cliente->getTiempoVida()){
		time=((double)clock()-inicial)/CLOCKS_PER_SEC;
		//cout<< time<<endl;
	}
	cliente->setEstado(false);

	char fin[60]="finalizar sesion";
	send(cliente->getDescriptor(),(void *) fin,60,0);
	cout<<"Cliente desconectado"<<endl;	
	exit(EXIT_SUCCESS);

}



void * Cliente::actualizarTiempo(void * cli){
	Cliente* cliente=(Cliente *) cli;

	while(1){
		char tiempo[60];
		string desactivar="false";
		string aux;
		int err= recv(cliente->getDescriptor(),(void *)&tiempo ,60,0);

		if(err>0){
			//cout<<tiempo<<endl;
			aux.assign(tiempo);
			if(aux.compare(desactivar)==0){
				cliente->setEstado(false);
				char fin[60]="finalizar sesion";
				send(cliente->getDescriptor(),(void *) fin,60,0);
			}else{
				cliente->setTiempoVida(cliente->getTiempoVida()+atoi(tiempo));
			}
		}else{

			cout<<"Error"<<endl;
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
		pthread_t hilo;
		pthread_create(&hilo,NULL,tiempoCliente,(void *)this);

		pthread_t hilo2;
		pthread_create(&hilo2,NULL,actualizarTiempo,(void *) this);
		int boolean=1;
		
		
		while(boolean && estado){
			char msg[128];
		double tiempo= tiempoVida -((double)clock()-inicial)/CLOCKS_PER_SEC;

		 ostringstream convertir;
		 convertir<<tiempo;

		sprintf(msg,"Tiempo restante %s segundos",convertir.str().c_str());
		
			int i=send(descriptorCliente,(void *)msg,sizeof(msg),0);
			sleep(1);
			if(i==-1){
				boolean=0;
				cout<<"se desconecto del servidor"<<endl;
				close(descriptorCliente);
			}
		}
		while(1){
			
		}	
		close(descriptorCliente);
		cout<<"termino la conexion"<<endl;	
	}else{

		cout<<"No se pudo conectar con el servidor"<<endl;
	}
}

int Cliente::getTiempoVida(){
	return this->tiempoVida;
}

void Cliente::setTiempoVida(int tiempo){
	 this->tiempoVida=tiempo;
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

