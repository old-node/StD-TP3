#include "sqlConnect.h"

sqlConnect::sqlConnect()
{
}

sqlConnect::~sqlConnect()
{
}

void sqlConnect::connexion() {
	//Initialisations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	/* COURS déclencher 2 *//*

							sur sql
							audit /// rapport
							ordonnancer
							Database properties > options > recursive triggers
							*/

	try
	{
		//Allocations
		if (!((SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) || (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) || (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)))) {
			//Affichage
			cout << "Tentative de connexion";
			cout << "\n";

			//Connexion au SQL Server
			switch (SQLDriverConnectW(sqlConnHandle, NULL,
				(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=ThePainter3;UID=sa;PWD==user123;", SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {

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

void sqlConnect::deconnexion() {

	cout << "Deconnexion ..." << "\n";

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

void sqlConnect::selectUsager() {

	try
	{
		connexion();

		//S'il y a un problème avec la requête on quitte l'application sinon on affiche le résultat
		if (SQL_SUCCESS != SQLExecDirectW(sqlStmtHandle, (SQLWCHAR*)L"SELECT usagerprenom, usagernom FROM usager", SQL_NTS)) {
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

		retcode = SQLPrepareW(sqlStmtHandle, (SQLWCHAR*)L"INSERT INTO Usager (username) VALUES (?)", SQL_NTS);

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


bool sqlConnect::userConnect(const char * user, const char * password)
{
	try
	{
		connexion();

		//S'il y a un problème avec la requête on quitte l'application sinon on affiche le résultat
		if (SQL_SUCCESS != SQLExecDirectW(sqlStmtHandle, (SQLWCHAR*)L"SELECT usagerNom, usagerPassword FROM tblUsager", SQL_NTS)) {
			throw string("Erreur dans la requête");
		}
		else {
			//Déclarer les variables d'affichage

			SQLCHAR username[SQL_RESULT_LEN];
			SQLLEN ptrusername;

			SQLCHAR pass[SQL_RESULT_LEN];
			SQLLEN ptrpass;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_CHAR, username, SQL_RESULT_LEN, &ptrusername);
				SQLGetData(sqlStmtHandle, 2, SQL_CHAR, pass, SQL_RESULT_LEN, &ptrpass);

				//Compaison des strings de la BD et ceux entrés en parametre
				if (strcmp(((const char*)username),user)==0 && strcmp(((const char*)pass),password)==0)
				{
					cout << "VALID CONNECTION" << endl;
					return true;
				}
				else
					cout << "Nope" << endl;

			}
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";
		deconnexion();
	}

	deconnexion();
	return false;
}