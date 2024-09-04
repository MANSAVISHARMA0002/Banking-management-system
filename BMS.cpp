// bank manage system using c++
#include<bits/stdc++.h>
using namespace std;

class Bank_account{
    int account_number;
    char name[50];
    char type;
    int money_deposit;

    public:
        void modify();
        void deposit(int n){
            money_deposit += n;
        }
        void withdraw(int n){
            money_deposit-=n;
        }
        int retdeposit() const{
            return money_deposit;
        }
        void report() const;
        int retacno() const{
            return account_number;
        }
        void create_account();
        void display_account();
};

void Bank_account::modify(){
    cout<<"\t Account No. : "<<account_number<<endl;;
	cout<<"\t Modify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\t Modify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\t Modify Balance amount : ";
	cin>>money_deposit;
}
void Bank_account::report() const{
    cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<type<<setw(10)<<money_deposit<<endl;
}
void Bank_account::create_account(){
    cout<<"\t Enter the account number: ";
    cin>>account_number;
    Bank_account ac;
    bool found=false;
    fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\t File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_account));
		if(ac.retacno()==account_number){
            found = true;
            //break;
        }
    }
    if(found==true){
        cout<<"\t Account already exists! \nPress any key to continue....";
        return;
    }
    cout<<"\t Enter the account holder name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\t Enter the type of account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter a initial amount (500>= for Saving and 1000>= for current): ";
    cin>>money_deposit;
    cout<<endl;
    cout<<"\t Account created...... :)"<<endl;
}
void Bank_account::display_account(){
    cout<<"\t Account number: "<<account_number<<endl;
    cout<<"\t Account Holder's Name: "<<name<<endl;
    cout<<"\t Type of account: "<<type<<endl;
    cout<<"\t Balance amount: "<<money_deposit<<endl;
}

// function write account details in binary file
void write_account(){
    Bank_account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
    outFile.close();
}

//function to delete account;
void delete_account(int n){
    Bank_account ac;
    ifstream infile;
    ofstream outFile;
    infile.open("account.dat", ios::binary);
    if(!infile){
        cout<<"File couldn't be open. Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_account))){
        if(ac.retacno()!=n){
            outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_account));
        }
    }
    infile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\t Account Deleted....."<<endl;
}

//function to search an account
void display_details(int n){
    Bank_account ac;
    bool flag=false;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if(!infile){
        cout<<"File couldn't be open. Press any Key...";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
    while(infile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_account))){
        if(ac.retacno()==n){
            ac.display_account();
            flag=true;
            break;
        }
    }
    infile.close();
    if(flag==false){
        cout<<"\t Account doesn't exist."<<endl;
    }
}

//display all account
void display_all(){
    Bank_account ac;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"File could not be opened.Press any key.....";
        return;
    }
    cout<<"\t All account Holder Lists"<<endl;
    cout<<"=================================================="<<endl;
    cout<<"A/c No.      Name         Type          Balance"<<endl;
    cout<<"=================================================="<<endl;
    while(infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account))){
        ac.report();  //calling member function of class
    }
    infile.close();
}

//deposit withdraw money
void deposit_withdraw_money(int n, int option){
    int amt;
	bool found=false;
	Bank_account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_account));
		if(ac.retacno()==n)
		{
			ac.display_account();
			if(option==2)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.deposit(amt);
			}
			if(option==3)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.withdraw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_account));
			cout<<"\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\t Record Not Found ";
}

//updation account
void updation_account(int n){
    bool found=false;
	Bank_account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(!File.eof() && found==false){
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank_account));
        if(ac.retacno()==n){
            ac.display_account();
            cout<<"\t Enter the new details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(Bank_account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_account));
			cout<<"\n\n\t Record Updated";
			found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\t Record Not Found."<<endl;
}
int main(){
    char ch;
    int num;
    do{
        cout<<"\t\t-----------------------------------------"<<endl;
        cout<<"\t\t | Welcome to the Banking Managemetn system | "<<endl;
        cout<<"\t\t-----------------------------------------"<<endl;
        cout<<endl;
        cout<<"\t ---Main Menu---"<<endl;
        cout<<"\t 1.Create account"<<endl;
        cout<<"\t 2.Deposite Money"<<endl;
        cout<<"\t 3.Withdraw Money"<<endl;
        cout<<"\t 4.Balance Enquiry"<<endl;
        cout<<"\t 5.All account Holder List"<<endl;
        cout<<"\t 6.Close an Account"<<endl;
        cout<<"\t 7.Modify an Account"<<endl;
        cout<<"\t 8.Exit"<<endl;
        cout<<endl;

        cout<<"\t Enter your choice from (1-8): ";
        cin>>ch;
        cout<<endl;
        switch(ch){
            case '1':
                write_account();
                break;
            case '2': //deposit money
                cout<<"\t Enter account number: ";
                cin>>num;
                deposit_withdraw_money(num, 2);
                break;
            case '3': // withdraw money
                cout<<"\t Enter account number: ";
                cin>>num;
                deposit_withdraw_money(num, 3);
                break; 
            case '4': // balance enquiry
                cout<<"\t Enter account number: ";
                cin>>num;
                display_details(num);
                break; 
            case '5': //display all 
                display_all();
                break;
            case '6': //close an account
                cout<<"\t Enter account number: ";
                cin>>num;
                cout<<endl;
                delete_account(num);
                break;
            case '7': //modify an account
                cout<<"\t Enter account number: ";
                cin>>num;
                updation_account(num);
                break;
            case '8':
                cout<<"\t Thanks for using Banking Management System"<<endl;
                break;
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    
    return 0;
}
