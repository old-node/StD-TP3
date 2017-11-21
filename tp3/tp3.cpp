/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagac�
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donn�e. Application de dessin.
======================================================================================*/


#include <locale>
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


// Programme principal
int main()
{
	setlocale(LC_CTYPE, "can");

	//Commit
	RenderWindow sandbox;
	//sandbox.create();
	RectangleShape test(Vector2f(100, 100));
	test.setFillColor(Color(120, 210, 100, 130));

	Texture machin;
	machin.loadFromFile("machin.jpg");
	Sprite truc(machin);

	sandbox.create(VideoMode(300, 200), "Sandbox");
	sandbox.draw(truc);
	sandbox.draw(test);
	

	system("pause");

	return 0;
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