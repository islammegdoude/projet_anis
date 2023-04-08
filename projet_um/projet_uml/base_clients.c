#include <unistd.h>
#include "base_clients.h"
#include <stdio.h>
#include <time.h>
void base_clients_initialiser()
{	
	int i;
	for(i = 0; i < 100; i++)
		 baseClients[i] = 0;
}
void base_clients_ajouter(int numero, int code)
{
	baseClients[numero] = code;
}
int  base_clients_authentifier(int numero, int code)
{	
	if(baseClients[numero] == code)
		return 1;
	else
		return 0;
}
void base_clients_supprimer(int numero)
{
	numeroBloquer = numero;
}






