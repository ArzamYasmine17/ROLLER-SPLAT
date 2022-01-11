#include "carre.h"
#include "MainMenuScene.h"
#include "Array.h"

/*******************************************************************************************/
//le compteur egale 0 au debut de level1
int MainMenu::count = 0;
/*******************************************************************************************/
//on donne des valeurs par defaut à les attributs (la boule est  stable)
MainMenu::MainMenu() {
    ismoving = false;
	bool haut = false;
	bool bas = false;
	bool droit = false;
	bool gauche = false;
    _direction_x = 0;
    _direction_y = 0;
}
/*******************************************************************************************/
MainMenu::~MainMenu() {}
/*******************************************************************************************/
//la fonction update
void MainMenu::update(float dt) {


	//on change la position de la ball en fonction de x et y,si il est en mouvement
	if (ismoving == true) {
		_cercle->setPosition(_cercle->getPosition().x + _direction_x, _cercle->getPosition().y + _direction_y);
	}


	
	for (auto _sprites : _collisionsprite) {
		//ses boucles sont respensables sur l'arret de ball pour s'arreter avant le mur 
		if (_direction_x == 0 && _direction_y == 1) {
			if (_cercle->getPositionX() == _sprites->getPositionX() && _cercle->getPositionY() == _sprites->getPositionY() - 10) {
				ismoving = false;
			}
		}
		if (_direction_x == 0 && _direction_y == -1) {
			if (_cercle->getPositionX() == _sprites->getPositionX() && _cercle->getPositionY() == _sprites->getPositionY() + 10) {
				ismoving = false;
			}
		}
		if (_direction_x == 1 && _direction_y == 0) {
			if (_cercle->getPositionX() == _sprites->getPositionX() - 10 && _cercle->getPositionY() == _sprites->getPositionY()) {
				ismoving = false;
			}
		}
		if (_direction_x == -1 && _direction_y == 0) {
			if (_cercle->getPositionX() == _sprites->getPositionX() + 10 && _cercle->getPositionY() == _sprites->getPositionY()) {
				ismoving = false;
			}
		}
	}

	//l'itération de vecteur carre
	for (auto _mysprites : _carrevector) {
		//on change la couleur et on incrémente coc, si la ball est dans la meme position que le carre
		if (_cercle->getPosition() == _mysprites->getPosition() && _mysprites->iscolored == false) {
			_mysprites->changecolor(Color3B(150, 351, 110));
			coc++;
		}
	}
	//vérification si coc egale end.
	if (coc == end) {
		//l'incrémentation de count pour passer au level suivant.
		count++;
		//on utilise director->getInstance()->replaceScene(scene) pour passer d'une scene a l'autre.
		auto scene = Scene::create();
		auto layer = MainMenu::create();
		scene->addChild(layer);
		director->getInstance()->replaceScene(scene);
	}
}
/*******************************************************************************************/
//on utilise la fonction --EventListenerKeyboard-- pour renvoyer les écouteurs , et detecter les touches sur les boutons fléchés. 
EventListenerKeyboard* MainMenu::onKeyBoardEvent() {
	//la création de --Listener-- pour écouter les événements de touche sur les boutons.
	auto listener = EventListenerKeyboard::create();
	//le clavier doit écouter la presse de chaque touche.
	listener->onKeyPressed = [=](EventKeyboard::KeyCode _keycode, Event* event) {
		//si la ball est en pause on peut la déplacer avec les 4 directions.
		if (!ismoving) {
			//on change les directions selon le bouton presser .
			switch (_keycode) {
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				//la ball doit monter vers le haut si on clique sur la flèche de direction-y=1 , sur l'axe de x la ball reste stable.
				_direction_y = 1;
				_direction_x = 0;
				ismoving = true;
			     break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				//la ball doit monter vers le bas si on clique sur la flèche de direction-y=-1 , sur l'axe de x la ball reste stable.
				
				_direction_y = -1;
				_direction_x = 0;
				ismoving = true;
				
					break;
				
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				//la ball doit monter vers le haut si on clique sur la flèche de direction-x=1 , sur l'axe de y la ball reste stable.
				
				_direction_x = -1;
				_direction_y = 0;
				ismoving = true;
					break;
				
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				//la ball doit monter vers le bas si on clique sur la flèche de direction-x=-1 , sur l'axe de y la ball reste stable.
				
				_direction_x = 1;
				_direction_y = 0;
				ismoving = true;
					break;
				
			}
		}
	};
	return listener;
}
/*******************************************************************************************/
Scene* MainMenu::createScene()
{
	auto scene = Scene::create(); //la scène est un objet 
	auto layer = MainMenu::create();  //la couche est un objet
	scene->addChild(layer); //ajouter layer comme fils pour la scene 
	return scene; 
}
/*******************************************************************************************/
bool MainMenu::init() {
	//la vérifiction de renvois si il est faux ou pas.
	if (!Layer::init()) {
		return false;
	}
	//la création de level1 en fonction de la variable count.
	if (count == 0) {
		//la fin de level1 
		end = 700 ;//((8*8)-50)*50=700
		//le tableau prend les valeurs du tableau de level1 qui se trouve dans le fichier Array.h
		auto _array = arraylevel1;
		//création du matrice de deux dimensions.
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				//on utilise x pour l'incrémentation du tableau 
				for (auto x = 0; x < 50; x++) {
					//pour préciser la position de chque mur
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						//l'initialisation du sprite avec la fonction carre init pour l'utilisé dans la classe carre 
						auto _sprite = carre::carreinit();
						//on donne la position au sprite
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						//on donne au sprite une couleur 
						_sprite->setColor(Color3B(200, 160, 100));
						//on utilise la fonction pushback pour pousser sprite
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(140, 50, 25));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level2 en fonction de la variable count.
	if (count == 1) {
		end = 924;
		auto _array = arraylevel2;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 42; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(200, 125, 175));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(0, 50, 25));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level3 en fonction de la variable count.
	if (count == 2) {
		end = 855;
		auto _array = arraylevel3;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 45; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(300, 255, 155));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(1, 30, 25));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level4 en fonction de la variable count.
	if (count == 3) {
		end = 880;
		auto _array = arraylevel4;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 44; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(255, 255, 255));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(100, 50, 25));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level5 en fonction de la variable count.
	if (count == 4) {
		end = 1024;
		auto _array = arraylevel5;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 32; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(30, 75, 125));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(102, 502, 145));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level6 en fonction de la variable count.
	if (count == 5) {
		end = 988;
		auto _array = arraylevel6;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 26; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(100, 220, 205));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(250, 230, 155));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de level7 en fonction de la variable count.
	if (count == 6) {
		end = 1008;
		auto _array = arraylevel7;
		for (auto i = 0; i <= 9; i++) {
			for (auto j = 0; j <= 9; j++) {
				for (auto x = 0; x < 28; x++) {
					if ((i == _array[x][0] && j == _array[x][1]) || i == 0 || i == 9 || j == 0 || j == 9) {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(200, 175, 250));
						_collisionsprite.pushBack(_sprite);
						this->addChild(_sprite);
						break;
					}
					else {
						auto _sprite = carre::carreinit();
						_sprite->setPosition(Vec2(100 + i * 10, 100 + j * 10));
						_sprite->setColor(Color3B(250, 255, 225));
						_carrevector.pushBack(_sprite);
						this->addChild(_sprite);
					}
				}
			}
		}
	}
/*******************************************************************************************/
	//la création de ball
	_cercle = Sprite::create("ball-hd.png");
	_cercle->setPosition(Vec2(110, 110)); //la position de ball
	_cercle->setScale(0.1); //la taille de ball par rapport au carre
	this->addChild(_cercle);
	this->scheduleUpdate();//une fonction de mis a jour de l'arrière-plans programmer pour appeler à chaque image.
	auto eventListener = onKeyBoardEvent();//l'appel de onKeyBoardEvent pour déplacer ball
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _cercle);//pour supression de la detection de touche precedante 
	return true;
}
/*******************************************************************************************/