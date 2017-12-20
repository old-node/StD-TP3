/*======================================================================================
Fichier:		oButton.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
Description:
======================================================================================*/

#pragma once

#include "stdafx.h"


#include <string>
#include <iostream>

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
using namespace std;

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

class sqlConnect
{
private:
	//Variable SQL
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	sqlConnect();
	~sqlConnect();

	void connexion();

	void deconnexion();

	void selectUsager();

	void ajouteUsager(const char * nom, const char * prenom);
};

// .
sqlConnect::sqlConnect()
{
}

// .
sqlConnect::~sqlConnect()
{
	///deconnexion();
}

// .
void sqlConnect::connexion() {
	//Initialisations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	/* COURS déclencher 2 */
	
	/*
	sur sql
	audit /// rapport
	ordonnancer
	Database properties > options > recursive triggers
	*/

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
				(SQLCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=ThePainter3;UID=sa;PWD=user123;",
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

// .
void sqlConnect::deconnexion() {

	cout << "Deconnexion ..." << "\n";

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

// .
void sqlConnect::selectUsager() {

	try
	{
		connexion();

		//S'il y a un problème avec la requête on quitte l'application sinon on affiche le résultat
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)L"SELECT usagerprenom, usagernom FROM usager", SQL_NTS)) {
			throw string("Erreur dans la requête");
		}
		else {
			//Déclarer les variables d'affichage

			SQLCHAR nom[SQL_RESULT_LEN];
			SQLLEN ptrnom;

			SQLCHAR prenom[SQL_RESULT_LEN];
			SQLLEN ptrprenom;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_CHAR, prenom, SQL_RESULT_LEN, &ptrprenom);
				SQLGetData(sqlStmtHandle, 2, SQL_CHAR, nom, SQL_RESULT_LEN, &ptrnom);

				//Afficher le résultat d'une requête			
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

// .
void sqlConnect::ajouteUsager(const char * nom, const char * prenom) {

	try
	{
		connexion();

		SQLRETURN retcode;

		/*
		Paramètre SQLBindParameter:
		- Handler de la requête
		- No du paramètre (commence à 1)
		- Est-ce un paramètre de type Input ou Output
		- Quel est le type de la variable en C++
		- Quel est le type de la variable en SQL
		- Quelle est la taille de la colonne dans la BD
		- Nombre de décimal
		- Quelle variable ou données (pointeur)
		- Longueur du buffer
		- Pointeur du buffer
		*/

		retcode = SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, &nom, 0, 0);

		retcode = SQLPrepare(sqlStmtHandle, (SQLCHAR*)L"INSERT INTO Usager (username) VALUES (?)", SQL_NTS);

		retcode = SQLExecute(sqlStmtHandle);

		if (SQL_SUCCESS != retcode) {
			throw string("Erreur dans la requête");
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
