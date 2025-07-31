#include"heirarchical_inherit.cpp"

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
		//	age=a;
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


int main()
{
	student s1("mohan",26,"m.tech",'O',600);
  	s1.display();
  	Sport obj1("rakesh",12,'A');
	cout<<"details of Sport:"<<endl;
	obj1.display();
	Result obj("sahil",23,505);
	obj.cal_year();
	obj.display();
}
