#include "Ant.h"
#include "Case.h"


Ant::Ant(int _x, int _y, int l, int h, int r, int v, int b, int _step, int widthBoard, int heightBoard, vector<Case*> c, int step): Forme(_x, _y, l, h, Couleur(r, v, b)), step(_step), widthOfBoard(widthBoard), heightOfBoard(heightBoard), _case(c), nbrOfCaseOnWidth(step) {
	largeurCase = largeur - 2*largeur/5;
	hauteurCase = hauteur - 2*hauteur/5;
	
	if (_case.empty()) {
		cout << "Erreur" << endl;
	} else {
		cout << x/(largeur) + y/(hauteur)*nbrOfCaseOnWidth << endl;
		thisCase = _case[x/(largeur) + y/(hauteur)*nbrOfCaseOnWidth];
		thisCase->setAnt(this);
	}
}


Ant::~Ant() {
}


void Ant::dessine(sf::RenderWindow *win) {
	/**
	 * Effacement de la trace du cube
	 */
	if (oldCase != NULL) {
		oldCase->dessine(win);
	}
	//thisCase->dessine(win);

	int red, green, blue;
  	couleur.getRVB(red, green, blue);
  	sf::RectangleShape shape(sf::Vector2f(largeurCase, hauteurCase));
  	shape.setFillColor(sf::Color(red, green, blue));
  	shape.setPosition(x+largeur/5,y+hauteur/5);
	win->draw(shape);
}


void Ant::move(string direction) {
	oldCase = _case[returnPositionOfCase()];
	oldCase->setAnt(NULL);

	moveAnt(direction);

	thisCase = _case[returnPositionOfCase()];
	thisCase->setAnt(this);
}


void Ant::move() {

	/**
	 * Vérification qu'il n'existe pas de cube dans la ligne
	 */
	cout << " -> Vérification dans la ligne   ";
	bool findCubeInLine = false;
	string rightOrLeft = "gauche";

	/**
	 * Boucle vérifiant chaque case dans la ligne à vérifier
	 */
	for (int i = 0; i < nbrOfCaseOnWidth && !findCubeInLine; i++) {

		int indice = i + y/hauteur*nbrOfCaseOnWidth;

		if (NULL != _case[indice]->getAnt()) {
			if (this != _case[indice]->getAnt()) {
				findCubeInLine = true;
				/**
				 * Changement de la direction
				 */
				direction = rightOrLeft;
			} else {
				rightOrLeft = "droite";
			}
		}
	}

	if (findCubeInLine) {
		cout << "\033[1;32mOK\033[0m" << ", position: " << rightOrLeft << endl;
	} else {
		cout << "\033[1;31mKO\033[0m" << endl;
	}

	/**
	 * Vérification qu'il n'existe pas de cube dans la colonne
	 */
	cout << " -> Vérification dans la colonne ";
	bool findCubeInCulumn = false;
	string upOrDown = "haut";

	/**
	 * Boucle vérifiant chaque case dans la colonne à vérifier
	 */
	for (int i = 0; i < nbrOfCaseOnWidth && !findCubeInCulumn; i++) {

		int indice = x/largeur + i*nbrOfCaseOnWidth;
		
		if (NULL != _case[indice]->getAnt()) {
			if (this != _case[indice]->getAnt()) {
				findCubeInCulumn = true;
				/**
				 * Changement de la direction
				 */
				direction = upOrDown;
			} else {
				upOrDown = "bas";
			}
		}
	}

	if (findCubeInCulumn) {
		cout << "\033[1;32mOK\033[0m" << ", position: " << upOrDown << endl;
	} else {
		cout << "\033[1;31mKO\033[0m" << endl;
	}

	/**
	 * Déplacement du cube
	 */
	move(direction);
}


void Ant::moveAnt(string direction) {
	if (direction == "haut") {
		if (y - step < 0 
			&& NULL == _case[returnPositionOfCaseThanksToY(heightOfBoard - step)]->getAnt()) {
			y = heightOfBoard - step;
		} else if (y - step >= 0 
			&& NULL == _case[returnPositionOfCaseThanksToY(y - step)]->getAnt()) {
			y -= step;
		}
	} else if (direction == "droite") {
		if (x + step >= widthOfBoard 
			&& NULL == _case[returnPositionOfCaseThanksToX(0)]->getAnt()) { 
			x = 0; 
		} else if (x + step < widthOfBoard 
			&& NULL == _case[returnPositionOfCaseThanksToX(x + step)]->getAnt()) {
			x += step;
		}
	} else if (direction == "bas") {
		if (y + step >= heightOfBoard 
			&& NULL == _case[returnPositionOfCaseThanksToY(0)]->getAnt()) {
			y = 0;
		} else if (y + step < heightOfBoard
			&& NULL == _case[returnPositionOfCaseThanksToY(y + step)]->getAnt()) { 
			y += step;
		}
	} else if (direction == "gauche") {
		if (x - step < 0
			&& NULL == _case[returnPositionOfCaseThanksToX(widthOfBoard - step)]->getAnt()) {
			x = widthOfBoard - step;
		} else if (x - step >= 0 
			&& NULL == _case[returnPositionOfCaseThanksToX(x - step)]->getAnt()) {
			x -= step;
		}
	}
}


void Ant::moveThanksToMouse(int _x, int _y) {
	oldCase = _case[returnPositionOfCase()];
	oldCase->setAnt(NULL);

	moveAntThanksToMouse(_x, _y);

	thisCase = _case[returnPositionOfCase()];
	thisCase->setAnt(this);
}


void Ant::moveAntThanksToMouse(int _x, int _y) {
	if (_x >= 0 && _x <= widthOfBoard 
		&& NULL == _case[returnPositionOfCaseThanksToXAndY(_x, _y)]->getAnt()) {
		x = (_x/step)*step;
	}

	if (_y >= 0 && _y <= widthOfBoard 
		&& NULL == _case[returnPositionOfCaseThanksToXAndY(_x, _y)]->getAnt()) {
		y = (_y/step)*step;
	}
}