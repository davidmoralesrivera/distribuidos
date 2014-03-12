#include "clienteInfo.h"

ClienteInfo::ClienteInfo(int desc , struct sockaddr_in infor){
	this->descriptorCliente=desc;
	this->clienteInfor= infor;
	this->estado=true;
}

int ClienteInfo::getId(){
	return this->id;
}

void ClienteInfo::setId(int id){
 	this->id=id;
}


int ClienteInfo::getDescriptorCliente(void){
	return this->descriptorCliente;
}
struct sockaddr_in ClienteInfo::getClienteInfor(){
	return this->clienteInfor;
}

bool ClienteInfo::getEstado(){
	return this->estado;
}

void ClienteInfo::setEstado(bool estado){
	this->estado=estado;
}