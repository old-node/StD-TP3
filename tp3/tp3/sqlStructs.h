#pragma once
#include <string>
using namespace std;

#define SQL_TYPE_DESC 20
#define SQL_RETURN_CODE_LEN 1000


// SQLCHAR x;
// SQL_SMALL_INT c = (int)x - 48;
// SQL_SMALL_INT c = (SQL_SMALL_INT)x - 48;


// The following buffer is used to store parameter values.  
typedef struct tblDessin {
	int dessID;
	int dessUser;
} tblDessinCol;

typedef struct tblShape {
	int shaID;
	float shaPosX;
	float shaPosY;
	float shaDimX;
	float shaDimY;
	int shaType;
	int shaColor;
	int shaDessin;
} tblShapeCol;

typedef struct tblTypeColor {
	int typColID;
	string typColDescription;
} tblTypeColorCol;

typedef struct tblTypeShape {
	int typShaID;
	string typShaDescription;
} tblTypeShapeCol;

typedef struct tblUsager {
	int usagerID;
	string usagerNom;
	string usagerPassword;
} tblUsagerCol;