#include <unistd.h>
#include "prise_trappe.h"


entrees *io;
int shmid;

void prise_trappe_initialiser()
{
	io=acces_memoire(&shmid); 
	/* associe la zone de memoire partageeau pointeur */
	if (io==NULL) 
		printf("Erreur pas de mem sh\n");
}

void prise_trappe_deverrouiller()
{	
	io->led_trappe=VERT;
}

void prise_trappe_verrouiller()
{
	io->led_trappe=OFF;	
}

void prise_trappe_setPrise(led couleur)
{
	io->led_prise=couleur;
}
