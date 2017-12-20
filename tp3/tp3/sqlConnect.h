/*======================================================================================
Fichier:		oButton.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			22-11-2017
Description:
======================================================================================*/

#pragma once

#include "stdafx.h"
#include "sqlStructs.h"

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

	tblShapeCol shapeElem;
	tblDessinCol dessinElem;
	tblTypeColorCol typeColorElem;
	tblTypeShapeCol typeShapeElem;
	tblUsagerCol usagerElem;

public:
	sqlConnect();
	~sqlConnect();

	void saveCanva(tblShapeCol *shapeElem, int shapeQty)
	{
		/*https://docs.microsoft.com/en-us/sql/odbc/reference/develop-app/binding-parameters-by-name-named-parameters
		
		// With the following example
		--CREATE PROCEDURE test @title_id int = 1, @quote char(30) AS <blah>
		
		// In this procedure, the first parameter, @title_id, has a default 
		//	value of 1. An application can use the following code to invoke 
		//	this procedure such that it specifies only one dynamic parameter. 
		//	This parameter is a named parameter with the name "@quote". 

		// Prepare the procedure invocation statement.
		SQLPrepare(hstmt, "{call test(?)}", SQL_NTS);

		// Populate record 1 of ipd.
		SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
				  30, 0, szQuote, 0, &cbValue);

		// Get ipd handle and set the SQL_DESC_NAMED and SQL_DESC_UNNAMED fields for record #1.
		SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);
		SQLSetDescField(hIpd, 1, SQL_DESC_NAME, "@quote", SQL_NTS);

		// Assuming that szQuote has been appropriately initializedm execute.
		SQLExecute(hstmt);
		*/

		// Notre procédure stockée: 
		///		L'appel de la procédure suivante n'est pas conforme,
		///		Il faudra faire l'insertion de chaques enregistrmeent à la fois
		///		si nous l'utilisont, sinon il faut ajuster la requête pour qu'elle
		///		accepte une structure plus complexe.
		/*CREATE PROCEDURE saveCanva @usermame VARCHAR(20), @dessID int = -1,
									 @shapeQty INT, @shapeList --INPUT(shqpeQty) ///
		AS
		BEGIN
		BEGIN TRAN addCanva

			DECLARE @errorID INT = 0

			SET @shapeQty = @shapeQty - 1
			WHILE (@shapeQty > 0 OR @errorID != 0)
			BEGIN
				INSERT INTO tbl Shape (shaPoX, shaPoY, shaDimX, shaDimY, shaType, shaColor, shaDessin)
				VALUES (shapeList[@shapeQty].shaPoX, shapeList[@shapeQty].shaPosY, 
					shapeList[@shapeQty].shaDimX, shapeList[@shapeQty].shaDimY, 
					shapeList[@shapeQty].shaType, shapeList[@shapeQty].shaColor, 
					shapeList[@shapeQty].shaDessin)

				SET @shapeQty = @shapeQty - 1
				SET @errorID = @@ERROR
			END

			IF !(0 > (SELECT COUNT(*) FROM inserted))
				@errorID = 1

			IF (@errorID > 0)
				ROLLBACK
			ELSE
				COMMIT
		END
		GO
		*/

		SQLRETURN retcode;	// Code d'erreur

		// Prépare l'invocation de la procedure
		retcode = SQLPrepare(sqlStmtHandle, (SQLCHAR*)L"{call saveCanva(?)}", SQL_NTS);

		// Prépare les variables vers la requête /// Populate record 1 of ipd.
		for (int i = 0; i < shapeQty; i++)
		{
			retcode = SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
				1000, 0, &shapeElem[i].shaPosX, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
				1000, 0, &shapeElem[i].shaPosY, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 4, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
				1000, 0, &shapeElem[i].shaDimX, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_REAL,
				1000, 0, &shapeElem[i].shaDimY, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
				1000, 0, &shapeElem[i].shaType, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
				1000, 0, &shapeElem[i].shaColor, 0, 0);
			retcode = SQLBindParameter(sqlStmtHandle, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
				1000, 0, &shapeElem[i].shaDessin, 0, 0);
		}

		// Get ipd handle and set the SQL_DESC_NAMED and SQL_DESC_UNNAMED fields for record #1.
		
		/// Je crois que je fais les choses à l'envert,
		///		Il se peut que le deuxième paramètre est plutôt la position de
		///		l'enregistrement, si c'est le cas, il faut obtenir celle-ci d'avance.
		//SQLGetStmtAttr(sqlStmtHandle, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);
		retcode = SQLSetDescField(sqlStmtHandle, 2, SQL_DESC_NAME, "@shaPosX", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 3, SQL_DESC_NAME, "@shaPosY", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 4, SQL_DESC_NAME, "@shaDimX", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 5, SQL_DESC_NAME, "@shaDimY", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 6, SQL_DESC_NAME, "@shaType", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 7, SQL_DESC_NAME, "@shaColor", SQL_NTS);
		retcode = SQLSetDescField(sqlStmtHandle, 8, SQL_DESC_NAME, "@shaDessin", SQL_NTS);

		retcode = SQLExecute(sqlStmtHandle);

		if (SQL_SUCCESS != retcode) {
			throw string("Erreur dans la requête");
		}
	}
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
			case SQL_SUCCESS_WITH_INFO:
				cout << "Connexion reussi";
				cout << "\n";
				break;

			case SQL_INVALID_HANDLE:
			case SQL_ERROR:
				throw string("Erreur de connexion");
				break;

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
