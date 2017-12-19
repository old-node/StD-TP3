/* En-tête du programme
====================================================================================================
Fichier: 		mainMenu.h (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Classe qui représente le menu principal ou l'utilisateur va pouvoir se connecter
====================================================================================================
*/

#include <iostream>
#include "inputMenu.h"


using namespace sf;
using namespace std;

#pragma once

#define MAX_NUMBER_OF_ITEMS 4

class mainMenu
{
private:
	RenderWindow _window;		//Fenêtre d'affichage

	Font _font;
	Text options[MAX_NUMBER_OF_ITEMS]; //Les differentes options du menu

	int _height;						//Hauteur de l'ecran
	int _width;							//Largeur de l'ecran
	int selectedIndex = 0;				//Index de l'option sélectionné 

	void setOptionsFont();				//Applique le font sur les options
	void setOptionsPosition();			//Applique la position des options

	void draw();						//Dessine le menu

	inputMenu* inputM = nullptr;		//Menu de input
	sqlConnect bd;						
	const char* username = "";
	const char* password = "";
	Text infoConnexion;					//Texte qui affiche qui est connecté
	string info = "Vous êtes connecté en tant que : ";

public:
	mainMenu(int width, int height);	//Constructeur avec largeur et hauteur en param
	~mainMenu();

	void run();					//Boucle principal qui va runner le menu

	void moveUp();				//Monte dans les options
	void moveDown();			//Descend dans les options

	void enterOption();			//Fait une action selon l'option choisie
	
};

