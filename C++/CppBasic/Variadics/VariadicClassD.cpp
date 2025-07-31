#include<iostream>
using namespace std;
//POLICY DESIGN WITH VARIADIC CLASS TEMPLATE
class Flute
{
public:
	void playFlute()
	{
		cout << "playing flute" << endl;
	}
};

class Piano
{
public:
	void playPiano()
	{
		cout << "playing flute" << endl;
	}
};

class Drums
{
public:
	void playDrums()
	{
		cout << "playing Drums" << endl;
	}
};

template<typename... Policy> class Music :public Policy...
{   };

int main()
{
	Music<Flute, Drums, Piano> obj1;
	obj1.playFlute();
	obj1.playDrums();
	obj1.playPiano();
}