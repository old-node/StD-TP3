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
const float SCREENW = 800;				// Largeur de l'écran /// inclus à partir du (main) ?
const float SCREENH = 800;				// Hauteur de l'écran

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
static float textDim(float & p, float t, float MAX)
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

	vector<selection> * _selected;	// 
	elemColors _elemC;		// Couleurs à appliquer aux formes.
	elemColors _focusC;		// Couleurs à appliquer au focus
	float _focusOL;			// 

	list<shape> * _listShape;// Pointeur sur la liste des formes de l'application.

	void resetButtonColor()
	{
		RectangleShape::setFillColor(_oColor.f);
		RectangleShape::setOutlineColor(_oColor.ol);
		Text::setFillColor(_oColor.t);
	}
	void setButtonColor(Color fill, Color outline = Color::Black, Color text = Color::Black)
	{
		/// Make text white if fill is too dark??
		RectangleShape::setFillColor(fill);
		RectangleShape::setOutlineColor(outline);
		Text::setFillColor(text);
	}
	/// Initialiseur
	void initMode(cMode mode);
	void makeFocusRectangle(shape & focus)
	{
		focus.shapePtr = new RectangleShape(Vector2f(*_current - *_click));
		focus.shapePtr->setPosition(*_click);
		setFocus(focus);
	}
	void setFocus(shape & focus)
	{
		focus.shapeType = _s;
		focus.shapePtr->setFillColor(_elemC.f);
		focus.shapePtr->setOutlineColor(_focusC.ol);
	}
	void resetFocus(shape & focus)
	{
		_clicking = false;
		focus.shapePtr = new RectangleShape();
		focus.shapeType = sDefault;
		//focus.shapePtr->setFillColor(Color::White);
		//focus.shapePtr->setOutlineColor(Color::Black);
		focus.shapePtr->setPosition(*_current);
	}
	void moveSelected()
	{
		for (auto & s : *_selected)
		{
			s._it->shapePtr->move(*_current - s._o);
		}
	}

	void resetSelection()
	{
		for (auto & s : *_selected)
			s.pop();

		_selected->clear();
	}
	// Cherche une shape dans le vecteur et retourne l'iterateur ou la shape est
	// selon une position de la sourie
	void selectShapes(shape focus)
	{
		if (_listShape->empty())
			return;

		bool same = false;
		list<shape>::iterator it = _listShape->end();
		FloatRect zone = focus.shapePtr->getGlobalBounds();
		zone.width = max(zone.width, (float)1);
		zone.height = max(zone.height, (float)1);

		do
		{
			same = false;
			it--;
			if (it->shapePtr->getGlobalBounds().intersects(zone))
			{
				// Vérifie que la forme ciblée n'est pas déjà sélectionnée
				for (auto & s : *_selected)
				{
					if (it == s._it)
					{
						same = true;
						break;
					}
				}

				if (!same)
				{
					_selected->push_back(it);
					_selected->back().setOffset(*_click);
					it->shapePtr->setFillColor(_elemC.f);
					it->shapePtr->setOutlineColor(_elemC.ol);
					// Si la zone de sélection est étroite,
					//	ne retourner qu'une seule forme.
					if (zone.width < 4 && zone.height < 4)
						return;
				}
			}
		} while (it != _listShape->begin());

		// Si la boucle est fini sans qu'on retourne l'iterateur,
		// on retourne l'iterateur a la fin
		it = _listShape->end();	/// Encore utile??
		return;
	}
