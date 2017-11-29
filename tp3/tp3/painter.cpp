/* En-tête du programme
====================================================================================================
Fichier: 		painter.cpp (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Classe qui reprente l'interface ou l'on va pouvoir dessiner et cliquer sur les
differents boutons
====================================================================================================
*/

#include "painter.h"


//Constructeur sans parametre
painter::painter()
{
	
}

//Initiatlise l'interface
void painter::init()
{
	window.create(VideoMode(sWeight, sHeight), "Test de simon");	
}

//void interface::show()
//{
//	window.display();
//}

//Va afficher l'interface et gèrer les evements
//Un peu comme une boucle de main...
void painter::run()
{
	init();
	RectangleShape menuGauche(Vector2f(100, sHeight));
	RectangleShape menuHaut(Vector2f(sWeight, 100));
	menuGauche.setFillColor(Color(120, 210, 100, 130));
	menuHaut.setFillColor(Color(120, 210, 100, 130));

	Vector2f mousePos, posInit, posEnd;
	bool drag = false;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;
				case Event::MouseMoved:
					mousePos = (Vector2f)Mouse::getPosition(window);
					//cout << "Position en X : " << mousePos.x << endl;
					//cout << "Position en Y : " << mousePos.y << endl;
					if(drag)
						menuGauche.setSize(mousePos - posInit);
					break;
				case Event::MouseButtonPressed:
					if (event.mouseButton.button == Mouse::Left)
					{
						drag = true;
						posInit = (Vector2f)Mouse::getPosition(window);
						menuGauche.setPosition(posInit);
						menuGauche.setSize(Vector2f());
					}
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Left)
					{
						drag = false;
						posEnd = mousePos;
						menuGauche.setSize(posEnd - posInit);
					}
						
					break;
				default :
					break;
						
			}
			window.clear(Color::Black);

			
			
			window.draw(menuHaut);
			window.draw(menuGauche);
			window.display();
		}
			
	}

}

void painter::clear()
{

}



