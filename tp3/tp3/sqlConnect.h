/*======================================================================================
Fichier:		oButton.h
Auteur:			Olivier Lemay Dostie & Simon Lagac�
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
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	
	tblShapeCol shapeElem;
	tblDessinCol dessinElem;
	tblTypeColorCol typeColorElem;
	tblTypeShapeCol typeShapeElem;
	tblUsagerCol usagerElem;

	

public:
	sqlConnect();
	~sqlConnect();

	void saveCanva()
	{
		
		/*Statement;
		EXEC SQL CALL INOUT_PARAM(:inout_median:medianind, : out_sqlcode : codeind,
			: out_buffer : bufferind);*/
	}
	void connexion();
	void deconnexion();
	void selectUsager();
	void ajouteUsager(const char * nom, const char * prenom);
	bool userConnect(const char * user, const char * password);
};


