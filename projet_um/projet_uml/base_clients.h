#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <stdio.h>
int baseClients[100];
int numeroBloquer;

void base_clients_initialiser();
void base_clients_ajouter(int numero, int code);
int base_clients_authentifier(int numero, int code);
void base_clients_supprimer(int numero);

#endif // BASE_CLIENTS_H
