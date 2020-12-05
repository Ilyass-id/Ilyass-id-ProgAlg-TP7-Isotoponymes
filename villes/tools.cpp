#include "tools.h"

//Construction du set

set<string> setTownNamesFonction(const vector<Town> townsExemple){
    set<string> setTownNames;
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)     //Ensemble des noms de villes
        setTownNames.insert((*it).name());
    return setTownNames;
}

unordered_map<string, int> constructorMapTowsNames(const vector<Town> townsExemple){
    unordered_map<string, int> unorderedMapTowsNames;
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)     //On initialise unorderedMapTowsNames avec des 0 pour tous les noms de ville
        unorderedMapTowsNames.insert(pair<string,int>((*it).name(),0));
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)
        unorderedMapTowsNames[(*it).name()]++;
    return unorderedMapTowsNames;
}



unordered_map<int, int> constructorMapHistName(unordered_map<string, int> unorderedMapTowsNames){
    unordered_map<int, int> unorderedMapHistName;
    for(unordered_map<string,int>::iterator it =unorderedMapTowsNames.begin(); it!=unorderedMapTowsNames.end(); ++it)
        unorderedMapHistName[it->second]++;
    return unorderedMapHistName;
}


void afficherHistogramme(unordered_map<int,int> histogramme){
    for(unordered_map<int,int>::iterator it =histogramme.begin(); it!=histogramme.end(); ++it) {
        cout<<it->first;
        for(int j = 0; j<histogramme[it->first]; j++){
            if (j%200==1) cout<<"-";
        }
        cout<<" "<<endl;
    }

    cout<<" "<<endl;
    cout<<"Commentaires de l'histogramme"<<endl;
    cout << "-----------------"<< endl;
    for(unordered_map<int,int>::iterator it =histogramme.begin(); it!=histogramme.end(); ++it) {
        cout<<"Il y a ";
        cout<<it->second;
        cout<<" noms de ville qui sont utilise par ";
        cout<<it->first;
        cout<<" villes dans notre echantillon "<<endl;
    }
    cout << "-----------------"<< endl;
    cout<<" "<<endl;
}


set<Point2D> setTownCoordFonction(const vector<Town> townsExemple){
    set<Point2D> setTownCoord;
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)     //Creation de l'ensemble muni des coordonnées
        setTownCoord.insert((*it).point());                                 //Dans Town.h on peut voir que point() retourne le Point2D (_x,_y);
    return setTownCoord;
}

map<Point2D, int> constructorMapTownsCoord(const vector<Town> townsExemple){
    map<Point2D, int> orderedMapTowsCoord;
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)     //On initialise unorderedMapTowsCoord avec des 0 pour toutes les coordonnees de ville
        orderedMapTowsCoord.insert(pair<Point2D,int>((*it).point(),0));
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++)     //On rempli chaque coordonnée avec son nombre d'apparition dans le vecteur
        orderedMapTowsCoord[(*it).point()]++;

    return orderedMapTowsCoord;
}

unordered_map<int, int> constructorMapHistCoord(map<Point2D, int> orderedMapTowsCoord){
    unordered_map<int, int> unorderedMapHistCoord;                          // Supposée mettre en lien (x: Utilisé par x villes , y: Nombre de coord villes)
    for(map<Point2D,int>::iterator it = orderedMapTowsCoord.begin(); it!= orderedMapTowsCoord.end(); ++it)
        unorderedMapHistCoord[it->second]++;
    return unorderedMapHistCoord;
}

set<Town> ensembleVillesMemeNom(unordered_map<string, int> unorderedMapTowsNames, const vector<Town> townsExemple){
    set<Town> N;
    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++){
        if(unorderedMapTowsNames[(*it).name()]>1)
            N.insert(*it);
    }
    return N;
}

set<Town> ensembleVillesMemeCoord(map<Point2D, int> orderedMapTowsCoord, const vector<Town> townsExemple){
    set<Town> C;

    for(auto it = townsExemple.begin(); it != townsExemple.end(); it++){
        if(orderedMapTowsCoord[(*it).point()]>1)
            C.insert(*it);
    }
    return C;
}


int nombreVillesTromper(const set<Town> intersection){
    int nombreDeFoisPossibleTromper = 0;

    //D'abord parcourir l'intersection i == v1
    for (auto it1 = intersection.begin(); it1 != intersection.end(); it1++){
        //Determinons la liste des voisins de it1
        set<Town> listeDesVoisinsDeIt1;
        set<Town> listeDesHomonymesDeIt1;
        for (auto it2 = intersection.begin(); it2 != intersection.end(); it2++){
            if (it1->point() == it2->point() && it1 != it2 ){   //Voisins
                listeDesVoisinsDeIt1.insert(*it2);
            }
            if (it1->name() == it2->name() && it1 != it2 ){     //Homonymes
                listeDesHomonymesDeIt1.insert(*it2);
            }
        }
        //D'autre part, determinons tous les voisins des homonymes
        for (auto it3 = listeDesHomonymesDeIt1.begin(); it3 != listeDesHomonymesDeIt1.end(); it3++){
            for (auto it4 = intersection.begin(); it4 != intersection.end(); it4++){
                if (it3->point() == it4->point() && it3 != it4 ){
                    for (auto it2 = listeDesVoisinsDeIt1.begin(); it2 != listeDesVoisinsDeIt1.end(); it2++){ //Sur les voisins de it3
                        if(it2->name() == it4->name() && it1 != it2){           //Si on trouve un homonyme de it2 (voisin de it1)
                            nombreDeFoisPossibleTromper++;                            //Alors on incremente le nombre de fois qu'on peut se tromper
                        }
                    }
                }
            }
        }
    }
    return nombreDeFoisPossibleTromper;
};
