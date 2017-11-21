/*======================================================================================
Fichier:		tp3.hpp
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			20-11-2017
Description:	3e travail pratique du cours Structure de donnée. Application de dessin.
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

/////// Interfaces à Structure de données

Pour que SFML soit opérationnel, il faut suivre le guide suivant:
https://www.sfml-dev.org/tutorials/2.4/start-vc-fr.php

Les classes précédés de '^' sont nécessaires pour l'applications
Celles précédés de '¨' sont fortement souhaitées

Il va fauloir dabors faire fonctionner sfml avant de pouvoir se séparer les tâches.


///////
__Classes
¨::Save()				// Pour le TP3 de SQL
¨::Load()				// idem
::Parameters()

^::Operations()			// Liste des outils graphique disponible de l'application
	+ 1 for each tools?

^::Interface()			// Lieu d'affichage et de dessins
	^::Window()			// Fenêtre qui contiens l'interface
	^::Button()			// Boutons de commandes d'options et d'opérations
	^::Cursor()			// Curseur de la souris pour les opérations graphiques manuelles
	^::History()		// Contiens les opérations passés et 'futures'
	::Runtime()
	::Clipboard()
^::Object()				// Objet parent qui permet la création et l'affichage de formes
	^::Label()			// Étiquette de text
	^::Square()			// Forme simple rectangulaire
	¨::Line()			// Forme simple linéaire
	::Dot()
	::Template()
	::Custom()


__Opérations sur les objets
^::Add()				// Ajoute un objet à la fenêtre
Si possible (Si aucune autre opération est en cours),
	Commencer la création d'un objet
	TQ l'objet n'est pas complété, au click
		Compléter une partie de l'objet
	Terminer la création d'un objet

__Undo + Redo
^::Undo() max de 10?	// Défait les dernières opérations mémorisés
Après chaque opérations crées sans les commandes,
	l'ajouter dans back(),
		si pleine, retire front()
À l'appel de Ctrl+Z,
Si back() est existant, (sinon rien)
	Change l'interface avec le back()
	Déplace back() dans le front() de Redo
		si Redo est plein, retire son back()

^::Redo() (idem).		// Refais les dernières opérations mémorisés
À l'appel de Ctrl+Y, (doit faire les opérations à l'inverse)
Si front() est existant, (sinon rien)
	Si front() fait référence à des opérations valides,
		Change l'interface avec le front()
		Déplace le front() dans le back() de Undo
	Sinon,
		pop_front() TQ front() n'est pas valide

¨::Select()				//
¨::Delete()				//
Si sélection existante,
	Ajouter les éléments dans un tampon (Undo)
	Retirer l'élément
¨::Drag()				// changes its position

::Link()
Si possible,
	Trace une ligne entre les deux éléments
::Unlink()
Si ligne présente,
	Retire la ligne entre deux éléments
::Copy()
Met dans le presse papier les éléments sélectionnés, --(MO)
::Cut()
Copy() + Delete()
::Paste()
Ajoute les éléments dans le presse papier à l'endroit indiqué
--(MO)Mémorise les opérations(voir Undo + Redo)



/////// Autres configurations possibles
__Paramètres de configuration
::Ils sont sélectionné avec les méthodes suivantes
1 - Par un fichier de configutation
2 - Durant les choix du menu principal
3 - Par un menu d'option en mettant sur pause
4 - Au fur et à mesure si une limite est atteinte
::Ils comprennent les options suivants
A - Dimmenssions de la fenêtre(1)
B - Éléments à inclure(2)
C - Dimmenssions des éléments(1, 2)
D - Les données à représenter(1, 4)
E - ...
__Fichier de configuration
__Option du menu principal
__Menu d'option
__Limites



*/