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
		cout<<"in default con of class_person:"<<endl;
		strcpy(name,"raj");
		age=25;
		}
	person(const char *n,int a)
		{
		cout<<"in parametrized con of class_person :"<<endl;
		strcpy(name,n);
		age=a;
		}
	void display()
		{
		cout<<"name of the person:"<<name<<endl;
		cout<<"age of the person:"<<age<<endl;
		}
};
class student: virtual protected person
{
	protected:
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
	student(const char *n,int a,const char *q,const char g,int t):person(n,a)
		{
		cout<<"in parametrized con of drived class_student::"<<endl;	
		strcpy(quali,q);
		grade=g;
		tolmark=t;
		}
	void display()
		{
		person::display();
		cout<<"quali of the person::"<<quali<<endl;
		cout<<"grade of the person::"<<grade<<endl;
		cout<<"tolmark of the person::"<<tolmark<<endl;
		}
};
class Sport: virtual protected person
{
	protected : char sgrade;
	public: Sport()
		{	cout<<"in Sport def cons:"<<endl;
			sgrade='\0';
		}
		Sport(const char *n,int a,char ch)
		{	cout<<"in Sport para cons:"<<endl;
			age=a;
			strcpy(name,n);
			sgrade=ch;

		}		

		void display()
		{
			cout<<"in sport display"<<endl;
			person::display();
			cout<<"Sgrade:"<<sgrade<<endl;
		}
		~Sport()
		{
			cout<<"Sport Destructor:"<<endl;
		}
};
class Result : public student , public Sport
{
	int vote_id;
	public: Result()
		{	cout<<"in Result def cons:"<<endl;
			vote_id=0;
		}
		Result(const char *n,int a,int v)
		{
			cout<<"in result para:"<<endl;
			age=a;
			strcpy(name,n);
			vote_id=v;
		}
		void cal_year()
		{
		
			if(age>18)
			{
			cout<<"eligibile for voting"<<endl;
			}
			else
			{
			cout<<"not eligibile for voting"<<endl;
			}
		}
		void display()
		{
		Sport::display();
                cout<<"name of the person::"<<name<<endl;
                cout<<"age of the person::"<<age<<endl;
                cout<<"voter_id of the person::"<<age<<endl;
		}
	~Result()
	{
		cout<<"Result destructor"<<endl;
	}
};


main()
{
	student s("mohan",26,"m.tech",'O',600);
  	s.display();
  	Sport obj1("rakesh",12,'A');
	cout<<"details of Sport:"<<endl;
	obj1.display();
	Result obj("sahil",23,505);
	obj.cal_year();
	obj.display();
}
