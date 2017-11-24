/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:
======================================================================================*/


#include "cursor.h"



// Constructeur par défaut
cursor::cursor()
{
	_mode = nullptr;
}
// Destructeur
cursor::~cursor()
{
	_mode = nullptr;
}


/// Setteurs

void cursor::setMode(oButton * b)
{
	_mode = b;
}

void cursor::setClick(Vector2f click)
{
	_click = click;
}


/// Manipulations du focus

void cursor::setCurrent(Vector2f current)
{
	_current = current;
}

void cursor::setFocus(Vector2f current)
{
	float x = current.x - _click.x;
	float y = current.x - _click.x;

	if (x < 0)
	{
		if (y < 0)	// quadrant supérieur gauche
			_mode->setFocus(_current, Vector2f(-x, -y));
		else		// quadrant inférieur gauche
			_mode->setFocus(Vector2f(_current.x, _click.y), Vector2f(-x, y));
	}
	else if (y < 0)	// quadrant supérieur droit
		_mode->setFocus(Vector2f(_click.x, _current.y), Vector2f(x, -y));
	else			// quadrant inférieur droit
		_mode->setFocus(_click, Vector2f(x, y));
}


/// Clicker

void cursor::click(Vector2i click)
{
	_clicking = true;
	_click = (Vector2f)click;

}

void cursor::drag(Vector2i current)
{
	//_clicking = true;
	_current = (Vector2f)current;
	setFocus((Vector2f)current);
}

void cursor::unclick(Vector2i current)
{
	_clicking = false;
	setFocus((Vector2f)current);
}


/// Getteurs

bool cursor::getClicking() const { return _clicking; }

oButton * cursor::getMode() const { return _mode; }

Vector2f cursor::getClick() const { return _click; }

Vector2f cursor::getCurrent() const { return _current; }


/// Affichage

void cursor::drawFocus(RenderWindow & window)
{
	_mode->drawFocus(window);
}

