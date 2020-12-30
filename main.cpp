#include<iostream>
#include"OlimpycGame.h"


using namespace std;
int main(void)
{
	setlocale(LC_ALL, "rus");
	OlimpycGame* game = new OlimpycGame();
	int ans;
	while (1)
	{
		cout << "Создать нового подписчика?\n|1| - да\n|2| - Начать олимпийские игры" << endl;
		cin >> ans;
		if (ans == 1)
		{
			Listener* newListener = new Listener();
			game->subscribe(newListener);
		}
		else if (ans == 2)
		{
			break;
		}
	}
	cout << "================================== Начинаются олимпийские игры =====================================" << endl;
	game->Game();
	
	cin.get(); cin.get();
	return 0;
}
