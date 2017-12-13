/*======================================================================================
Fichier:		painterFuntion.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			25-11-2017
Description:	.
======================================================================================*/


#pragma once
#include <cassert>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


///============///
/* Enumérateurs */
///============///

// Palette de couleur
enum PBOARD;

// Zones où le pointeur peut être situé
enum rRegion {
	rStart, rMenuPrincipale, rButton, rDraw, rCOUNT
};
// Modes de fonctionnement avec le curseur
enum oMode {
	oDefault, oClick, oDrag, oUnclick, oCOUNT
};
// Options d'opérations dans l'application
enum cMode {
	cDefault, cCreate, cLink, cRemove, cSelect, cMove, cResize, cCOUNT
};
// Choix de la forme à dessinner
enum sShape {
	sNone, sBox, sLine, sCOUNT ///, sBall, sPoint, sLink?
};
// Coins d'un bouton
enum bCorner {
	bUpperLeft, bUpperRight, bLowerRight, bLowerLeft, bCenter
};
static bCorner oppositeC(bCorner c)
{
	switch (c)
	{
	case bUpperLeft:	return bLowerRight;
	case bUpperRight:	return bLowerLeft;
	case bLowerRight:	return bUpperLeft;
	case bLowerLeft:	return bUpperRight;
	default:	assert(false);		break;
	}
}
static Vector2f originOffset(bCorner c, float ol, Vector2f o)
{
	switch (c)
	{
	case bUpperLeft:	return Vector2f(o.x - ol, o.y - ol);
	case bUpperRight:	return Vector2f(o.x + ol, o.y - ol);
	case bLowerRight:	return Vector2f(o.x + ol, o.y + ol);
	case bLowerLeft:	return Vector2f(o.x - ol, o.y + ol);
	default:			return o;
	}
}

static Vector2f updateTextOrigin(bCorner c, FloatRect dim, Vector2f o)
{
	switch (c)
	{
	case bUpperLeft:	
		return Vector2f(-o.x, -o.y);
	case bUpperRight:	
		return Vector2f(dim.width + o.x, -o.y);
	case bLowerRight:	
		return Vector2f(dim.width + o.x, dim.height + o.y);
	case bLowerLeft:	
		return Vector2f(-o.x, dim.height + o.y);
	default:			
		return Vector2f(dim.width / 2, dim.height / 2);
	}
}

///========================///
/* Prototypes des fonctions */
///========================///

static const vector<Color> makeCBoard();
static const Font FONT(string fontLocation = "font_arial.ttf");
static const PBOARD getNewColor(PBOARD last);
static const Color getColor(PBOARD c);
static void swithColor(Shape & s, int c);



///===========================///
/* Constantes de l'application */
///===========================///

// Vecteur de deux points float pour les multiplications.
const Vector2f TWOO = Vector2f(2, 2);
// Palette des couleurs par défaut.
const vector<Color> DBOARD = makeCBoard();
// Palette de couleur personalisée.
enum PBOARD {
	P_A,	// 250, 255, 250
	P_B,	// 250, 229, 150
	P_C,	// 242, 182, 50
	P_D,	// 230, 233, 240
	P_E,	// 230, 175, 75
	P_F,	// 230, 39, 57
	P_G,	// 224, 80, 56
	P_H,	// 197, 213, 203
	P_I,	// 194, 221, 230
	P_J,	// 192, 223, 217
	P_K,	// 176, 161, 142
	P_L,	// 159, 168, 163
	P_M,	// 154, 211, 222
	P_N,	// 147, 83, 71
	P_O,	// 144, 104, 190
	P_P,	// 125, 70, 39
	P_Q,	// 106, 87, 80
	P_R,	// 103, 112, 119
	P_S,	// 102, 116, 103
	P_T,	// 59, 58, 54
	P_U,	// 48, 0, 50
	P_V,	// 23, 62, 67
	P_W,	// 22, 23, 79
	P_X,	// 12, 98, 3
	P_Y,	// 10, 20, 100
	P_Z,	// 0, 0, 1
	COUNT
};


///=========///
/* Fonctions */
///=========///

// Obtient la police de caractère SFML désirée
const Font FONT(string fontLocation)
{
	Font LFONT;
	assert(LFONT.loadFromFile(fontLocation));
	return Font(LFONT);
}
// Obtien une nouvelle couleur
const PBOARD getNewColor(PBOARD last = COUNT)
{
	PBOARD n = last;
	do {
		n = static_cast<PBOARD>(rand() % COUNT);
	} while (n == last);
	return n;
}
// Retourne la couleur à l'indice recherché
const Color getColor(PBOARD c)
{
	assert(0 < c && c < DBOARD.size());
	return DBOARD[c];
}
// Modifie la couleur interne d'une forme à partir de la palette personalisée
void swithColor(Shape & s, int c)
{
	assert(0 <= c && c <= PBOARD::COUNT);
	s.setFillColor(DBOARD[static_cast<PBOARD>(c)]);
}
// Constructeur de la palette par défaut
const vector<Color> makeCBoard()
{
	vector<Color> c;
	c.push_back(Color(250, 255, 250));
	c.push_back(Color(250, 229, 150));
	c.push_back(Color(242, 182, 50));
	c.push_back(Color(230, 233, 240));
	c.push_back(Color(230, 175, 75));
	c.push_back(Color(230, 39, 57));
	c.push_back(Color(224, 80, 56));
	c.push_back(Color(197, 213, 203));
	c.push_back(Color(194, 221, 230));
	c.push_back(Color(192, 223, 217));
	c.push_back(Color(176, 161, 142));
	c.push_back(Color(159, 168, 163));
	c.push_back(Color(154, 211, 222));
	c.push_back(Color(147, 83, 71));
	c.push_back(Color(144, 104, 190));
	c.push_back(Color(125, 70, 39));
	c.push_back(Color(106, 87, 80));
	c.push_back(Color(103, 112, 119));
	c.push_back(Color(102, 116, 103));
	c.push_back(Color(59, 58, 54));
	c.push_back(Color(48, 0, 50));
	c.push_back(Color(23, 62, 67));
	c.push_back(Color(22, 23, 79));
	c.push_back(Color(12, 98, 3));
	c.push_back(Color(10, 20, 100));
	c.push_back(Color(0, 0, 1));
	return c;
}