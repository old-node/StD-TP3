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
	oButton * _mode;		// Mode dans lequel le curseur fonctionne

	Vector2f _click;		// Position du dernier click
	Vector2f _current;		// Position actue /// ?? utiliser getPosition()
	Vector2f _offset;		// Offset pour la selection
	bool _clicking;			// État des boutons de la souris 
	bool _dragable;			// Condition qui permet le déplacement du focus
	bool _selecting;		// Condition à savoir si une forme est selectionne ou pas
	bool _onZone;			// Condition à savoir si le curseur est dans une zone

	shape _focus;			// Zone de sélection ou aperçu d'une forme
	elemColors _focusC;		// Couleurs a appliquer à la forme créée
	bool _defaultC;			// État qui spécifie si on utilise la couleur par défaut.
	bool _randomC;			// État qui indique qu'une couleur aléatoire sera appliquée.
	rRegion _zone;			// Zone active du curseur
	FloatRect _zones[static_cast<int>(rCOUNT)];	// Dimmenssions des zones

	// Recherche si un bouton est sous la souris
	///oButton * searchForButton();

public:
	cursor();
	~cursor();

	/// Setteurs
	int setMode(oButton * b);
	void setClick(Vector2f click);
	void setCurrent(Vector2f current);
	void setSelected(bool b);
	void setOnZone(bool b);
	void setColors(elemColors c)
	{
		_focusC = c;
		_defaultC = false;
		_randomC = false;
	}
	void setColorsRandom()
	{
		_randomC = true;
		_defaultC = false;
	}
	void setColorsDefault()
	{
		_randomC = false;
		_defaultC = true;
	}
	void applyColor(shape & s)
	{
		if (_randomC)
		{
			PBOARD randomF = static_cast<PBOARD>(rand() % DBOARD.size());
			PBOARD randomOL = static_cast<PBOARD>((rand() + 1) % DBOARD.size());
			PBOARD randomT = static_cast<PBOARD>((rand() + 2) % DBOARD.size());
			_focusC.set(randomF, randomOL, randomT);
			_focusC.apply(s);
		}
		else if (!_defaultC)
		{
			_focusC.apply(s);
		}
		else
		{
			;
		}
	}

	/// Manipulations du focus
	void initFocus();
	void setFocus(shape current);

	/// Clicker
	int click();
	void drag();
	void releaseClick(list<shape> & l);

	/// Getteurs
	bool isClicking(Mouse::Button it = Mouse::Left);
	bool getClicking() const;
	cMode getModeCurs() const;	// Retourner un int au lieu ?*
	shape getFocus() const;
	Vector2f * getClick();
	Vector2f * getCurrent();
	bool isOnZone() const;

	//void drawButton(oButton * oB);
	bool onZone(FloatRect z, RenderWindow & w);
};
