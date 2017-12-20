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
#include "sqlStructs.h"
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
	float _sHeight = 800;			// Hauteur de l'ecran
	float _sWidth = 1200;			// Largeur de l'ecran
	/// Utiliser un Vector2i au lieu des deux valeurs de dimmenssions?
	RenderWindow _window;		// Fen�tre d'affichage
	list<shape> _listShape;		// Liste des formes qui represente un dessin
	list<shape>::iterator _iteratorShape;	// It�rateur pour la liste de forme
	shape *_selectShape;		// Shape qui est selectionn�e
	cursor _cursorInterface;	// Curseur de l'interface
	
	Text _label;				// Message en bas de l'�cran.
	list<buttonStripH*> _bsH;	//	Banni�res de boutons d'ordre horizontal.
	list<buttonStripV*> _bsV;	// Banni�res de boutons d'ordre vertical.
	buttonStrip * _bs;			// Banni�re active.

	vector<selection> _selected;	// 

	vector<tblShapeCol> generateSaveData()
	{
		// get username -> get user ID in tblUsager:
		vector<tblUsagerCol> usagerElem;

		// get current dessID:
		vector<tblDessinCol> dessinElem;	///A

		// insert in tblShape those:
		const int shapeQty = (int)_listShape.size();
		vector<tblShapeCol> shapeElem;

		// store those in the right place
		vector<tblTypeColorCol> typeColorElem;
		
		int i = 0;
		for (auto & s : _listShape)
		{
			// M�thode 1
			shapeElem.push_back(tblShapeCol{ -1,
				s.shapePtr->getPosition().x, s.shapePtr->getPosition().y, 
				s.shapePtr->getGlobalBounds().width, s.shapePtr->getGlobalBounds().height,
				s.shapeType, s.f/*, dessinElem.dessID*/});
			
			/* // M�thode 2
			
			shapeElem[i].shaPosX = s.shapePtr->getPosition().x;
			shapeElem[i].shaPosY = s.shapePtr->getPosition().y;
			shapeElem[i].shaDimX = s.shapePtr->getGlobalBounds().width;
			shapeElem[i].shaDimY = s.shapePtr->getGlobalBounds().height;
			shapeElem[i].shaType = s.shapeType;
			shapeElem[i].shaColor = s.f;
			shapeElem[i].shaDessin = dessinElem.dessID;*/

			i++;
		}

		// Faire appel � la m�thode saveCanva de sqlConnect
		return shapeElem;
	}

public:
	painter();					// Constructeur sans param�tre
	void init();				// Initialise l'interface
	int run();					// Boucle principale
	
	/// Getteurs
	bool findShape() const;		// 
	///shape* selectedShape(Vector2f v); // Retourne la shape si elle est s�lectionn�e
	// 
	list<shape>::iterator searchShape(Vector2f v);
	bool isOnAZone();			// 
	buttonStrip * isOnZone();	// 
	oButton * isOnButton();		// 

	/// Setteurs
	// Ajoute une banni�re horizontale � l'interface.
	void addBsH(bool normalScope = true, bool normalInterval = true,
		Vector2f initPos = Vector2f(), Vector2f limitPos = Vector2f(),
		bool fixed = false, Vector2f minDim = Vector2f(1, 50));
	void addButton(oButton * b);	// Ajoute un bouton dans la banni�re active.

	/// Affichage
	void clear();				// Nettoie l'interface
	void drawListShape();		// Dessine les formes de la liste
	void drawButtonstrips();	// Dessine toutes les banni�res et leur boutons.
	//void show();				// Affiche l'interface ///inutile ?

};


