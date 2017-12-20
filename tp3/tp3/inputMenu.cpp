/* En-tête du programme
====================================================================================================
Fichier: 		inputMenu.cpp (TP3)
Auteur: 		Simon Lagacé et Olivier Lemay Dostie
Date création: 	11/28/2017
But: 			Petit menu qui permet d'entrer un nom d'utilisateur et un mot de passe
====================================================================================================
*/


#include "inputMenu.h"


/// Initialisation
// Constructeur
inputMenu::inputMenu(int w, int h)
{
	_window.create(VideoMode(w, h), "Entrez votre nom", Style::None);

	_sDim = Vector2f((float)w, (float)h);

	//Set les fonts et les couleurs
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		texts[i].setFont(D_F);
		texts[i].setFillColor(Color::Black);

		inputs[i].setFont(D_F);
		inputs[i].setFillColor(Color::Black);
		inputs[i].setCharacterSize(65);
	}
	
	texts[0].setString("Nom d'utilisateur :");
	texts[1].setString("Mot de passe :");

	inputs[0].setString("");
	inputs[1].setString("");

	texts[0].setPosition(50, 0);
	texts[1].setPosition(50, _sDim.y/2);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		rect[i] = RectangleShape(Vector2f(_sDim.x - 100, _sDim.y/4));
		rect[i].setPosition((Vector2f(50, 
			texts[i].getPosition().y + texts[i].getLocalBounds().height + 20)));
		rect[i].setFillColor(Color(98, 195, 98));
		inputs[i].setPosition((Vector2f(50, 
			texts[i].getPosition().y + texts[i].getLocalBounds().height + 20)));
	}

	inputs[0].setString(strInput[0]);
	inputs[1].setString(strInput[1]);

	//Petit rectangle pour montrer quel input est selectionné
	recSelect.setSize(Vector2f(40,40));
	recSelect.setFillColor(Color::Black);
	recSelect.setPosition(Vector2f(
		rect[0].getPosition().x - 45, rect[0].getPosition().y + 30));
}
// Destructeur
inputMenu::~inputMenu()
{
}

/// Actions
// Boucle principale
void inputMenu::run()
{
	string invisiblePass;

	while (_window.isOpen())
	{
		
		// Event processing
		Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				_window.close();
				break;
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Return:
					_window.close();
					break;
				case Keyboard::Tab:
					selectedIndex = (selectedIndex+1)%MAX_NUMBER_OF_ITEMS;
					recSelect.setPosition(Vector2f(rect[selectedIndex].getPosition().x - 45,
						rect[selectedIndex].getPosition().y + 30));
					break;
				default:
					break;
				}
				break;
			case Event::TextEntered:
				if (
					((event.key.code >= 97 && event.key.code <= 122)
						|| event.key.code == 32
						|| (event.key.code >= 48 && event.key.code <= 57))
					&& (strInput[selectedIndex].size() <= 20))	// caractere ASCII (A - Z, 0 - 9 )
				{
					if (selectedIndex == 1)
					{
						invisiblePass.push_back('*');
					}
					strInput[selectedIndex].push_back((char)event.text.unicode); // ajoute un char a la string
				}
				if (event.key.code == 8 && strInput[selectedIndex].size() != 0)		// touche backspace
				{
					if (selectedIndex == 1)
					{
						invisiblePass.pop_back();
					}
					strInput[selectedIndex].pop_back();			// Enleve le dernier char dans la string
				}
				if (selectedIndex == 1)
					inputs[1].setString(invisiblePass);
				else
					inputs[selectedIndex].setString(strInput[selectedIndex]);
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
// Affichage
void inputMenu::draw()
{
	_window.draw(recSelect);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		_window.draw(texts[i]);
		_window.draw(rect[i]);
		_window.draw(inputs[i]);
	}
}

/// Getteurs
// 
string inputMenu::getUsername() const
{
	return strInput[0];
}
// 
string inputMenu::getPassword() const
{
	return strInput[1];
}
