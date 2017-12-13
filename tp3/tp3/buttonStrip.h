/*======================================================================================
Fichier:		buttonStrip.h
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			29-11-2017
Description:	.
======================================================================================*/



#pragma once
#include "../oButton.h"
#include <algorithm>


// Prototype des fonctions

static bool initButtonSize(oButton * it,
	Vector2f minDim, Vector2f & dim, float & ol);



// Classe de base des listes de placement automatique de boutons.
class buttonStrip
{
private:
	/// Utiliser plut�t autre m�thode qui travail avec des min() et des max() ??
	Vector2f getCornerB(bCorner c)
	{
		float cPos = _buttons.back().getP(c).x;
		return Vector2f((_scopeNb > 1) ? _limitPos.x : cPos, _initPos.y);
	}
	Vector2f getCornerC(bCorner c)
	{
		float cPos = _buttons.back().getP(c).y;
		return Vector2f(_initPos.x, cPos);
	}
	Vector2f getCornerD(bCorner c)
	{
		Vector2f cPos = _buttons.back().getP(c);
		return (_scopeNb > 1) ? Vector2f(_limitPos.x, cPos.y) : cPos;
	}
protected:
	/// Pour que la liste fonctionne correctement, 
	///		il faut initialiser l'origine de ceux-ci au fur et � mesure.
	///	Il va falloir utiliser une liste au lieu d'un vecteur pour permettre une r�organisation des boutons.
	vector<oButton> _buttons;	// La liste des boutons.
	vector<oButton>::iterator _activeButton;	// Dernier bouton actif.
	/// Faire en sotre que la liste des boutons enclench�s soit des oButton* ou en des itt�rateurs au lieu??
	vector<int> _pressedButtons;// Indices des boutons enclench�s de la liste.
	elemColors _pressedColors;	// Couleur du corps des boutons enclench�s.
	oButton * _lastHovered;		// Dernier bouton que la souris a survoll�e.
	elemColors _hoveredColors;	// Couleurs des boutons lorsqu'ils sont survoll�s.

	Vector2f _minDim;			// Dimmenssions requises minimales des boutons.
	Vector2f _buttonPos;		// Position du bouton actif.
	Vector2f _initPos;			// La coordonn�e initiale des boutons.
	Vector2f _limitPos;			// La coordonn�e limite des boutons (intervale et port�e).

	bool _fixed;				// Permission d'ajout de boutons au del� de la port�e.
	bool _normalInterval;		// Sp�cifie � partir de quel bout de l'intervale on d�bute.
	bool _normalScope;			// Sp�cifie � partir de quel orientation la liste s'empile.
	int _scopeNb;				// Nombre de port�e contenant des boutons.
	bCorner _lastCorner;		// Indice qui sp�cifie le coin oppos� au d�part.

	RectangleShape _overlay;	// Zone de couleur qui entoure les boutons.
	///oB_bannerSet _hinge;		// Bouton de la bani�re qui permet d'activer le
	FloatRect _zone;			// Zone s�lectionnable ... utiliser _overlay ?

	////// POUR BS_HORIZONTALE SEULEMENT? ///////
	int initButtonStat(const float S = 1) {

		Vector2f dim = Vector2f(0, 0);	// Dimmenssions du bouton.
		float ol = 0;					// �paisseur de son contour (Outline).
		///static float lastDim = 0;	// Dim. en y du dernier bouton positionn�.
		// Dim. de la plage actuel dans lequel on place les boutons.
		static float offset = 0;
		int newScope = 0;// �tat qui pr�cise si la port�e a �t� chang�e.

		/// Pr�sentement pas utilis�, c'est un facteur pour le scope
		if (_normalInterval)
			assert(S > 0);
		else
			assert(S < 0);

		// Positionne le premier bouton au bon endroit.
		if (_activeButton == _buttons.begin())
		{
			_activeButton->initOrigins(oppositeC(_lastCorner));
			_activeButton->move(_buttonPos);
			return 0;
		}
		else	// Obtien les informations du bouton pr�c�dent.
		{
			_activeButton--;
			initButtonSize(&*_activeButton, _minDim, dim, ol);
			_activeButton++;
		}
		

		// Initialise et obtien de nouvelles informations du bouton.
		_activeButton->initOrigins(oppositeC(_lastCorner));

		// Modifie la position de la prochaine port�e si la dimmenssion du bouton est trop grande.
		if (offset < dim.y)
			offset = dim.y;
		///lastDim = dim.y;

		// Change les coordon�es si la largeur du bouton d�passe l'�cran.
		newScope = getValidPosition(dim.x, offset);

		// Si la limite de la port�e � �t� rencontr� ou si une erreur c'est produite.
		if (newScope < 0)
		{
			offset = 0;
			return newScope;
		}

		if (newScope)			// Si la port�e a chang�e.
			offset = 0;

		_activeButton->move(_buttonPos);

		return newScope;
	}
	/// ...to change the active button ??
	void setting2() { }

