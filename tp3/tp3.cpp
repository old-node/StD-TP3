/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donnée. Application de dessin.
======================================================================================*/


#include <locale>
#include <iostream>
using namespace std;
//#include "tp3\sqlConnect.h"
#include "tp3\painter.h"
#include "tp3\buttonStrip.h"
#include "cursor.h"
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

	painter interface;
	interface.init();
	interface.run();

	system("pause");
	return 0;

}

int interfaceOli()
{
	painter interface;

	interface.addBsH();
	interface.addButton(new oB_cBox());
	interface.addButton(new oB_cCircle());
	interface.addButton(new oB_remove());
	interface.addButton(new oB_link());
	interface.addButton(new oB_select());

	interface.run();

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

	RenderWindow sandbox		// Fenêtre principale ?
	(VideoMode(SCREENW, SCREENH), "Sandbox");

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
	cursor pointer();			// Souris
	Event event;				// Événement de l'application

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
				case Event::MouseButtonPressed:
					/// Doit exclure les zones sans boutons ici
					// 
					if (event.mouseButton.button == Mouse::Left)
						;// pointerclick();

					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Left)
						;// if (pointer.unclick() == 1)
						 //r.push_back(pointer.getFocus());
					break;
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