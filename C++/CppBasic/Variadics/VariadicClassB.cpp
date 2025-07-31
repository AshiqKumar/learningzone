#include<iostream>
#include<vector>
#include<initializer_list>
#include<algorithm>
using namespace std;
//****************
/*
* An enumerated type that represents the type of the variable currently
* being stored in the Variant.
*/
enum VariantType { IntType, FloatType, DoubleType, InvalidType };
//----------------------------------------
class Variant
{
	friend ostream& operator <<(ostream &print, Variant &v);
public:
	Variant();
	Variant(int val);
	Variant(float val);
	Variant(double val);
	~Variant();
	VariantType GetType() const;
	int AsInt();
	const int AsInt() const;
	float AsFloat();
	const float AsFloat() const;
	double AsDouble();
	const double AsDouble() const;
private:
	union VariantUnion
	{
		int intValue;
		float floatValue;
		double doubleValue;
	};
	VariantUnion value;
	VariantType type;
};

Variant::Variant() { type = InvalidType; }
Variant::Variant(int val)
{
	value.intValue = val;
	type = IntType;
}
Variant::Variant(float val)
{
	value.floatValue = val;
	type = FloatType;
}
Variant::Variant(double val)
{
	value.doubleValue = val;
	type = DoubleType;
}


Variant::~Variant() {	}
VariantType Variant::GetType() const
{
	return type;
}
int Variant::AsInt()
{
	return value.intValue;
}
const int Variant::AsInt() const
{
	return value.intValue;
}

float Variant::AsFloat()
{
	return value.floatValue;
}
const float Variant::AsFloat() const
{
	return value.floatValue;
}
double Variant::AsDouble()
{
	return value.doubleValue;
}
const double Variant::AsDouble() const
{
	return value.doubleValue;
}

ostream& operator <<(ostream &print, Variant &v)
{
	switch (v.GetType())
	{
	case IntType:
		cout << v.AsInt() << endl;
		break;
	case FloatType:
		cout << v.AsFloat() << endl;
		break;
	case DoubleType:
		cout << v.AsDouble() << endl;
		break;
	default:
		cout << "Invalid Type" << endl;
	}
	return print;
}

vector<Variant> v1;
//*******************
template<typename...TAIL> class Dummy
{
public:
	
};
template<typename HEAD, typename ... TAIL> class Dummy<HEAD, TAIL...> : Dummy<TAIL...>
{
private:
	HEAD data;
public:
	Dummy(HEAD h, TAIL... args) :Dummy<TAIL... >(args...), data(h)
	{
		//cout << "No. of elements left further ..." << sizeof...(args) << endl;
		//cout << data << endl;
		v1.push_back(h);
	}
};


//***************************
int main()
{
	Dummy<int, float, double> obj1(10,12.34f, 56.12);
	//Dummy<int, float, int> obj1(10, 12.34f, 56);
	auto itr = v1.begin();
	while(itr != v1.end())
	{
		cout << *itr ;
		itr++;
	}
	/*for (auto itr : v1)
	{
		cout << itr ;
	}*/
}