#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <stdio.h>
#include "prise_trappe.h"
#include "voyant_bouton.h"
#include "lecteurcarte.h"
#include "base_clients.h"

void generateur_save_initialiser();
void generateur_save_generer(pwm courant);
void generateur_save_charger();
void generateur_save_fermerAC();
void generateur_save_ouvrirAC();

#endif // GENERATEUR_SAVE_H
