#! /bin/bash
scp cliente.cpp  'root@192.168.1.21:'
scp cliente.h 'root@192.168.1.21:'
scp mainCliente.cpp 'root@192.168.1.21:'
ssh  'root@192.168.1.21' g++ cliente.cpp  mainCliente.cpp -pthread -o /root/cliente
ssh  'root@192.168.1.21' chmod 777 cliente
ssh  'root@192.168.1.21'  ./cliente $1 $2 120 &

scp cliente.cpp  'root@192.168.1.22:'
scp cliente.h 'root@192.168.1.22:'
scp mainCliente.cpp 'root@192.168.1.22:'
ssh  'root@192.168.1.22' g++ cliente.cpp  mainCliente.cpp -pthread -o /root/cliente
ssh  'root@192.168.1.22' chmod 777 cliente
ssh  'root@192.168.1.22'  ./cliente $1 $2 120 &
