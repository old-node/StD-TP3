/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donnée. Application de dessin.
======================================================================================*/


#include <locale>
#include <iostream>
using namespace std;

#include "tp3\sqlConnect.h"
#include "tp3\painter.h"
#include "tp3\buttonStrip.h"
#include "cursor.h"
#include "tp3\mainMenu.h"
#include "tp3\inputMenu.h"
using namespace sf;


/* Prototypes */

int mainSimon();
int interfaceOli();



// Programme principal
int main()
{
	setlocale(LC_CTYPE, "can");

	//mainSimon();
	interfaceOli();
}


int mainSimon()
{
	cout << "Bienvenue dans le main de Simon!" << endl;
	mainMenu menu(800, 500);
	menu.run();
	/*sqlConnect bd;

	bd.userConnect("boby", "lamop");*/

	system("pause");

	return 0;

}

int interfaceOli()
{
	int option = 0;

	do
	{
		mainMenu menu(800, 500);
		menu.run();

		painter canva;

		canva.addBsH();
		canva.addButton(new oB_save());
		canva.addButton(new oB_load());
		canva.addButton(new oB_menu());
		canva.addButton(new oB_quit());
		canva.addBsH();
		canva.addButton(new oB_cBox());
		canva.addButton(new oB_cCircle());
		canva.addButton(new oB_remove());
		canva.addButton(new oB_link());
		canva.addButton(new oB_select());

		option = canva.run();

	} while (option == cMenu);

	if (option != cQuit)
		return -1;

	return 1;
}