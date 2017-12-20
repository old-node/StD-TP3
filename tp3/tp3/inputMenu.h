/* En-tête du programme
====================================================================================================
Fichier: 		painter.cpp (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
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
	Vector2f _sDim;
	RenderWindow _window;						//Fenêtre d'affichage
	Text texts[MAX_NUMBER_OF_ITEMS];			//Text pour les titres d'inputs
	Text inputs[MAX_NUMBER_OF_ITEMS];			//Text pour les inputs
	RectangleShape rect[MAX_NUMBER_OF_ITEMS];	//Tableau de rectangle pour les inputs
	RectangleShape recSelect;					//Rectangle qui indique quelle input est selectionnee
	string strInput[MAX_NUMBER_OF_ITEMS];
	int selectedIndex = 0;						//Defini quel input est selectionné
	Text badLog;

public:
	inputMenu(int width, int height);
	~inputMenu();

	void init()
	{
		badLog.setFont(D_F);
		badLog.setFillColor(Color::Black);
		badLog.setCharacterSize(60);
		badLog.setString("Informations invalides!");
		badLog.setPosition(50, 150);


		//Set les fonts et les couleurs
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			texts[i].setFont(D_F);
			texts[i].setFillColor(Color::Black);

			inputs[i].setFont(D_F);
			inputs[i].setFillColor(Color::Black);
			inputs[i].setCharacterSize(65);
		}

		texts[0].setString("Nom d'utilisateur :");
		texts[1].setString("Mot de passe :");

		inputs[0].setString("");
		inputs[1].setString("");

		texts[0].setPosition(50, 0);
		texts[1].setPosition(50, _sDim.y / 2);

		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			rect[i] = RectangleShape(Vector2f( - 100, _sDim.y/ 4));
			rect[i].setPosition((Vector2f(50, texts[i].getPosition().y + texts[i].getLocalBounds().height + 20)));
			rect[i].setFillColor(Color(98, 195, 98));
			inputs[i].setPosition((Vector2f(50, texts[i].getPosition().y + texts[i].getLocalBounds().height + 20)));
		}

		inputs[0].setString(strInput[0]);
		inputs[1].setString(strInput[1]);

		//Petit rectangle pour montrer quel input est selectionné
		recSelect.setSize(Vector2f(40, 40));
		recSelect.setFillColor(Color::Black);
		recSelect.setPosition(Vector2f(rect[0].getPosition().x - 45, rect[0].getPosition().y + 30));
	}

	void run();

	void draw();

	string getUsername()const;
	string getPassword()const;
};

