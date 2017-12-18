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
	_mode = nullptr;

	_click = _current = Vector2f();

	_clicking = false;
	_dragable = true;
	_selecting = false;
	_onZone = false;

	_zone = rStart;

	//Initialisation du focus
	initFocus();
}

// Destructeur
cursor::~cursor()
{
	_mode = nullptr;
	_clicking = _dragable = false;
	_click = _current = Vector2f();

	_zone = rStart;
}


/// Setteurs

void cursor::setMode(oButton * b)
{
	assert(b != nullptr);

	if (_mode != nullptr)
		_mode->mLeave();
	_mode = b;
	_mode->mPick();
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
	_focus.shapePtr = new RectangleShape(Vector2f(0, 0));

	_focus.shapePtr->setPosition(_current);	/// fusionner origin et pos?
	//_focus.shapePtr->setSize(Vector2f());
}

void cursor::setFocus(shape s)
{
	_focus = s;
}

void cursor::setSelected(bool b)
{
	_selecting = b;
}

void cursor::setOnZone(bool b)
{
	_onZone = b;
}


/// Clicker
int cursor::click(elemColors focusC)
{
	//oButton * b = nullptr;	// Bouton sous la souris
	/*if (onZone(rButton))
		b = searchForButton();*/

	_clicking = true;
	_click = _current;
	int nb = 0;
	cMode mode = _mode->getMode();

	if (mode == cDefault)
		return -1;

	// Pour les modes de création de formes
	if (mode == cCreate)
	{
		switch (_mode->getShape())
		{
		case sBox:
			nb = dynamic_cast<oB_cBox*>(_mode)->mClick(_focus);
			break;
		case sCircle:
			nb = dynamic_cast<oB_cCircle*>(_mode)->mClick(_focus);
			break;
			//case sLine:
			//	dynamic_cast<oB_cLine*>(_mode)->mClick(_focus);
			//	break;
		default:
			break;
		}
		_focus.shapePtr->setPosition(_click);
		return nb;
	}

	// Pour les modes ayant besoin d'une forme sélectionnée.
	switch (mode)
	{
	case cSelect:
		return dynamic_cast<oB_select*>(_mode)->mClick(_focus);
		break;
	case cLink:
		return dynamic_cast<oB_link*>(_mode)->mClick(_focus);
		break;
	case cRemove:
		return dynamic_cast<oB_remove*>(_mode)->mClick(_focus);
		break;
	case cMove:
		//return dynamic_cast<oB_move*>(_mode)->mClick(_focus);
		break;
	case cResize:
		//return dynamic_cast<oB_resize*>(_mode)->mClick(_focus);
		break;
	default:
		break;
	}

	/* Mode sans héritage */
	/*if (_mode != nullptr && !_onZone)
	{
		switch (_mode->getMode())
		{
		case cCreate:
			switch (_mode->getShape())
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
			if (_selecting)
			{
				_offset = _click - _focus.shapePtr->getPosition();
				_focus.shapePtr->setPosition(_click - _offset);
			}
			break;
		default:
			break;
		}
	}*/
}


