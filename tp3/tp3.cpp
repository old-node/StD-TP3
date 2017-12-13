/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donn�e. Application de dessin.
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

// Programme principal
int main()
{
	setlocale(LC_CTYPE, "can");

	//mainSimon();

	/// Mettre la liste du bouton dans l'interface
	buttonStripH topBanner;
	topBanner.addButton(oB_cBox());
	topBanner.addButton(oB_cLine());
	topBanner.addButton(oB_remove());
	topBanner.addButton(oB_link());
	topBanner.addButton(oB_select());
	FloatRect rectTB = topBanner.getZone();
	
	// Au cas o� l'on veut impl�menter des banni�res � des positions diff�rentes.
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
	FloatRect _zones[static_cast<int>(rCOUNT)];	// Dimmenssions des zones

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


	RenderWindow sandbox		// Fen�tre principale ?
	(VideoMode(SCREENW, SCREENH), "Sandbox");

	vector<Vertex> v;			// Points rouges
	vector<Shape*> r;
	vector<RectangleShape> visible;
	cursor pointer(sandbox);	// Souris
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
				case Event::MouseButtonPressed:
					/// Doit exclure les zones sans boutons ici
					// 
					if (event.mouseButton.button == Mouse::Left)
						pointer.click();
					
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Left)
						if (pointer.unclick() == 1)
							r.push_back(pointer.getFocus());
					break;
				case Event::MouseMoved:
					/// Doit exclure les zones ayant des boutons ici ?
					if (pointer.isClicking())
					{
						pointer.drag();
						sandbox.draw(*pointer.getFocus()); /// ?
					}
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


int mainSimon()
{
	cout << "Bienvenue dans le main de Simon!" << endl;

	painter inte;
	inte.init();
	inte.run();

	system("pause");
	return 0;

}
/*for (auto & b : bOptions)
{
if (b->gotMouse(sandbox))
{

pointer.setMode(b);
pointer.unclick(Mouse::getPosition(sandbox));
b->drawFocus(sandbox);
cout << endl << "Unclicking ";
cursorPos(b, sandbox);
break;
}

}*/