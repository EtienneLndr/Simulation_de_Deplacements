#ifndef PONG_H
#define PONG_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Ant.h"

using namespace std;
using namespace std::chrono;

class Case;

class Pong {
	
	public: 
		int execute();
		
		Pong(string n = "Window", int w = 400, int h = 400, int step = 1);
		~Pong();
		
		Ant* getAnt(int i);
		void addAnt(Ant * a);
		Case* getCase(int i);
		void addCase(Case* c);
		
	private:
		string _name;
    	int _width, _height;
    	int step;
    	sf::RenderWindow *_win;
		vector<Ant*> ant;
		vector<Case*> _case;
		
		int limite;
		int positionOfCase;
		int dt 					= 1;
		int cubeSelectionne 	= 0;
		bool pause 				= false;
		bool mouseButtonPressed = false;
		bool cubeSelected 		= false;
		
		void move(string direction);
		void move();
		void initBoard(sf::RenderWindow * win);
		void drawAll(sf::RenderWindow * win); 
		void clicSourisDroite(int x, int y);
		void clicSourisGauche(int x, int y);
	
	};
		
		
inline Ant* Pong::getAnt(int i) { return ant[i]; }
inline void Pong::addAnt(Ant * a) { ant.push_back(a); }
inline Case* Pong::getCase(int i) { return _case[i]; }
inline void Pong::addCase(Case* c) { _case.push_back(c); }


#endif