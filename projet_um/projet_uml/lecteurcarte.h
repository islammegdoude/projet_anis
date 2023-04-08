#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <stdio.h>
#include <lcarte.h>
#include "voyant_bouton.h"
#include "timer.h"
#include "prise_trappe.h"
#include "generateur_save.h"
#include "base_clients.h"

void lecteur_carte_initialiser();
unsigned short int numero;
void lecteurcarte_initialiser();
void lecteurcarte_lire_carte();

#endif // LECTEURCARTE_H
