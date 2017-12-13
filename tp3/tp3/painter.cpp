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
#include <stdlib.h>

//Constructeur sans parametre
painter::painter()
{
	
}

//Initiatlise l'interface
void painter::init()
{
	_window.create(VideoMode(_sWeight, _sHeight), "Test de simon");	//Initialisation de la render window
	iteratorShape = listShape.begin();	//Initialisation de l'iterateur
}

//void interface::show()
//{
//	window.display();
//}

//Va afficher l'interface et gèrer les evenements
//Un peu comme une boucle de main...
void painter::run()
{
	init();

	Vector2f mousePos , mouseInit;

	while (_window.isOpen())
	{
		Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					_window.close();
					break;
				case Event::MouseMoved:
					mousePos = (Vector2f)Mouse::getPosition(_window);
					_cursorInterface.setCurrent(mousePos); //On met le current du cursor avec la position
					//cout << "Position en X : " << mousePos.x << endl;
					//cout << "Position en Y : " << mousePos.y << endl;
					if (_cursorInterface.getClicking())
					{
						_cursorInterface.drag();
						
						//if (!listShape.empty() && _cursorInterface.getModeCurs() == cSelect && selectShape != nullptr)
						//{
						//	//selectShape->shapePtr->move(_cursorInterface.getCurrent() - selectShape->shapePtr->getPosition());
						//	//_cursorInterface.getFocus().shapePtr->move(_cursorInterface.getCurrent() - selectShape->shapePtr->getPosition());
						//}	
					}
					break;
				case Event::MouseButtonPressed:
					if (event.mouseButton.button == Mouse::Left)
					{
						if (!listShape.empty() && _cursorInterface.getModeCurs() == cSelect && selectedShape(mousePos)!=nullptr)
						{
							_cursorInterface.setFocus(*selectedShape(mousePos));
							_cursorInterface.setSelected(true);
							//selectShape = selectedShape(mousePos);
						}
						else
							_cursorInterface.setSelected(false);

						_cursorInterface.click(); //On fait cliquer le curseur
					}
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Left)
					{	
						
						if (!listShape.empty() && _cursorInterface.getModeCurs() == cSelect)
						{
							selectShape = nullptr;
							_cursorInterface.releaseClick();
						}
						else if (_cursorInterface.getModeCurs() == cCreate)
						{
							//On push la nouvelle forme dans la liste
							listShape.push_back(_cursorInterface.releaseClick());
						}

						
					}		
					break;
				case Event::KeyPressed:
					if (event.key.code == sf::Keyboard::M)
					{
						_cursorInterface.changeMode();
					}
				default :
					break;	
			}

			_window.clear(Color::Black);
			drawListShape();
			//_window.draw(*_cursorInterface.getFocus().shapePtr);
			_window.display();
		}
			
	}

}

//Nettoie l'interface
void painter::clear()
{

}

//Dessine les formes de la liste
void painter::drawListShape()
{
	list<shape>::iterator it = listShape.begin();
	while (it != listShape.end())
	{
		_window.draw(*it->shapePtr);
		it++;
	}
}

shape* painter::selectedShape(Vector2f mousePos)
{
	list<shape>::iterator it = listShape.end();
	//On parcourt la liste
	do
	{
		it--;
		if (it->shapePtr->getGlobalBounds().intersects(FloatRect(mousePos, Vector2f(1, 1))))
			return &*it;
	}while(it != listShape.begin());

	return nullptr;
}



