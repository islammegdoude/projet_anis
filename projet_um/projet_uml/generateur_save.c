#include <unistd.h>
#include "generateur_save.h"
#include "prise_trappe.h"
#include "voyant_bouton.h"
#include "lecteurcarte.h"
#include "base_clients.h"


entrees *io;
int shmid;

void generateur_save_initialiser()
{
	io=acces_memoire(&shmid); 
	/* associe la zone de memoire partageeau pointeur */
	if (io==NULL) 
		printf("Erreur pas de mem sh\n");
}

void generateur_save_generer(pwm courant)
{
	io->gene_pwm=courant;
}

void generateur_save_charger()
{
	int voitureRetiree = 0;
	
	int code = 0;
	int i;
	int proprietaire = 0;
	while(io->gene_u != 9)
	{
		printf("Veuillez brancher la prise!!!\n");
		sleep(1);
	}
	
	prise_trappe_setPrise(VERT);
	prise_trappe_verrouiller();
	generateur_save_generer(AC_1K);
	sleep(1);
	generateur_save_fermerAC();
	generateur_save_generer(AC_CL);
	while(io->gene_u == 6)
	{
		printf("Chargement en cours\n");

		//chargementBatterie();						
		
		if(carte_inseree() && numero == lecture_numero_carte())
		{
			printf("Catre inserée!!\n");
		
			for(i = 0; i < 3 && code != baseClients[numero] ; i++)
			{
				printf("Entrer le code : ");
				scanf("%i", &code);
				if(base_clients_authentifier(lecture_numero_carte(), code))
				{
					printf("Code Bon!!\n");
					printf("Veuillez retirer la carte!!\n");
					attente_retrait_carte();
					printf("Catre retirée!!\n");
					proprietaire = 1;
					
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
		}
		else if(carte_inseree() && numero == numeroBloquer)
		printf("CARTE BLOQUEE\n");

		else if(carte_inseree() && numero != lecture_numero_carte())
		{
			printf("Ce n'est pas votre voiture !!! BACK OFF !!!\n");
			printf("Veuillez retirer la carte!!\n");
			attente_retrait_carte();
			printf("Catre retirée!!\n");	
			while(voitureRetiree == 0)
			{
				printf("Attente du propriétaire de la voiture!!!\n");
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
							voitureRetiree = 1;
							if(io->gene_u == 9)
							{
								prise_trappe_deverrouiller();	
								printf("Veuillez débranchez le prise !!\n");
								while(io->gene_u != 12){usleep(1);}
								printf("Prise débranchée!!\n");
								prise_trappe_verrouiller();
								prise_trappe_setPrise(OFF);
				 				setCharge(OFF);
								setDispo(VERT);
								voitureRetiree = 1;
							}
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
				}
						
			}	
				
				
		}	
	

		if(getBouttonStop() && proprietaire)
		{
			generateur_save_ouvrirAC();
			generateur_save_generer(DC);
			printf("*****************************CHARGEMENT ARRETE!!*******************************\n");
			prise_trappe_deverrouiller();	
			printf("Veuillez débranchez le prise !!\n");
			while(io->gene_u != 12){usleep(1);}
			printf("Prise débranchée!!\n");
			prise_trappe_verrouiller();
			prise_trappe_setPrise(OFF);
		 	setCharge(OFF);
			setDispo(VERT);	
		}
	}
	//printf("gene_u = %i\n",io->gene_u);
	if(io->gene_u == 9)
	{
		generateur_save_ouvrirAC();
		generateur_save_generer(DC);
		setCharge(VERT);
		printf("*****************************CHARGEMENT TERMINE!!*******************************\n");
		printf("Veuillez vous authentifiez pour reprendre véhicule!!\n");					
		printf("Veuillez inserée catre!!\n");	
		attente_insertion_carte();
		int code, i;
		if(carte_inseree() && numero == lecture_numero_carte())
		{
			printf("Catre inserée!!\n");
		
			for(i = 0; i < 3; i++)
			{
				printf("Entrer le code : ");
				scanf("%i", &code);
				if( base_clients_authentifier(lecture_numero_carte(), code))
				{
					printf("Code Bon!!\n");
					printf("Veuillez retirer la carte!!\n");
					attente_retrait_carte();
					printf("Catre retirée!!\n");
					prise_trappe_deverrouiller();	
					printf("Veuillez débranchez le prise !!\n");
					while(io->gene_u != 12){usleep(1);}
					printf("Prise débranchée!!\n");
					prise_trappe_verrouiller();
					prise_trappe_setPrise(OFF);
	 				setCharge(OFF);
					setDispo(VERT);
					break;
				}
			}
				if(i == 3)
					voyant_bouton_clignoteDefault(ROUGE);
					printf("Veuillez retirer la carte!!\n");
					attente_retrait_carte();
					printf("Catre retirée!!\n");
					base_clients_supprimer(numero);
					return 0;
		}
		else if(carte_inseree() && numero == numeroBloquer)
			printf("CARTE BLOQUEE\n");

		
		else if(carte_inseree() && numero != lecture_numero_carte())
		{
			printf("Ce n'est pas votre voiture !!! BACK OFF !!!\n");
			printf("Veuillez retirer la carte!!\n");
			attente_retrait_carte();
			printf("Catre retirée!!\n");	
			while( voitureRetiree == 0)
			{
				printf("Attente du propriétaire de la voiture!!!\n");
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
							if(io->gene_u == 9)
							{
								prise_trappe_deverrouiller();	
								printf("Veuillez débranchez le prise !!\n");
								while(io->gene_u != 12){usleep(1);}
								printf("Prise débranchée!!\n");
								prise_trappe_verrouiller();
								prise_trappe_setPrise(OFF);
				 				setCharge(OFF);
								setDispo(VERT);
								voitureRetiree = 1;
								
							}
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
				}
						
			}	
				
				
		}	
}	
	
}

void generateur_save_fermerAC()
{
	io->contacteur_AC=1;
}

void generateur_save_ouvrirAC()
{
	io->contacteur_AC=0;
}
