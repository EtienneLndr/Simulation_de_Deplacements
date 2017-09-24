#include <iostream>
#include "Pong.h"
#include "Constantes.h"
#include "save_datas.h"


int main(void) {
	srand(time(NULL));
	
  	Pong pong("Simulation de Deplacement", WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW, NUMBER_OF_STEP);
  	
	int timeMax = pong.execute();
	  
	cout << "Temps d'exécution maximale: " << timeMax << endl;

	writeInFile("Temps d'exécution maximale: " + to_string(timeMax));
	
	return 0;
}