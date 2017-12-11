/*======================================================================================
Fichier:		cursor.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
======================================================================================*/


#include "cursor.h"



///Va dans painter.cpp???
// Recherche si un bouton est sous la souris

//oButton * cursor::searchForButton()
//{
//	for (auto & b : _bOptions)
//		if (b->gotMouse(_w))
//			return b;
//	return nullptr;
//}

// Constructeur
cursor::cursor()
{
	_bOptions.push_back(new oB_cBox());
	_bOptions.push_back(new oB_cCircle());
	_bOptions.push_back(new oB_remove());
	_bOptions.push_back(new oB_link());
	_bOptions.push_back(new oB_select());

	_mode = _bOptions[0];

	_click = _current = Vector2f();

	_clicking = false;

	_dragable = true;
	
	_zone = rStart;

	//Initialisation du focus
	initFocus();

	//if (HORIZONTALMENU)
	//	_zones[rRegion::rButton] = FloatRect(
	//		Vector2f(), Vector2f((float)SCREENW, _bOptions.back()->getP(2).y));
	//else
	//	_zones[rRegion::rButton] = FloatRect(
	//		Vector2f(), Vector2f(_bOptions.back()->getP(2).x, (float)SCREENH));
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

void cursor::initFocus()
{
	//_focus.setOrigin(_current);	/// sa bug 
	_focus.shapePtr = new RectangleShape(Vector2f(0,0));

	_focus.shapePtr->setPosition(_current);	/// fusionner origin et pos?
	//_focus.shapePtr->setSize(Vector2f());
}

void cursor::setFocus(shape s)
{
	_focus = s;
}


/// Clicker
void cursor::click()
{
	//oButton * b = nullptr;	// Bouton sous la souris
	/*if (onZone(rButton))
		b = searchForButton();*/

	_clicking = true;
	_click = _current;
	
	if (_mode != nullptr)
	{
		switch (_mode->getMode())
		{
		case cCreate:
			switch (static_cast<oB_create*>(_mode)->getShape())
			{
			case sBox:
				_focus.shapePtr = new RectangleShape();
				_focus.shapeType = sBox;
				break;
			case sCircle:
				_focus.shapePtr = new CircleShape();
				_focus.shapeType = sCircle;
				break;
			default:
				break;
			}
			_focus.shapePtr->setPosition(_click);
			break;
		case cSelect:
			_offSet = _click - Vector2f(_focus.shapePtr->getPosition().x/2 + (_focus.shapePtr->getLocalBounds().width/2),
				_focus.shapePtr->getPosition().y/2 + (_focus.shapePtr->getLocalBounds().height/2));
			break;
		default:
			break;
		}
	}
}

void cursor::drag(Vector2i mouse)
{
	if (_clicking)
	{
		//Rayon pour le cercle
		int radius = distance2Points(_click, _current); 

		switch (_mode->getMode())
		{
		case cCreate:
			switch (static_cast<oB_create*>(_mode)->getShape())
			{
			case sBox:
				_focus.shapePtr = new RectangleShape(_current - _click);
				_focus.shapePtr->setPosition(_click);
				break;
			case sCircle:
				_focus.shapePtr = new CircleShape(radius);
				_focus.shapePtr->setOrigin(radius, radius);
				_focus.shapePtr->setPosition(_click);
				break;
			default:
				break;
				
			}
			break;
		case cSelect:
			_focus.shapePtr->move(_current - _focus.shapePtr->getPosition() - _offSet);
			break;	
		default:
			break;
		}
	}

}


//Va retourner la forme selon le mode du curseur
shape cursor::releaseClick()
{
	_clicking = false;
	if (_mode != nullptr)
	{
		int radius = distance2Points(_click,_current);
		int random = rand() % DBOARD.size();
		switch (_mode->getMode())
		{
		case cCreate:
			switch (static_cast<oB_create*>(_mode)->getShape())
			{
			case sBox:
				_focus.shapePtr = new RectangleShape(_current - _click);
				break;
			case sCircle:
				_focus.shapePtr = new CircleShape(radius);
				_focus.shapePtr->setOrigin(radius, radius);
				break;
			default:
				break;
			}
			_focus.shapePtr->setPosition(_click);
			//Couleur aleatoire
			srand(time(NULL));
			_focus.shapePtr->setFillColor(DBOARD.at(random));
			break;
		default:
			break;
		}


		
		return _focus;
	}
}


/// Getteurs


/// Getteurs

bool cursor::isClicking(Mouse::Button it)
{
	return (isButtonPressed(it) && _clicking);
}

bool cursor::getClicking() const { return _clicking; }

cMode cursor::getModeCurs() const 
{ 
	return _mode->getMode();
}

// Retourner un int au lieu ?*

//Retourne le focus
shape cursor::getFocus() const
{
	assert(_mode != nullptr);
	return _focus;
}

Vector2f cursor::getClick() const { return _click; }

Vector2f cursor::getCurrent() const { return _current; }

void cursor::changeMode()
{
	if (_mode == _bOptions[0])
		_mode = _bOptions[4];
	else
		_mode = _bOptions[0];
}

/// Affichage
// Procède à une méthode avec chaqu'un des boutons

//void cursor::drawMenu()
//{
//	for (auto & b : _bOptions)	// Pour chaque bouton d'options
//	{
//		if (b->gotMouse(_w)) /// b->gotMouse(_window)
//		{
//			drawButton(b);
//			cursorPos(b, _w);
//		}
//	}
//}

///// Affichage
//
//void cursor::drawButton(oButton * oB)
//{
//	_w.draw(oB->body());
//	_w.draw(oB->text());
//
//}
//
//void cursor::drawFocus()
//{
//	if (_mode != nullptr)
//		_w.draw(_focus);
//}

//bool cursor::onZone(rRegion z)
//{
//	if (_zones[z].contains((Vector2f)getPosition(_w)))
//	{
//		_zone = z;
//		return true;
//	}
//	return false;
//}

