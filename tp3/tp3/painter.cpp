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
	_window.create(VideoMode(_sWidth, _sHeight), "Test de simon");	//Initialisation de la render window
	iteratorShape = listShape.begin();	//Initialisation de l'iterateur
}

void painter::show()
{
	_window.display();
}

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
			drawButtonstrips();
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

//Dessine les formes de la liste

void painter::drawButtonstrips()
{
	
	for (auto & s : _bsH)
	{
		_window.draw(s->getOverlay());
		for (auto & b : s->getButtonList())
		{
			_window.draw(b.getBody());
			//_window.draw(b.getText());
		}
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

// Ajoute une bannière horizontale à l'interface.
void painter::addBsH(bool normalScope, bool normalInterval, Vector2f initPos, Vector2f limitPos, bool fixed, Vector2f minDim)
{
	assert(limitPos.x >= initPos.x
		&& limitPos.y >= initPos.y);

	if (limitPos.x == 0)
		limitPos.x = _sWidth;
	if (limitPos.y == 0)
		limitPos.y = _sHeight;

	// Une erreur se produit à la destruction de la copie
	_bsH.push_back(new buttonStripH(normalScope, normalInterval,
		initPos, limitPos, fixed, minDim));
	_bs = _bsH.back();		// Change la bannière active
}

// Ajoute un bouton dans la bannière active.
void painter::addButton(oButton b)
{
	assert(_bs != nullptr);
	_bs->addButton(b);
	_bs->updateZone();
}

bool painter::isOnAZone()
{
	for (auto & s : _bsH)
		if (_cursorInterface.onZone(s->getZone(), _window))
			return true;
	/*for (auto & s : _bsV)
	if (_cursorInterface.onZone(s->getZone(), _window))
	return true;*/
	return false;
}

buttonStrip * painter::isOnZone()
{
	for (auto & s : _bsH)
		if (_cursorInterface.onZone(s->getZone(), _window))
			return s;
	/*for (auto & s : _bsV)
	if (_cursorInterface.onZone(s->getZone(), _window))
	return s;*/
	return nullptr;
}

oButton * painter::isOnButton()
{
	for (auto & s : _bsH)
		for (auto & b : s->getButtonList())
			if (_cursorInterface.onZone(b.RectangleShape::getGlobalBounds(), _window))
				return &b;
	return nullptr;
}



