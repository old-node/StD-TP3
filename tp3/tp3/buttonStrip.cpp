/*======================================================================================
Fichier:		buttonStrip.cpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			29-11-2017
======================================================================================*/


#include "buttonStrip.h"



///==========================///
/* Classe de base buttonStrip */
///==========================///

/// Initialisation
// Constructeur
buttonStrip::buttonStrip(bool fromTopOrLeft, bool reverseOrder,
	Vector2f initPos, Vector2f limitPos, bool fixed, Vector2f minDim)
{
	assert(0 <= initPos.x && 0 <= initPos.y
		&& 0 <= limitPos.x && 0 <= limitPos.y
		&& 1 <= minDim.x && 1 <= minDim.y);

	_normalScope = fromTopOrLeft;
	if (_normalScope)
		assert(initPos.y <= limitPos.y);
	else
		assert(initPos.y >= limitPos.y);

	_normalInterval = reverseOrder;
	if (_normalInterval)
		assert(initPos.x <= limitPos.x);
	else
		assert(initPos.x >= limitPos.x);

	_overlay.setOutlineThickness(1);
	_overlay.setOrigin(Vector2f(-1, -1));
	_overlay.setPosition(_initPos);
	_overlay.setFillColor(Color(100, 100, 100, 255));
	_overlay.setOutlineColor(Color::Black);

	_buttonPos.x = initPos.x + TOLW;
	_buttonPos.y = initPos.y + TOLH;
	_initPos = _buttonPos;

	float ol; // = _hinge.RectangleShape::getOutlineThickness();
			  // _hinge.setPos(initPos + Vector2f(ol, ol));
			  // initPos.x += _hinge.RectangleShape::getGlobalBounds().width + ol * 2;

	_limitPos = limitPos;
	_fixed = fixed;
	_minDim = minDim;
	_buttonPos = _initPos;

	///initCorner();	// Seullement dans les enfants ??
}
// Destructeur
buttonStrip::~buttonStrip()
{
	_normalScope = false;
	removeButtons(0, _buttons.size());
}
// Initialisation des boutons ajoutés
int buttonStrip::initButtonStat(const float S) {

	Vector2f dim = Vector2f(0, 0);	// Dimmenssions du bouton.
	float ol = 0;					// Épaisseur de son contour (Outline).
	
	///static float lastDim = 0;	// Dim. en y du dernier bouton positionné.
	// Dim. de la plage actuel dans lequel on place les boutons.
	static float offset = 0;
	int newScope = 0;// État qui précise si la portée a été changée.

	/// Présentement pas utilisé, c'est un facteur pour le scope
	if (_normalInterval)
		assert(S > 0);
	else
		assert(S < 0);

	// Positionne le premier bouton au bon endroit.
	if (_activeButton == _buttons.begin())
	{
		(*_activeButton)->initOrigins(oppositeC(_lastCorner));
		(*_activeButton)->move(_buttonPos);
		return 0;
	}
	else	// Obtien les informations du bouton précédent.
	{
		_activeButton--;
		initButtonSize(*_activeButton, _minDim, dim, ol);
		_activeButton++;
	}


	// Initialise et obtien de nouvelles informations du bouton.
	(*_activeButton)->initOrigins(oppositeC(_lastCorner));

	// Modifie la position de la prochaine portée si la dimmenssion du bouton est trop grande.
	if (offset < dim.y)
		offset = dim.y;
	///lastDim = dim.y;

	// Change les coordonées si la largeur du bouton dépasse l'écran.
	newScope = getValidPosition(dim.x, offset);

	// Si la limite de la portée à été rencontré ou si une erreur c'est produite.
	if (newScope < 0)
	{
		offset = 0;
		return newScope;
	}

	if (newScope)			// Si la portée a changée.
		offset = 0;

	(*_activeButton)->move(_buttonPos);

	return newScope;
}
// Met à jour la zone après chaque ajout de boutons.
void buttonStrip::updateZone()
{
	assert(!_buttons.empty());

	Vector2f ul = getUpperLeftCorner();
	ul.x -= TOLW/* - _hinge.P(bUpperLeft)*/;
	ul.y -= TOLH;
	Vector2f lr = getLowerRightCorner();
	lr.x += TOLW/* - _hinge.P(bUpperLeft)*/;
	lr.y += TOLH;

	_overlay.setPosition(ul);
	_overlay.setSize(Vector2f(lr.x - ul.x,
		lr.y - ul.y));
}

