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
	sqlConnect bd;

	bd.userConnect("boby", "lamop");

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

		/*canva.addBsH();
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 1"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 2"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 3"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 4"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 5"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 6"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 7"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 8"));
		canva.addButton(new oB_link(0, 0, 0, 0, 1, P_2, P_L, "Bouton etc no. 9"));*/

		canva.addBsH();
		canva.addButton(new oB_save());
		canva.addButton(new oB_load());
		canva.addButton(new oB_menu());
		canva.addButton(new oB_quit());

		canva.addBsH();
		canva.addButton(new oB_cBox());
		canva.addButton(new oB_cCircle());
		canva.addButton(new oB_link());
		canva.addButton(new oB_select());
		canva.addButton(new oB_remove());

		//canva.addBsH();
		//canva.addButton(new oB_p1(P_A, P_B, "Jaune", P_A, P_B));
		//canva.addButton(new oB_p1(P_C, P_D, "Orange", P_C, P_D));
		//canva.addButton(new oB_p1(P_Y, P_Z, "Bleu", P_Y, P_Z));
		//canva.addButton(new oB_p1(P_H, P_I, "Gris", P_H, P_I));

		option = canva.run();

	} while (option == cMenu);

	if (option != cQuit)
		return -1;

	return 1;
}