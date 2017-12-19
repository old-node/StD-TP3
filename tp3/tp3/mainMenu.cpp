/* En-tête du programme
====================================================================================================
Fichier: 		mainMenu.cpp (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Classe qui représente le menu principal ou l'utilisateur va pouvoir se connecter
====================================================================================================
*/

#include "mainMenu.h"

//Attribu le font a tous les options 
void mainMenu::setOptionsFont()
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		options[i].setFont(_font);
}

//Donne la position a tous les options
void mainMenu::setOptionsPosition()
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		options[i].setPosition(Vector2f((_width / 2) - (options[i].getLocalBounds().width / 2),
			_height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1)));
	}
}

//Dessine le menu
void mainMenu::draw()
{
	_window.draw(infoConnexion);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		_window.draw(options[i]);
	}
}

mainMenu::mainMenu(int w, int h)
{
	_width = w;
	_height = h;

	_window.create(VideoMode(_width, _height), "The painter 3",0);	//Initialisation de la renderWindow

	//On applique le default font de painterFunction qui est arial
	_font = D_F;
	
	infoConnexion.setFont(_font);
	infoConnexion.setPosition(20, 20);
	infoConnexion.setCharacterSize(30);
	infoConnexion.setFillColor(Color::Black);
	infoConnexion.setString(info+=username);
	//On applique le font aux options
	setOptionsFont();

	//On applique les couleurs pour le menu
	options[0].setFillColor(sf::Color::Red);
	for (int i = 1; i <MAX_NUMBER_OF_ITEMS; i++)
	{
		options[i].setFillColor(sf::Color::Black);
	}

	//Texte des options du menu
	options[0].setString("Nouvelle connexion");
	options[1].setString("Nouveau dessin");
	options[2].setString("Charger un dessin");
	options[3].setString("Sortir");

	setOptionsPosition();

}


mainMenu::~mainMenu()
{
}

void mainMenu::run()
{
	while (_window.isOpen())
	{
		// Event processing
		Event event;
		while (_window.pollEvent(event))
		{
			if (inputM != nullptr)
			{
				_window.setVisible(false);
				inputM->run();
				bd.userConnect(inputM->getUsername(), inputM->getPassword());
				username = inputM->getUsername();
				password = inputM->getPassword();
				infoConnexion.setString(info += username);
				inputM = nullptr;
				delete inputM;
				_window.setVisible(true);
			}
			
			switch (event.type)
			{
			case Event::Closed:
				_window.close();
				break;
			case Event::KeyReleased :
				switch (event.key.code)
				{
				case Keyboard::Up:
					moveUp();
					break;
				case Keyboard::Down:
					moveDown();
					break;
				case Keyboard::Return:
					enterOption();
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		_window.clear(Color::Green);

		draw();

		_window.display();
	}
}

//Monte dans les options
void mainMenu::moveUp()
{
	if (selectedIndex - 1 >= 0)
	{
		options[selectedIndex].setFillColor(Color::Black);
		selectedIndex--;
		options[selectedIndex].setFillColor(Color::Red);

	}
	
}

//Descend dans les options
void mainMenu::moveDown()
{
	if (selectedIndex +1 < MAX_NUMBER_OF_ITEMS)
	{
		options[selectedIndex].setFillColor(Color::Black);
		selectedIndex++;
		options[selectedIndex].setFillColor(Color::Red);

	}
}

void mainMenu::enterOption()
{
	switch (selectedIndex)
	{
	case 0:
		inputM = new inputMenu(900, 500);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		_window.close();
		break;
	default:
		break;
	}
}