public:
	/// Constructeur
	oButton(float left, float top, float width, float height,
		float outline, Color fillC, Color OLC,
		string text, Font police, int charSize, Color fontC,
		Color focusC = Color::Transparent, Color focusOLC = Color::Black, float focusOL = 0,
		Color elemFillC = Color::Transparent, Color elemOLC = Color::Black, Color elemFontC = Color::Black);
	~oButton();

	/// Setteurs
	void initCursorData(Vector2f * current, Vector2f * click, list<shape> * listShape, vector<selection> * selected)
	{
		_current = current;
		_click = click;
		_listShape = listShape;
		_selected = selected;
	}
	void setColors(Color fillC = FILLC, Color OLC = OUTLC);
	void setFocus(Color focusC = Color::Transparent, Color focusOLC = Color::Yellow, float focusOL = 1);

	void move(Vector2f pos = Vector2f());
	void resize(Vector2f dim = Vector2f(1, 1));
	// Met à jour l'origine du rectangle et ...
	void initOrigins(bCorner corner = bUpperLeft);
	///void scaleFocus(Vector2f diff)	{ _focus->shapePtr->setScale(diff); }

	/// Opérations virtuelles des modes
	virtual int mPick() = 0;
	virtual void mLeave(shape & focus) = 0;
	virtual int mClick(shape & focus, elemColors focusC, bool defaultC) = 0;
	virtual void mRelease(shape & focus, float radius) = 0;
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
		Color fC, Color folC, float fol,
		Color eC, Color eOLC, Color eFC) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
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
		Color fC = CBOX, Color folC = Color::Black, float fol = 1,
		Color eC = Color::Green, Color eOLC = Color::Black, Color eFC = Color::Blue) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
	{
		initShape(sBox);
	}

	/// Opérations du mode
	int mPick() override
	{
		resetSelection();
		return 0;
	}
	void mLeave(shape & focus) override
	{
		resetFocus(focus);
	}
	int mClick(shape & focus, elemColors focusC, bool defaultC) override
	{
		_clicking = true;

		focus.shapePtr = new RectangleShape();
		
		if (focusC != elemColors())
			focusC.apply(focus);
		else
			setFocus(focus);

		return 0;
	}
	void mRelease(shape & focus, float radius = 0) override
	{
		_clicking = false;

		Vector2f dim = Vector2f(*_current - *_click);
		focus.shapePtr = new RectangleShape(dim);

		dim = Vector2f((float)dim.x / 2, (float)dim.y / 2);
		focus.shapePtr->setPosition(*_click + dim);
		focus.shapePtr->setOrigin(dim);
		_listShape->push_back(shape(focus));

		resetFocus(focus);
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
		Color fC = Color::Yellow, Color folC = CLINE, float fol = 2,
		Color eC = Color::Blue, Color eOLC = Color::Magenta, Color eFC = Color::Green) :
		oB_create(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
	{
		initShape(sCircle);
	}

	/// Opérations du mode
	int mPick() override
	{
		resetSelection();
		return 0;
	}
	void mLeave(shape & focus) override
	{
		resetFocus(focus);
	}
	int mClick(shape & focus, elemColors focusC, bool defaultC) override
	{
		_clicking = true;

		focus.shapePtr = new CircleShape();
		
		if (focusC != elemColors())
			focusC.apply(focus);
		else
			setFocus(focus);

		return 0;
	}
	void mRelease(shape & focus, float radius = 0) override
	{
		_clicking = false;

		focus.shapePtr = new CircleShape(radius);
		focus.shapePtr->setOrigin(radius, radius);
		focus.shapePtr->setPosition(*_click);
		_listShape->push_back(shape(focus));
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
			moveSelected();
	}
	void mUndrag() override {}
};

// Classe du bouton d'option pour lier des éléments
class oB_link : public oButton
{
private:
protected:
public:
	oB_link(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = Color::Yellow,
		string s = "Liaison", Font p = D_F, int c = TSIZE, Color sC = OUTLC,
		Color fC = OUTLC, Color folC = Color::Yellow, float fol = 1,
		Color eC = Color::White, Color eOLC = Color::Magenta, Color eFC = OUTLC) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
	{
		initMode(cLink);
	}

	/// Opérations du mode
	int mPick() override { return 0; }
	void mLeave(shape & focus) override
	{
		resetFocus(focus);
	}
	int mClick(shape & focus, elemColors focusC, bool defaultC) override
	{
		/// Permet de lier deux ou plus ?? formes
		setFocus(focus);
		return 0;
	}
	void mRelease(shape & focus, float radius = 0) override {}
	void mDrag(shape & focus) override {}
	void mUndrag() override {}
};


// Classe du bouton d'option pour effacer des formes
class oB_remove : public oButton
{
private:
protected:
public:
	oB_remove(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = Color::Red,
		string s = "Effacer", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color(201, 18, 18, 50), Color folC = Color(255, 9, 9, 255), float fol = 2,
		Color eC = Color::Red, Color eOLC = Color::Black, Color eFC = Color::White) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
	{
		initMode(cRemove);
	}

	/// Opérations du mode
	int mPick() override
	{
		if (_selected->empty())
			return 0;

		// Efface les formes préalablement sélectionnés.
		for (auto & s : *_selected)
			_listShape->erase(s._it);

		_selected->clear();

		return 0;
	}
	void mLeave(shape & focus) override
	{
		resetFocus(focus);
	}
	int mClick(shape & focus, elemColors focusC = elemColors(), bool defaultC = true) override
	{
		_clicking = true;
		makeFocusRectangle(focus);

		// Sélectionne les formes sous le curseur
		if (!_listShape->empty())
			selectShapes(focus);

		return 0;
	}
	void mRelease(shape & focus, float radius = 0) override
	{
		mDrag(focus);

		if (_selected->empty()
			|| focus.shapePtr->getGlobalBounds().height > 4
			|| focus.shapePtr->getGlobalBounds().width > 4)
			selectShapes(focus);

		for (auto & s : *_selected)
			_listShape->erase(s._it);

		resetFocus(focus);
		_selected->clear();
	}
	void mDrag(shape & focus) override
	{
		if (_clicking)
			makeFocusRectangle(focus);
		//else
		//	mUndrag();	/// Exemple d'utilisation de mUndrag
	}
	void mUndrag() override
	{
		cout << endl << "Undrag" << endl;
	}
};


