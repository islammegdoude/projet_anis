#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include "voyant_bouton.h"
#include "timer.h"
#include "lecteurcarte.h"
#include "generateur_save.h"
#include "base_clients.h"

int main()
{
	lecteur_carte_initialiser();
	lecteurcarte_initialiser();
	base_clients_initialiser();
	timer_initialiser();
	voyant_bouton_initialiser();
	generateur_save_initialiser();
	

    	while (1)
    	{
        	lecteurcarte_lire_carte();
    	}

}
