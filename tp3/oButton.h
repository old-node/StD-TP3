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
#include <list>
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
	elemColors(Color fill = Color::White,
		Color outline = Color::Black,
		Color text = Color::Black)
	{
		set(fill, outline, text);
	}
	void set(Color fill = Color::White,
		Color outline = Color::Black,
		Color text = Color::Black)
	{
		f = fill;
		ol = outline;
		t = text;
	}
	void set(elemColors c)
	{
		set(c.f, c.ol, c.t);
	}
	~elemColors()
	{
		t = ol = f = Color();
	}
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

	sShape _s;				// Type de forme à créer
	cMode _m;				// Type d'opérations que le bouton effectue
	bool _clicking;			/// ??
	bool _selecting;		/// ??

	Vector2f * _click;		// 
	Vector2f * _current;	// 
	Vector2f _offset;		// 
	vector<list<shape>::iterator> _selected;	// 
	///shape * _focus;			// 
	elemColors _focusC;		// Couleurs à appliquer au focus
	float _focusOL;			// 

	list<shape> * _listShape;// Pointeur sur la liste des formes de l'application.

	/// Initialiseur
	void initMode(cMode mode = cDefault);

	// Cherche une shape dans le vecteur et retourne l'iterateur ou la shape est
	// selon une position de la sourie
	vector<list<shape>::iterator> selectShapes(shape focus)
	{
		assert(!_listShape->empty());
		list<shape>::iterator it = _listShape->end();
		vector<list<shape>::iterator> selection;	// Formes comprises dans le focus
		FloatRect zone = focus.shapePtr->getGlobalBounds();

		do
		{
			it--;
			if (it->shapePtr->getGlobalBounds().intersects(zone))
			{
				selection.push_back(it);
				// Si la zone n'est qu'un pixel de large ou de hauteur,
				//	ne retourner qu'une seule forme.
				if (zone.width < 2 && zone.height < 2)
					return selection;
			}
		} while (it != _listShape->begin());

		// Si la boucle est fini sans qu'on retourne l'iterateur,
		// on retourne l'iterateur a la fin
		it = _listShape->end();	/// Encore utile??
		return selection;
	}
public:
	/// Constructeur
	oButton(float left, float top, float width, float height,
		float outline, Color fillC, Color OLC,
		string text, Font police, int charSize, Color fontC,
		Color focusC, Color focusOLC, float focusOL, shape * focus);
	~oButton();

	/// Setteurs
	void initCursorData(Vector2f * current, Vector2f * click, list<shape> * listShape)
	{
		_current = current;
		_click = click;
		_listShape = listShape;
	}
	void setColors(Color fillC = FILLC, Color OLC = OUTLC);
	void setFocus(Color focusC = Color::Transparent, Color focusOLC = Color::Yellow,
		float focusOL = 1, shape * focus = nullptr);

	void move(Vector2f pos = Vector2f());
	void resize(Vector2f dim = Vector2f(1, 1));
	// Met à jour l'origine du rectangle et ...
	void initOrigins(bCorner corner = bUpperLeft);
	///void scaleFocus(Vector2f diff)	{ _focus->shapePtr->setScale(diff); }

	/// Opérations virtuelles des modes
	virtual void mPick() = 0;
	virtual void mLeave() = 0;
	virtual int mClick(shape & focus) = 0;
	virtual shape mRelease(shape & focus, float radius) = 0;
	virtual void mDrag(shape & focus) = 0;
	virtual void mUndrag() = 0;

	/// Getteurs
	float getW();
	float getH();
	Vector2f getP(bCorner p = bLowerRight);
	cMode getMode() const;
	bool gotMouse(RenderWindow & screen) const;
	sShape getShape() const;

	/// Affichage
	RectangleShape getBody();
	Text getText();

};


// Classe de base des boutons de création
class oB_create : public oButton
{
private:
protected:

	/// Initialiseur
	void initShape(sShape vertex = sBox);/// avec un default ?

public:
	oB_create(float l, float t, float w, float h,
		float o, Color bC, Color olC,
		string s, Font p, int c, Color sC,
		Color fC, Color folC, float fol, shape * f) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cCreate);
	}
};

