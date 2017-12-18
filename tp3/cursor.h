/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagac�
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




// Classe cursor qui est manipul� par la sourie de l'ordinateur
class cursor : private Mouse
{
private:
	oButton * _mode;		// Mode dans lequel le curseur fonctionne
	
	Vector2f _click;		// Position du dernier click
	Vector2f _current;		// Position actue /// ?? utiliser getPosition()
	Vector2f _offset;		// Offset pour la selection
	bool _clicking;			// �tat des boutons de la souris 
	bool _dragable;			// Condition qui permet le d�placement du focus
	bool _selecting;		// Condition � savoir si une forme est selectionne ou pas
	bool _onZone;			// Condition � savoir si le curseur est dans une zone (buttonstrip)

	shape _focus;			// Zone de s�lection ou aper�u d'une forme

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
	void setOnZone(bool b);

	/// Manipulations du focus
	void initFocus();
	void setFocus(shape current);

	/// Clicker
	int click(elemColors focusC);
	void drag();
	shape releaseClick();

	/// Getteurs
	bool isClicking(Mouse::Button it = Mouse::Left);
	bool getClicking() const;
	cMode getModeCurs() const;	// Retourner un int au lieu ?*
	shape getFocus() const;
	Vector2f * getClick();
	Vector2f * getCurrent();
	bool isOnZone() const;

	/// Affichage


	//void drawButton(oButton * oB);
	bool onZone(FloatRect z, RenderWindow & w);
};
