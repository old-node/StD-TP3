/*======================================================================================
Fichier:		painterFuntion.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			25-11-2017
Description:	.
======================================================================================*/


#pragma once
#include <cassert>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

///============///
/* Enumérateurs */
///============///

// Palette de couleur
enum PBOARD;

// Coins d'un bouton
enum bCorner {
	bUpperLeft, bUpperRight, bLowerRight, bLowerLeft, bCenter
};
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
	cDefault, cCreate, cColor, cLink, cResize, cMove, cSelect, cRemove,
	cClear, cSave, cLoad, cMenu, cQuit, cCOUNT
};
// Choix de la forme à dessinner
enum sShape {
	sDefault, sBox, sCircle, sCOUNT ///, sBall, sPoint, sLink?
};
// Choix de couleurs par bouton
enum pColor
{
	pDefault, pC1, pC2, pC3, pC4, pCOUNT
};

// 
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
	return bCenter;
}
// 
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
// 
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

// Palette de couleur personalisée.
enum PBOARD {
	P_0,	// 0, 0, 0, 0		Transparent
	P_1,	// 0, 0, 0			Noir
	P_2,	// 255, 255, 255	Blanc

	P_oB,	// 113, 198, 113	Box
	P_oC,	// 173, 216, 230	Circle
	P_oL,	// 195, 178, 100	Liaison

	P_oZ,	// 2, 165, 255		Resize
	P_oM,	// 255, 196, 162	Move
	P_oS1,	// 0, 227, 136, 50	Select focus
	P_oS2,	// 0, 210, 110, 150	Select elem

	P_oR1,	// 201, 18, 18, 50	Remove focus
	P_oR2,	// 255, 9, 9		Remove elem
	P_oR3,	// 255, 9, 9		Clear

	P_oA1,	// 0, 236, 246		Save
	P_oA2,	// 165, 128, 246	Load
	P_o1,	// 139, 117, 0		Menu
	P_o0,	// 139, 0, 0		Quit

	P_02,	// 60, 40, 10		etc no.2
	P_o3,	// 110, 182, 30		etc no.3
	P_o4,	// 30, 182, 110		etc no.4
	P_o5,	// 30, 110, 182		etc no.5
	P_o6,	// 110, 30, 182		etc no.6
	P_o7,	// 182, 30, 110		etc no.7
	P_o8,	// 182, 110, 30		etc no.8
	P_o9,	// 200, 200, 200	etc no.9

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


///========================///
/* Prototypes des fonctions */
///========================///

static const vector<Color> makeCBoard();
static const Font FONT(string fontLocation = "font_arial.ttf");
static const PBOARD getNewColor(PBOARD last);
static const Color getEnumC(PBOARD c);
static void swithColor(Shape & s, int c);
static float distance2Points(Vector2f p1, Vector2f p2);
static float textDim(float & p, float t, float MAX);


///===========================///
/* Constantes de l'application */
///===========================///

/// Variables par défaut

const Font D_F = FONT();	// Police par défaut de l'application
const Vector2f TWOO = Vector2f(2, 2);		// Vecteur pour les calculs rapides.
const vector<Color> DBOARD = makeCBoard();	// Palette des couleurs par défaut.

/// Pour l'emplacement
const float SCREENW = 800;	// Largeur de l'écran /// inclus à partir du (main) ?
const float SCREENH = 800;	// Hauteur de l'écran
const int BUTTONSPAN = 5;	// Rapport de boutons en largeur
const float BW = SCREENW / BUTTONSPAN;	// Largeur maximum des boutons
const float BH = 40.0;		// Hauteur maximum des boutons
const bool HORIZONTALMENU = false;		// Sens de la liste des boutons
const float BOL = 1;		// Largeur des bordures par défaut

/// Pour l'affichage
const PBOARD FILLC = P_2;	// Couleur par défaut du corps de formes
const PBOARD OUTLC = P_1;	// Couleur par défaut des bordures de formes
const PBOARD FONTC = P_T;	// Couleur par défaut du texte
const int TSIZE = (int)(BH / 2 - 2 * BOL);	// hauteur du texte par défaut
const float TOLW = 15;		// Espacement entre le texte et le coté des boutons
const float TOLH = 8;		// Espacement entre le texte et le haut et le bas des boutons

/// Couleurs des formes
const PBOARD C_B = P_B;		// Couleur par défaut des rectangles
const PBOARD C_C = P_C;		// Couleur par défaut des cercles
const PBOARD C_L = P_L;		// Couleur par défaut des liaisons


///==========///
/* Structures */
///==========///

// Structure d'une forme pour connaître son type
struct shape
{
	Shape* shapePtr;	//Pointeur pour la forme
	PBOARD f;			// Couleur du corps de la forme.
	PBOARD ol;			// Couleur de la bordure de la forme.
	PBOARD t;			// Couleur du text sur la forme.
	sShape shapeType;	//Type de forme selon l'enum
	shape(Shape* s = nullptr, sShape sT = sDefault,
		PBOARD fill = P_2, PBOARD outline = P_1, PBOARD text = P_1)
	{
		f = fill;
		ol = outline;
		t = text;
		shapePtr = s;
		shapeType = sT;
	}
};

// Assortissement des couleurs des formes.
struct elemColors
{
	PBOARD f;				// Couleur du corps de la forme.
	PBOARD ol;				// Couleur de la bordure de la forme.
	PBOARD t;				// Couleur du text sur la forme.
	elemColors(PBOARD fill = P_2,
		PBOARD outline = P_1,
		PBOARD text = P_1)
	{
		set(fill, outline, text);
	}
	void set(PBOARD fill = P_2,
		PBOARD outline = P_1,
		PBOARD text = P_1)
	{
		f = fill;
		ol = outline;
		t = text;
	}
	void apply(shape & s)
	{
		s.shapePtr->setFillColor(getEnumC(f));
		s.shapePtr->setOutlineColor(getEnumC(ol));
	}
	void set(elemColors c)
	{
		set(c.f, c.ol, c.t);
	}
	~elemColors()
	{
		t = ol = f = P_0;
	}
	bool operator!=(elemColors eC)
	{
		if (f != eC.f)
			return false;
		if (ol != eC.ol)
			return false;
		if (t != eC.t)
			return false;
		return true;
	}
};

// Structure qui mémorise les formes sélectionnés
struct selection
{
	list<shape>::iterator _it;	// 
	elemColors _c;	// Couleurs d'origine des formes sélectionnées.
	Vector2f _o;	// Offset pour permettre le déplacement des formes.

