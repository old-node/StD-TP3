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
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	sqlConnect();
	~sqlConnect();
	void connexion();
	void deconnexion();
	void ajouterDessin(char *user);
	bool userConnect(const char * user, const char * password);
};

sqlConnect::sqlConnect()
{
}

sqlConnect::~sqlConnect()
{
}