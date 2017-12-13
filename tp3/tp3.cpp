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
	interface.addButton(oB_cBox());
	interface.addButton(oB_cCircle());
	interface.addButton(oB_remove());
	interface.addButton(oB_link());
	interface.addButton(oB_select());

	interface.run();

	return 1;
}

int mainOli()
{
	/*
	sqlConnect bd;
	bd.selectUsager();

	const char * nom = { "LastName\0" };
	const char * prenom = { "Uner\0" };

	bd.ajouteUsager(nom, prenom);
	*/

	/// Mettre la liste du bouton dans l'interface
	buttonStripH topBanner;
	topBanner.addButton(oB_cBox());
	topBanner.addButton(oB_cCircle());
	topBanner.addButton(oB_remove());
	topBanner.addButton(oB_link());
	topBanner.addButton(oB_select());
	topBanner.updateZone();
	FloatRect rectTB = topBanner.getZone();

	// Au cas où l'on veut implémenter des bannières à des positions différentes.
	///buttonStripH lowerBanner(false, false, Vector2f(0, SCREENH), Vector2f(SCREENW, SCREENH));
	///lowerBanner.addButton();
	///FloatRect rectLB = lowerBanner.getZone();
	///buttonStripV leftBanner;

	vector<oButton*> bOptionList;	// Pointeurs de toutes les options pour le curseur.

	for (auto & b : topBanner.getButtonList())
		bOptionList.push_back(&b);
	/*for (auto & b : lowerBanner.getButtonList())
	bOptionList.push_back(&b);
	for (auto & b : leftBanner.getButtonList())
	bOptionList.push_back(&b);*/

	/// Mettre bOptionList dans le curseur
	/// Les zones aussi
	// Dimmenssions des zones
	FloatRect _zones[static_cast<int>(rCOUNT)];

	/*
	sqlConnect bd;
	bd.selectUsager();

	const char * nom = { "LastName\0" };
	const char * prenom = { "Uner\0" };

	bd.ajouteUsager(nom, prenom);
	*/


	/* Tests */
	RectangleShape test(Vector2f(100, 500));
	test.setFillColor(Color(120, 210, 100, 130));
	Texture machin;
	machin.loadFromFile("machin.jpg");
	Sprite truc(machin);

	/*Text help("HELP ME", *FONT, 80);
	Text help3("DONT help", *FONT, 80);
	help.setPosition(Vector2f(60,88));
	help3.setPosition(Vector2f(60, 120));
	sandbox.draw(help);
	sandbox.draw(help3);

	sandbox.display();
	/* Fin des tests */


	RenderWindow sandbox		// Fenêtre principale ?
	(VideoMode(SCREENW, SCREENH), "Sandbox");

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

				for (auto & b : topBanner.getButtonList())
				{
					sandbox.draw(b.getBody());
					//sandbox.draw(b.getText());
				}
				sandbox.display();
			}
		}

		if (false)
			play = false;
	}

	system("pause");
	return 0;
}