/*======================================================================================
Fichier:		oButton.h
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			22-11-2017
Description:
======================================================================================*/


#pragma once
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


const Color FONTC = Color::Blue;
const Color FILLC = Color::White;
const Color OUTLC = Color::Black;

const Color BOXC = Color::Green;
const Color LINEC = Color::Yellow;

const Color FOCUSFILL = Color::Transparent;
const Color FOCUSOL = Color::Black;


// Modes de fonctionnement avec le curseur
enum oMode
{
	oDefault, oClick, oDrag, oUnclick
};
// Options d'op�rations dans l'application
enum cMode
{
	cDefault, cCreate, cLink, cRemove, cSelect, cMove, cResize
};
// Choix de la forme � dessinner
enum shape
{
	sNone, sBox, sLine
};


// Classe de base des boutons
class oButton : public RectangleShape, public Text
{
protected:
	cMode _m;				// Type d'op�rations que le bouton effectue
	RectangleShape _focus;	// Zone de s�lection ou aper�u d'une forme

private:
public:
	/// Constructeur
	oButton(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = FONTC, Color fillC = FILLC, Color outlineC = OUTLC,
		int charSize = 5, float outline = 1);

	/// Setteurs
	virtual void setMode(cMode mode = cDefault) = 0;
	virtual void setShape(shape vertex = sNone) = 0;
	virtual void setFocusColor(Color fillC = Color::Transparent,
		Color outlineC = Color::Yellow, float outlineT = 1) = 0;

	void setFocus(Vector2f origin, Vector2f size);

	/// Getteurs	
	cMode getMode() const;
	bool gotMouse(RenderWindow & screen) const;

	/// Affichage
	void draw(RenderWindow & window) const;
	void drawFocus(RenderWindow & window) const;
};



// Classe de base des boutons de cr�ation
class oB_create : public oButton
{
protected:
	shape _s;				// Type de forme � cr�er

	void setMode(cMode mode = cCreate) override;
	oB_create(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = FONTC, Color fillC = FILLC, Color outlineC = OUTLC);
private:
public:
	/// Getteurs
	shape getShape() const;
};

/*
*/

// Classe du bouton de cr�ation de boites
class oB_cBox : public oB_create
{
protected:
private:
	void setShape(shape vertex = sBox) override;
	void setFocusColor(Color fillC = BOXC,
		Color outlineC = Color::Black, float outlineT = 1) override;
public:
	oB_cBox(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = BOXC, Color fillC = FILLC, Color outlineC = BOXC);

};

// Classe du bouton de cr�ation de traits
class oB_cLine : public oB_create
{
protected:
private:

	void setShape(shape vertex = sLine) override;
	void setFocusColor(Color fillC = Color::Yellow,
		Color outlineC = LINEC, float outlineT = 2) override;
public:
	oB_cLine(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = LINEC, Color fillC = FILLC, Color outlineC = LINEC);
};

// Classe du bouton d'option pour effacer des formes
class oB_remove : public oButton
{
protected:
private:
	void setMode(cMode mode = cRemove) override;
	void setShape(shape vertex = sNone) override {}
	void setFocusColor(Color fillC = Color::Transparent,
		Color outlineC = Color::Red, float outlineT = 2) override;
public:
	oB_remove(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = Color::Red, Color fillC = FILLC, Color outlineC = Color::Red);

};

// Classe de base des boutons de cr�ation
class oB_select : public oButton
{
protected:
private:
	void setMode(cMode mode = cSelect) override;
	void setShape(shape vertex = sNone) override {}
	void setFocusColor(Color fillC = Color::White,
		Color outlineC = Color::Green, float outlineT = 3) override;
public:
	oB_select(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = Color::Green, Color fillC = FILLC, Color outlineC = Color::Green);

};

// Classe du bouton d'option pour lier des �l�ments
class oB_link : public oButton
{
protected:
private:
	void setMode(cMode mode = cLink) override;
	void setShape(shape vertex = sNone) override {}
	void setFocusColor(Color fillC = Color::Black,
		Color outlineC = Color::Yellow, float outlineT = 1) override;
public:
	oB_link(float left, float top, float width, float height,
		Font & font, string text = "",
		Color fontC = Color::Cyan, Color fillC = FILLC, Color outlineC = Color::Cyan);

};