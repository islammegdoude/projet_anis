#include <unistd.h>
#include <stdio.h>

#include "voyant_bouton.cpp"
#include "timer.cpp"
#include "base_clients.cpp"
#include "donnees_borne.cpp"
#include "prise_trappe.cpp"
class CardReader {
private:
    entrees *io;
    int shmid;
    unsigned short int numero;
    Timer time ;
    Voyant_Bouton voyant;
    PriseTrappe prise_trappe;
    Generateur_Save generateur_Save;
    BaseClients base_clients ;

public:
    void lecteur_carte_initialiser() {
        io = acces_memoire(&shmid);
        if (io == NULL)
            std::cout << "Erreur pas de mem sh\n";
    }

    void lecteurcarte_initialiser() {
        initialisations_ports();
    }

    void lecteurcarte_lire_carte() {
        int i;
        int code;
        std::cout << "Veuillez inserée catre!!\n";
        attente_insertion_carte();
        numero = lecture_numero_carte();
        base_clients.base_clients_ajouter(13, 1234);
        base_clients.base_clients_ajouter(31, 4321);
        if (carte_inseree() && numero != numeroBloquer && numero == lecture_numero_carte()) {
            std::cout << "Catre inserée!!\n";
            std::cout << "numero de la carte = " << numero << "\n";
            for (i = 0; i < 3; i++) {
                std::cout << "Entrer le code : ";
                std::cin >> code;
                if (base_clients.base_clients_authentifier(numero, code)) {
                    std::cout << "Code Bon!!\n";
                    std::cout << "Veuillez retirer la carte!!\n";
                    attente_retrait_carte();
                    std::cout << "Catre retirée!!\n";
                    break;
                }
            }
            if (i == 3) {
                voyant.voyant_bouton_clignoteDefault(ROUGE);
                std::cout << "Veuillez retirer la carte!!\n";
                attente_retrait_carte();
                std::cout << "Catre retirée!!\n";
                base_clients.base_clients_supprimer(numero);
            }

            time.timer_raz();
            voyant.voyant_bouton_clignoteCharge(VERT);

            if (voyant.getBouttonCharge())
                if (time.timer_valeur() <= 60) {
                    voyant.setDispo(OFF);
                    voyant.setCharge(ROUGE);
                    prise_trappe.prise_trappe_deverrouiller();
                    generateur_Save.generateur_save_generer(DC);
                    generateur_Save.generateur_save_charger();
                }

        } else if (carte_inseree() && numero == numeroBloquer)
            std::cout << "CARTE BLOQUEE\n";
    }


};
