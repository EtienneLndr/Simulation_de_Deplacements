#ifndef ANT_H
#define ANT_H
#include "Forme.h"
#include <vector>

class Case;

class Ant : public Forme {
	
	public:
		void dessine(sf::RenderWindow *win);
		void move(string direction);
		void move();
		void moveAnt(string direction);
		void moveThanksToMouse(int _x, int _y);
		void moveAntThanksToMouse(int _x, int _y);

		Case * getCaseAt(int i);
		void setCase(vector<Case *> _case);
		
		Ant(int _x, int _y, int l, int h, int r, int v, int b, int _step, int widthBoard, int heightBoard, vector<Case*> _case, int step);
		~Ant();
		
	protected:
		int step;
		int widthOfBoard;
		int heightOfBoard;
		vector<Case*> _case;
		int nbrOfCaseOnWidth;
		int largeurCase;
		int hauteurCase;
		Case * thisCase;
		Case * oldCase;
		string direction = "haut";

		int returnPositionOfCase();
		int returnPositionOfCaseThanksToX(int _x);
		int returnPositionOfCaseThanksToY(int _y);
		int returnPositionOfCaseThanksToXAndY(int _x, int _y);
	
	};


inline Case * Ant::getCaseAt(int i) { return this->_case[i]; }
inline void Ant::setCase(vector<Case *> _case) { this->_case = _case; }

inline int Ant::returnPositionOfCase() { return x/largeur + y/hauteur*nbrOfCaseOnWidth; }
inline int Ant::returnPositionOfCaseThanksToX(int _x) { return _x/largeur + y/hauteur*nbrOfCaseOnWidth; }
inline int Ant::returnPositionOfCaseThanksToY(int _y) { return x/largeur + _y/hauteur*nbrOfCaseOnWidth; }
inline int Ant::returnPositionOfCaseThanksToXAndY(int _x, int _y) { return _x/largeur + _y/hauteur*nbrOfCaseOnWidth; }


#endif