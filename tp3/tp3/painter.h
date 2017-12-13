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
#include <list>
using namespace sf;
using namespace std;

#pragma once
class painter
{
private:
	int _sHeight = 800;			//Hauteur de l'ecran
	int _sWeight = 1200;			//Largeur de l'ecran
	RenderWindow _window;		//Fenêtre d'affichage
	list<shape> listShape;		//Liste des formes qui represente un dessin
	list<shape>::iterator iteratorShape;	//Iterateur pour la liste de forme
	shape *selectShape;		//Shape qui est selectionne
	cursor _cursorInterface;		//Curseur de l'interface 

public:
	painter();	//Constructeur sans parametre
	void init();	//Initialise l'interface
	//void show();	//Affiche l'interface ///inutile ?
	void run();		//Boucle qui va faire 
	void clear();	//Nettoie l'interface
	void drawListShape(); //Dessine les formes de la liste
	shape* selectedShape(Vector2f v); //Retourne la shape si elle est selectionne

};