/// Setteurs
/// Utiliser l'itérateur _activeButton au lieu ?
/// Modificateurs de la liste de bouton.
int buttonStrip::addButton(oButton * b)
{
	_buttons.push_back(b);
	_activeButton = _buttons.end();
	if (_activeButton != _buttons.begin())
		_activeButton--;

	// Retourne si une nouvelle portée a été nécessaire.
	return initButtonStat();
}

int buttonStrip::addButtons(const vector<oButton*> buttons)
{
	int newScope = 0;
	for (const auto & b : buttons)
	{
		int newS = addButton(b);
		if (newS < 0)
			return newS;
		if (newScope < newS)
			newScope = newS;
	}
	return newScope;
}
// Retire des ensembles de boutons.
void buttonStrip::removeButtons(size_t begin, size_t end)
{
	assert(0 <= begin && begin <= end
		&& end <= _buttons.size());

	vector<oButton*>::iterator it = _buttons.begin();
	for (int i = 0; i < begin; i++)
		it++;

	for (size_t i = end - begin; i < end; i++, it++)
		_buttons.erase(it);

	_buttonPos = _buttons.back()->getP(_lastCorner); /// _lastCorner-- ?
}
/// Marche seullement avec seullement l'horizontal ??
// Obtien les bonnes coordonnées du prochain bouton par raport à sa liste.
int buttonStrip::getValidPosition(float dim, float offset)
{
	if (_normalScope)
	{
		if (_normalInterval)	// À partir du coin supérieur gauche vers l'opposé.
		{
			if (!useInterval(_buttonPos.x, _buttonPos.x + dim, _limitPos.x, _initPos.x))
				return useScope(_buttonPos.y, _buttonPos.y + offset, _limitPos.y, _limitPos.y);
		}
		else					// À partir du coin supérieur droit vers l'opposé.
		{
			if (!useInterval(_buttonPos.x, _initPos.x, _buttonPos.x - dim, _initPos.x))
				return useScope(_buttonPos.y, _buttonPos.y + offset, _limitPos.y, _limitPos.y);
		}
	}
	else
	{
		if (_normalInterval)	// À partir du coin inférieur gauche vers l'opposé.
		{
			if (!useInterval(_buttonPos.x, _buttonPos.x + dim, _limitPos.x, _initPos.x))
				return useScope(_buttonPos.y, _limitPos.y, _buttonPos.y - offset, _limitPos.y);
		}
		else					// À partir du coin supérieur droit vers l'opposé.
		{
			if (!useInterval(_buttonPos.x, _initPos.x, _buttonPos.x - dim, _initPos.x))
				return useScope(_buttonPos.y, _limitPos.y, _buttonPos.y - offset, _limitPos.y);
		}
	}
	return 0;
}
/// Utiliser le mot reach (étendue) au lieu ??
// Modifie ou remplace la position des prochains boutons dans l'intervale (i = intervale)
bool buttonStrip::useInterval(float & iPos, float smallI, float bigI, float initIPos)
{
	if (smallI < bigI)	// Si le bouton ne dépasserait pas l'intervale.
	{
		iPos = smallI;	// Ajuste la position dans l'intervale du bouton.
		return true;
	}
	else
	{	/// Implémentation possible d'une méthode qui permet d'étirer
		/// le bouton précédent jusqu'à la limite de son intervale.
		{
			// Le code suivant est fait pour un buttonStripH 
			//	positionné au top et formé dans un ordre normale 
			//	(des étages du haut en bas et les boutons de gauche à droite).
			assert(_activeButton != _buttons.begin());
			_activeButton--;

			Vector2f newSize = (*_activeButton)->getSize();
			newSize.x += (_limitPos.x 
				- (*_activeButton)->RectangleShape::getPosition().x
				- (*_activeButton)->getP(_lastCorner).x);
			(*_activeButton)->resize(newSize);

			_activeButton++;
		}

		iPos = initIPos;// Réinitialise la position au début de l'intervale.
		return false;
	}
}
// Modifie la portée si nécessaire et si possible (s = portée).
int buttonStrip::useScope(float & sPos, float smallS, float bigS, float & sPosLimit)
{
	if (smallS > bigS)	// Si le bouton dépasserait la portée.
	{
		if (!_fixed)	// Ajuste la portée maximale.
			sPosLimit = sPos; /// smallS au lieu de sPos ??
		else
		{
			// cout << "Code d'erreur : " << -1
			// << ". Le bouton " << _activeButton->getString() 
			// << " à été inséré dans la liste, "
			// << "mais elle est pleine. Retirez le dernier bouton "
			// << "si vous voulez l'utiliser ailleur.";
			return -1;
		}

		return 2;
	}
	else				// Ajuste la position en portée du bouton.
		sPos = smallS;

	return 1;
}

