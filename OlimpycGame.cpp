#include "OlimpycGame.h"

//методы класса Listener
Listener::Listener()
{
	cout << "Введите имя подписчика: ";
	cin.get();
	getline(cin, name);
	cout << "Выберите страну для ставки по биатлону: " << endl;
	bid_biathlon = retCountry();
	cout << "Выберите страну для ставки по скелетону: " << endl;
	bid_sceleton = retCountry();
	cout << "Выберите страну для ставки по конькобежному спорту: " << endl;
	bid_skating = retCountry();
	cout << "Выберите страну для ставки по фигурному катанию: " << endl;
	bid_fskating = retCountry();
}
string Listener::retCountry()
{
point:
	cout << "|0| - Россия" << endl;
	cout << "|1| - Канада" << endl;
	cout << "|2| - Франция" << endl;
	cout << "|3| - Финляндия" << endl;
	cout << "|4| - Япония" << endl;
	int ans;
	cin >> ans;
	switch (ans)
	{
	case 0:
		return "Russia";
	case 1:
		return "Canada";
	case 2:
		return "France";
	case 3:
		return "Finland";
	case 4:
		return "Japan";
	default:
		cerr << "Некорректный ввод индекса страны. Возвращение на выбор..." << endl;
		goto point;
	}
}
void Listener::update(string in, int sport)
{
	if (bid_biathlon == in && sport == BIATH)
	{
		cout << "По биатлону сыграла ставка!" << endl; return;
	}
	else if (sport == BIATH)
	{
		cout << "По биатлону ставка не сыграла!" << endl; return;
	}
	if (bid_sceleton == in && sport == SCEL)
	{
		cout << "По скелетону сыграла ставка!" << endl; return;
	}
	else if (sport == SCEL)
	{
		cout << "По скелетону ставка не сыграла!" << endl; return;
	}
	if (bid_skating == in && sport == SKAT)
	{
		cout << "По конькобежному спорту сыграла ставка!" << endl; return;
	}
	else if (sport == SKAT)
	{
		cout << "По конькобежному спорту ставка не сыграла!" << endl; return;
	}
	if (bid_fskating == in && sport == FSKAT)
	{
		cout << "По фигурному катанию сыграла ставка!" << endl; return;
	}
	else if (sport == FSKAT)
	{
		cout << "По фигурному катанию ставка не сыграла!" << endl; return;
	}
	cerr << "Некорректные переданные данные: указанная страна победитель " << in << endl;
}
//методы класса sportsman
istream& sportsman::setSportsman(istream& in)
{
	getline(in, family);
	getline(in, name);
	getline(in, secfamily);
	in >> power;
	in >> dexterity;
	in >> lacky;
	in >> stamina;
	return in;
}
float sportsman::getMid()//возвращает среднее между параметрами спортсмена
{
	return double(power + dexterity + lacky + stamina) / 4.0;
}

//методы класса country

void country::createCountry(string filename)
{
	s = new sportsman();
	setFile(filename);
	initSportsman();
}
//инициализирует показатели спортсмена
void country::initSportsman()
{
	fs.open(filestring, ios_base::in);
	s->setSportsman(fs);
	fs.close();
}
//устанавливает имя файла 
void country::setFile(string files)
{
	filestring = files;
}
//возвращает усредненные показатели спортсмена
float country::getMidSportsman()
{
	return s->getMid();
}


//методы класса OlimpycGames

void OlimpycGame::subscribe(Listener* l)
{
	listeners.push_back(l);
	cout << "Подписчик добавлен." << endl;
}
void OlimpycGame::unsubscribe(int index)
{
	listeners.erase(listeners.begin() + index);
	cout << "Подписчик (" << index << ") удален." << endl;
}
void OlimpycGame::notify(int sport)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		cout << "Рассылка подписчику " << listeners[i]->name << ":" << endl;
		listeners[i]->update(winner, sport);
	}
}
//непосредственный процесс игры
void OlimpycGame::Game()
{
	// создание стран, учавствующих в олимпийских играх
	Russia = new country();
	Canada = new country();
	France = new country();
	Finland = new country();
	Japan = new country();
	// инициализация стран, учавсвующих в ол.и.
	Russia->createCountry("russia.txt");
	Canada->createCountry("canada.txt");
	France->createCountry("france.txt");
	Finland->createCountry("finland.txt");
	Japan->createCountry("japan.txt");
	//биатлон, скелетон, конькобежный спорт, фигурное катание
	cout << "====================================== Начались соревнования по биатлону ======================================" << endl;
	winner = endGame();
	notify(BIATH);
	cout << "====================================== Начались соревнования по скелетону ======================================" << endl;
	winner = endGame();
	notify(SCEL);
	cout << "====================================== Начались соревнования по конькобежному спорту ======================================" << endl;
	winner = endGame();
	notify(SKAT);
	cout << "====================================== Начались соревнования по фигурному катанию ======================================" << endl;
	winner = endGame();
	notify(FSKAT);
}

string OlimpycGame::endGame() //возвращает победителя
{
	float tmp = getResult();
	if (tmp == Russia->k)return "Russia";
	else if (tmp == Canada->k) return "Canada";
	else if (tmp == France->k) return "France";
	else if (tmp == Finland->k) return "Finland";
	else if (tmp == Japan->k) return "Japan";
	else cerr << "Непредвиденная ошибка, ни один из коэффициентов стран не совпал с коэффициентом победителя." << endl;
	return "none";
}
OlimpycGame::~OlimpycGame()
{
	delete Russia;
	delete Canada;
	delete France;
	delete Finland;
	delete Japan;
	if (result != nullptr) delete[] result;
}

float OlimpycGame::getResult()
{
	result[0] = Russia->getMidSportsman();
	result[1] = Canada->getMidSportsman();
	result[2] = France->getMidSportsman();
	result[3] = Finland->getMidSportsman();
	result[4] = Japan->getMidSportsman();

	//учет рандомного стечения обстоятельств
	srand(time(NULL));
	Russia->k = result[0] *= (rand() % 100) / 100;
	Canada->k = result[1] *= (rand() % 100) / 100;
	France->k = result[2] *= (rand() % 100) / 100;
	Finland->k = result[3] *= (rand() % 100) / 100;
	Japan->k = result[4] *= (rand() % 100) / 100;
	// сортировка массива
	int tmp = 0;
	for (int i = 0; i < ccc; i++) {
		for (int j = (ccc - 1); j >= (i + 1); j--) {
			if (result[j] > result[j - 1]) {
				tmp = result[j];
				result[j] = result[j - 1];
				result[j - 1] = tmp;
			}
		}
	}
	return result[0];
}
