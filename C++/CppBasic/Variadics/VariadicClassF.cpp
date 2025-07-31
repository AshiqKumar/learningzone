#include<iostream>
using namespace std;
template<typename...TAIL> class Compose
{
public:
	void play_music() { }
};
template<typename HEAD, typename ... TAIL> class Compose<HEAD, TAIL...> : Compose<TAIL...>
{
private:
	HEAD data;
public:
	void play_music()
	{
		data.play();
		Compose<TAIL...>::play_music();
	}
};

class Flute
{
public:
	void play()
	{
		cout << "playing flute" << endl;
	}
};

class Piano
{
public:
	void play()
	{
		cout << "playing flute" << endl;
	}
};

class Drums
{
public:
	void play()
	{
		cout << "playing Drums" << endl;
	}
};
int main()
{
	Compose<Flute, Drums> obj1;
	obj1.play_music();

	Compose<Drums, Piano, Flute> obj2;
	obj2.play_music();

}