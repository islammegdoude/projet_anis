#include <unistd.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <time.h>

using namespace std;

class BaseClients {
private:
    vector<int> baseClients;
    int numeroBloquer;

public:
    void base_clients_initialiser() {
        for (int i = 0; i < 100; i++)
            baseClients.push_back(0);
        numeroBloquer = 0;
    }

    void base_clients_ajouter(int numero, int code) {
        baseClients[numero] = code;
    }

    bool base_clients_authentifier(int numero, int code) {
        return (baseClients[numero] == code);
    }

    void base_clients_supprimer(int numero) {
        numeroBloquer = numero;
    }
};
