#include <iostream>
#include "donnees_borne.cpp"
#include <unistd.h>

using namespace std;
class Generateur_Save{
private:
    entrees *io;
    int shmid;
	PriseTrappe prise_trappe;
	BaseClients base_clients;
	Voyant_Bouton voyant_bouton;
public:
    void generateur_save_initialiser()
    {
    	io=acces_memoire(&shmid); 
    	/* associe la zone de memoire partageeau pointeur */
    	if (io==NULL) 
    		cout<<"Erreur pas de mem sh\n";
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
    		cout<<"Veuillez brancher la prise!!!\n";
    		sleep(1);
    	}
    
    	prise_trappe.prise_trappe_setPrise(VERT);
    	prise_trappe.prise_trappe_verrouiller();
    	generateur_save_generer(AC_1K);
    	sleep(1);
    	generateur_save_fermerAC();
    	generateur_save_generer(AC_CL);
    	while(io->gene_u == 6)
    	{
    		cout<<"Chargement en cours\n";

    		//chargementBatterie();						
    
    		if(carte_inseree() && numero == lecture_numero_carte())
    		{
    			cout<<"Catre inserée!!\n";
    
    			for(i = 0; i < 3 && code != baseClients[numero] ; i++)
    			{
    				cout<<"Entrer le code : ";
    				cin>>code;
    				if(base_clients.base_clients_authentifier(lecture_numero_carte(), code))
    				{
    					cout<<"Code Bon!!\n";
    					cout<<"Veuillez retirer la carte!!\n";
    					attente_retrait_carte();
    					cout<<"Catre retirée!!\n";
    					proprietaire = 1;
    
    				}
    			}
    				if(i == 3)
    				{
    					voyant_bouton.voyant_bouton_clignoteDefault(ROUGE);
    					cout<<"Veuillez retirer la carte!!\n";
    					attente_retrait_carte();
    					cout<<"Catre retirée!!\n";
    					base_clients.base_clients_supprimer(numero);
    					
    				}
    		}
    		else if(carte_inseree() && numero == numeroBloquer)
    		cout<<"CARTE BLOQUEE\n";

    		else if(carte_inseree() && numero != lecture_numero_carte())
    		{
    			cout<<"Ce n'est pas votre voiture !!! BACK OFF !!!\n";
    			cout<<"Veuillez retirer la carte!!\n";
    			attente_retrait_carte();
    			cout<<"Catre retirée!!\n";	
    			while(voitureRetiree == 0)
    			{
    				cout<<"Attente du propriétaire de la voiture!!!\n";
    				if(carte_inseree() && numero != numeroBloquer && numero == lecture_numero_carte())
    				{
    					cout<<"Catre inserée!!\n";
    
    					cout<<"numero de la carte = %i\n", numero;
    
    					for(i = 0; i < 3; i++)
    					{
    						cout<<"Entrer le code : ";
    						cin>>code;
    						if( base_clients.base_clients_authentifier(numero, code))
    						{
    							cout<<"Code Bon!!\n";
    							cout<<"Veuillez retirer la carte!!\n";
    							attente_retrait_carte();
    							cout<<"Catre retirée!!\n";
    							voitureRetiree = 1;
    							if(io->gene_u == 9)
    							{
    								prise_trappe.prise_trappe_deverrouiller();	
    								cout<<"Veuillez débranchez le prise !!\n";
    								while(io->gene_u != 12){usleep(1);}
    								cout<<"Prise débranchée!!\n";
    								prise_trappe.prise_trappe_verrouiller();
    								prise_trappe.prise_trappe_setPrise(OFF);
    				 				voyant_bouton.setCharge(OFF);
    								voyant_bouton.setDispo(VERT);
    								voitureRetiree = 1;
    							}
    							break;
    						}
    					}
    					if(i == 3)
    					{
    						voyant_bouton.voyant_bouton_clignoteDefault(ROUGE);
    						cout<<"Veuillez retirer la carte!!\n";
    						attente_retrait_carte();
    						cout<<"Catre retirée!!\n";
    						base_clients.base_clients_supprimer(numero);
    					}
    				}
    
    			}	
    
    
    		}	
    

    		if(voyant_bouton.getBouttonStop() && proprietaire)
    		{
    			generateur_save_ouvrirAC();
    			generateur_save_generer(DC);
    			cout<<"*****************************CHARGEMENT ARRETE!!*******************************\n";
    			prise_trappe.prise_trappe_deverrouiller();	
    			cout<<"Veuillez débranchez le prise !!\n";
    			while(io->gene_u != 12){usleep(1);}
    			cout<<"Prise débranchée!!\n";
    			prise_trappe.prise_trappe_verrouiller();
    			prise_trappe.prise_trappe_setPrise(OFF);
    		 	voyant_bouton.setCharge(OFF);
    			voyant_bouton.setDispo(VERT);	
    		}
    	}
    	//printf("gene_u = %i\n",io->gene_u);
    	if(io->gene_u == 9)
    	{
    		generateur_save_ouvrirAC();
    		generateur_save_generer(DC);
    		voyant_bouton.setCharge(VERT);
    		cout<<"*****************************CHARGEMENT TERMINE!!*******************************\n";
    		cout<<"Veuillez vous authentifiez pour reprendre véhicule!!\n";					
    		cout<<"Veuillez inserée catre!!\n";	
    		attente_insertion_carte();
    		int code, i;
    		if(carte_inseree() && numero == lecture_numero_carte())
    		{
    			cout<<"Catre inserée!!\n";
    
    			for(i = 0; i < 3; i++)
    			{
    				cout<<"Entrer le code : ";
    				cin>>code;
    				if( base_clients.base_clients_authentifier(lecture_numero_carte(), code))
    				{
    					cout<<"Code Bon!!\n";
    					cout<<"Veuillez retirer la carte!!\n";
    					attente_retrait_carte();
    					cout<<"Catre retirée!!\n";
    					prise_trappe.prise_trappe_deverrouiller();	
    					cout<<"Veuillez débranchez le prise !!\n";
    					while(io->gene_u != 12){usleep(1);}
    					cout<<"Prise débranchée!!\n";
    					prise_trappe.prise_trappe_verrouiller();
    					prise_trappe.prise_trappe_setPrise(OFF);
    	 				voyant_bouton.setCharge(OFF);
    					voyant_bouton.setDispo(VERT);
    					break;
    				}
    			}
    				if(i == 3){
                        voyant_bouton.voyant_bouton_clignoteDefault(ROUGE);
    					cout<<"Veuillez retirer la carte!!\n";
    					attente_retrait_carte();
    					cout<<"Catre retirée!!\n";
    					base_clients.base_clients_supprimer(numero);
                    }
    					
    					
    		}
    		else if(carte_inseree() && numero == numeroBloquer)
    			cout<<"CARTE BLOQUEE\n";

    
    		else if(carte_inseree() && numero != lecture_numero_carte())
    		{
    			cout<<"Ce n'est pas votre voiture !!! BACK OFF !!!\n";
    			cout<<"Veuillez retirer la carte!!\n";
    			attente_retrait_carte();
    			cout<<"Catre retirée!!\n";	
    			while( voitureRetiree == 0)
    			{
    				cout<<"Attente du propriétaire de la voiture!!!\n";
    				if(carte_inseree() && numero != numeroBloquer && numero == lecture_numero_carte())
    				{
    					cout<<"Catre inserée!!\n";
    
    					cout<<"numero de la carte = %i\n", numero;
    
    					for(i = 0; i < 3; i++)
    					{
    						cout<<"Entrer le code : ";
    						cin>>code;
    						if( base_clients.base_clients_authentifier(numero, code))
    						{
    							cout<<"Code Bon!!\n";
    							cout<<"Veuillez retirer la carte!!\n";
    							attente_retrait_carte();
    							cout<<"Catre retirée!!\n";
    							if(io->gene_u == 9)
    							{
    								prise_trappe.prise_trappe_deverrouiller();	
    								cout<<"Veuillez débranchez le prise !!\n";
    								while(io->gene_u != 12){usleep(1);}
    								cout<<"Prise débranchée!!\n";
    								prise_trappe.prise_trappe_verrouiller();
    								prise_trappe.prise_trappe_setPrise(OFF);
    				 				voyant_bouton.setCharge(OFF);
    								voyant_bouton.setDispo(VERT);
    								voitureRetiree = 1;
    
    							}
    							break;
    						}
    					}
    					if(i == 3)
    					{
    						voyant_bouton.voyant_bouton_clignoteDefault(ROUGE);
    						cout<<"Veuillez retirer la carte!!\n";
    						attente_retrait_carte();
    						cout<<"Catre retirée!!\n";
    						base_clients.base_clients_supprimer(numero);
    
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

};