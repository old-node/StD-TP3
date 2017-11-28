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

	rRegion _zone;			// Zone active du curseur
	FloatRect _zones[static_cast<int>(rCOUNT)];	// Dimmenssions des zones


	// Recherche si un bouton est sous la souris
	oButton * searchForButton()
	{
		for (auto & b : _bOptions)
			if (b->gotMouse(_w))
				return b;
		return nullptr;
	}

public:
	cursor(RenderWindow & window);
	~cursor();

	/// Setteurs
	void setMode(oButton * b);
	void setClick(Vector2f click);
	void setCurrent(Vector2f current);

	/// Manipulations du focus
	void initFocus(Vector2f current);
	void setFocus(Vector2f current)
	{
		if (_mode != nullptr)
		{
			_mode->scaleFocus(_click - current);
		}
	}

	/// Clicker
	void click(Vector2i click = getPosition());
	void drag(Vector2i mouse = getPosition());
	int unclick(Vector2i current = getPosition());

	/// Getteurs
	bool isClicking(Mouse::Button it = Mouse::Left)
	{
		return (isButtonPressed(it) && _clicking);
	}
	bool getClicking() const;
	oButton * getMode() const;	// Retourner un int au lieu ?*
	RectangleShape * getFocus() const
	{
		assert(_mode != nullptr);
		return _mode->getFocus();
	}
	Vector2f getClick() const;
	Vector2f getCurrent() const;
	//RectangleShape getFocus() const { return _focus; }

	/// Affichage
	// Procède à une méthode avec chaqu'un des boutons
	void drawMenu()
	{
		for (auto & b : _bOptions)	// Pour chaque bouton d'options
		{
			if (b->gotMouse(_w)) /// b->gotMouse(_window)
			{
				drawButton(b);
				cursorPos(b, _w);
			}
		}
	}


	void drawButton(oButton * oB)
	{
		_w.draw(oB->body());
		_w.draw(oB->text());

	}
	void drawFocus();
	void drawCanvas()
	{

	}
	bool onZone(rRegion z)
	{
		if (_zones[z].contains((Vector2f)getPosition(_w)))
		{
			_zone = z;
			return true;
		}
		return false;
	}
};


//if (x < 0)
//{
//	if (y < 0)	// quadrant supérieur gauche
//		_mode->setFocus(_current, Vector2f(-x, -y));
//	else		// quadrant inférieur gauche
//		_mode->setFocus(Vector2f(_current.x, _click.y), Vector2f(-x, y));
//}
//else if (y < 0)	// quadrant supérieur droit
//	_mode->setFocus(Vector2f(_click.x, _current.y), Vector2f(x, -y));
//else			// quadrant inférieur droit
//	_mode->setFocus(_click, Vector2f(x, y));



//void forwarder(void* context, int i0, int i1) {
//	;//static_cast<oButton*>(context)->member(i0, i1);
//}
/*bool gotZone(void* oB)
{
return static_cast<oButton*>(oB)->gotMouse(_window);
}*/