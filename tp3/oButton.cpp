/*======================================================================================
Fichier:		oButton.cpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
======================================================================================*/


#include "oButton.h"


// Constructeur de la classe parente
oButton::oButton(float left, float top, float width, float height,
	float OL, Color fillC, Color OLC,
	string text, Font police, int tSize, Color fontC,
	Color focusC, Color focusOLC, float focusOL, Shape * focus)
{
	assert(/// Peut changer si les boutons possèdent des icones ?
		text != ""								// Message du bouton
		&& 0 < tSize && tSize <= 25);			// Largeur de la police
	assert(0 - width <= left && left <= SCREENW + width	// Pos en x
		&& 0 - height <= top && top <= SCREENH + height	// Pos en y
		&& 0 <= width && width <= BW			// Largeur du bouton
		&& 0 <= height && height <= SCREENH);	// Hauteur du bouton
	assert(0 <= OL && OL <= 20					// Outline du bouton
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

	// Positionne le texte
	mid = Vector2f(width / 2, height / 2);
	center = Vector2f(box.x / 2, box.y / 2/* - TOLH / 2*/);
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
	setFocus(focusC, focusOLC, focusOL, focus); /// 
}

oButton::~oButton()
{
	_nbB = 0; /// shared_ptr?
	RectangleShape::~RectangleShape();
	Text::~Text();
	//_p.~Font();

	_m = cDefault;
	_clicking = false;
	_focusC = _focusOLC = Color();
	_focusOL = 0;
	_focus = nullptr;
}

/// Initialiseurs
void oButton::initMode(cMode mode)
{
	assert(cDefault <= mode && mode <= cResize);
	_m = mode;
}

/// Setteurs

void oButton::setColors(Color fillC, Color OLC)
{
	RectangleShape::setFillColor(fillC);
	RectangleShape::setOutlineColor(OLC);
}

void oButton::setFocus(Color focusC, Color focusOLC, 
	float focusOL, Shape * focus) /// ?
{
	_focusC = focusC;
	_focusOLC = focusOLC;
	_focusOL = focusOL;
	_focus = focus;
}

void oButton::move(Vector2f pos)
{
	RectangleShape::setPosition(pos);
	Text::setPosition(pos);
}

/// Manipulation du focus

void oButton::click(Vector2f pos)
{
	_clicking = true;
}

int oButton::release(/*Vector2f pos*/)
{
	_clicking = false;
	_focus->setOrigin(Vector2f(
		abs(_focus->getPoint(1).x - _focus->getOrigin().x),
		abs(_focus->getPoint(2).y - _focus->getOrigin().y)));

	return 1;
}


void oButton::drag(Vector2f pos)
{
	
	_focus->setScale(pos);
}

void oButton::undrag(Vector2f pos)
{

}


// Met à jour l'origine du rectangle et 

void oButton::resize(Vector2f dim)	/// Trop petit ??
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

void oButton::initOrigins(bCorner corner)
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

/// ?
void oButton::scaleFocus(Vector2f diff)
{
	_focus->setScale(diff);
}


void oButton::leave()
{
	_focus->~Shape();
}

/// Getteurs

float oButton::getW()
{
	return getP(bUpperRight).x - getP(bUpperLeft).x;
}

float oButton::getH()
{
	return getP(bLowerLeft).y - getP(bUpperLeft).y;
}



/// Getteurs

Vector2f oButton::getP(bCorner p)
{
	if (p == bCenter)
	{
		Vector2f diagonal = RectangleShape::getPoint(bLowerRight);
		return Vector2f(diagonal.x / 2, diagonal.y / 2);
	}
	return RectangleShape::getPoint(p);
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
RectangleShape oButton::getBody()
{
	return static_cast<RectangleShape>(*this);
}

Text oButton::getText()
{
	return static_cast<Text>(*this);
}


///======///
/* Create */
///======///

void oB_create::initShape(sShape vertex)
{
	assert(sBox <= vertex && vertex <= sCOUNT);
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