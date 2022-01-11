#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "carre.h"
using namespace cocos2d;
//la création de la class MainMenu pour représenter les --levels--
class MainMenu : public Layer {
private:
	//création de --carrevector-- pour collorer --carre--
	Vector<carre*> _carrevector;
	//création de --collisionsprite-- pour les murs
	Vector<carre*> _collisionsprite; 
	bool ismoving = false;
	/***************************************************************************************/
	//les attributs de direction 
	int _direction_x = 0;
	int _direction_y = 0;
	int end;
	int coc = 0; //initialisation de variable coc 
	//si coc=end en passe au --level-- suivant 
/*******************************************************************************************/
public:
    static int count; // Renvoie un pointeur d'instance de scène
	Director* director;//pour passer d'une scene à l'autre
	//constructor
	MainMenu();
	//destructor
	virtual ~MainMenu();
	Sprite* _cercle; //pour controler la boule
    virtual bool init();  // fonction pour initialiser la classe
	static Scene* createScene();
    CREATE_FUNC(MainMenu);  // Crée une méthode create() //implémenter manuellement la méthode statique de création 
	EventListenerKeyboard* onKeyBoardEvent();//fonction qui renvoie un eventlistener 
	void update(float dt);//fonction de mise à jour 
};
#endif // !__MAINMENU_SCENE_H__