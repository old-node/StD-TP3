#pragma once
#include <string>
using namespace std;

#define SQL_TYPE_DESC 20
#define SQL_RETURN_CODE_LEN 1000

// The following buffer is used to store parameter values.  
typedef struct tblDessinCol {
	int dessID;
	int dessUser;
} tblDessinCol;

typedef struct tblShapeCol {
	int shaID;
	float shaPosX;
	float shaPosY;
	float shaDimX;
	float shaDimY;
	int shaType;
	int shaColor;
	int shaDessin;
} tblShapeCol;

typedef struct tblTypeColorCol {
	int typColID;
	string typColDescription;
} tblTypeColorCol;

typedef struct tblTypeShapeCol {
	int typShaID;
	string typShaDescription;
} tblTypeShapeCol;

typedef struct tblUsagerCol {
	int usagerID;
	string usagerNom;
	string usagerPassword;
} tblUsagerCol;