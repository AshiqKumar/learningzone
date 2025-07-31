#include"SingleInherit.cpp"

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
/*
main()
 {
  student s1("mohan",26,"m.tech",'O',600);
  s1.display();
  Sport obj1("rakesh",12,'A');
  cout<<"details of Sport:"<<endl;
  obj1.display();
 }
  */							
