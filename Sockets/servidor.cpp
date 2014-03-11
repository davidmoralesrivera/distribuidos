#include "servidor.h"

//variables globales
clock_t inicial;
int count;


Servidor:: Servidor(){
	this->puerto=9000;
}


Servidor:: Servidor(int puerto){
	this->puerto=puerto;
}
 
void Servidor::inicializarServidor(){

	descriptorSer= socket(AF_INET,SOCK_STREAM,0);
	servidorInfo.sin_family=AF_INET;
	servidorInfo.sin_addr.s_addr=htonl(INADDR_ANY);
	servidorInfo.sin_port=htons(puerto);
	idBind=bind(descriptorSer,(struct sockaddr *)&servidorInfo, sizeof(servidorInfo));
	
	listen(descriptorSer, maxClientes);

	if(descriptorSer==-1 && idBind==-1)
		cout<<"Error iniciando el servidor."<<endl;

}

void Servidor::cerrarServidor(){
	exit(EXIT_SUCCESS);
}


void * recibirCliente(void * cli){
	ClienteInfo * cliente=(ClienteInfo *) cli;

	char tiempo[128];

	while(cliente->getEstado()){
		int i=recv(cliente->getDescriptorCliente(),(void *)&tiempo,128,0);
		sleep(1);

		if(i!=0){
			string aux;
			string fin="finalizar sesion";
			
			aux.assign(tiempo);
			if(aux.compare(fin)==0){
				cout<<"Se desconecto el cliente con ip: "<<inet_ntoa(cliente->getClienteInfor().sin_addr)<<endl;
				cliente->setEstado(false);

				close(cliente->getDescriptorCliente());
			}else{

				cout<<"El cliente con ip: "<<inet_ntoa(cliente->getClienteInfor().sin_addr)<<" envio: "<<tiempo<<endl;
				char msg[60];
				sprintf(msg,"Hola");
				send(cliente->getClienteInfor(),(void *)msg,sizeof(msg),0);
				inicial=clock();
			}
		}else{
			//se acabo el tiempo//
			cout<<"Se desconecto el cliente con ip: "<<inet_ntoa(cliente->getClienteInfor().sin_addr)<<" con error"<<endl;
			cliente->setEstado(false);
			close(cliente->getDescriptorCliente());
		}

	}
	
}




void * tiempoServidor(void * servidor){
	Servidor * server=(Servidor *) servidor;
	double time=0;
	while(time<120){
		time=((double)clock()-inicial)/CLOCKS_PER_SEC;
		//cout<< time<<endl;
	}
	cout<<"Servidor apagado"<<endl;	
	server->cerrarServidor();

}


void Servidor::aceptarClientes(){

	int descriptorCliente;

	count=0;
	inicial=clock();
	pthread_t tiempoHilo;

	pthread_create(&tiempoHilo,NULL,&tiempoServidor,(void *) this);
	while(count<maxClientes){
		struct sockaddr_in clienteInfor;
		int tamano= sizeof(struct sockaddr_in);
		cout<<"Aceptando cliente"<<endl;
		descriptorCliente=accept(this->descriptorSer,(struct sockaddr *)&clienteInfor,(socklen_t*) &tamano);
		//recibiendo clientes

		if(descriptorCliente!=-1){
			inicial=clock();
			cout<< "Cliente Conectado"<<endl;
			clientesDescriptor.push_back(new ClienteInfo(descriptorCliente,clienteInfor));
			pthread_t clientesHilos;
			
			pthread_create(&clientesHilos,NULL,&recibirCliente,(void *) clientesDescriptor[count]);
			count++;
		}
	}
}

void * Servidor::comenzarServidor(void * servidor){
	Servidor * server=(Servidor *) servidor;
	server->aceptarClientes();
}

void Servidor::ejecutarServidor(){
	pthread_t hilo;
	pthread_create(&hilo,NULL,&comenzarServidor,(void *) this);
}

void Servidor::migrarCodigo(){
	char comando[128];

	sprintf(comando,"sh conectar.sh %d 192.168.1.20",getPuerto());
	system(comando);

}

int Servidor::buscarCliente(string ipCliente){
	
	int descriptor=-1;
	string ipAux;
	for(int i=0;i<getClientes().size() && descriptor==-1;i++){
		ipAux.assign(inet_ntoa(getClientes()[i]->getClienteInfor().sin_addr));
		if(ipAux.compare(ipCliente)==0 && getClientes()[i]->getEstado()){
			descriptor=getClientes()[i]->getDescriptorCliente();
		}
	}

	return descriptor;
}



void Servidor::tiempos(){
	while(1){
		int opcion;
		string ipCliente;
		int tiempo;
		cout<<"Digite: "<<endl<<"1 para aumentar tiempo al cliente"<<endl<<"2 para disminuir tiempo al cliente"<<endl<<"3 para detener a todos los clientes"<<endl;
		cin>>opcion;
		
		switch(opcion){
			case 1:
				char mens[60];
				cout<<"Digite la ip del cliente"<<endl;
				cin>>ipCliente;
				cout<<"Digite el tiempo que quiere aumentar"<<endl;
				cin>>tiempo;
				int descriptorCliente;
				descriptorCliente=buscarCliente(ipCliente);
				if(descriptorCliente!=-1){
					sprintf(mens,"%d",tiempo);
					int err=send(descriptorCliente,(void *) &mens,60,0);
					if(err==-1){
						cout<<"Error al enviar"<<endl;
					}
				}else{
					cout<<"La ip ingresada no corresponde a un cliente o no esta activo el cliente"<<endl;
				}
				
			break;

			case 2:
				char mensa[60];
				cout<<"Digite la ip del cliente"<<endl;
				cin>>ipCliente;
				cout<<"Digite el tiempo que quiere disminuir"<<endl;
				cin>>tiempo;
				int descriptorCli;
				descriptorCli=buscarCliente(ipCliente);
				if(descriptorCli!=-1){
					tiempo=tiempo*-1;
					sprintf(mensa,"%d",tiempo);
					int err=send(descriptorCli,(void *) &mensa,60,0);
					if(err==-1){
						cout<<"Error al enviar"<<endl;
					}
				}else{
					cout<<"La ip ingresada no corresponde a un cliente o no esta activo el cliente"<<endl;
				}
			break;

			case 3:
				for(int i=0;i<getClientes().size();i++){
					if(getClientes()[i]->getEstado()){
						char fin[60]="false";
						send(getClientes()[i]->getDescriptorCliente(),(void *)&fin,60,0);
					}
				}

			break;
		}
	}
}


void Servidor::setDescriptorServidor(int descriptor){
	this->descriptorSer=descriptor;
}

void Servidor::setIdBin(int bind){
	this->idBind=bind;
}
void Servidor::setPuerto(int puerto){
	this->puerto=puerto;
}
void Servidor::setServidorInfo(struct sockaddr_in info){
	this->servidorInfo = info;
}



int Servidor::getDescriptorServidor(){
	return this->descriptorSer;
}
int Servidor::getIdBin(){
	return this->idBind;
}
int Servidor::getPuerto(){
	return this->puerto;
}
struct sockaddr_in Servidor::getServidorInfo(){
	return this->servidorInfo;
}

vector<ClienteInfo *> Servidor::getClientes(){
	return this->clientesDescriptor;
}


