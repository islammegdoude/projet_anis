#include <iostream>

#include "donnees_borne.cpp"

using namespace std;
class Voyant_Bouton{
private:
    entrees *io;
    int shmid;
public:

    void voyant_bouton_initialiser()
    {
    	io=acces_memoire(&shmid); 
    	/* associe la zone de memoire partageeau pointeur */
    	if (io == NULL) 
            cout<<"Erreur pas de mem sh\n";
    }
    
    void voyant_bouton_clignoteDefault(led couleur)
    {
    	int i;
    
    	for(i = 0; i < 4; i++)
    	{	
    		io->led_defaut=couleur;
    		sleep(1);
    		io->led_defaut=OFF;
    		sleep(1);
    	}
    
    }
    
    void voyant_bouton_clignoteCharge(led couleur)
    {
    	int i;
    
    	for(i = 0; i < 4; i++)
    	{	
    		io->led_charge=couleur;
    		sleep(1);
    		io->led_charge=OFF;
    		sleep(1);
    	}
    }
    
    int getBouttonCharge()
    {
    	io->bouton_charge = 0;
    	while(io->bouton_charge == 0)
    		usleep(5000);
    	io->bouton_charge = 0;
    	return 1;
    }
    
    void setDispo(led couleur)
    {
    	io->led_dispo=couleur;
    }
    
    void setCharge(led couleur)
    {
    	io->led_charge=couleur;
    }
    
    int getBouttonStop()
    {
    	io->bouton_stop = 0;
    		sleep(1);
    	return io->bouton_stop;
    
    }
    
};