// Classe du bouton de création de boites
class oB_cBox : public oB_create
{
private:
protected:
public:
	oB_cBox(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = CBOX,
		string s = "Boite", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = CBOX, Color folC = Color::Black, float fol = 1, shape * f = nullptr) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initShape(sBox);
	}

	/// Opérations du mode
	void mPick() override
	{

	}
	void mLeave() override
	{

	}
	int mClick(shape & focus) override
	{
		_clicking = true;

		focus.shapePtr = new RectangleShape();
		focus.shapeType = _s;
		focus.shapePtr->setFillColor(_focusC.f);
		focus.shapePtr->setOutlineColor(_focusC.ol);
		focus.shapePtr->setPosition(*_current);
		return 0;
	}
	shape mRelease(shape & focus, float radius = 0) override
	{
		_clicking = false;

		Vector2f dim = Vector2f(*_current - *_click);
		focus.shapePtr = new RectangleShape(dim);
		focus.shapePtr->setPosition(*_click + Vector2f(dim.x * 0.5, dim.y * 0.5));
		focus.shapePtr->setOrigin(Vector2f(dim.x * 0.5, dim.y * 0.5));
		_listShape->push_back(shape(focus));
		return nullptr;
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
		{
			Vector2f dim = Vector2f(*_current - *_click);
			focus.shapePtr = new RectangleShape(dim);
			focus.shapePtr->setPosition(*_click);
		}
	}
	void mUndrag() override
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
		string s = "Cercle", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::Yellow, Color folC = CLINE, float fol = 2, shape * f = nullptr) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initShape(sCircle);
	}

	/// Opérations du mode
	void mPick() override
	{

	}
	void mLeave() override
	{

	}
	int mClick(shape & focus) override
	{
		_clicking = true;

		focus.shapePtr = new CircleShape();
		focus.shapeType = _s;
		focus.shapePtr->setFillColor(_focusC.f);
		focus.shapePtr->setOutlineColor(_focusC.ol);
		focus.shapePtr->setPosition(*_current);
		return 0;
	}
	shape mRelease(shape & focus, float radius = 0) override
	{
		_clicking = false;

		focus.shapePtr = new CircleShape(radius);
		focus.shapePtr->setOrigin(radius, radius);
		focus.shapePtr->setPosition(*_click);
		_listShape->push_back(shape(focus));
		return nullptr;
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
		{
			for (auto & s : _selected)
			{
				_offset = *_click - s->shapePtr->getPosition();
				s->shapePtr->setPosition(Vector2f(*_current - _offset));
			}
		}
	}
	void mUndrag() override
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
		string s = "Efface", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::Transparent, Color folC = Color::Red, float fol = 2, shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cRemove);
	}

	/// Opérations du mode
	void mPick() override
	{

	}
	void mLeave() override
	{

	}
	int mClick(shape & focus) override
	{
		_clicking = true;
		focus.shapePtr = new RectangleShape();
		focus.shapeType = sDefault;
		focus.shapePtr->setFillColor(_focusC.f);
		focus.shapePtr->setOutlineColor(_focusC.ol);
		focus.shapePtr->setPosition(*_current);

		if (!_listShape->empty())
		{
			_selected = selectShapes(focus);
			for (auto & s : _selected)
			{
				_offset = *_click - s->shapePtr->getPosition();
				s->shapePtr->setPosition(*_click - _offset);
			}
			return 1;
		}
		return 0;
	}
	shape mRelease(shape & focus, float radius = 0) override
	{
		_clicking = false;

		if (_selected.size() == 0)
			_selected = selectShapes(focus);

		for (auto & s : _selected)
			_listShape->erase(s);

		return nullptr;
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
		{
			focus.shapePtr = new RectangleShape(Vector2f(*_current - *_click));
			_offset = *_click - focus.shapePtr->getPosition();
			focus.shapePtr->setPosition(*_click);
		}
	}
	void mUndrag() override
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
		string s = "Sélection", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::White, Color folC = Color::Green, float fol = 3, shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cSelect);
	}

	/// Opérations du mode
	void mPick() override
	{

	}
	void mLeave() override
	{

	}
	int mClick(shape & focus) override
	{
		_selecting = true;
		focus.shapePtr = new RectangleShape();
		focus.shapeType = sDefault;
		focus.shapePtr->setFillColor(_focusC.f);
		focus.shapePtr->setOutlineColor(_focusC.ol);
		focus.shapePtr->setPosition(*_current);

		if (!_listShape->empty())
		{
			_selected = selectShapes(focus);
			for (auto & s : _selected)
			{
				_offset = *_click - s->shapePtr->getPosition();
				s->shapePtr->setPosition(*_click - _offset);
			}
			return 1;
		}
		return 0;
	}
	shape mRelease(shape & focus, float radius = 0) override
	{
		_selecting = false;
		focus.shapePtr = new RectangleShape(Vector2f(*_current - *_click));
		focus.shapePtr->setPosition(*_click);

		if (!_listShape->empty())
		{
			_selected = selectShapes(focus);
			for (auto & s : _selected)
			{
				_offset = *_click - s->shapePtr->getPosition();
				s->shapePtr->setPosition(*_click - _offset);
			}
		}
		return nullptr;
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
		{
			focus.shapePtr = new RectangleShape(Vector2f(*_current - *_click));
			_offset = *_click - focus.shapePtr->getPosition();
			focus.shapePtr->setPosition(*_click);

			for (auto & s : _selected)
			{
				_offset = *_click - s->shapePtr->getPosition();
				s->shapePtr->setPosition(Vector2f(*_current - _offset));
			}
		}
	}
	void mUndrag() override
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
		string s = "Lier", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::Black, Color folC = Color::Yellow, float fol = 1, shape * f = nullptr) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, f)
	{
		initMode(cLink);
	}

	/// Opérations du mode
	void mPick() override
	{

	}
	void mLeave() override
	{

	}
	int mClick(shape & focus) override
	{
		return 0;
	}
	shape mRelease(shape & focus, float radius = 0) override
	{
		return nullptr;
	}
	void mDrag(shape & focus) override
	{

	}
	void mUndrag() override
	{

	}
};


// 
void cursorPos(oButton * b, RenderWindow & screen);

