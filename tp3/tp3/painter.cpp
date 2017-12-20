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
#include "sqlStructs.h"
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
	//Initialisation de la render window
	_window.create(VideoMode(
		(unsigned int)_sWidth, (unsigned int)_sHeight), "The Painter f3");
	_iteratorShape = _listShape.begin();	//Initialisation de l'iterateur
}

//void painter::show()
//{
//	_window.display();
//}

//Va afficher l'interface et gèrer les evenements
//Un peu comme une boucle de main...
int painter::run()
{
	init();

	Vector2f mousePos, mouseInit;

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
				cout << "MousePos X :" << mousePos.x << endl;
				cout << "MousePos Y :" << mousePos.y << endl;
				//Regarde si on est dans un buttonstrip
				_cursorInterface.setOnZone(isOnAZone());

				_cursorInterface.drag();

				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					if (_cursorInterface.isOnZone())
					{
						oButton * b = isOnButton();
						int option = 0;
						if (b != nullptr)
							option = _cursorInterface.setMode(b);
						switch (option)
						{
						case 0:
						default:
							break;
						case cSave:
							/// sauvegarde des formes
							generateSave();
							break;
						case cLoad:
							break;
						case cMenu:
							return cMenu;
							break;
						case cQuit:
							return cQuit;
							break;
						}
					}
					else
						_cursorInterface.click();

				}
				break;
			case Event::MouseButtonReleased:
				if (event.mouseButton.button == Mouse::Left)
				{
					if (!isOnAZone())
						_cursorInterface.releaseClick();
					else
						_cursorInterface;
				}
				break;
			default:
				break;
			}

			_window.clear(Color::Black);

			/*for (auto & s : _selected)
				s._it->shapePtr->setFillColor(Color::Blue);*/

			drawListShape();

			if (_cursorInterface.getModeCurs() != cDefault)
				_window.draw(*_cursorInterface.getFocus().shapePtr);

			drawButtonstrips();
			_window.draw(_label);

			_window.display();
		}
	}

	return 0;
}

//Nettoie l'interface
void painter::clear()
{

}

//Dessine les formes de la liste
void painter::drawListShape()
{
	list<shape>::iterator it = _listShape.begin();
	while (it != _listShape.end())
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
			_window.draw(b->getBody());
			_window.draw(b->getText());
		}
	}
}

bool painter::findShape() const
{
	return false;
}

//Cherche une shape dans le vecteur et retourne l'iterateur ou la shape est
//selon une position donnee
list<shape>::iterator painter::searchShape(Vector2f pos)
{
	assert(!_listShape.empty());
	list<shape>::iterator it = _listShape.end();

	do
	{
		it--;
		if (it->shapePtr->getGlobalBounds().intersects(FloatRect(pos, Vector2f(1, 1))))
			return it;
	} while (it != _listShape.begin());

	//Si la boucle est fini sans qu'on retourne l'iterateur,
	//On retourne l'iterateur a la fin
	it = _listShape.end();
	return it;
}

// Ajoute une bannière horizontale à l'interface.
void painter::addBsH(bool normalScope, bool normalInterval, Vector2f initPos, Vector2f limitPos, bool fixed, Vector2f minDim)
{
	if (!_bsH.empty() && _bsH.back() != nullptr && initPos.y == 0)
		initPos.y = _bsH.back()->getLowerRightCorner().y;

	if (limitPos.x == 0)
		limitPos.x = _sWidth;
	if (limitPos.y == 0)
		limitPos.y = _sHeight;

	assert(limitPos.x >= initPos.x
		&& limitPos.y >= initPos.y);

	if (!_bsH.empty())
	{
		//initButtonSize();
		initPos.y += TOLH;
	}

	_bsH.push_back(new buttonStripH(normalScope, normalInterval,
		initPos, limitPos, fixed, minDim));
	_bs = _bsH.back();		// Change la bannière active
}

// Ajoute un bouton dans la bannière active.
void painter::addButton(oButton * b)
{
	assert(_bs != nullptr);
	_bs->addButton(b);
	_bs->getButtonList().back()->initCursorData(_cursorInterface.getCurrent(),
		_cursorInterface.getClick(), &_listShape, &_selected);
	_bs->updateZone();
	///_cursorInterface.addButton(_bs->getButtonList().back());
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
	{
		for (auto & b : s->getButtonList())
		{
			if (_cursorInterface.onZone(b->RectangleShape::getGlobalBounds(), _window))
				return b;
		}
	}
	return nullptr;
}



