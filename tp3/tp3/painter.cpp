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
	_label.setFont(D_F);
	_label.setCharacterSize(22);
	_label.setFillColor(Color::White);
	_label.setOrigin(Vector2f(0, 50));
	_label.setPosition(Vector2f(20, (float)_sHeight));
}

//Initiatlise l'interface
void painter::init()
{
	_window.create(VideoMode(_sWidth, _sHeight), "Test de simon");	//Initialisation de la render window
	iteratorShape = listShape.begin();	//Initialisation de l'iterateur
}

//void painter::show()
//{
//	_window.display();
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
					
					//Regarde si on est dans un buttonstrip
					_cursorInterface.setOnZone(isOnAZone());
					if (isOnAZone())
						if (isOnButton()->getMode() == cCreate)
							cout << "Release sur cCreate!!!!!" << mousePos.x << endl;
		
					if (_cursorInterface.getClicking())
					{
						_cursorInterface.drag();
					}
					break;
				case Event::MouseButtonPressed:
					if (event.mouseButton.button == Mouse::Left)
					{
						
						if (!listShape.empty() && _cursorInterface.getModeCurs() == cSelect && selectedShape(mousePos) != nullptr)
						{
							_cursorInterface.setFocus(*selectedShape(mousePos));
							_cursorInterface.setSelected(true);
						}
						else if (_cursorInterface.getModeCurs() == cRemove)
							_label.setString("Remove");
						else
							_cursorInterface.setSelected(false);


						_cursorInterface.click(); //On fait cliquer le curseur
					}
					break;
				case Event::MouseButtonReleased:
					if (event.mouseButton.button == Mouse::Left)
					{	
						if (isOnAZone())
							if (isOnButton() != nullptr)
								_cursorInterface.setMode(isOnButton());

						switch (_cursorInterface.getModeCurs())
						{
						case cSelect:
							if (!listShape.empty())
							{
								selectShape = nullptr;
								_cursorInterface.releaseClick();
							}
							break;
						case cCreate:
							//On push la nouvelle forme dans la liste si on est pas sur un bouton strip
							if (!isOnAZone())
								listShape.push_back(_cursorInterface.releaseClick());
							break;
						case cRemove:
							if (!listShape.empty() && (searchShape(_cursorInterface.getClick()) != listShape.end()))
							{
								listShape.erase(searchShape(_cursorInterface.getClick()));
							}
							break;
						default:
							break;
						}
					}		
					break;

				default :
					break;	
			}

			_window.clear(Color::Black);

			drawListShape();

			if(_cursorInterface.getModeCurs() != cRemove)
				_window.draw(*_cursorInterface.getFocus().shapePtr);

			drawButtonstrips();
			_window.draw(_label);

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
			_window.draw(b.getText());
		}
	}
}

bool painter::findShape() const
{
	return false;
}

//Retourne la shape selon une position
//Retourne nullptr si elle n'est pas trouvée
shape* painter::selectedShape(Vector2f mousePos)
{
	assert(!listShape.empty());
	list<shape>::iterator it = listShape.end();
	//On parcourt la liste
	it = searchShape(mousePos);
	if (it == listShape.end())
		return nullptr;
	else
		return &*it;
}

//Cherche une shape dans le vecteur et retourne l'iterateur ou la shape est
//selon une position donnee
list<shape>::iterator painter::searchShape(Vector2f pos)
{
	assert(!listShape.empty());
	list<shape>::iterator it = listShape.end();

	do
	{
		it--;
		if (it->shapePtr->getGlobalBounds().intersects(FloatRect(pos, Vector2f(1, 1))))
			return it;
	} while (it != listShape.begin());

	//Si la boucle est fini sans qu'on retourne l'iterateur,
	//On retourne l'iterateur a la fin
	it = listShape.end();
	return it;
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
	_cursorInterface.addButton(&_bs->getButtonList().back());
}

bool painter::isOnAZone()
{
	for (auto & s : _bsH)
		if (_cursorInterface.onZone(s->getZone(), _window))
			return true;
	for (auto & s : _bsV)
	if (_cursorInterface.onZone(s->getZone(), _window))
	return true;
	return false;
}

buttonStrip * painter::isOnZone()
{
	for (auto & s : _bsH)
		if (_cursorInterface.onZone(s->getZone(), _window))
			return s;
	for (auto & s : _bsV)
	if (_cursorInterface.onZone(s->getZone(), _window))
	return s;
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