	selection(list<shape>::iterator it)
	{
		_it = it;
		_c.f = _it->f;
		_c.ol = _it->ol;
	}
	void setOffset(Vector2f click)
	{
		_o = click - _it->shapePtr->getPosition();
	}
	list<shape>::iterator pop()
	{
		_it->shapePtr->setFillColor(getEnumC(_c.f));
		_it->shapePtr->setOutlineColor(getEnumC(_c.ol));
		return _it;
	}
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
const Color getEnumC(PBOARD c)
{
	assert(0 <= c && c < DBOARD.size());
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
	c.push_back(Color(0, 0, 0, 0));			//	Transparent
	c.push_back(Color(0, 0, 0));			//	Noir
	c.push_back(Color(255, 255, 255));		//	Blanc

	c.push_back(Color(113, 198, 113));		//	Box
	c.push_back(Color(173, 216, 230));		//	Circle
	c.push_back(Color(195, 178, 100));		//	Liaison

	c.push_back(Color(2, 165, 255));		// 	Resize
	c.push_back(Color(255, 196, 162));		//	Move
	c.push_back(Color(0, 227, 136, 50));	// 	Select focus
	c.push_back(Color(0, 210, 110, 150));	// 	Select elem

	c.push_back(Color(201, 18, 18, 50));	// 	Remove focus
	c.push_back(Color(255, 9, 9));			// 	Remove elem
	c.push_back(Color(255, 9, 9));			//	Clear	

	c.push_back(Color(0, 236, 246));		// 	Save	
	c.push_back(Color(165, 128, 246));		// 	Load	
	c.push_back(Color(139, 117, 0));		// 	Menu	
	c.push_back(Color(139, 0, 0));			// 	Quit	

	c.push_back(Color(60, 40, 10));			// 	etc no.2
	c.push_back(Color(110, 182, 30));		// 	etc no.3
	c.push_back(Color(30, 182, 110));		// 	etc no.4
	c.push_back(Color(30, 110, 182));		// 	etc no.5
	c.push_back(Color(110, 30, 182));		// 	etc no.6
	c.push_back(Color(182, 30, 110));		// 	etc no.7
	c.push_back(Color(182, 110, 30));		//	etc no.8
	c.push_back(Color(200, 200, 200));		//	etc no.9

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

float distance2Points(Vector2f p1, Vector2f p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Calcul les dimmensions nécessaire du bouton pour le texte
float textDim(float & p, float t, float MAX)
{
	if (p == 0)
		if (t <= MAX)
			p = t;
		else
			p = MAX;
	return p;
}