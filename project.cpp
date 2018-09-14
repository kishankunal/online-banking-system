#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<cctype>
#include<ctime>
#include<string>

using namespace std;

bool isloggedin()
{
	string username,password,un,pw;
	cout<<"Enter User Name"<<" ";
	cin>>username;
	cout<<"enter password"<<" ";
	cin>>password;
	ifstream read("record");
	getline(read,un);
	getline(read,pw);
	if(un==username && pw==password)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class account
{
	long long int acno;
	char name[50];
	long long int adhar;
	long long int mobile;
	int deposit;
	char type;
public:
	void create_account();	
	void show_account() const;	
	void modify();	
	void dep(int);	
	void draw(int);	
	void report() const;	
	int retacno() const;	
	int retdeposit() const;	
	char rettype() const;	
};

void time()
{
	
	time_t now=time(0);
	char* dt=ctime(&now);
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<dt<<endl;
	
}

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\nEnter aadhar card no : ";
	cin>>adhar;
	cout<<"\n\nEnter mobile number : ";
	cin>>mobile;
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nAadhar number : "<<adhar;
	cout<<"\nMobile number : "<<mobile;
	cout<<"\nBalance amount : "<<deposit;
}

void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Aadhar number : ";
	cin>>adhar;
	cout<<"\nModify Mobile number : ";
	cin>>mobile;
	cout<<"\nMobile number : "<<mobile;
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<adhar<<setw(10)<<" "<<mobile<<setw(10)<<" "<<type<<setw(6)<<" "<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


void write_account();	
void display_sp(int);	
void modify_account(int);	
void delete_account(int);	
void display_all();		
void deposit_withdraw(int, int); 
void intro();


int main()
{
	int choice;
	time();
	cout<<"1:  register";
	cout<<"\n2: log in";
	b:cout<<"\nyour choice : ";
	cin>>choice;
	if(choice==1)
	{
		string username,password;
		cout<<"select a username ";
		cin>>username;
		cout<<"choose password ";
		cin>>password;
		ofstream file("record");
		file<<username<<endl<<password;
		file.close();
		system("cls");
		main();
	}
	else if(choice==2)
	{
		bool status =isloggedin();
		if(!status)
		{
			cout<<"\t\tEither user name or password entered is wrong  "<<endl<<"\t\ttry again "<<endl;
			system("pause");
			goto b;
			return 0;
		}
		else
		{
			cout<<"succesfully logged in ";
			system("cls");
			char ch;
	        int num;
	    do
	    {
		system("cls");
		time();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			 cout<<"\t----Account transcation form----";
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			 cout<<"\t----Account transcation form----";
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
		 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
				break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
		 	time();
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	    }
	    while(ch!='8');
	    return 1;
		}
	}
}


void write_account()
{
	time();
	account ac;
	ofstream outFile;
	outFile.open("project.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	time();
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("project.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	time();
	bool found=false;
	account ac;
	fstream File;
	File.open("project.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));//confusion
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));//confusion
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	time();
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("project.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("project.txt");
	rename("Temp.txt","project.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	time();
	account ac;
	ifstream inFile;
	inFile.open("project.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=============================================================================\n";
	cout<<"A/c no.      NAME       Aadhar No.          Mobile No.      Type  Balance\n";
	cout<<"==============================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	time();
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("project.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			cout<<"\n\tAccount status\n";
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

