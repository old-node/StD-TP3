/*======================================================================================
Fichier:		oButton.cpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
Description:
======================================================================================*/


#include "oButton.h"


// Constructeur de la classe parente
oButton::oButton(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC,
	int charSize, float outline) :
	RectangleShape(Vector2f(width, height)),
	Text(text, font, charSize)
{
	//RectangleShape::setOrigin(Vector2f(left, top));
	RectangleShape::setPosition(Vector2f(left, top));
	RectangleShape::setFillColor(fillC);
	RectangleShape::setOutlineColor(outlineC);
	RectangleShape::setOutlineThickness(outline);

	//Text::setOrigin(Vector2f(left, top));
	Text::setPosition(left + 3, top + 3);
	Text::setFillColor(fontC);

	//_focus.setOrigin(Vector2f());
	setFocus(Vector2f(), Vector2f());
	_focus.setFillColor(Color::Transparent);
}


void oButton::setFocus(Vector2f pos, Vector2f size)
{
	_focus.setPosition(pos);
	_focus.setSize(size);
}


cMode oButton::getMode() const
{
	return _m;
}

bool oButton::gotMouse(RenderWindow & screen) const
{
	if (RectangleShape::getTextureRect().
		contains(sf::Mouse::getPosition(screen)))
		return true;
	return false;
}


void oButton::draw(RenderWindow & window) const
{
	window.draw(static_cast<RectangleShape>(*this));
	window.draw(static_cast<Text>(*this));
	//Text::Drawable::draw(window, RenderStates::Default);
}

void oButton::drawFocus(RenderWindow & window) const
{
	window.draw(_focus);
}







void oB_create::setMode(cMode mode)
{
	_m = mode;
}
oB_create::oB_create(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oButton(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setMode();
}


shape oB_create::getShape() const
{
	return _s;
}




void oB_cBox::setShape(shape vertex)
{
	_s = vertex;
}
void oB_cBox::setFocusColor(Color fillC, Color outlineC, float outlineT)
{
	_focus.setFillColor(fillC);
	_focus.setOutlineColor(outlineC);
	_focus.setOutlineThickness(outlineT);
}
oB_cBox::oB_cBox(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oB_create(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setShape();
	setFocusColor();
}








void oB_cLine::setShape(shape vertex)
{
	_s = vertex;
}

void oB_cLine::setFocusColor(Color fillC, Color outlineC, float outlineT)
{
	_focus.setFillColor(fillC);
	_focus.setOutlineColor(outlineC);
	_focus.setOutlineThickness(outlineT);
}

oB_cLine::oB_cLine(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oB_create(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setShape();
	setFocusColor();
}




void oB_remove::setMode(cMode mode)
{
	_m = mode;
}

void oB_remove::setFocusColor(Color fillC, Color outlineC, float outlineT)
{
	_focus.setFillColor(fillC);
	_focus.setOutlineColor(outlineC);
	_focus.setOutlineThickness(outlineT);
}

oB_remove::oB_remove(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oButton(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setMode();
	setFocusColor();
}




void oB_select::setMode(cMode mode)
{
	_m = mode;
}

void oB_select::setFocusColor(Color fillC, Color outlineC, float outlineT)
{
	_focus.setFillColor(fillC);
	_focus.setOutlineColor(outlineC);
	_focus.setOutlineThickness(outlineT);
}

oB_select::oB_select(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oButton(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setMode();
	setFocusColor();
}



void oB_link::setMode(cMode mode)
{
	_m = mode;
}

void oB_link::setFocusColor(Color fillC, Color outlineC, float outlineT)
{
	_focus.setFillColor(fillC);
	_focus.setOutlineColor(outlineC);
	_focus.setOutlineThickness(outlineT);
}

oB_link::oB_link(float left, float top, float width, float height,
	Font & font, string text, Color fontC, Color fillC, Color outlineC) :
	oButton(left, top, width, height, font, text, fontC, fillC, outlineC)
{
	setMode();
	setFocusColor();
}
