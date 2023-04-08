#include <unistd.h>
#include "lecteurcarte.h"
#include "voyant_bouton.h"
#include "timer.h"
#include "prise_trappe.h"
#include "generateur_save.h"
#include "base_clients.h"


entrees *io;
int shmid;

void lecteur_carte_initialiser()
{
	io=acces_memoire(&shmid); 
	/* associe la zone de memoire partageeau pointeur */
	if (io==NULL) 
		printf("Erreur pas de mem sh\n");
}

void lecteurcarte_initialiser()
{
	initialisations_ports();
}

void lecteurcarte_lire_carte()
{
	int i;
	int code;
	printf("Veuillez inserée catre!!\n");	
	attente_insertion_carte();
	numero = lecture_numero_carte();
	base_clients_ajouter(13, 1234);
	base_clients_ajouter(31, 4321);
	if(carte_inseree() && numero != numeroBloquer && numero == lecture_numero_carte())
	{
		printf("Catre inserée!!\n");
		printf("numero de la carte = %i\n", numero);
		
		for(i = 0; i < 3; i++)
		{
			printf("Entrer le code : ");
			scanf("%i", &code);
			if( base_clients_authentifier(numero, code))
			{
				printf("Code Bon!!\n");
				printf("Veuillez retirer la carte!!\n");
				attente_retrait_carte();
				printf("Catre retirée!!\n");
				break;
			}
		}
		if(i == 3)
		{
			voyant_bouton_clignoteDefault(ROUGE);
			printf("Veuillez retirer la carte!!\n");
			attente_retrait_carte();
			printf("Catre retirée!!\n");
			base_clients_supprimer(numero);
			return 0;
		}

		timer_raz();
		voyant_bouton_clignoteCharge(VERT);

		if(getBouttonCharge())
			if(timer_valeur() <= 60)
			{
				setDispo(OFF);
				setCharge(ROUGE);
				prise_trappe_deverrouiller();
				generateur_save_generer(DC);
				generateur_save_charger();
			}

	}
	else if(carte_inseree() && numero == numeroBloquer)
		printf("CARTE BLOQUEE\n");

	/*else if(carte_inseree() && numero != lecture_numero_carte())
		{
			printf("Ce n'est pas votre voiture !!! BACK OFF !!!\n");
			printf("Veuillez retirer la carte!!\n");
			attente_retrait_carte();
			printf("Catre retirée!!\n");	
			while(!carte_inseree() &&  numero != lecture_numero_carte())
			{
				printf("Attente du propriétaire de la voiture!!!");
			}
		}	
	
	*/
}

