#pragma once
#include "cocos2d.h"
using namespace cocos2d;
//cr�ation de la class carre 
class carre : public Sprite {
public:
	//pour savoir est-ce-que le carre a �t� color�.
	bool iscolored;
	//constructor //
	carre();
	//desctructor
	virtual ~carre();
	static carre* carreinit();
	//fonction pour changer les couleurs
	void changecolor(Color3B _color);	
};