	/// Marche seullement avec seullement l'horizontal ??
	// Obtien les bonnes coordonn�es du prochain bouton par raport � sa liste.
	int getValidPosition(float dim, float offset)
	{
		if (_normalScope)
		{
			if (_normalInterval)	// � partir du coin sup�rieur gauche vers l'oppos�.
			{
				if (!useInterval(_buttonPos.x, _buttonPos.x + dim, _limitPos.x, _initPos.x))
					return useScope(_buttonPos.y, _buttonPos.y + offset, _limitPos.y, _limitPos.y);
			}
			else					// � partir du coin sup�rieur droit vers l'oppos�.
			{
				if (!useInterval(_buttonPos.x, _initPos.x, _buttonPos.x - dim, _initPos.x))
					return useScope(_buttonPos.y, _buttonPos.y + offset, _limitPos.y, _limitPos.y);
			}
		}
		else
		{
			if (_normalInterval)	// � partir du coin inf�rieur gauche vers l'oppos�.
			{
				if (!useInterval(_buttonPos.x, _buttonPos.x + dim, _limitPos.x, _initPos.x))
					return useScope(_buttonPos.y, _limitPos.y, _buttonPos.y - offset, _limitPos.y);
			}
			else					// � partir du coin sup�rieur droit vers l'oppos�.
			{
				if (!useInterval(_buttonPos.x, _initPos.x, _buttonPos.x - dim, _initPos.x))
					return useScope(_buttonPos.y, _limitPos.y, _buttonPos.y - offset, _limitPos.y);
			}
		}
	}
	// Modifie ou remplace la position des prochains boutons dans l'intervale (i = intervale)
	bool useInterval(float & iPos, float smallI, float bigI, float initIPos)
	{
		if (smallI < bigI)	// Si le bouton ne d�passerait pas l'intervale.
		{
			iPos = smallI;	// Ajuste la position dans l'intervale du bouton.
			return true;
		}
		else
		{	/// Impl�mentation possible d'une m�thode qui permet d'�tirer
			/// le bouton pr�c�dent jusqu'� la limite de son intervale.
			{
				// Le code suivant est fait pour un buttonStripH 
				//	positionn� au top et form� dans un ordre normale 
				//	(des �tages du haut en bas et les boutons de gauche � droite).
				assert(_activeButton != _buttons.begin());
				_activeButton--;

				Vector2f newSize = _activeButton->getSize();
				newSize.x + (_limitPos.x - _activeButton->getP(_lastCorner).x);
				_activeButton->resize(newSize);

				_activeButton++;
			}

			iPos = initIPos;// R�initialise la position au d�but de l'intervale.
			return false;
		}
	}
	// Modifie la port�e si n�cessaire et si possible (s = port�e).
	int useScope(float & sPos, float smallS, float bigS, float & sPosLimit)
	{
		if (smallS > bigS)	// Si le bouton d�passerait la port�e.
		{
			if (!_fixed)	// Ajuste la port�e maximale.
				sPosLimit = sPos; /// smallS au lieu de sPos ??
			else
			{
				// cout << "Code d'erreur : " << -1
				// << ". Le bouton " << _activeButton->getString() 
				// << " � �t� ins�r� dans la liste, "
				// << "mais elle est pleine. Retirez le dernier bouton "
				// << "si vous voulez l'utiliser ailleur.";
				return -1;
			}

			return 2;
		}
		else				// Ajuste la position en port�e du bouton.
			sPos = smallS;

		return 1;
	}

	virtual void initCorner() = 0;
public:
	buttonStrip(bool fromTopOrLeft, bool reverseOrder,
		Vector2f initPos, Vector2f limitPos,
		bool fixed, Vector2f minDim);
	~buttonStrip();

