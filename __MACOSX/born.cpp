#include "donnees_borne.cpp"
#include "voyant_bouton.cpp"
#include "timer.cpp"
#include "lecteurcarte.cpp"
#include "generateur_save.cpp"
#include "base_clients.cpp"
using namespace std;
class Borne{
private:
	Timer time;
	CardReader lecteur_carte;
    Generateur_Save generateur_Save;
	BaseClients base_clients;
	Voyant_Bouton voyant_bouton;
	PriseTrappe prise_trappe;
public:
	Borne(){
		lecteur_carte.lecteur_carte_initialiser();
		lecteur_carte.lecteurcarte_initialiser();
		base_clients.base_clients_initialiser();
		time.timer_initialiser();
		voyant_bouton.voyant_bouton_initialiser();
		generateur_Save.generateur_save_initialiser();
		
	
    	while (1)
    	{
    		lecteur_carte.lecteurcarte_lire_carte();
    	}
	}	
		

};
