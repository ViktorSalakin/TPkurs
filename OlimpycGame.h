#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <string>
#include<ctime>
#include<cstdlib>

enum {BIATH = 0, SCEL, FSKAT, SKAT};


using namespace std;

class Listener
{
	string name; //имя подписчика
	string bid_biathlon; //ставка на биатлон
	string bid_sceleton;//ставка на скелетон
	string bid_skating; //ставка на конькобежный спорт
	string bid_fskating; //ставка на фигурное катание
		//биатлон, скелетон, конькобежный спорт, фигурное катание
public:
	Listener();
	string retCountry();
	void update(string in, int sport);
	friend class OlimpycGame;
};

class sportsman
{
	string family;				//фамилия
	string name;				//имя
	string secfamily;			//отчество
	string country;				//страна
	//эти параметры варьируются от 0 до 100
	float power = 0;				//сила
	float dexterity = 0;			//ловкость
	float lacky = 0;				//удача
	float stamina = 0;			//выносливость
public:
	// метод инициализации свойств спортсмена
	istream& setSportsman(istream& in);
	float getMid();
	void setCountry(string in);

};
//Из внешнего файла загружаются данные по каждому спортсмену: ФИО, страна, сила, ловкость, удача, выносливость.
class country
{

	sportsman* s; // здесь будет указатель на спортсмена
	fstream fs;//файл с которого будут считываться данные об спортмене
	string filestring; // здесь будет хранится строка с именем файла, где будет спортсменус
public:
	float k = 0.0;	//коэффициент с учетом нандомного стечения обстоятельств
	// метод создания новой страны, в качестве входного параметра -строка с названием файла с информацией о спортсмене
	void createCountry(string filename);
	//инициализирует показатели спортсмена
	void initSportsman();
	//устанавливает имя файла 
	void setFile(string files);
	//возвращает усредненные показатели спортсмена
	float getMidSportsman();
	~country()
	{
		delete s;
	}
};


class OlimpycGame
{
	vector<Listener*> listeners; //база подписчиков
	int ccc = 5; //count of country - количество стран, учавствующих в ОИ
	//перечисление стран, на каждую страну приходится по спортсмену
	country* Russia;			
	country* Canada;
	country* France;
	country* Finland;
	country* Japan;
	string winner;	//победитель
	float* result = new float[ccc];
	//получение коэффициента выиграша спортсмена стран
	float getResult();
public:
	//
	void subscribe(Listener* l);
	void unsubscribe(int index);
	void notify(int sport);
	//непосредственный процесс игры
	void Game();
	
	string endGame();
	~OlimpycGame();
};