/// Getteurs
/// Il est possible de former un FloatRect directement 
///		en combinant les deux prochaines méthodes si nécessaire.
// 
Vector2f buttonStrip::getUpperLeftCorner(bool front)
{
	if (_normalScope)
	{
		if (_normalInterval)
			//if (front)
			return _initPos; // Pareil à : getCornerA()
							 //else
							 //	return ;
		else
			return getCornerB(bUpperLeft);
	}
	else
	{
		if (_normalInterval)
			return getCornerC(bUpperLeft);
		else
			return getCornerD(bUpperLeft);
	}
}
// 
Vector2f buttonStrip::getLowerRightCorner(bool front)
{
	if (_normalScope)
	{
		if (_normalInterval)
			return getCornerD(bLowerRight, front);
		else
			return getCornerC(bLowerRight, front);
	}
	else
	{
		if (_normalInterval)
			return getCornerB(bLowerRight);
		else
			return _initPos; // Pareil à : getCornerA()
	}
}
// 
Vector2f buttonStrip::getCornerB(bCorner c, bool front)
{
	float cPos;
	oButton * b;
	if (front)
		b = _buttons.front();
	else
		b = _buttons.back();

	cPos = b->RectangleShape::getPosition().x + b->getP(c).x;
	return Vector2f((_scopeNb > 1) ? _limitPos.x : cPos, _initPos.y);
}
// 
Vector2f buttonStrip::getCornerC(bCorner c, bool front)
{
	float cPos;
	oButton * b;
	if (front)
		b = _buttons.front();
	else
		b = _buttons.back();

	cPos = b->RectangleShape::getPosition().y + b->getP(c).y;
	return Vector2f(_initPos.x, cPos);
}
// 
Vector2f buttonStrip::getCornerD(bCorner c, bool front)
{
	Vector2f cPos;
	oButton * b;
	if (front)
		b = _buttons.front();
	else
		b = _buttons.back();

	Vector2f bPos = b->RectangleShape::getPosition();
	cPos = Vector2f(bPos.x + b->getP(c).x, bPos.y + b->getP(c).y);
	return (_scopeNb > 1) ? Vector2f(_limitPos.x, cPos.y) : cPos;
}
// 
vector<oButton*> & buttonStrip::getButtonList()
{
	return _buttons;
}
// Retourne la zone comprise par la bannière.
FloatRect buttonStrip::getZone()
{
	return _overlay.getGlobalBounds();
}


///=========================================///
/* Classe buttonStripH : Banière horizontale */
///=========================================///

/// Initialisation
// Initialise l'indice du dernier coin des objets.
void buttonStripH::initCorner()
{
	if (_normalScope)
	{
		if (_normalInterval)
			_lastCorner = bLowerRight;
		else
			_lastCorner = bLowerLeft;
	}
	else
	{
		if (_normalInterval)
			_lastCorner = bUpperRight;
		else
			_lastCorner = bUpperLeft;
	}
}
// 
buttonStripH::~buttonStripH()
{
	_buttons.clear();
	_activeButton = _buttons.begin();
	_pressedButtons.clear();
	_pressedColors.~elemColors();
	_lastHovered = nullptr;
	_hoveredColors.~elemColors();

	_minDim = _buttonPos = _initPos = _limitPos = Vector2f();

	_fixed = _normalInterval = _normalScope = false;
	_scopeNb = 0;
	_lastCorner = bUpperLeft;

	_zone = FloatRect();
}


///=======================================///
/* Classe buttonStripH : Banière Verticale */
///=======================================///

/// Initialisation
// 
buttonStripV::~buttonStripV()
{
	//buttonStrip::~buttonStrip();
}