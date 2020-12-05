#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "town.h"
#include "tools.h"

using namespace std;

#ifndef srcPath
#define srcPath "."
#endif
// The path and name of the town file
const string townFile = srcPath "/villes.txt";



// Study French isotoponyms
int main() {
    vector<Town> towns;
    // Read file
    cout << "Reading town file: " << townFile << endl;
    clock_t time1 = clock();
    int nb_towns = Town::read_file(townFile, towns);
    clock_t time2 = clock();
    // Sanity check
    if (nb_towns < 0) {
        cout << "Error while reading file" << endl;
        return 2;
    }
    if (nb_towns == 0) {
        cout << "No town found" << endl;
        return 1;
    }

    //////////////////////////////////////////
    /// Ilyass RAMDANI
    ///
    ///
    cout<<"########### Histogramme des repetitions de noms de villes  ###########"<<endl;
    cout << "construction de notre set :";
    vector<Town> townsExemple(towns.begin(), towns.end());
    set<string> setTownNames;
    setTownNames = setTownNamesFonction(townsExemple);
    cout<<" 100%"<<endl;

    cout << "construction de notre map et verifications par rapport aux donnees dans le txt:"<<endl;
    unordered_map<string, int> unorderedMapTowsNames;
    unorderedMapTowsNames = constructorMapTowsNames(townsExemple);  //Incremente le nombre d'apparition par nom de ville

    cout<<"Il y a bien "<<unorderedMapTowsNames.at("Abancourt")<<" Abancourt dans le fichier txt"<<endl;
    cout<<"Il y a bien "<<unorderedMapTowsNames.at("Abaucourt")<<" Abaucourt dans le fichier txt"<<endl;
    cout << "-----------------"<< endl;
    cout<<" "<<endl;

    cout << "Verification de notre histogramme de noms:"<<endl;
    cout<<" "<<endl;
    unordered_map<int, int> unorderedMapHistName;                                 // Supposée mettre en lien (x: Utilisé par x villes , y: Nombre de noms villes)
    unorderedMapHistName = constructorMapHistName(unorderedMapTowsNames);
    cout<<" "<<endl;

    cout << "Affichage de l'histogramme :"<<endl;
    cout<<" "<<endl;

    afficherHistogramme(unorderedMapHistName);

    cout<<"########### Histogramme des villes de meme coordonnees  ###########"<<endl;

    cout << "Construction de notre ensemble :";

    set<Point2D> setTownCoord;
    setTownCoord = setTownCoordFonction(townsExemple);

    cout<<" 100%"<<endl;
    cout << "Construction de notre map :";

    map<Point2D, int> orderedMapTowsCoord;
    orderedMapTowsCoord = constructorMapTownsCoord(townsExemple);

    unordered_map<int, int> unorderedMapHistCoord;                          // Supposée mettre en lien (x: Utilisé par x villes , y: Nombre de coord villes)
    unorderedMapHistCoord = constructorMapHistCoord(orderedMapTowsCoord);
    cout<<" 100%"<<endl;

    cout << "-----------------"<< endl;
    cout<<" "<<endl;

    cout << "Affichage de l'histogramme :"<<endl;
    cout<<" "<<endl;
    afficherHistogramme(unorderedMapHistCoord);
    cout<<" "<<endl;

    cout<<"########### Intersection de N et C  ###########"<<endl;

    cout << "L'ensemble N des villes qui ont une autre ville de meme nom :";
    set<Town> N;
    N= ensembleVillesMemeNom(unorderedMapTowsNames, townsExemple);
    cout<<" 100%"<<endl;

    cout << "L'ensemble C des villes qui ont une autre ville de meme coordonnées : il y en a ";
    set<Town> C;
    C= ensembleVillesMemeCoord(orderedMapTowsCoord, townsExemple);
    cout<<" 100%"<<endl;

    cout << "L'ensemble des villes qui sont dans l'intersection de N et C sont au nombre de : ";
    set<Town> intersection;
    set_intersection(N.begin(), N.end(), C.begin(), C.end(), insert_iterator<set<Town>>(intersection, intersection.begin()));

    cout<<intersection.size()<<endl;
    cout << "-----------------"<< endl;
    cout<<" "<<endl;

    cout<<"###########  Pour combien de villes on peut se tromper en entendant parler d'une ville A toute proche d'une ville B  ###########"<<endl;

    cout<<"###########  Verifions d'abord que notre fonction est fonctionnelle avec une approche naive  ###########"<<endl;
    cout << "Dans le cas du test il devrait y en avoir 4 et Il y en a ";

    set<Town> setTestTromper;
    Town v1("A", 1, 1);
    Town v2("B", 1, 1);
    Town v3("A", 2, 2);
    Town v4("B", 2, 2);

    setTestTromper.insert(Town("A", 1, 1));
    setTestTromper.insert(Town("B", 1, 1));
    setTestTromper.insert(Town("A", 2, 2));
    setTestTromper.insert(Town("B", 2, 2));

    cout<<nombreVillesTromper(setTestTromper)<<endl;
    cout<<" "<<endl;
    cout << "-----------------"<< endl;

    cout << "Regardons maintenant dans l'intersection N et C pour combien de villes on peut se tromper : Il y en a ";

    cout<<nombreVillesTromper(intersection)<<endl;



    cout << "-----------------"<< endl;
    cout<<" "<<endl;

    //////////////////////////////////////
    ///
    ///

    srand(time(NULL));
    // Say how many towns have been read
    cout << "File read in: "
         << ((float)(time2-time1)/CLOCKS_PER_SEC) << " s" << endl;
    cout << "Number of towns in file: "
         << towns.size() /* same as nb_towns */ << endl;
    cout << "A random town, using format \"name[lat,lon](x,y)\": "
         << towns[rand() % towns.size()] << endl;

    // That's all folks
    return 0;
}