// Classe de base des boutons de création
class oB_select : public oButton
{
private:
protected:
public:
	oB_select(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = Color::Green,
		string s = "Sélection", Font p = D_F, int c = TSIZE, Color sC = Color::Black,
		Color fC = Color::White, Color folC = Color::Green, float fol = 3,
		Color eC = Color::Green, Color eOLC = Color::Blue, Color eFC = Color::White) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC, folC, fC, fol, eC, eOLC, eFC)
	{
		initMode(cSelect);
	}

	/// Opérations du mode
	int mPick() override { return 0; }
	void mLeave(shape & focus) override
	{
		_selecting = false;
		resetFocus(focus);
	}
	int mClick(shape & focus, elemColors focusC, bool defaultC) override
	{
		_clicking = _selecting = true;
		makeFocusRectangle(focus);

		for (auto & s : *_selected)
			s.setOffset(*_click);

		if (!_listShape->empty())
			selectShapes(focus);

		return 0;
	}
	void mRelease(shape & focus, float radius = 0) override
	{
		/// check if ny selection was made before releselecting more??
		mDrag(focus);

		// version : 
		if (!_listShape->empty())
		{
			selectShapes(focus);
			/*for (auto & s : *_selected)
			{
				s._it->shapePtr->setFillColor(_focusC.f);
				s._it->shapePtr->setOutlineColor(_elemC.ol);
			}*/
		}

		// 
		if (_selected->empty())
			_selecting = false;

		resetFocus(focus);
	}
	void mDrag(shape & focus) override
	{
		if (!_clicking)
			return;

		makeFocusRectangle(focus);

		if (_selected->size() == 1)
			moveSelected();

	}
	void mUndrag() override
	{

	}
};

// Classe du bouton d'option pour charger un dessin
class oB_save : public oButton
{
private:
protected:
public:
	oB_save(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = OUTLC,
		string s = "Sauver", Font p = D_F, int c = TSIZE, Color sC = Color::Green) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC)
	{
		initMode(cSave);
	}

	/// Opérations du mode
	int mPick() override
	{ 
		// Fait la sauvegarde du dessin actuel.
		return cSave;
	}
	void mLeave(shape & focus) override {}
	int mClick(shape & focus, elemColors focusC = elemColors(), bool defaultC = true) override { return 0; }
	void mRelease(shape & focus, float radius = 0) override {}
	void mDrag(shape & focus) override {}
	void mUndrag() override {}
};

// Classe du bouton d'option pour charger un dessin
class oB_load : public oButton
{
private:
protected:
public:
	oB_load(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = OUTLC,
		string s = "Charger", Font p = D_F, int c = TSIZE, Color sC = Color::Blue) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC)
	{
		initMode(cLoad);
	}

	/// Opérations du mode
	int mPick() override
	{
		// Fait appel à la sélection différent dessin ou d'une version précédente.
		return cLoad;
	}
	void mLeave(shape & focus) override {}
	int mClick(shape & focus, elemColors focusC = elemColors(), bool defaultC = true) override { return 0; }
	void mRelease(shape & focus, float radius = 0) override {}
	void mDrag(shape & focus) override {}
	void mUndrag() override {}
};

// Classe du bouton d'option pour retourner au menu principal.
class oB_menu : public oButton
{
private:
protected:
public:
	oB_menu(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = OUTLC,
		string s = "Menu", Font p = D_F, int c = TSIZE, Color sC = Color::Green) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC)
	{
		initMode(cMenu);
	}

	/// Opérations du mode
	int mPick() override
	{
		// Retourner au menu principal
		return cMenu;
	}
	void mLeave(shape & focus) override {}
	int mClick(shape & focus, elemColors focusC = elemColors(), bool defaultC = true) override { return 0; }
	void mRelease(shape & focus, float radius = 0) override {}
	void mDrag(shape & focus) override {}
	void mUndrag() override {}
};

// Classe du bouton d'option pour quitter l'application
class oB_quit : public oButton
{
private:
protected:
public:
	oB_quit(float l = 0, float t = 0, float w = 0, float h = 0,
		float o = 1, Color bC = FILLC, Color olC = OUTLC,
		string s = "Quitter", Font p = D_F, int c = TSIZE, Color sC = Color::Red) :
		oButton(l, t, w, h, o, bC, olC, s, p, c, sC)
	{
		initMode(cQuit);
	}

	/// Opérations du mode
	int mPick() override
	{
		// Fermer l'application
		return cQuit;
	}
	void mLeave(shape & focus) override {}
	int mClick(shape & focus, elemColors focusC = elemColors(), bool defaultC = true) override { return 0; }
	void mRelease(shape & focus, float radius = 0) override {}
	void mDrag(shape & focus) override {}
	void mUndrag() override {}
};


// 
void cursorPos(oButton * b, RenderWindow & screen);

