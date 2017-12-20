/* En-t�te du programme
====================================================================================================
Fichier: 		painter.cpp (TP3)
Auteur: 		Simon Lagac� et Olivier Lemay Dostie
Date cr�ation: 	11/28/2017
But: 			Petit menu qui permet d'entrer un nom d'utilisateur et un mot de passe
====================================================================================================
*/


#pragma once
using namespace std;

#include <SFML/Graphics.hpp>
#include "painterFuction.h"
using namespace sf;

#define MAX_NUMBER_OF_ITEMS 2

// Menu de saisie
class inputMenu
{
private:
	RenderWindow _window;						//Fen�tre d'affichage
	Text texts[MAX_NUMBER_OF_ITEMS];			//Text pour les titres d'inputs
	Text inputs[MAX_NUMBER_OF_ITEMS];			//Text pour les inputs
	RectangleShape rect[MAX_NUMBER_OF_ITEMS];	//Tableau de rectangle pour les inputs
	RectangleShape recSelect;					//Rectangle qui indique quelle input est selectionnee
	string strInput[MAX_NUMBER_OF_ITEMS];
	int selectedIndex = 0;						//Defini quel input est selectionn�
public:
	inputMenu(int width, int height);
	~inputMenu();

	void run();

	void draw();

	string getUsername()const;
	string getPassword()const;
};

