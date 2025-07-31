#include<iostream>
#include<cstring>
using namespace std;
class person
{
	protected:
	char name[20];
	int age;
	public:
	person()
		{
		cout<<"in default con of class_ person:"<<endl;
		strcpy(name,"raj");
		age=25;
		}
	person(char *n,int a)
		{
		cout<<"in parametrized con of class_person:"<<endl;
		strcpy(name,n);
		age=a;
		}
	void display()
		{
		cout<<"name of the person:"<<name<<endl;
		cout<<"age of the person:"<<age<<endl;
		}
};
class student:protected person
{
	private:
	char quali[20];
	char grade;
	int  tolmark;
	public:
	student()
		{
		cout<<"in default con of drived class_student::"<<endl;	
		strcpy(quali,"b.tech");
		grade='A';
		tolmark=500;
		}
	student(char *q,char g,int t)
		{
		cout<<"in parametrized con of drived class_student::"<<endl;	
		strcpy(quali,q);
		grade=g;
		tolmark=t;
		}
	void display()
		{
		person::display();
	//	cout<<"name of the person::"<<name<<endl;
	//	cout<<"age  of the person::"<<age<<endl;
		cout<<"quali of the person::"<<quali<<endl;
		cout<<"grade of the person::"<<grade<<endl;
		cout<<"tolmark of the person::"<<tolmark<<endl;
		}
};

int main()		
{
	person p1;
	p1.display();
	person p2("mohan",26);
	p2.display();
	student s;
	s.display();
	student s1("m.tech",'O',600);
	s1.display();
}
