/*======================================================================================
Fichier:		buttonStrip.cpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			29-11-2017
======================================================================================*/


#include "buttonStrip.h"


///==========================///
/* Classe de base buttonStrip */
///==========================///

// Constructeur
buttonStrip::buttonStrip(bool fromTopOrLeft, bool reverseOrder,
	Vector2f initPos, Vector2f limitPos, bool fixed, Vector2f minDim)
{
	assert(0 <= initPos.x && 0 <= initPos.y
		&& 0 <= limitPos.x && 0 <= limitPos.y
		&& 1 <= minDim.x && 1 <= minDim.y);

	_normalScope = fromTopOrLeft;
	if (_normalScope)
		assert(_initPos.y <= _limitPos.y);
	else
		assert(_initPos.y >= _limitPos.y);

	_normalInterval = reverseOrder;
	if (!_normalInterval)
		assert(_initPos.x <= _limitPos.x);
	else
		assert(_initPos.x >= _limitPos.x);

	_initPos = initPos;
	_limitPos = limitPos;
	_fixed = fixed;
	_minDim = minDim;
	_buttonPos = _initPos;
	///initCorner();	// Seullement dans les enfants
}
// 
buttonStrip::~buttonStrip()
{
	_normalScope = false;
	removeButtons(0, _buttons.size());
}


///=========================================///
/* Classe buttonStripH : Banière horizontale */
///=========================================///

// 
buttonStripH::~buttonStripH()
{
	buttonStrip::~buttonStrip();
}


///=======================================///
/* Classe buttonStripH : Banière Verticale */
///=======================================///

// 
buttonStripV::~buttonStripV()
{
	buttonStrip::~buttonStrip();
}