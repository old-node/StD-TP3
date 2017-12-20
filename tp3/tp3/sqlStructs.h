#pragma once


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
	SQLCHAR typColDescription[20];
} tblTypeColorCol;

typedef struct tblTypeShapeCol {
	int typShaID;
	SQLCHAR typShaDescription[20];
} tblTypeShapeCol;

typedef struct tblUsagerCol {
	int usagerID;
	SQLCHAR usagerNom[30];
	SQLCHAR usagerPassword[30];
} tblUsagerCol;