// Va retourner la forme selon le mode du curseur
shape cursor::releaseClick()
{
	_clicking = false;
	float radius = distance2Points(_click, _current);
	int random = rand() % DBOARD.size();

	if (_mode == nullptr)
		return nullptr;

	switch (_mode->getMode())
	{
	case cCreate:
		switch (_mode->getShape())
		{
		case sBox:
			return dynamic_cast<oB_cBox*>(_mode)->mRelease(_focus, radius);
			break;
		case sCircle:
			return dynamic_cast<oB_cCircle*>(_mode)->mRelease(_focus, radius);
			break;
			//case sLine:
			//	return dynamic_cast<oB_cLine*>(_mode)->mRelease(_focus, radius);
			//	break;
		default:
			break;
		}
		_focus.shapePtr = new RectangleShape();
		break;

	case cSelect:
		return dynamic_cast<oB_select*>(_mode)->mRelease(_focus, radius);
		break;
	case cLink:
		return dynamic_cast<oB_link*>(_mode)->mRelease(_focus, radius);
		break;
	case cRemove:
		return dynamic_cast<oB_remove*>(_mode)->mRelease(_focus, radius);
		break;
	case cMove:
		//return dynamic_cast<oB_move*>(_mode)->mRelease(_focus, radius);
		break;
	case cResize:
		//return dynamic_cast<oB_resize*>(_mode)->mRelease(_focus, radius);
		break;
	default:
		break;
	}

	/* Version non héritée */
	//if (_mode != nullptr && !_onZone)
	//{
	//	float radius = distance2Points(_click, _current);
	//	int random = rand() % DBOARD.size();
	//	switch (_mode->getMode())
	//	{
	//	case cCreate:
	//		switch (static_cast<oB_create*>(_mode)->getShape())
	//		{
	//		case sBox:
	//			_focus.shapePtr = new RectangleShape(
	//				Vector2f(_current.x - _click.x, _current.y - _click.y));
	//			break;
	//		case sCircle:
	//			_focus.shapePtr = new CircleShape(radius);
	//			_focus.shapePtr->setOrigin(radius, radius);
	//			break;
	//		default:
	//			break;
	//		}
	//		_focus.shapePtr->setPosition(_click);
	//		//Couleur aleatoire
	//		srand(time(NULL));
	//		_focus.shapePtr->setFillColor(DBOARD.at(random));
	//		break;
	//	case cSelect:
	//		_selecting = false;
	//		break;
	//	default:
	//		break;
	//	}
	//	return _focus;
	//}
}


void cursor::drag()
{
	//Si le cursor est en mode click et qu'il n'est pas sur une zone (buttonstrip)
	if (!_clicking || _onZone)
		return;

	switch (_mode->getMode())
	{
	case cCreate:
		switch (_mode->getShape())
		{
		case sBox:
			dynamic_cast<oB_cBox*>(_mode)->mDrag(_focus);
			break;
		case sCircle:
			dynamic_cast<oB_cCircle*>(_mode)->mDrag(_focus);
			break;
			//case sLine:
			//	dynamic_cast<oB_cLine*>(_mode)->mDrag(_focus);
			//	break;
		default:
			break;
		}
		break;

	case cSelect:
		dynamic_cast<oB_select*>(_mode)->mDrag(_focus);
		break;
	case cLink:
		dynamic_cast<oB_link*>(_mode)->mDrag(_focus);
		break;
	case cRemove:
		dynamic_cast<oB_remove*>(_mode)->mDrag(_focus);
		break;
	case cMove:
		//dynamic_cast<oB_move*>(_mode)->mDrag(_focus);
		break;
	case cResize:
		//dynamic_cast<oB_resize*>(_mode)->mDrag(_focus);
		break;
	default:
		break;
	}


	/* Options */
	//if (_clicking && !_onZone)
	//{
	//	//Rayon pour le cercle
	//	int radius = distance2Points(_click, _current);
	//	switch (_mode->getMode())
	//	{
	//	case cCreate:
	//		switch (static_cast<oB_create*>(_mode)->getShape())
	//		{
	//		case sBox:
	//			_focus.shapePtr = new RectangleShape(
	//				Vector2f(_current.x - _click.x, _current.y - _click.y));
	//			_focus.shapePtr->setPosition(_click);
	//			break;
	//		case sCircle:
	//			_focus.shapePtr = new CircleShape(radius);
	//			_focus.shapePtr->setOrigin(radius, radius);
	//			_focus.shapePtr->setPosition(_click);
	//			break;
	//		default:
	//			break;
	//		}
	//		break;
	//	case cSelect:
	//		if (_selecting)
	//			_focus.shapePtr->setPosition(
	//				Vector2f(_current.x - _offset.x, _current.y - _offset.y));
	//		break;
	//	default:
	//		break;
	//	}
	//}

}


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

//Retourne le focus
shape cursor::getFocus() const
{
	assert(_mode != nullptr);
	return _focus;
}

Vector2f * cursor::getClick() { return &_click; }

Vector2f * cursor::getCurrent() { return &_current; }

bool cursor::isOnZone() const
{
	return _onZone;
}

/// Affichage
bool cursor::onZone(FloatRect z, RenderWindow & w)
{
	if (z.contains((Vector2f)getPosition(w)))
	{
		///_zone = z;
		return true;
	}
	return false;
}

