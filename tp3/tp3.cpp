/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donn�e. Application de dessin.
======================================================================================*/


#include <locale>
#include <iostream>


#include "tp3\sqlConnect.h"
#include "tp3\painter.h"
#include "tp3\buttonStrip.h"
#include "cursor.h"
#include "tp3\mainMenu.h"
#include "tp3\inputMenu.h"

using namespace std;
using namespace sf;

int mainSimon();
int mainOli();
int interfaceOli();

// Programme principal
int main()
{
	setlocale(LC_CTYPE, "can");

	//mainSimon();
	//mainOli();
	interfaceOli();
}


int mainSimon()
{
	cout << "Bienvenue dans le main de Simon!" << endl;
	mainMenu menu(800, 500);

	menu.run();

	return 0;

}

int interfaceOli()
{
	int option = 0;

	do
	{
		mainMenu menu(800, 500);
		menu.run();

		painter canva;
		canva.addBsH();
		canva.addButton(new oB_cBox());
		canva.addButton(new oB_cCircle());
		//inter.addButton(new oB_link());
		canva.addButton(new oB_select());
		canva.addButton(new oB_remove());
		canva.addButton(new oB_save());
		canva.addButton(new oB_load());
		canva.addButton(new oB_menu());
		canva.addButton(new oB_quit());

		option = canva.run();

	} while (option == cMenu);
	

	return 1;
}

int mainOli()
{
	/* Tests */
	RectangleShape test(Vector2f(100, 500));
	test.setFillColor(Color(120, 210, 100, 130));
	Texture machin;
	machin.loadFromFile("machin.jpg");
	Sprite truc(machin);

	RenderWindow sandbox		// Fen�tre principale ?
	(VideoMode((unsigned int)SCREENW, (unsigned int)SCREENH), "Sandbox");

	/*Text help("HELP ME", *FONT, 80);
	Text help3("DONT help", *FONT, 80);
	help.setPosition(Vector2f(60,88));
	help3.setPosition(Vector2f(60, 120));
	sandbox.draw(help);
	sandbox.draw(help3);

	sandbox.display();
	/* Fin des tests */
	
	vector<Vertex> v;			// Points rouges
	vector<Shape*> r;
	vector<RectangleShape> visible;
	cursor pointer;				// Souris
	Event event;				// �v�nement de l'application

	sandbox.clear();
	sandbox.draw(truc);
	sandbox.draw(test);
	sandbox.display();

	//system("pause");


	bool play = true;
	while (play)
	{
		while (sandbox.isOpen())
		{
			while (sandbox.pollEvent(event))
			{
				sandbox.clear();
				visible.clear();

				switch (event.type)
				{
				case Event::Closed:
					exit(0);
				case Event::KeyPressed:
					if (event.key.code == Keyboard::Escape)
						exit(0);
				case Event::MouseMoved:
					/// Doit exclure les zones ayant des boutons ici ?
					/*if (pointer.isClicking())
					{
					pointer.drag();
					sandbox.draw(*pointer.getFocus()); /// ?
					}*/
					v.push_back(Vertex((Vector2f)Mouse::getPosition(sandbox),
						Color::Red, (Vector2f)Mouse::getPosition(sandbox)));
					break;
				default:
					break;
				}

				for (const auto & V : v)
					sandbox.draw(&V, 1, PrimitiveType::Points);
				for (const auto & R : r)
					sandbox.draw(*R);

				sandbox.display();
			}
		}

		if (false)
			play = false;
	}

	system("pause");
	return 0;
}