#ifndef CASE_H
#define CASE_H
#include "Forme.h"
//#include "Ant.h"

class Ant;

class Case : public Forme {
	
	public:
		Case(int _x, int _y, int l, int h, int r, int v, int b);
		~Case() { }
		
		void dessine(sf::RenderWindow *win);
		void changeColor();

		string getStrCouleur();
		void setStrCouleur(string _strCouleur);
		Ant * getAnt();
		void setAnt(Ant* a);
		
	private:
		double coefficient;
		string strCouleur;
		Ant * ant = NULL;
	
	};

inline string Case::getStrCouleur() { return this->strCouleur; }
inline void Case::setStrCouleur(string strCouleur) { this->strCouleur = strCouleur; }
inline Ant * Case::getAnt() { return this->ant; }
inline void Case::setAnt(Ant * a) { this->ant = a; }



#endif