/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:
======================================================================================*/


#pragma once
#include <cassert>
#include <math.h>
using namespace std;
#include <SFML/Graphics.hpp>
#include "oButton.h"
using namespace sf;



// Classe cursor qui est manipulé par la sourie de l'ordinateur
class cursor
{
private:
	bool _clicking;
	bool _dragable;
	Vector2f _click;
	Vector2f _current;
	oButton * _mode;

public:
	cursor();
	~cursor();

	/// Setteurs
	void setMode(oButton * b);
	void setClick(Vector2f click);
	void setCurrent(Vector2f current);

	/// Manipulations du focus
	void setFocus(Vector2f current);

	/// Clicker
	void click(Vector2i click);
	void drag(Vector2i current);
	void unclick(Vector2i current);

	/// Getteurs
	bool getClicking() const;
	oButton * getMode() const;	// Retourner un int au lieu ?*
	Vector2f getClick() const;
	Vector2f getCurrent() const;
	//RectangleShape getFocus() const { return _focus; }

	/// Affichage
	void drawFocus(RenderWindow & window);

};

