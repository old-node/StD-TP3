/*======================================================================================
Fichier:		oButton.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
Description:
======================================================================================*/


#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
#include "tp3/painterFuction.h"
using namespace sf;


// Pour l'emplacement
const int SCREENW = 800;				// Largeur de l'écran /// inclus à partir du (main) ?
const int SCREENH = 800;				// Hauteur de l'écran

const int BUTTONSPAN = 5;				// Rapport de boutons en largeur
const float BW = SCREENW / BUTTONSPAN;	// Largeur maximum des boutons
const float BH = 40.0;					// Hauteur maximum des boutons
const bool HORIZONTALMENU = false;		// Sens de la liste des boutons
const float BOL = 1;

// pour l'apparence
const Color FILLC = Color::White;
const Color OUTLC = Color::Black;

// Pour le text
//const sf::Font FONT = FONT();
const Color FONTC = Color::Blue;
const int TSIZE = (int)(BH / 2 - 2 * BOL);
const float TOLW = 15;
const float TOLH = 8;

// Pour le focus
const Color FOCUSFILL = Color::Transparent;
const Color FOCUSOL = Color::Black;

// Couleurs des formes
/// Faire un énum des couleurs ??
const Color CBOX = Color::Green;
const Color CLINE = Color::Cyan;
const Color CLINK = Color::Yellow;



// Calcul les dimmensions nécessaire du bouton pour le texte
static float textDim(float p, float t, float MAX)
{
	if (p == 0)
		if (t <= MAX)
			p = t;
		else
			p = MAX;
	return p;
}

/// Classe de base des boutons de la boite à outils et du menu principal
//class button
//{
//private:
//public:
//	button()
//	{
//	}
//	~button()
//	{
//	}
//};

// Assortissement des couleurs des formes.
struct elemColors
{
	Color f;				// Couleur du corps de la forme.
	Color ol;				// Couleur de la bordure de la forme.
	Color t;				// Couleur du text sur la forme.
};


// Classe de base des boutons
class oButton : public RectangleShape, public Text
{
private:
	int _nbB;				// Nombre de bouton d'option ou son identifiant.
	Font _p;				// Police du bouton.
	Vector2f _textOrigin;	// Décallage entre le text et le cadre du bouton.
	bCorner _originCorner;	// Position du coin du bouton où son origine est placé.
	elemColors _oColor;		// Couleurs originales du bouton.

protected:
	cMode _m;				// Type d'opérations que le bouton effectue
	bool _clicking;			/// ??

	Shape * _focus;			// 
	Color _focusC;			// Couleur de la forme interne du 
	Color _focusOLC;		// 
	float _focusOL;			// 

	/// Initialiseur
	void initMode(cMode mode = cDefault);
public:
	/// Constructeur
	oButton(float left, float top, float width, float height,
		float outline, Color fillC, Color OLC,
		string text, Font police, int charSize, Color fontC,
		Color focusC, Color focusOLC, float focusOL,
		Shape * focus);
	~oButton();

	/// Setteurs
	void setColors(Color fillC = FILLC, Color OLC = OUTLC);
	void setFocus(Color focusC = Color::Transparent, Color focusOLC = Color::Yellow,
		float focusOL = 1, Shape * focus = nullptr);
	void move(Vector2f pos = Vector2f())
	{
		RectangleShape::setPosition(pos);
		Text::setPosition(pos);
	}
	void resize(Vector2f dim = Vector2f(1, 1))	/// Trop petit ??
	{
		assert(0 < dim.x && dim.x < 1000
			&& 0 < dim.y && dim.y < 1000
			/*&& dim.y >= Text::getGlobalBounds().height*/);

		Vector2f box, mid, center, pos;
		float ol = RectangleShape::getOutlineThickness();
		RectangleShape::setOrigin(Vector2f(-ol, -ol));
		pos = RectangleShape::getPosition();

		float width = textDim(dim.x, Text::getGlobalBounds().width, BW);
		float height;// = textDim(dim.y, Text::getGlobalBounds().height, BH);
		/// Resizer seullement la largeur ??

		while (dim.x < Text::getGlobalBounds().width)
		{
			string current = Text::getString();
			current.pop_back();
			Text::setString(current);
		}
		if (dim.x > Text::getGlobalBounds().width)
			width = dim.x;
		
		/*//if (dim.y != Text::getGlobalBounds().height)
		height = dim.y;
		box = Vector2f(width + TOLW * 2, height + TOLH * 2);
		mid = Vector2f(width / 2, height / 2);
		center = Vector2f(box.x / 2, box.y / 2 - TOLH / 2);
		Text::setOrigin(mid);
		Text::setPosition(pos);
		Text::move(center);
		//RectangleShape::setTextureRect((IntRect)FloatRect(pos, box));
		RectangleShape::setOrigin(center);*/

		initOrigins();
	}
	// Met à jour l'origine du rectangle et 
	void initOrigins(bCorner corner = bUpperLeft)
	{
		///if (_originCorner == corner)
		///	return;
		
		_originCorner = corner;
		
		// Initialise l'origine du rectangle.
		float ol = RectangleShape::getOutlineThickness();
		Vector2f rPos = RectangleShape::getPosition();
		Vector2f origin = originOffset(_originCorner, ol, getP(_originCorner));
		RectangleShape::setOrigin(origin);

		// Initialise l'origine du texte.
		Vector2f rDim = RectangleShape::getSize();
		FloatRect tDim = Text::getLocalBounds();
		_textOrigin = Vector2f(
			((rDim.x + ol * 2) - tDim.width) / 2,
			((rDim.y + ol * 2) - tDim.height) / 2);
		_textOrigin = updateTextOrigin(_originCorner, tDim, _textOrigin);
		Text::setOrigin(_textOrigin);
		Text::setPosition(rPos);	/// À enlever pour certains cas??
	}
	void scaleFocus(Vector2f diff);

