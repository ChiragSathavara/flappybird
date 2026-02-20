#include <iostream>
#include "Game/Game.h"

using namespace std;

int main(int agrv, char* agrc[])
{
	
	Game G1;
	G1.InitGame();
	G1.RunGame();
	G1.DestroyGame();

	cout << "Hello World" << endl;

	return 0;

}