/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donn�e. Application de dessin.
======================================================================================*/


#include <locale>
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
using namespace std;
#include <SFML/Graphics.hpp>
#include "cursor.h"
using namespace sf;




#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

//Variable SQL
SQLHANDLE sqlConnHandle;
SQLHANDLE sqlStmtHandle;
SQLHANDLE sqlEnvHandle;
SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];


const float SCREENW = 800;
const int NBBUTTON = 5;
const float BW = SCREENW / NBBUTTON;


void connexion();
void deconnexion();
void selectUsager();
void ajouteUsager(char *nom, char *prenom);



// Programme principal
int main()
{
	setlocale(LC_CTYPE, "can");

	RenderWindow sandbox;
	sandbox.create(VideoMode(SCREENW, 800), "Sandbox");

	Color tColor;
	Font font;
	font.loadFromFile("styles/font_arial.ttf");

	vector<oButton*> bOptions;
	bOptions.push_back(new oB_cBox(0, 0, BW, 30, font, "Boite"));
	bOptions.push_back(new oB_cLine(BW, 0, BW, 30, font, "Ligne"));
	bOptions.push_back(new oB_remove(BW * 2, 0, BW, 30, font, "Effacer"));
	bOptions.push_back(new oB_link(BW * 3, 0, BW, 30, font, "Lier"));
	bOptions.push_back(new oB_select(BW * 4, 0, BW, 30, font, "S�lectionner"));
	vector<Vertex> s;

	cursor pointer;

	Event event;

	//system("pause");

	/* Tests */
	RectangleShape test(Vector2f(100, 500));
	test.setFillColor(Color(120, 210, 100, 130));
	Texture machin;
	machin.loadFromFile("images/machin.jpg");
	Sprite truc(machin);
	sandbox.draw(truc);
	sandbox.draw(test);
	/* Fin des tests */

	bool play = true;
	while (play)
	{
		while (sandbox.isOpen())
		{
			while (sandbox.pollEvent(event))
			{
				sandbox.clear();

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

					for (auto & b : bOptions)	// Pour chaque bouton d'options
					{
						// V�rifie si l'utilisateur clique sur le bouton
						if (b->gotMouse(sandbox))
						{
							pointer.setMode(b);
							pointer.click(Mouse::getPosition(sandbox));

							cout << "A click was made in the button whos origin is at : ("
								<< b->RectangleShape::getOrigin().x << ","
								<< b->RectangleShape::getOrigin().y << "), the mouse was at : ("
								<< Mouse::getPosition(sandbox).x << ","
								<< Mouse::getPosition(sandbox).y << ").";
							break;
						}
					}

					break;
				case Event::MouseButtonReleased:

					for (auto & b : bOptions)
					{
						if (b->gotMouse(sandbox))
						{
							pointer.setMode(b);
							pointer.unclick(Mouse::getPosition(sandbox));
							b->drawFocus(sandbox);
							cout << "A click was released in the button whos origin is at : ("
								<< b->RectangleShape::getOrigin().x << ","
								<< b->RectangleShape::getOrigin().y << "), the mouse was at : ("
								<< Mouse::getPosition(sandbox).x << ","
								<< Mouse::getPosition(sandbox).y << ").";
							break;
						}
					}

					break;
				case Event::MouseMoved:
					/// Doit exclure les zones ayant des boutons ici
					// 

					s.push_back(Vertex((Vector2f)Mouse::getPosition(sandbox),
						Color::Red, (Vector2f)Mouse::getPosition(sandbox)));

					for (auto & b : bOptions)
					{
						if (b->gotMouse(sandbox))
						{
							b->RectangleShape::setFillColor(Color::Black);
							break;
						}
					}

					if (pointer.getClicking())
						pointer.drag(Mouse::getPosition(sandbox));
					break;
				default:
					break;
				}

				for (auto & b : bOptions)
					b->draw(sandbox);
				for (const auto & p : s)
					sandbox.draw(&p, 1, sf::PrimitiveType::Points);

				//pointer.drawFocus(sandbox);

				sandbox.display();
			}
		}

		if (false)
			play = false;
	}

	system("pause");

	return 0;
}