	/// Manipulation du focus
	virtual void click(Vector2f pos = (Vector2f)Mouse::getPosition());
	virtual int release(/*Vector2f pos*/);
	virtual void drag(Vector2f pos);
	virtual void undrag(Vector2f pos);	/// ?
	virtual void c(Vector2f pos) {}		/// ?

	void leave();
	virtual void pick() {}				/// ?

	/// Getteurs
	float getW()
	{
		return getP(bUpperRight).x - getP(bUpperLeft).x;
	}
	float getH()
	{
		return getP(bLowerLeft).y - getP(bUpperLeft).y;
	}
	Vector2f getP(bCorner p = bLowerRight);
	cMode getMode() const;
	bool gotMouse(RenderWindow & screen) const;

	/// Affichage
	RectangleShape getBody();
	Text getText();
};


// Classe de base des boutons de création
class oB_create : public oButton
{
private:
protected:
	sShape _s;				// Type de forme à créer

	/// Initialiseur
	void initShape(sShape vertex = sBox);/// avec un default ?

public:
	oB_create(float l, float t, float w, float h,
		float o, Color bC, Color olC,
		string s, Font p, int c, Color sC,
		Color fC, Color folC, float fol, Shape * f) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cCreate);
	}

	/// Getteurs
	sShape getShape() const;


};

// Classe du bouton de création de boites
class oB_cBox : public oB_create
{
private:
protected:
public:
	oB_cBox(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = CBOX,
		string s = "Boite", Font p = FONT(), int c = TSIZE, Color sC = CBOX,
		Color fC = CBOX, Color folC = Color::Black, float fol = 1, Shape * f = nullptr) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initShape(sBox);
	}

	// 
	void click()
	{

	}
};

// Classe du bouton de création de traits
class oB_cCircle : public oB_create
{
private:
protected:

public:
	oB_cCircle(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = BOL, Color bC = FILLC, Color olC = CLINE,
		string s = "Trait", Font p = FONT(), int c = TSIZE, Color sC = CLINE,
		Color fC = Color::Yellow, Color folC = CLINE, float fol = 2, Shape * f = nullptr) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initShape(sCircle);
	}

	// 
	void click()
	{

	}
};



// Classe du bouton d'option pour effacer des formes
class oB_remove : public oButton
{
private:
protected:
public:
	oB_remove(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = Color::Red,
		string s = "Efface", Font p = FONT(), int c = TSIZE, Color sC = Color::Red,
		Color fC = Color::Transparent, Color folC = Color::Red, float fol = 2, Shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cRemove);
	}

	// 
	void click()
	{

	}
};


// Classe de base des boutons de création
class oB_select : public oButton
{
private:
protected:
public:
	oB_select(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 5, Color bC = FILLC, Color olC = Color::Green,
		string s = "Sélection", Font p = FONT(), int c = TSIZE, Color sC = Color::Green,
		Color fC = Color::White, Color folC = Color::Green, float fol = 3, Shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cSelect);
	}

	// 
	void click()
	{

	}
};


// Classe du bouton d'option pour lier des éléments
class oB_link : public oButton
{
private:
protected:
public:
	oB_link(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 11, Color bC = FILLC, Color olC = Color::Yellow,
		string s = "Lier", Font p = FONT(), int c = TSIZE, Color sC = Color::Yellow,
		Color fC = Color::Black, Color folC = Color::Yellow, float fol = 1, Shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cLink);
	}

	// 
	void click()
	{

	}
};


// 
void cursorPos(oButton * b, RenderWindow & screen);