	/// Utiliser l'it�rateur _activeButton au lieu ?
	/// Modificateurs de la liste de bouton.
	int addButton(oButton b)
	{
		_buttons.push_back(b);
		_activeButton = _buttons.end();
		_activeButton--;
		// Retourne si une nouvelle port�e a �t� n�cessaire.
		return initButtonStat();
	}
	int addButtons(const vector<oButton> buttons)
	{
		for (const auto & b : buttons)
			if (addButton(b) < 0)
				return -1;
	}
	//virtual bool placeButton() = 0;
	void removeButtons(size_t begin, size_t end)
	{
		assert(0 <= begin && begin <= end
			&& end <= _buttons.size());

		vector<oButton>::iterator it = _buttons.begin();
		for (int i = 0; i < begin; i++)
			it++;

		for (size_t i = end - begin; i < end; i++, it++)
			_buttons.erase(it);

		_buttonPos = _buttons.back().getP(_lastCorner); // _lastCorner--
	}

	/// Getteurs
	vector<oButton> & getButtonList()
	{
		return _buttons;
	}
	void updateZone()
	{
		assert(_buttons.size() != 0);
		Vector2f ul = getUpperLeftCorner();
		Vector2f lr = getLowerRightCorner();
		_overlay.setPosition(ul);
		_overlay.setSize(Vector2f(lr.x - ul.x, lr.y - ul.y));
	}
	FloatRect getZone()
	{
		return _overlay.getGlobalBounds();
	}
	/// Il est possible de former un FloatRect directement 
	///		en combinant les deux prochaines m�thodes si n�cessaire.
	virtual Vector2f getUpperLeftCorner()
	{
		if (_normalScope)
		{
			if (_normalInterval)
				return _initPos; // Pareil � : getCornerA()
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
	virtual Vector2f getLowerRightCorner()
	{
		if (_normalScope)
		{
			if (_normalInterval)
				return getCornerD(bLowerRight);
			else
				return getCornerC(bLowerRight);
		}
		else
		{
			if (_normalInterval)
				return getCornerB(bLowerRight);
			else
				return _initPos; // Pareil � : getCornerA()
		}
	}
};


// Liste de boutons positionn�s � l'horizontale.
class buttonStripH : public buttonStrip
{
private:
	// Initialise l'indice du dernier coin des objets.
	void initCorner() override
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
public:
	buttonStripH(bool normalScope = true, bool normalInterval = true,
		Vector2f initPos = Vector2f(), Vector2f limitPos = Vector2f(SCREENW, 0),
		bool fixed = false, Vector2f minDim = Vector2f(1, 1))
		: buttonStrip(normalScope, normalInterval,
			initPos, limitPos, fixed, minDim)
	{
		initCorner();
	}
	~buttonStripH();

	// 
	//bool placeButton() override
	//{
	//	bool newScope = false;		// �tat de si la port�e a �t� chang�e.
	//	// Bouton en cour.
	//	vector<oButton>::iterator it = _buttons.begin();
	//	int i = 0;	// Obtien le premier bouton � positionner.
	//	while (i < start) { i++; it++; }
	//	// Pour le bouton et tout les suivants, 
	//	//	positionner le bouton selon ses dimmenssions.
	//	while (it < _buttons.end())
	//	{
	//		_activeButton = it;
	//		initButtonStat();
	//		it++;	// Obtien le prochain bouton � placer de la liste.
	//	}
	//	// Retourne si une nouvelle port�e a �t� n�cessaire.
	//	return newScope;
	//}
};

// 
class buttonStripV : public buttonStrip
{
private:
public:
	buttonStripV(bool normalScope = true, bool normalInterval = true,
		Vector2f initPos = Vector2f(), Vector2f limitPos = Vector2f(0, SCREENH),
		bool fixed = false, Vector2f minDim = Vector2f(1, 1))
		: buttonStrip(normalScope, normalInterval,
			initPos, limitPos, fixed, minDim)
	{
		initCorner();
	}


	~buttonStripV();

	//offsetButton(_top, _left, height, width, TOLH, OL, SCREENH);
};

/// Mettre dans la classe?
// Obtien la dimmenssion du bouton incluant son contour.
bool initButtonSize(oButton * it,
	Vector2f minDim, Vector2f & dim, float & ol)
{
	bool resize = false;
	ol = it->RectangleShape::getOutlineThickness();
	dim.y = it->getH() + ol * 2;
	if (minDim.y > dim.y)
	{
		dim.y = minDim.y;
		resize = true;
	}
	dim.x = it->getW() + ol * 2;
	if (minDim.x > dim.x)
	{
		dim.x = minDim.x;
		resize = true;
	}

	if (!resize)
		return false;

	it->resize(dim);
	return true;
}

//static bool offsetButton(float & corner, float dim,
//	float & scope, float & offset, Vector2f & limit,
//	bool fixed/*, int MAX*/);