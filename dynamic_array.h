#ifndef INC_3105_TP1_TABLEAU_H
#define INC_3105_TP1_TABLEAU_H

#include <cassert>
#include <iostream>


template<class T>
class Dynamic_array {
public:

    struct hachage {
        T valeur;
        int clef;
    };

    mutable struct hachage *hachage_array = nullptr;
    mutable struct hachage *hachage_tab_gauche = nullptr;
    mutable struct hachage *hachage_tab_droite = nullptr;

    // Constructeurs
    explicit Dynamic_array(int capacite_initiale = 8);

    Dynamic_array(const Dynamic_array<T> &);

    ~Dynamic_array();

// Fonctions de modifications
    void ajouter(const T &element); // à la fin
    void vider();

    void inserer(const T &element, int index = 0);

    void enlever(int index = 0);

    void enlever_dernier();

    void resize();

    void mergeSort(int min, int max) const;

    void merge(int min, int milieu, int max) const;

    int trouverOccurenceGauche(T element, int min, int max) const;

    int trouverOccurenceDroite(T element, int min, int max) const;

    //int trouverOccurenceMilieu(T element, int left, int right) const;

// Opérateurs d'accès []
    T &operator[](int index);

    const T &operator[](int index) const;

// Fonctions utilitaires
    bool vide() const { return nbElements == 0; }

    int taille() const { return nbElements; }

    int chercher(const T &element) const; // retourne indice première occurrence
    bool contient(const T &element) const;

    // Opérateurs
    Dynamic_array<T> &operator=(const Dynamic_array<T> &autre);

    bool operator==(const Dynamic_array<T> &autre) const;

    // Fonctionnalités spécifiques au TP1
    int compter(const T &element) const; // retourne le nb d'occurrences de element
    void creer_index() const; // cette fonction permet d'optimiser les fonctions     chercher, contient et compter.


private:
    T *elements;
    int nbElements;
    int capacite;
};


// ---------- Définitions -------------


template<class T>
Dynamic_array<T>::Dynamic_array(int capacite_) {
    this->capacite = capacite_;
    elements = new T[capacite_];
    nbElements = 0;
}

template<class T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array &autre) {
    capacite = autre.nbElements; // ou autre.capacite
    nbElements = autre.nbElements;
    elements = new T[capacite];
    for (int i = 0; i < nbElements; i++)
        elements[i] = autre.elements[i];
}

template<class T>
Dynamic_array<T>::~Dynamic_array() {
    delete [] elements;
    delete [] hachage_array;
    delete [] hachage_tab_gauche;
    delete [] hachage_tab_droite;
}

template<class T>
void Dynamic_array<T>::resize() {
    if (nbElements == capacite) {
        T *temp = new T[capacite * 2];
        for (int i = 0; i < capacite; i++)
            temp[i] = elements[i];
        delete[] elements;
        capacite *= 2;
        elements = temp;
    }
}

template<class T>
void Dynamic_array<T>::ajouter(const T &element) {
    resize();
    elements[nbElements] = element;
    nbElements++;
    delete [] hachage_array;
    delete [] hachage_tab_gauche;
    delete [] hachage_tab_droite;
}

template<class T>
void Dynamic_array<T>::inserer(const T &element, int index) {
    resize();
    for (int i = this->taille() - 1; i >= index; i--)
        elements[i + 1] = elements[i];
    elements[index] = element;
    nbElements++;
    delete [] hachage_array;
}

template<class T>
void Dynamic_array<T>::enlever(int index) {
    for (int i = index; i < nbElements; i++)
        elements[i] = elements[i + 1];
    nbElements--;
    delete [] hachage_array;
}

template<class T>
void Dynamic_array<T>::enlever_dernier() {
    if (capacite > 0)
        this->elements[taille() - 1] = 0;
    nbElements--;
}

template<class T>
int Dynamic_array<T>::chercher(const T &element) const {
    if (hachage_array == nullptr) {
        for (int i = 0; i <= taille() - 1; ++i) {
            if (this->elements[i] == element)
                return i;
        }
        return -1;
    } else {
        int min = 0;
        int max = taille() - 1;
        int res = -1;
        while (min <= max) {
            int milieu = (min + max) / 2;
            if (hachage_array[milieu].valeur < element)
                min = milieu + 1;
            else if (element < hachage_array[milieu].valeur)
                max = milieu - 1;
            else {
                res = milieu;
                max = milieu - 1;
            }
        }
        if (res != -1) {
            return hachage_array[res].clef;
        } else {
            hachage_array = nullptr;
            return chercher(element);
        }
    }
}

template<class T>
void Dynamic_array<T>::vider() {
    nbElements = 0;
}

template<class T>
const T &Dynamic_array<T>::operator[](int index) const {
    assert(index < nbElements);
    return elements[index];
}

template<class T>
T &Dynamic_array<T>::operator[](int index) {
    assert(index < nbElements);
    return elements[index];
}

