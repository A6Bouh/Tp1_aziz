#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Classe orientée objet
class GestionFichier {
private:
    vector<string> mots;

    // Fonction d'aide pour la recherche récursive
    bool RechercheRecursiveHelper(const string& motCherche, int gauche, int droite) const {
        if (gauche > droite) return false;

        int milieu = gauche + (droite - gauche) / 2;

        if (mots[milieu] == motCherche) return true;
        else if (mots[milieu] > motCherche)
            return RechercheRecursiveHelper(motCherche, gauche, milieu - 1);
        else
            return RechercheRecursiveHelper(motCherche, milieu + 1, droite);
    }

public:
    // Charger les mots depuis un fichier
    bool ChargerDepuisFichier(const string& nomFichier) {
        ifstream fichier(nomFichier);
        if (!fichier) {
            cout << " Erreur : fichier introuvable !" << endl;
            return false;
        }

        mots.clear(); // vide l’ancien contenu
        string mot;
        while (fichier >> mot) {
            mots.push_back(mot);
        }
        fichier.close();
        return true;
    }

    // Trier les mots
    void Trier() {
        sort(mots.begin(), mots.end());
    }

    // Afficher les mots triés
    void Afficher() const {
        cout << "   Mots tries :" << endl;
        for (const string& mot : mots) {
            cout << mot << endl;
        }
    }

    // Sauvegarder dans un fichier
    bool Sauvegarder(const string& nomFichier) const {
        ofstream fichier(nomFichier);
        if (!fichier) {
            cout << " Erreur : Impossible de creer le fichier trie !" << endl;
            return false;
        }

        for (const string& mot : mots) {
            fichier << mot << endl;
        }

        fichier.close();
        return true;
    }

    // Recherche récursive
    bool RechercheRecursive(const string& motCherche) const {
        return RechercheRecursiveHelper(motCherche, 0, mots.size() - 1);
    }
};

int main() {
    GestionFichier gestion;

    // Charger les mots
    if (!gestion.ChargerDepuisFichier("mots.txt")) {
        return 1;
    }

    // Trier et afficher
    gestion.Trier();
    gestion.Afficher();

    // Sauvegarder les mots triés
    if (gestion.Sauvegarder("mots_Trie.txt")) {
        cout << " Fichier trie sauvegarde sous 'mots_Trie.txt'" << endl;
    }

    // Recherche d’un mot
    string motCherche;
    cout << " Entrez un mot à rechercher : ";
    cin >> motCherche;

    if (gestion.RechercheRecursive(motCherche)) {
        cout << " Le mot '" << motCherche << "' est present dans le fichier !" << endl;
    }
    else {
        cout << " Le mot '" << motCherche << "' n'est PAS present." << endl;
    }

    return 0;
}
