#include "Pong.h"
#include "Case.h"


using namespace std;


Pong::Pong(string n, int w, int h, int _step) : _name(n), _width(w), _height(h), step(_step) {
	// Création de la fenêtre de jeu
	_win = new sf::RenderWindow(sf::VideoMode(_width, _height), _name);
	
	// Création des cases
	for(int i=0; i<step; i++) {
		for(int j=0; j<step; j++) {
			addCase(new Case(_width/step*j, _height/step*i, _width/step, _height/step, 255, 255, 255));
			}
		}
	
	// Création des cubes pouvant se déplacer
	for (int i=0; i<2; i++) {
		addAnt(new Ant(
			_width/step*(rand()%step),
			_width/step*(rand()%step),
			_width/step,
			_height/step,
			25 + rand()%200,
			25 + rand()%200,
			25 + rand()%200,
			_width/step,
			_width,
			_height,
			_case,
			step));
	}
}


Pong::~Pong(void) {
  	// Destruction des objets graphiques
	cout << "Destruction des objets graphiques" << endl;
  	delete _win;
  	for (unsigned int i=0; i<_case.size(); i++) {
  		delete _case[i];
	}
	for (unsigned int i=0; i<ant.size(); i++) {
  		delete ant[i];
	}
}


void Pong::clicSourisDroite(int x, int y) {
	cout << "x = " << x << ", y = " << y << endl;
	cout << "valeur en x " << x/(_width/step) << ", valeur en y " << y/(_height/step)*step << endl;
	cout << "cube numéro " << x/(_width/step) + y/(_height/step)*step << endl;
	positionOfCase = x/(_width/step) + y/(_height/step)*step;
	_case[positionOfCase]->changeColor();
	_case[positionOfCase]->dessine(this->_win);
}


void Pong::clicSourisGauche(int x, int y) {
	for (int i=0; i<(int)ant.size(); i++) {
		int xMin = ant[i]->getX();
		int yMin = ant[i]->getY();
		int xMax = ant[i]->getX() + ant[i]->getLargeur();
		int yMax = ant[i]->getY() + ant[i]->getHauteur();
		if ((xMin <= x) && (x <= xMax) && (yMin <= y) && (y <= yMax)) {
			if (cubeSelectionne != i) {
				cubeSelectionne = i;
				cout << "Changement du cube sélectionné: c'est désormais le cube numéro " << cubeSelectionne << endl;
			} else {
				cout << "Déplacement du cube numéro " << cubeSelectionne << endl;
				ant[cubeSelectionne]->moveThanksToMouse(x, y);
				cubeSelected = true;
			}
		}
	}
}


void Pong::move(string direction) {
	ant[cubeSelectionne]->move(direction);
}


void Pong::move() {
	cout << "Déplacement du cube numéro " << cubeSelectionne << ":" <<endl;
	ant[cubeSelectionne]->move();
	cout << endl;
}


void Pong::drawAll(sf::RenderWindow * win) {
	// On dessine tous les objets graphiques en appelant leur fonction de dessin
	for (unsigned int i=0; i<ant.size(); i++) {
		ant[i]->dessine(win);
	}
}


void Pong::initBoard(sf::RenderWindow * win) {
	// On dessine tous les objets graphiques en appelant leur fonction de dessin
	for (unsigned int i=0; i<_case.size(); i++) {
		_case[i]->dessine(win);
	}
	for (unsigned int i=0; i<ant.size(); i++) {
		ant[i]->dessine(win);
	}
}


int Pong::execute(void) { 
	/**
	 * Cette fonction est l'élément clé de notre programme. Une boucle while permet
	 * de lancer indéfiniment notre programme jusqu'à ce que l'utilisateur décide de mettre
	 * fin à la partie en fermant la fenêtre de jeu. Dans cette boucle while on fait appel
	 * à différentes fonctions permettant de mettre en place notre jeu. 
	 */
	_win->clear(sf::Color(240, 240, 240));
	
	initBoard(_win);

	int timeMax = 0; 
	
  	while (_win->isOpen()) {

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    	// Dessin des objets graphiques
		drawAll(_win);
		
		// On déplace les fourmis
		if (!pause) {
			//move();
		}
		
		_win->display();
		
    	sf::Event event;
    	if(_win->pollEvent(event)) {
      		switch (event.type) {
				// Fermeture de la fenêtre
      			case sf::Event::Closed:
             		_win->close();
					break;
				// Réacquisition du focus
				case sf::Event::GainedFocus:
					cout << "Focus regain" << endl;
					pause = false;
					break;
				// Perte du focus
				case sf::Event::LostFocus:
					cout << "Focus lost" << endl;
					pause = true;
					break;
             	// Si une touche du clavier est pressée:
        		case sf::Event::KeyPressed:
        			// Si c'est la touche 'echap' on met le jeu en pause
        			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        				// On met le jeu en pause --> plus aucun mouvement
        				if (!pause) pause = true;
        				else pause = false;
        			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        				move("haut");
        			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        				move("droite");
        			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        				move("bas");
        			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        				move("gauche");
        			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						move();
					} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
						cubeSelectionne = (cubeSelectionne + 1)%2;
						cout << "Changement du cube sélectionné: c'est désormais le cube numéro " << cubeSelectionne << endl;
					}
             		break;
             	// Si on clique avec la souris:
             	case sf::Event::MouseButtonPressed:
    				// Si c'est un clic gauche:
    				if (event.mouseButton.button == sf::Mouse::Right) {
        				/**
        				 * On teste si le clic est sur une forme à l'aide de la méthode 
        				 * cliqueSouris(int, int)
        				 */
        				clicSourisDroite(event.mouseButton.x, event.mouseButton.y);
    				} else if (event.mouseButton.button == sf::Mouse::Left && !mouseButtonPressed) {
						mouseButtonPressed = true;
						clicSourisGauche(event.mouseButton.x, event.mouseButton.y);
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left && mouseButtonPressed) {
						mouseButtonPressed = false;
						cubeSelected = false;
					}
        		default:
         			break;
      		}
		}

		if (mouseButtonPressed && cubeSelected) {
			/**
			 * Récupération de la positon de la souris par rapport à la fenêtre
			 */
			sf::Vector2i globalPosition = sf::Mouse::getPosition(*_win);

			ant[cubeSelectionne]->moveThanksToMouse(globalPosition.x, globalPosition.y);
		}

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		
		// Calcul de l'intervalle de temps
		auto duration = duration_cast<microseconds>( t2 - t1 ).count();
		
		if ((int)duration > timeMax) {
			timeMax = (int)duration;
			cout << "Maximum time -> " << timeMax << endl;
		}
		
    	/**
    	 * On met le programme en pause pendant une petite durée car sinon celui-ci est trop rapide
		 * et il plante
    	 */
		usleep(3000);
	}

	return timeMax;
}