template<class T>
Dynamic_array<T> &Dynamic_array<T>::operator=(const Dynamic_array<T> &autre) {
    if (this == &autre) return *this;//cas special lorsqu’on affecte un objet a lui−meme
    nbElements = autre.nbElements;
    if (capacite < autre.nbElements) {
        delete [] elements;
        capacite = autre.nbElements; //ou autre.capacite
        elements = new T[capacite];
    }
    for (int i = 0; i < nbElements; i++)
        elements[i] = autre.elements[i];
    return *this;
}

template<class T>
bool Dynamic_array<T>::operator==(const Dynamic_array<T> &autre) const {
    int a;
    (this->taille() < autre.taille() || this->taille() > autre.taille()) ? a = 1 : a = 0;
    for (int i = 0; i < this->taille() + a; i++) {
        if (this->elements[i] != autre.elements[i])
            return false;
    }
    return true;
}

template<class T>
bool Dynamic_array<T>::contient(const T &element) const {
    if (hachage_array == nullptr) {
        for (int i = 0; i < nbElements; i++)
            if (elements[i] == element)
                return true;
    } else {
        if (chercher(element) != -1)
            return true;
    }
    return false;
}

template<class T>
int Dynamic_array<T>::trouverOccurenceDroite(T element, int min, int max) const {
    if (min == max)
        return max;
    int milieu = min + (max - min) / 2;
    if (element < hachage_array[milieu].valeur)
        return trouverOccurenceDroite(element, min, milieu);
    else
        return trouverOccurenceDroite(element, milieu + 1, max);
}

template<class T>
int Dynamic_array<T>::trouverOccurenceGauche(T element, int min, int max) const {
    if (min == max)
        return max;
    int milieu = min + (max - min) / 2;
    if (element > hachage_array[milieu].valeur)
        return trouverOccurenceGauche(element, milieu + 1, max);
    else
        return trouverOccurenceGauche(element, min, milieu);
}

template<class T>
int Dynamic_array<T>::compter(const T &element) const {
    int compte = 0;
    int min = 0;
    int max = taille();
    if (hachage_array == nullptr) {
        for (int i = 0; i < taille(); ++i) {
            if (elements[i] == element)
                compte++;
        }
    } else {
        int occurenceDroite = trouverOccurenceDroite(element, min, max);
        if (occurenceDroite == 0)
            return compte;
        int occurenceGauche = trouverOccurenceGauche(element, min, occurenceDroite);
        compte = occurenceDroite - occurenceGauche;
        return compte;
    }
    return compte;
}

template<class T>
void Dynamic_array<T>::merge(int min, int milieu, int max) const {
    int taille_tab1 = milieu - min + 1;
    int taille_tab2 = max - milieu;

    for (int i = 0; i < taille_tab1; i++)
        hachage_tab_gauche[i] = hachage_array[min + i];
    for (int j = 0; j < taille_tab2; j++)
        hachage_tab_droite[j] = hachage_array[milieu + 1 + j];

    int compteur_gauche = 0;
    int compteur_droite = 0;
    int compteur_array = min;
    while (compteur_gauche < taille_tab1 && compteur_droite < taille_tab2) {
        if (hachage_tab_gauche[compteur_gauche].valeur <= hachage_tab_droite[compteur_droite].valeur) {
            hachage_array[compteur_array] = hachage_tab_gauche[compteur_gauche];
            compteur_gauche++;
        } else {
            hachage_array[compteur_array] = hachage_tab_droite[compteur_droite];
            compteur_droite++;
        }
        compteur_array++;
    }

    while (compteur_gauche < taille_tab1) {
        hachage_array[compteur_array] = hachage_tab_gauche[compteur_gauche];
        compteur_gauche++;
        compteur_array++;
    }

    while (compteur_droite < taille_tab2) {
        hachage_array[compteur_array] = hachage_tab_droite[compteur_droite];
        compteur_droite++;
        compteur_array++;
    }
}

template<class T>
void Dynamic_array<T>::mergeSort(int min, int max) const {
    if (min < max) {
        int milieu = min + (max - min) / 2;
        mergeSort(min, milieu);
        mergeSort(milieu + 1, max);
        merge(min, milieu, max);

    }
}

template<class T>
void Dynamic_array<T>::creer_index() const {
    hachage_array = new hachage[taille()]();

    for (int i = 0; i < nbElements; i++) {
        hachage_array[i].valeur = elements[i];
        hachage_array[i].clef = i;
    }
    if (taille() > 0) {
        int milieu = 0 + (taille()-1 - 0) / 2;
        int taille_tab1 = milieu - 0 + 1;
        int taille_tab2 = taille()-1 - milieu;
        hachage_tab_gauche = new hachage[taille_tab1]();
        hachage_tab_droite = new hachage[taille_tab2]();
        //quickSort(0, taille() - 1);
        mergeSort(0, taille() - 1);
//        for (int i = 0; i < this->taille(); i++)
//            printf("%d : %d\n", hachage_array[i].valeur, hachage_array[i].clef);
    } else
        hachage_array = nullptr;
}


#endif

