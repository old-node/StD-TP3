/* En-tête du programme
====================================================================================================
Fichier: 		painter.cpp (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Petit menu qui permet d'entrer un nom d'utilisateur et un mot de passe
====================================================================================================
*/

#include <SFML/Graphics.hpp>
#include "painterFuction.h"
#include "sqlConnect.h"

using namespace sf;
using namespace std;

#pragma once

#define MAX_NUMBER_OF_ITEMS 2

class inputMenu
{
private:
	RenderWindow _window;						//Fenêtre d'affichage
	Text badLog;								//Text pour afficher quand le login est invalide
	Text texts[MAX_NUMBER_OF_ITEMS];			//Text pour les titres d'inputs
	Text inputs[MAX_NUMBER_OF_ITEMS];			//Text pour les inputs
	RectangleShape rect[MAX_NUMBER_OF_ITEMS];	//Tableau de rectangle pour les inputs
	RectangleShape recSelect;					//Rectangle qui indique quelle input est selectionnee
	string strInput[MAX_NUMBER_OF_ITEMS];
	int selectedIndex = 0;						//Defini quel input est selectionné
	int _width;
	int _height;
	bool invalidInfo = false;
	sqlConnect bd;

public:
	inputMenu(float width, float height);
	~inputMenu();

	void init();
	void run();
	void draw();

	const char* getUsername()const;
	const char* getPassword()const;
};

