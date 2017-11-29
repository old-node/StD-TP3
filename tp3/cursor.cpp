/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:
======================================================================================*/


#include "cursor.h"



// Constructeur
cursor::cursor(RenderWindow & window) : _w(window)
{
	_bOptions.push_back(new oB_cBox());
	_bOptions.push_back(new oB_cLine());
	_bOptions.push_back(new oB_remove());
	_bOptions.push_back(new oB_link());
	_bOptions.push_back(new oB_select());

	_mode = nullptr;
	_click = _current = Vector2f();
	_clicking = false;
	_dragable = true;

	_zone = rStart;
	if (HORIZONTALMENU)
		_zones[rRegion::rButton] = FloatRect(
			Vector2f(), Vector2f((float)SCREENW, _bOptions.back()->getP(2).y));
	else
		_zones[rRegion::rButton] = FloatRect(
			Vector2f(), Vector2f(_bOptions.back()->getP(2).x, (float)SCREENH));
}

// Destructeur
cursor::~cursor()
{
	_bOptions.clear();

	_mode = nullptr;
	_clicking = _dragable = false;
	_click = _current = Vector2f();

	_zone = rStart;
	//for (cRegion i = rNone; i != rDraw; /*i++*/)
	//	_zones[i] = FloatRect();
}


/// Setteurs

void cursor::setMode(oButton * b)
{
	assert(b != nullptr);

	if (_mode != nullptr)
		_mode->leave();
	_mode = b;
	//_mode->pick(); /// ?
}

void cursor::setClick(Vector2f click)
{
	_click = click;
}


/// Manipulations du focus

void cursor::setCurrent(Vector2f current)
{
	_current = current;
}

void cursor::initFocus(Vector2f current)
{
	float x = current.x - _click.x;
	float y = current.x - _click.x;

	_mode->scaleFocus(_click - current);
}

 void cursor::setFocus(Vector2f current)
{
	if (_mode != nullptr)
	{

		_mode->scaleFocus(_click - current);
	}
}


/// Clicker
void cursor::click(Vector2i click)
{
	oButton * b = nullptr;	// Bouton sous la souris
	if (onZone(rButton))
		b = searchForButton();

	_clicking = true;
	_click = (Vector2f)click;

	// Si un bouton est sélectionné
	if (b != nullptr)
	{
		setMode(b);
	}
	// Initialise le focus
	if (_mode != nullptr)
	{
		_mode->initFocus(_click, _click);
		_mode->click();
	}
}

void cursor::drag(Vector2i mouse)
{
	if (_clicking)
	{
		if (_zone != rStart && _zone != rButton)
		{
			_mode->RectangleShape::setFillColor(Color::White);
			drawButton(_mode);
		}
		else if (_zone == rButton)
			return;
	}
	else if (_mode != nullptr)
	{
		Vector2f m = (Vector2f)mouse;
		_current = m;
		setFocus(m);
	}
}

int cursor::unclick(Vector2i current)
{
	_clicking = false;
	if (_mode != nullptr)
	{
		setFocus((Vector2f)current);
		switch (_mode->getMode())
		{
		case cCreate:
			return onZone(rDraw);
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}


/// Getteurs


/// Getteurs

 bool cursor::isClicking(Mouse::Button it)
{
	return (isButtonPressed(it) && _clicking);
}

bool cursor::getClicking() const { return _clicking; }

oButton * cursor::getMode() const { return _mode; }

// Retourner un int au lieu ?*

 RectangleShape * cursor::getFocus() const
{
	assert(_mode != nullptr);
	return _mode->getFocus();
}

Vector2f cursor::getClick() const { return _click; }

Vector2f cursor::getCurrent() const { return _current; }

/// Affichage
// Procède à une méthode avec chaqu'un des boutons

 void cursor::drawMenu()
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


/// Affichage

 void cursor::drawButton(oButton * oB)
{
	_w.draw(oB->body());
	_w.draw(oB->text());

}

void cursor::drawFocus()
{
	if (_mode != nullptr)
		_w.draw(_mode->focus());

}

 bool cursor::onZone(rRegion z)
{
	if (_zones[z].contains((Vector2f)getPosition(_w)))
	{
		_zone = z;
		return true;
	}
	return false;
}

