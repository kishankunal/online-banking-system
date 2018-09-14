#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<cctype>
#include<ctime>
#include<string>

using namespace std;

class bank
{
	private:
	int acno;
	long int adhar;
	long int mob;
	int deposit;
	char name[30];
	char type;
	
	public:
		void new_acc();
		void show_acc() const;
		void modify();
	    void dep(int);	
	    void draw(int);
	    void report() const;	
    	int retacno() const;	
		int retdeposit() const;	
	    char rettype() const;	    
};

void bank :: new_acc()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nenter aadhar card number : ";
	cin>>adhar;
	fflush(stdin);
	cout<<"\nenter your mobile number : ";
	cin>>mob;
	fflush(stdin);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	fflush(stdin);
	cout<<"\n\n\nAccount Created..";
}

void bank :: show_acc() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name<<endl;
	cout<<" aadhar card number :"<<adhar<<endl;
	cout<<"/n";
	cout<<" mobile number :"<<mob<<endl;
	cout<<" Type of Account : "<<type<<endl;
	cout<<" Balance amount : "<<deposit<<endl;
}

void bank :: modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	fflush(stdin);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"modify aadhar card number :";
	cin>>adhar;
	cout<<"modify mobile number :";
	cin>>mob;
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

void bank :: dep(int x)
{
		deposit+=x;
}

void bank :: draw(int x)
{
	deposit-=x;
}

void bank :: report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<adhar<<setw(12)<<mob<<setw(10)<<type<<setw(10)<<deposit<<endl;
}

	
int bank::retacno() const
{
	return acno;
}

int bank::retdeposit() const
{
	return deposit;
}

char bank::rettype() const
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
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
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
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


void write_account()
{
	bank b;
	ofstream outFile;
	outFile.open("account.txt",ios::binary|ios::app);
	b.new_acc();
	outFile.write(reinterpret_cast<char *> (&b), sizeof(bank));//confusion
	outFile.close();
}

void display_sp(int n)
{
	bank b;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&b), sizeof(bank)))
	{
		if(b.retacno()==n)
		{
			b.show_acc();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found=false;
	bank b;
	fstream File;
	File.open("account.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&b), sizeof(bank));//confusion
		if(b.retacno()==n)
		{
			b.show_acc();
			cout<<"\n\nEnter The New Details of account"<<endl;
			b.modify();
			int pos=(-1)*static_cast<int>(sizeof(bank));//confusion
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&b), sizeof(bank));
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
	bank b;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&b), sizeof(bank)))
	{
		if(b.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&b), sizeof(bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	bank b;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"================================================================================\n";
	cout<<"A/c no.      NAME          aadhar card no    mobile no        Type       Balance\n";
	cout<<"=================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&b), sizeof(bank)))
	{
		b.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	bank b;
	fstream File;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&b), sizeof(bank));
		if(b.retacno()==n)
		{
			cout<<"\n\tAccount status\n";
			b.show_acc();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				b.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=b.retdeposit()-amt;
				if((bal<500 && b.rettype()=='S') || (bal<1000 && b.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					b.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(b));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&b), sizeof(bank));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : your name";
	cout<<"\n\nSCHOOL : your school name";
	cin.get();
}









