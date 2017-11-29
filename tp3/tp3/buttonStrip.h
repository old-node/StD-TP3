/*======================================================================================
Fichier:		buttonStrip.h
Auteur:			Olivier Lemay Dostie & Simon Lagacé
Date:			29-11-2017
Description:	.
======================================================================================*/



#pragma once
#include "../oButton.h"


// Prototype des fonctions

static bool offsetButton(float & p, float & q, float P, float Q,
	float tol, float ol, int MAX);


// Classe de base des listes de boutons
class buttonStrip
{
private:

protected:
	Vector2f _startPos;
	Vector2f _endPos;
	vector<oButton> _buttons;
	bool _fromTopOrLeft;
	//bool _reverseOrder;	/// optionnel
	bCorner _lastCorner;
	static float _left;
	static float _top;

public:
	buttonStrip(bool fromTopOrLeft, Vector2f startPos, Vector2f endPos);
	~buttonStrip();

	virtual void initStrip() = 0;

	int addButtons(const vector<oButton> buttons)
	{
		int size = _buttons.size();
		for (const auto & b : buttons)
			_buttons.push_back(b);
		placeButtons(size);
	}
	virtual Vector2f placeButtons(int size = 0) = 0;
	virtual Vector2f getLastPos() = 0;
	bool removeButtons(int begin, int end)
	{
		assert(0 <= begin
			&& begin <= end
			&& end <= _buttons.size());

		vector<oButton>::iterator it = _buttons.begin();
		for (int i = 0; i < begin; i++)
			it++;
		for (int i = end - begin; i < end; i++, it++)
			_buttons.erase(it);

		Vector2f v = getLastPos();
		_left = v.x;
		_top = v.y;
	}
};


// 
class buttonStripH : public buttonStrip
{
private:
public:
	using buttonStrip::buttonStrip;
	~buttonStripH();

	void initStrip() override
	{
		_lastCorner = (_fromTopOrLeft) ? bLowerRight : bUpperRight;
	}


	Vector2f placeButtons(int start = 0) override
	{
		vector<oButton>::iterator it = _buttons.begin();
		for (int i = 0; i < start; i++, it++);

		float width = 0;
		float height = 0;
		float OL = 0;
		
		for (; it < _buttons.end(); it++)
		{
			width = it->getW();
			height = it->getH();
			OL = it->RectangleShape::getOutlineThickness();
			// Prépare la position du prochain bouton
			offsetButton(_left, _top, width, height, TOLW, OL, SCREENW);

		}
		return getLastPos();
	}
	Vector2f getLastPos() override
	{
		return _buttons.back().getP();
	}
};


// 
class buttonStripV : public buttonStrip
{
private:
public:
	using buttonStrip::buttonStrip;
	~buttonStripV();

	void initStrip() override
	{
		_lastCorner = (_fromTopOrLeft) ? bLowerRight : bLowerLeft;
	}

	//offsetButton(_top, _left, height, width, TOLH, OL, SCREENH);
};


// Obtien les bonnes coordonnées du prochain bouton selon sa liste
bool offsetButton(float & p, float & q, float P, float Q,
	float tol, float ol, int MAX)
{
	// 
	if (p + P > MAX)
	{
		p = 0;
		q += Q + ol * 3 + tol;
		return true;
	}
	// 
	else
		p += P + ol * 2 + tol * 2;
	return false;
}