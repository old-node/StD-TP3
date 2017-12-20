/* En-tête du programme
====================================================================================================
Fichier: 		mainMenu.h (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Classe qui représente le menu principal ou l'utilisateur va pouvoir se connecter
====================================================================================================
*/

#pragma once
#include <iostream>
using namespace std;

#include "painterFuction.h"
#include "inputMenu.h"
#include <SFML/Graphics.hpp>
using namespace sf;

#define MAX_NUMBER_OF_ITEMS 4


// Menu principal
class mainMenu
{
private:
	RenderWindow _window;		//Fenêtre d'affichage

	Font _font;
	Text options[MAX_NUMBER_OF_ITEMS]; //Les differentes options du menu

	Vector2i _sDim;						//Dimmenssions de l'écran
	int selectedIndex = 0;				//Index de l'option sélectionné 

	void setOptionsFont();				//Applique le font sur les options
	void setOptionsPosition();			//Applique la position des options

	void draw();						//Dessine le menu

	inputMenu* inputM = nullptr;		//Menu de input

public:
	mainMenu(int width, int height);	//Constructeur avec largeur et hauteur en param
	~mainMenu();

	void run();					//Boucle principal qui va runner le menu

	void moveUp();				//Monte dans les options
	void moveDown();			//Descend dans les options

	void enterOption();			//Fait une action selon l'option choisie
};
