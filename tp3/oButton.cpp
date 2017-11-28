/*======================================================================================
Fichier:		oButton.cpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
Description:
======================================================================================*/


#include "oButton.h"



/// Initialiseurs

void oButton::initMode(cMode mode)
{
	assert(cDefault <= mode && mode <= cResize);
	_m = mode;
}

// Constructeur de la classe parente
oButton::oButton(float left, float top, float width, float height,
	float OL, Color fillC, Color OLC,
	string text, Font police, int tSize, Color fontC,
	Color focusC, Color focusOLC, float focusOL)
{
	assert(/// Peut changer si les boutons possèdent des icones ?
		text != ""								// Message du bouton
		&& 0 < tSize && tSize <= 25);			// Largeur de la police
	assert(0 - width <= left && left <= SCREENW + width	// Pos en x
		&& 0 - height <= top && top <= SCREENH + height	// Pos en y
		&& 0 <= width && width <= BW			// Largeur du bouton
		&& 0 <= height && height <= SCREENH);	// Hauteur du bouton
	assert(0 <= OL && OL <= 10					// Outline du bouton
		&& 0 <= focusOL && focusOL <= 10);		// Outline du focus

	_p = police;

	// Positionnement
	static float l = left + OL;		// Pos. en X cummulée des boutons
	static float t = top + OL;		// Pos. en Y cummulée des boutons

	// Position, millieu du texte, centre du bouton et ses dimmenssions
	Vector2f pos, mid, center, box;
	pos = Vector2f(l, t);			// Origine du bouton

	// Initiaise le text
	this->Text::Text(text, _p, tSize);
	Text::setFillColor(fontC);

	// Obtien les dimenssions nécessaires au bouton
	width = textDim(width, Text::getGlobalBounds().width, BW);
	height = textDim(height, Text::getGlobalBounds().height, BH);
	box = Vector2f(width + TOLW * 2, height + TOLH * 2);

	if (_nbB == NULL || _nbB < 1)	/// static ??
	{
		_nbB++;

	}

	// Prépare la position du prochain bouton
	if (HORIZONTALMENU)
		offsetButton(l, t, width, height, TOLW, OL, SCREENW);
	else
		offsetButton(t, l, height, width, TOLH, OL, SCREENH);

	// Positionne le texte
	mid = Vector2f(width / 2, height / 2);
	center = Vector2f(box.x / 2, box.y / 2 - TOLH / 2);
	Text::setOrigin(mid);
	Text::setPosition(pos);
	Text::move(center);

	// Initialise le bouton
	this->RectangleShape::RectangleShape(box);
	RectangleShape::setTextureRect((IntRect)FloatRect(pos, box));
	RectangleShape::setOrigin(center);
	RectangleShape::setPosition(pos);
	RectangleShape::move(center);

	RectangleShape::setFillColor(fillC);
	RectangleShape::setOutlineColor(OLC);
	RectangleShape::setOutlineThickness(OL);

	// Initialise le focus
	initFocus(Vector2f(), Vector2f());
	_focus.setFillColor(focusC);
	_focus.setOutlineColor(focusOLC);
	_focus.setOutlineThickness(focusOL);
}

oButton::~oButton()
{
	_nbB = 0; /// shared_ptr?
	RectangleShape::~RectangleShape();
	Text::~Text();
	_p.~Font();

	_m = cDefault;
	_clicking = false;
	_focus.~RectangleShape();
}

/// Manipulation du focus

void oButton::click(Vector2f pos)
{
	_clicking = true;
	initFocus(pos, pos);
}

RectangleShape oButton::unclick(Vector2f pos)
{
	_clicking = false;
	_focus.setOrigin(Vector2f(
		abs(_focus.getPoint(1).x - _focus.getOrigin().x),
		abs(_focus.getPoint(2).y - _focus.getOrigin().y)));

	return RectangleShape(_focus);
}


void oButton::drag(Vector2f pos)
{
	Vector2f factor = _focus.getOrigin() - pos;
	_focus.setScale(factor);
}

void oButton::undrag(Vector2f pos)
{

}

void oButton::initFocus(Vector2f origin, Vector2f pos)
{
	_focus.setOrigin(origin);	/// after pos ?
	_focus.setPosition(pos);	/// fusionner origin et pos?
	_focus.setSize(Vector2f());
}


void oButton::leave()
{
	Vector2f zero = Vector2f();
	_focus.setSize(zero);
	_focus.setPosition(zero);
	_focus.setRotation(0);
}


cMode oButton::getMode() const
{
	return _m;
}

bool oButton::gotMouse(RenderWindow & screen) const
{
	cout << endl << getString().toAnsiString()
		<< " at (" << RectangleShape::getPosition().x << ","
		<< RectangleShape::getPosition().y << "), the mouse was at : ("
		<< Mouse::getPosition(screen).x << ","
		<< Mouse::getPosition(screen).y << ")."
		<< endl << "\t" << RectangleShape::getTextureRect().left << ","
		<< RectangleShape::getTextureRect().top << ".";

	/// cout << RectangleShape::setGlobalBounds().left << "," << RectangleShape::getGlobalBounds().top;
	if (RectangleShape::getGlobalBounds().contains((Vector2f)Mouse::getPosition()))
		cout << "another method. for it to work, the button needs to be placed through transformation ?" << endl;

	if (RectangleShape::getTextureRect().
		contains(Mouse::getPosition(screen)))
		return true;
	return false;
}

// 
RectangleShape oButton::body()
{
	return static_cast<RectangleShape>(*this);
}

RectangleShape oButton::focus()
{
	return _focus;
}


///======///
/* Create */
///======///

void oB_create::initShape(sShape vertex)
{
	assert(sNone <= vertex && vertex <= sLine);
	_s = vertex;
}

sShape oB_create::getShape() const
{
	return _s;
}


///=====///
/* Créer */
///=====///




///=====///
/* Trait */
///=====///





///====///
/* Lier */
///====///




///=========///
/* Sélection */
///=========///





///======///
/* Efface */
///======///





// Information de la position de la souris
void cursorPos(oButton * b, RenderWindow & screen)
{
	cout << b->getString().toAnsiString()
		<< " at (" << b->RectangleShape::getPosition().x << ","
		<< b->RectangleShape::getPosition().y << "), the mouse was at : ("
		<< Mouse::getPosition(screen).x << ","
		<< Mouse::getPosition(screen).y << ").";
}