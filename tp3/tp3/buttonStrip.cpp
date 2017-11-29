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
buttonStrip::buttonStrip(bool fromTopOrLeft, Vector2f startPos, Vector2f endPos)
{
	assert(0 <= startPos.x && 0 <= startPos.y
		&& 0 <= endPos.x && 0 <= endPos.y);
	_fromTopOrLeft = fromTopOrLeft;
	_startPos = startPos;
	_endPos = endPos;
	initStrip();
}
// 
buttonStrip::~buttonStrip()
{
	_fromTopOrLeft = false;
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