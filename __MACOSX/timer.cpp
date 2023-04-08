#include <iostream>
#include "donnees_borne.cpp"

using namespace std;
class Timer{
private:
    entrees *io;
    int shmid;
    int depart_timer;
public:
    timer_initialiser() {
        io = acces_memoire(&shmid); 
        /* associe la zone de memoire partageeau pointeur */
        if (io == NULL) 
            cout<<"Erreur pas de mem sh\n";
    }

    void timer_raz() {	
        depart_timer = io->timer_sec;
    }

    int timer_valeur() {
        return io->timer_sec - depart_timer;	
    }
};
