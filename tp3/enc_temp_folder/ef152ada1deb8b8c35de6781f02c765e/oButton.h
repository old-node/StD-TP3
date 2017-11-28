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
const bool HORIZONTALMENU = true;			// Sens de la liste des boutons

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
// Obtien les bonnes coordonnées du prochain bouton selon sa liste
static bool offsetButton(float & p, float & q, float P, float Q,
	float tol, float ol, int MAX)
{
	if (p + P > MAX)
	{
		p = 0;
		q += Q + ol * 3 + tol;
		return true;
	}
	else
		p += P + ol * 2 + tol * 2;
	return false;
}



// Classe de base des boutons
class oButton : public RectangleShape, public Text
{
private:
	Font _p;				// Police du bouton
	int _nbB;				// Nombre de bouton d'option

protected:
	cMode _m;				// Type d'opérations que le bouton effectue
	bool _clicking;			/// ??
	RectangleShape _focus;	// Zone de sélection ou aperçu d'une forme

	/// Initialiseur
	void initMode(cMode mode = cDefault);
public:
	/// Constructeur
	oButton(float left = 0, float top = 0, float width = 0, float height = 0,
		float outline = BOL, Color fillC = FILLC, Color OLC = OUTLC,
		string text = "Bouton", Font police = FONT(), int charSize = TSIZE, Color fontC = FONTC,
		Color focusC = Color::Transparent, Color focusOLC = Color::Yellow, float focusOL = 1);
	~oButton();

	/// Setteurs
	void setColors(Color fillC = FILLC, Color OLC = OUTLC)
	{
		RectangleShape::setFillColor(fillC);
		RectangleShape::setOutlineColor(OLC);
	}
	void setFocusColor(Color focusC = Color::Transparent,
		Color focusOLC = Color::Yellow) /// ?
	{
		_focus.setFillColor(focusC);
		_focus.setOutlineColor(focusOLC);
	}
	void initFocus(Vector2f origin, Vector2f pos); /// ?
	void scaleFocus(Vector2f diff)
	{
		_focus.setScale(diff);
	}

	/// Manipulation du focus
	virtual void click(Vector2f pos = (Vector2f)Mouse::getPosition());
	virtual RectangleShape unclick(Vector2f pos);
	virtual void drag(Vector2f pos);
	virtual void undrag(Vector2f pos); /// ?
	virtual void c(Vector2f pos) {} /// ?

	void leave();
	virtual void pick() {} /// ?

	/// Getteurs
	Vector2f getP(int p = 0)
	{
		return RectangleShape::getPoint(p);
	}
	cMode getMode() const;
	RectangleShape * getFocus()
	{
		return new RectangleShape(_focus);
	}
	bool gotMouse(RenderWindow & screen) const;

	/// Affichage
	RectangleShape body();
	Text text()
	{
		return static_cast<Text>(*this);
	}
	RectangleShape focus();
};


// Classe de base des boutons de création
class oB_create : public oButton
{
private:
protected:
	sShape _s;				// Type de forme à créer

	/// Initialiseur
	void initShape(sShape vertex = sNone);/// avec un default ?

public:
	oB_create(float l = 0, float t = 0, float w = BW, float h = BH,
		float o = BOL, Color bC = FILLC, Color olC = Color::Black,
		string s = "Créer", Font p = FONT(), int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::Black, Color folC = Color::Black, float fol = 1) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
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
		float o = BOL, Color bC = FILLC, Color olC = CBOX,
		string s = "Boite", Font p = FONT(), int c = TSIZE, Color sC = CBOX,
		Color fC = CBOX, Color folC = Color::Black, float fol = 1) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
	{
		initShape(sBox);
	}

	// 
	void click()
	{

	}
};

// Classe du bouton de création de traits
class oB_cLine : public oB_create
{
private:
protected:

public:
	oB_cLine(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = BOL, Color bC = FILLC, Color olC = CLINE,
		string s = "Trait", Font p = FONT(), int c = TSIZE, Color sC = CLINE,
		Color fC = Color::Yellow, Color folC = CLINE, float fol = 2) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
	{
		initShape(sLine);
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
		float o = BOL, Color bC = FILLC, Color olC = Color::Red,
		string s = "Efface", Font p = FONT(), int c = TSIZE, Color sC = Color::Red,
		Color fC = Color::Transparent, Color folC = Color::Red, float fol = 2) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
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
		float o = BOL, Color bC = FILLC, Color olC = Color::Green,
		string s = "Sélection", Font p = FONT(), int c = TSIZE, Color sC = Color::Green,
		Color fC = Color::White, Color folC = Color::Green, float fol = 3) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
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
		float o = BOL, Color bC = FILLC, Color olC = Color::Yellow,
		string s = "Lier", Font p = FONT(), int c = TSIZE, Color sC = Color::Yellow,
		Color fC = Color::Black, Color folC = Color::Yellow, float fol = 1) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol)
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

