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

/// Mettre dans la classe?
// Obtien la dimmenssion du bouton incluant son contour.
static bool initButtonSize(oButton * it,
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



// Classe de base des listes de placement automatique de boutons.
class buttonStrip
{
private:
	/// Utiliser plut�t autre m�thode qui travail avec des min() et des max() ??
	Vector2f getCornerB(bCorner c, bool front = false);
	Vector2f getCornerC(bCorner c, bool front = false);
	Vector2f getCornerD(bCorner c, bool front = false);
protected:
	/// Pour que la liste fonctionne correctement, 
	///		il faut initialiser l'origine de ceux-ci au fur et � mesure.
	///	Il va falloir utiliser une liste au lieu d'un vecteur pour permettre une r�organisation des boutons.
	vector<oButton*> _buttons;	// La liste des boutons.
	vector<oButton*>::iterator _activeButton;	// Dernier bouton actif.
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
	int initButtonStat(const float S = 1);

	/// Marche seullement avec seullement l'horizontal ??
	// Obtien les bonnes coordonn�es du prochain bouton par raport � sa liste.
	int getValidPosition(float dim, float offset);
	/// Utiliser le mot reach (�tendue) au lieu ??
	// Modifie ou remplace la position des prochains boutons dans l'intervale (i = intervale)
	bool useInterval(float & iPos, float smallI, float bigI, float initIPos);
	// Modifie la port�e si n�cessaire et si possible (s = port�e).
	int useScope(float & sPos, float smallS, float bigS, float & sPosLimit);

	virtual void initCorner() = 0;
public:
	buttonStrip(bool fromTopOrLeft, bool reverseOrder,
		Vector2f initPos, Vector2f limitPos,
		bool fixed, Vector2f minDim);
	~buttonStrip();

	/// Utiliser l'it�rateur _activeButton au lieu ?
	/// Modificateurs de la liste de bouton.
	int addButton(oButton * b);
	int addButtons(const vector<oButton*> buttons);

	void removeButtons(size_t begin, size_t end);

	/// Getteurs
	vector<oButton*> & getButtonList();
	void updateZone();
	FloatRect getZone();
	RectangleShape & getOverlay()
	{
		return _overlay;
	}
	/// Il est possible de former un FloatRect directement 
	///		en combinant les deux prochaines m�thodes si n�cessaire.
	virtual Vector2f getUpperLeftCorner(bool front = true);
	virtual Vector2f getLowerRightCorner(bool front = false);
};


// Liste de boutons positionn�s � l'horizontale.
class buttonStripH : public buttonStrip
{
private:
	// Initialise l'indice du dernier coin des objets.
	void initCorner() override;
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


};

