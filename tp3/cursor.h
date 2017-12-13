/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:
======================================================================================*/


#pragma once
#include <cassert>
#include <vector>
#include <math.h>
using namespace std;
#include "oButton.h"

using namespace sf;




// Classe cursor qui est manipulé par la sourie de l'ordinateur
class cursor : private Mouse
{
private:
	vector<oButton*> _bOptions;	// Listes des modes disponibles

	oButton * _mode;		// Mode dans lequel le curseur fonctionne
	
	Vector2f _click;		// Position du dernier click
	Vector2f _current;		// Position actue /// ?? utiliser getPosition()
	Vector2f _offSet;		//Offset pour la selection
	bool _clicking;			// État des boutons de la souris 
	bool _dragable;			// Condition qui permet le déplacement du focus
	bool _selecting;		// Condition à savoir si une forme est selectionne ou pas

	shape _focus;	// Zone de sélection ou aperçu d'une forme

	rRegion _zone;			// Zone active du curseur
	FloatRect _zones[static_cast<int>(rCOUNT)];	// Dimmenssions des zones


	// Recherche si un bouton est sous la souris
	//oButton * searchForButton();

public:
	cursor();
	~cursor();

	/// Setteurs
	void setMode(oButton * b);
	void setClick(Vector2f click);
	void setCurrent(Vector2f current);
	void setSelected(bool b);

	/// Manipulations du focus
	void initFocus();
	void setFocus(shape current);

	/// Clicker
	void click();
	void drag(Vector2i mouse = getPosition());
	shape releaseClick();

	/// Getteurs
	bool isClicking(Mouse::Button it = Mouse::Left);
	bool getClicking() const;
	cMode getModeCurs() const;	// Retourner un int au lieu ?*
	shape getFocus() const;
	Vector2f getClick() const;
	Vector2f getCurrent() const;
	
	void changeMode();
	//Setteur de focus

	//RectangleShape getFocus() const { return _focus; }

	/// Affichage
	// Procède à une méthode avec chaqu'un des boutons


	//void drawButton(oButton * oB);
	Shape * getFocus();
	bool onZone(FloatRect z, RenderWindow & w);
};
