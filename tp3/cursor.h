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
	RenderWindow & _w;		// Fenêtre active du curseur
	vector<oButton*> _bOptions;	// Listes des modes disponibles

	oButton * _mode;		// Mode dans lequel le curseur fonctionne
	Vector2f _click;		// Position du dernier click
	Vector2f _current;		// Position actue /// ?? utiliser getPosition()
	bool _clicking;			// État des boutons de la souris 
	bool _dragable;			// Condition qui permet le déplacement du focus

	RectangleShape _focus;	// Zone de sélection ou aperçu d'une forme

	rRegion _zone;			// Zone active du curseur
	FloatRect _zones[static_cast<int>(rCOUNT)];	// Dimmenssions des zones


	// Recherche si un bouton est sous la souris
	oButton * searchForButton();

public:
	cursor(RenderWindow & window);
	~cursor();

	/// Setteurs
	void setMode(oButton * b);
	void setClick(Vector2f click);
	void setCurrent(Vector2f current);

	/// Manipulations du focus
	void initFocus(Vector2f current);
	void setFocus(Vector2f current);

	/// Clicker
	void click(Vector2i click = getPosition());
	void drag(Vector2i mouse = getPosition());
	int unclick(Vector2i current = getPosition());

	/// Getteurs
	bool isClicking(Mouse::Button it = Mouse::Left);
	bool getClicking() const;
	oButton * getMode() const;	// Retourner un int au lieu ?*
	RectangleShape * getFocus() const;
	Vector2f getClick() const;
	Vector2f getCurrent() const;
	//RectangleShape getFocus() const { return _focus; }

	/// Affichage
	// Procède à une méthode avec chaqu'un des boutons
	void drawMenu();


	void drawButton(oButton * oB);
	void drawFocus();
	bool onZone(rRegion z);
};
