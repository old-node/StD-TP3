/* En-tête du programme
====================================================================================================
Fichier: 		painter.h (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Classe qui reprente l'interface ou l'on va pouvoir dessiner et cliquer sur les
differents boutons
====================================================================================================
*/
#include "../cursor.h"
#include "../oButton.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#pragma once
class painter
{
private:
	int sHeight = 800;			//Hauteur de l'ecran
	int sWeight = 1200;			//Largeur de l'ecran
	RenderWindow window;		//Fenêtre d'affichage
	//cursor cursorInterface;	//Curseur de l'interface ///Constructeur a changer

public:
	painter();	//Constructeur sans parametre
	void init();	//Initialise l'interface
	//void show();	//Affiche l'interface ///inutile ?
	void run();		//Boucle qui va faire 
	void clear();	//Nettoie l'interface

};