void connexion() {
	//Initialisations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;


	try
	{
		//Allocations
		if (!((SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) 
			|| (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) 
			|| (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)))) {
			//Affichage
			cout << "Tentative de connexion";
			cout << "\n";

			//Connexion au SQL Server
			switch (SQLDriverConnect(sqlConnHandle, NULL,
				(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=demo;UID=sa;PWD=user123;", 
				SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {

			case SQL_SUCCESS:
				cout << "Connexion reussi";
				cout << "\n";


				break;
			case SQL_SUCCESS_WITH_INFO:
				cout << "Connexion reussi";
				cout << "\n";

				break;
			case SQL_INVALID_HANDLE:
				throw string("Erreur de connexion");

			case SQL_ERROR:
				throw string("Erreur de connexion");
			default:
				throw string("Erreur");
				break;
			}

			//Si la connexion est impossible
			if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
				throw string("Connexion impossible");
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";
		deconnexion();

		cout << "\n Appuyer sur Retour pour fermer ...";
		getchar();
		exit(1);
	}

}

void deconnexion() {

	cout << "Deconnexion ..." << "\n";

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

void selectUsager() {

	try
	{
		connexion();

		//S'il y a un probl�me avec la requ�te on quitte l'application sinon on affiche le r�sultat
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, 
			(SQLWCHAR*)L"SELECT usagerprenom, usagernom FROM usager", SQL_NTS)) {
			throw string("Erreur dans la requ�te");
		}
		else {
			//D�clarer les variables d'affichage

			SQLCHAR nom[SQL_RESULT_LEN];
			SQLINTEGER ptrnom;

			SQLCHAR prenom[SQL_RESULT_LEN];
			SQLINTEGER ptrprenom;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_CHAR, prenom, SQL_RESULT_LEN, &ptrprenom);
				SQLGetData(sqlStmtHandle, 2, SQL_CHAR, nom, SQL_RESULT_LEN, &ptrnom);

				//Afficher le r�sultat d'une requ�te			
				cout << nom << "  " << prenom << endl;
			}
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";
		deconnexion();
	}

	deconnexion();
}



void ajouteUsager(char *nom, char *prenom) {

	try
	{
		connexion();

		SQLRETURN retcode;

		/*
		Param�tre SQLBindParameter:
		- Handler de la requ�te
		- No du param�tre (commence � 1)
		- Est-ce un param�tre de type Input ou Output
		- Quel est le type de la variable en C++
		- Quel est le type de la variable en SQL
		- Quelle est la taille de la colonne dans la BD
		- Nombre de d�cimal
		- Quelle variable ou donn�es (pointeur)
		- Longueur du buffer
		- Pointeur du buffer
		*/
		retcode = SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, 
			SQL_C_CHAR, SQL_CHAR, 50, 0, prenom, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, 
			SQL_C_CHAR, SQL_CHAR, 50, 0, nom, 0, 0);

		retcode = SQLPrepare(sqlStmtHandle, 
			(SQLWCHAR*)L"INSERT INTO Usager (usagerprenom, usagernom) VALUES (?, ?)", SQL_NTS);

		retcode = SQLExecute(sqlStmtHandle);

		if (SQL_SUCCESS != retcode) {
			throw string("Erreur dans la requ�te");
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";

		deconnexion();

		getchar();
		exit(1);
	}

	deconnexion();
}


/*	TP3
============
/////// Interfaces � Structure de donn�es
Pour que SFML soit op�rationnel, il faut suivre le guide suivant:
https://www.sfml-dev.org/tutorials/2.4/start-vc-fr.php
Les classes pr�c�d�s de '^' sont n�cessaires pour l'applications
Celles pr�c�d�s de '�' sont fortement souhait�es
Il va fauloir dabors faire fonctionner sfml avant de pouvoir se s�parer les t�ches.
///////
__Classes
�::Save()				// Pour le TP3 de SQL
�::Load()				// idem
::Parameters()
^::Operations()			// Liste des outils graphique disponible de l'application
+ 1 for each tools?
^::Interface()			// Lieu d'affichage et de dessins
^::Window()			// Fen�tre qui contiens l'interface
^::Button()			// Boutons de commandes d'options et d'op�rations
^::Cursor()			// Curseur de la souris pour les op�rations graphiques manuelles
^::History()		// Contiens les op�rations pass�s et 'futures'
::Runtime()
::Clipboard()
^::Object()				// Objet parent qui permet la cr�ation et l'affichage de formes
^::Label()			// �tiquette de text
^::Square()			// Forme simple rectangulaire
�::Line()			// Forme simple lin�aire
::Dot()
::Template()
::Custom()
__Op�rations sur les objets
^::Add()				// Ajoute un objet � la fen�tre
Si possible (Si aucune autre op�ration est en cours),
Commencer la cr�ation d'un objet
TQ l'objet n'est pas compl�t�, au click
Compl�ter une partie de l'objet
Terminer la cr�ation d'un objet
__Undo + Redo
^::Undo() max de 10?	// D�fait les derni�res op�rations m�moris�s
Apr�s chaque op�rations cr�es sans les commandes,
l'ajouter dans back(),
si pleine, retire front()
� l'appel de Ctrl+Z,
Si back() est existant, (sinon rien)
Change l'interface avec le back()
D�place back() dans le front() de Redo
si Redo est plein, retire son back()
^::Redo() (idem).		// Refais les derni�res op�rations m�moris�s
� l'appel de Ctrl+Y, (doit faire les op�rations � l'inverse)
Si front() est existant, (sinon rien)
Si front() fait r�f�rence � des op�rations valides,
Change l'interface avec le front()
D�place le front() dans le back() de Undo
Sinon,
pop_front() TQ front() n'est pas valide
�::Select()				//
�::Delete()				//
Si s�lection existante,
Ajouter les �l�ments dans un tampon (Undo)
Retirer l'�l�ment
�::Drag()				// changes its position
::Link()
Si possible,
Trace une ligne entre les deux �l�ments
::Unlink()
Si ligne pr�sente,
Retire la ligne entre deux �l�ments
::Copy()
Met dans le presse papier les �l�ments s�lectionn�s, --(MO)
::Cut()
Copy() + Delete()
::Paste()
Ajoute les �l�ments dans le presse papier � l'endroit indiqu�
--(MO)M�morise les op�rations(voir Undo + Redo)
/////// Autres configurations possibles
__Param�tres de configuration
::Ils sont s�lectionn� avec les m�thodes suivantes
1 - Par un fichier de configutation
2 - Durant les choix du menu principal
3 - Par un menu d'option en mettant sur pause
4 - Au fur et � mesure si une limite est atteinte
::Ils comprennent les options suivants
A - Dimmenssions de la fen�tre(1)
B - �l�ments � inclure(2)
C - Dimmenssions des �l�ments(1, 2)
D - Les donn�es � repr�senter(1, 4)
E - ...
__Fichier de configuration
__Option du menu principal
__Menu d'option
__Limites
*/