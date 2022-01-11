#include "carre.h"
/*******************************************************************************************/
carre::carre(void) {
	this->iscolored = false;
};
/*******************************************************************************************/
carre::~carre(void) {}
/*******************************************************************************************/
carre* carre::carreinit() {
	auto sprite = new carre();
	sprite->initWithFile("carre1.png");
	sprite->setScale(0.2);
	return sprite;
}
/*******************************************************************************************/
void carre::changecolor(Color3B _color) {
	this->setColor(_color);
	this->iscolored = true;
}