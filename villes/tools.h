#pragma once

#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>

#include "town.h"

//Construit l'ensemble des noms de villes
set<string> setTownNamesFonction(const vector<Town> townsExemple);
//Construit la map qui donne le nombre d'occurence par nom de ville
unordered_map<string, int> constructorMapTowsNames(const vector<Town> townsExemple);
//Construit l'histogramme de nombre de villes par nombre d'occurence
unordered_map<int, int> constructorMapHistName(unordered_map<string, int> unorderedMapTowsNames);
//Affiche l'histogramme
void afficherHistogramme(unordered_map<int,int> histogramme);

//Construit l'ensemble des Coordonnees de villes
set<Point2D> setTownCoordFonction(const vector<Town> townsExemple);
//Construit la map qui donne le nombre d'occurence par nom de ville
map<Point2D, int> constructorMapTownsCoord(const vector<Town> townsExemple);
//Construit l'histogramme de nombre de villes par nombre d'occurence
unordered_map<int, int> constructorMapHistCoord(map<Point2D, int> orderedMapTowsCoord);

//Construit l'ensemble de Villes de meme nom
set<Town> ensembleVillesMemeNom(unordered_map<string, int> unorderedMapTowsNames, const vector<Town> townsExemple);
//Construit l'ensemble de Villes de meme coordonnees
set<Town> ensembleVillesMemeCoord(map<Point2D, int> orderedMapTowsCoord, const vector<Town> townsExemple);

//Question 4 - Retourne le nombre de fois où on peut se tromper en parlant d'isotoponymes.
int nombreVillesTromper(const set<Town> intersection);
