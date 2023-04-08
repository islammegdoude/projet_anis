#include <unistd.h>
#include "donnees_borne.cpp"
#include <iostream>



class PriseTrappe {
    private:
        entrees *io;
        int shmid;

    public:
        PriseTrappe() {
            io = acces_memoire(&shmid); 
            if (io == nullptr) {
                std::cerr << "Erreur pas de mem sh\n";
            }
        }

        void prise_trappe_deverrouiller() {	
            io->led_trappe = led::VERT;
        }

        void prise_trappe_verrouiller() {
            io->led_trappe = led::OFF;	
        }

        void prise_trappe_setPrise(led couleur) {
            io->led_prise = couleur;
        }
};
