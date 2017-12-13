/* En-t�te du programme
====================================================================================================
Fichier: 		painter.h (TP3)
Auteur: 		Simon Lagac� et Olivier Lemay Dostie
Date cr�ation: 	11/28/2017
But: 			Classe qui reprente l'interface ou l'on va pouvoir dessiner et cliquer sur les
differents boutons
====================================================================================================
*/
#include "../cursor.h"
#include "buttonStrip.h"
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
	int _sWidth = 1200;			//Largeur de l'ecran
	/// Utiliser un Vector2i au lieu des deux valeurs de dimmenssions?
	RenderWindow _window;		//Fen�tre d'affichage
	list<shape> listShape;		//Liste des formes qui represente un dessin
	list<shape>::iterator iteratorShape;	//Iterateur pour la liste de forme
	shape *selectShape;			//Shape qui est selectionn�e
	cursor _cursorInterface;	//Curseur de l'interface 

	list<buttonStripH*> _bsH;	// 	Banni�res de boutons d'ordre horizontal.
	//list<buttonStripV*> _bsV;	/// Banni�res de boutons d'ordre vertical.
	buttonStrip * _bs;			// Banni�re active.

public:
	painter();					// Constructeur sans parametre
	void init();				// Initialise l'interface
	//void show();				// Affiche l'interface ///inutile ?
	void run();					// Boucle principale
	void clear();				// Nettoie l'interface
	void drawListShape();		// Dessine les formes de la liste
	void drawButtonstrips();	// Dessine toutes les banni�res et leur boutons.
	shape* selectedShape(Vector2f v); //Retourne la shape si elle est selectionn�e

	// Ajoute une banni�re horizontale � l'interface.
	void addBsH(bool normalScope = true, bool normalInterval = true,
		Vector2f initPos = Vector2f(), Vector2f limitPos = Vector2f(),
		bool fixed = false, Vector2f minDim = Vector2f(1, 1));
	// Ajoute un bouton dans la banni�re active.
	void addButton(oButton b);
	bool isOnAZone();
	buttonStrip * isOnZone();
	oButton * isOnButton();


};


