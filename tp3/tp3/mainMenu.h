/* En-t�te du programme
====================================================================================================
Fichier: 		mainMenu.h (TP3)
Auteur: 		Simon Lagac� et Olivier Lemay Dostie
Date cr�ation: 	11/28/2017
But: 			Classe qui repr�sente le menu principal ou l'utilisateur va pouvoir se connecter
====================================================================================================
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "painterFuction.h"
#include "inputMenu.h"

using namespace sf;
using namespace std;

#pragma once

#define MAX_NUMBER_OF_ITEMS 4

class mainMenu
{
private:
	RenderWindow _window;		//Fen�tre d'affichage

	Font _font;
	Text options[MAX_NUMBER_OF_ITEMS]; //Les differentes options du menu

	float _height;						//Hauteur de l'ecran
	float _width;							//Largeur de l'ecran
	int selectedIndex = 0;				//Index de l'option s�lectionn� 

	void setOptionsFont();				//Applique le font sur les options
	void setOptionsPosition();			//Applique la position des options

	void draw();						//Dessine le menu

	inputMenu* inputM = nullptr;		//Menu de input

public:
	mainMenu(float width, float height);	//Constructeur avec largeur et hauteur en param
	~mainMenu();

	void run();					//Boucle principal qui va runner le menu

	void moveUp();				//Monte dans les options
	void moveDown();			//Descend dans les options

	void enterOption();			//Fait une action selon l'option choisie
};
