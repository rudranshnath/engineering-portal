/*****************************************************************************
		I N V E N T O R Y    M A N A G E M E N T
	This program is meant for inventory shops to manage the item stock.
	It uses two data files ->
		1. for storing the records of items("INVENTORY.DAT")
		2. to generate bill("BILL.DAT")

	MADE BY :
		 Rudransh Nath Tripathi;
*******************************************************************************/
#include<fstream.h>
#include<conio.h>
#include<iomanip.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
//____________________FUNCTION--PROTOTYPE____________________________________
void main_menu();
void add_item();
void show_item();
void rem_item();
void mod_item();
void add_qty();
void cus_slip();
void printBILL();
//___________________________________________________________________________
char g;              		//global variables
float today_sale=0;  		//global variables
int S=0;			//global variables
//___________________________________________________________________________
class shop			//class for records of products
{
	int code;
	float price;
	char name[30];
	int qty;

     public:

	void getdata()
	{      	cout<<"\nEnter Item code = ";
		 cin>>code;
		cout<<"\nEnter Item name = ";
		 gets(name);
		cout<<"\nEnter Price = ";
		 cin>>price;
		cout<<"\nEnter Quantity = ";
		cin>>qty;
	}

	void putdata()
	{
		cout<<"Item Code = "<<code<<"\t Price ="<<price<<"\t Name ="<<name<<"\t Quantity ="<<qty;
	}

	void add_q(int q)
	{
		qty+=q;
	}

	void mod_qty(int q)
	{
		qty-=q;
	}

	int getcode()
	{
		return code;
	}

	char* getname()
	{
		return name;
	}

	int getqty()
	{
		return qty;

	}

	float getp()
	{
		return price;
	}
};
//__________________________________________________________________________
class Bill
{       int Sno;
	int itemcode;
	char itemname[30];
	int qty;
	float price;
      public:
	void accept(shop A,int q)
	{  	Sno=++S;
		itemcode=A.getcode();
		strcpy(itemname,A.getname());
		qty=q;
		price=q*(A.getp());
	}
	void display()
	{
		cout<<"|"<<setw(2)<<Sno<<"  |"<<setw(5)<<itemcode<<"      |"<<setw(30)<<itemname<<" |"<<setw(5)<<qty<<"     |"<<setw(7)<<price<<" |"<<endl;
	}
};
//__________________________________________________________________________
//________________________MAIN--FUNCTION____________________________________
//__________________________________________________________________________
void main()
{
	clrscr();
	char n[30];

	cout<<"\n\nEnter username = ";
	 cin>>n;

	if( (strcmpi(n,"Rudransh")==0)||(strcmpi(n,"Prajjwal")==0)||(strcmpi(n,"Vinayak")==0) )
	{
		main_menu();
	}
	else
	{
		cout<<"\n Wrong username !!!";
		cout<<"\nDo you want to retry  (y/n) = ";
		 cin>>g;
		if(g=='y')
		{	main();
		}
		else
		{	exit(0);
		}
	}
	getch();
}
//__________________________________________________________________________
//______________________FUNCTION-for-main-menu______________________________
//__________________________________________________________________________
void main_menu()
{
	clrscr();
	cout<<"\n************************************************************";
	cout<<"\n             WELCOME     TO     OUR                         ";
	cout<<"\n               INVENTORY    SHOP                            ";
	cout<<"\n************************************************************";
	int ch;
	cout<<"\n\nChoose an option          -->  \n\n";
	cout<<"1. Add item to the shop \n";
	cout<<"2. Remove item from the shop \n";
	cout<<"3. Modify details of a item \n";
	cout<<"4. Add more quantity \n";
	cout<<"5. Show all available items \n";
	cout<<"6. Generate Bill\n";
	cout<<"7. Today's Sale\n";
	cout<<"8. Exit  \n";
	cout<<"\n\n Enter your choice = ";
	 cin>>ch;

	switch(ch)
	{
		case 1:
			add_item();
			break;
		case 2:
			rem_item();
			break;
		case 3:
			mod_item();
			break;
		case 4:
			add_qty();
			break;
		case 5:
			show_item();
			break;
		case 6:
			cus_slip();
			break;
		case 7:
			{
				clrscr();
				cout<<"\nToday's total sale = "<<today_sale;
				cout<<"\n\n\nDo you want to go to main menu (y/n) = ";
				 cin>>g;

				if(g=='y')
					main_menu();
			}
			break;
		case 8:
			exit(0);
		default:
			cout<<"\nInvalid Choice !!\n";

	}			//switch case closed
}                               //End of main menu function
//__________________________________________________________________________
//_____________________FUNCTION-to-add-items-to-shop________________________
//__________________________________________________________________________
void add_item()
{
	clrscr();
	cout<<"\n***********************************************************";

	fstream f1;
	shop s1;
	char c='y';
	f1.open("inventory.dat",ios::out|ios::app|ios::binary);
	while(c=='y')
	{
		cout<<"\n\nEnter detail of the item -> ";
		s1.getdata();
		f1.write((char*)&s1,sizeof(s1));
		cout<<"\nDo you want to enter more details (y/n) = ";
		 cin>>c;
	}
	f1.close();
	cout<<"\nDo you want to go the main menu (y/n) = ";
	 cin>>g;

	if(g=='y')
	{	clrscr();
		main_menu();
	}
	else
	{	exit(0);
	}
}				//End of add shop function
//___________________________________________________________________________
//__________________________FUNCTION-to-show-all-available-items_____________
//___________________________________________________________________________
void show_item()
{
	clrscr();
	fstream f1;
	shop s1;
	cout<<"\n*******************I T E M    L I S T*************************\n";
	f1.open("inventory.dat",ios::in|ios::binary);
	if(!f1)
	{	cout<<"\nError in opening file ";
		exit(1);
	}
	while(1)
	{
		f1.read((char*)&s1,sizeof(s1));
		if(!f1.eof())
		{
			cout<<endl;
			s1.putdata();
			continue;
		}
		else
		{	break;
		}
	}
	f1.close();
	cout<<"\nDo you want to go to main menu (y/n) = ";
	 cin>>g;

	if(g=='y')
	{	main_menu();
	}
	else
	{	exit(0);
	}
}				//End of show shop function
//___________________________________________________________________________
//______________________FUNCTION-for-modifying-details-of-items______________
//___________________________________________________________________________
void mod_item()
{
	clrscr();
	int k;
	fstream f1;
	shop s1;
	cout<<"\nEnter the item code whose data is to be modified = ";
	 cin>>k;
	f1.open("inventory.dat",ios::in|ios::out|ios::ate|ios::binary);
	f1.seekg(0,ios::beg);
	int pos;
	while(!f1.eof())
	{
		pos=f1.tellg();
		f1.read((char*)&s1,sizeof(s1));
		if(k==s1.getcode())
		{       s1.putdata();
			cout<<"\n***********************************************";
			cout<<"\nEnter new details = \n";
			s1.getdata();
			f1.seekp(pos);
			f1.write((char*)&s1,sizeof(s1));
			break;
		}
	}
	f1.close();
	main_menu();
}
//__________________________________________________________________________
//_______________________FUNCTION-for-removing-details-of-an-item___________
//__________________________________________________________________________
void rem_item()
{
	clrscr();
	fstream f1,f2;
	shop s1;
	int flag=0;
	char opt1;
	f1.open("inventory.dat",ios::in|ios::out|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	f1.seekg(0,ios::beg);
	int k;
	cout<<"\n\nEnter the item code whose record you want to delete = ";
	 cin>>k;
	while(!f1.eof())
	{
		f1.read((char*)&s1,sizeof(s1));
		if(f1.eof())
			break;
		if(k!=s1.getcode())
		{	f2.write((char*)&s1,sizeof(s1));
		}
		else
		{       s1.putdata();
			cout<<"\nEnter 'y' to confirm deletion  : ";
			cin>>opt1;
			flag=1;
			if(opt1!='y')
				f2.write((char*)&s1,sizeof(s1));
		}
	}
	f1.close();
	f2.close();
	remove("inventory.dat");
	rename("temp.dat","inventory.dat");
	if(flag)
		cout<<"\nThe item has been removed !!!\n";
	else
		cout<<"\nItem not found !!!\n";
	cout<<"\nDo you want to go to main menu (y/n) = ";
	 cin>>g;
	if(g=='y')
	{	clrscr();
		main_menu();
	}
	else
	{	exit(0);
	}
}
//___________________________________________________________________________
//________________________FUNCTION-to-add-more-quantity______________________
//___________________________________________________________________________

void add_qty()
{       clrscr();
	int k,q;
	fstream f1;
	shop s1;
	cout<<"\nEnter the item code whose data is to be modified = ";
	 cin>>k;
	f1.open("inventory.dat",ios::in|ios::out|ios::ate|ios::binary);
	f1.seekg(0,ios::beg);
	int pos;
	while(!f1.eof())
	{
		pos=f1.tellg();
		f1.read((char*)&s1,sizeof(s1));
		if(k==s1.getcode())
		{
			cout<<"\nEnter quantity you want to add = \n";
			 cin>>q;
			s1.add_q(q);
			f1.seekp(pos);
			f1.write((char*)&s1,sizeof(s1));
			break;
		}
	}
	f1.close();
	main_menu();


}
//___________________________________________________________________________
//________________________FUNCTION-for-displaying-customer's-bill____________
//___________________________________________________________________________
void cus_slip()
{
	clrscr();
	cout<<"\n\n********************* B I L L I N G **************************\n\n";
	fstream f1,f2;
	shop s1;
	Bill B;
	int qty,pos;
	float cost,total_cost=0;
	int item_no;
	char ch='y';
	f1.open("inventory.dat",ios::in|ios::out|ios::binary|ios::ate);
	f2.open("bill.dat",ios::out|ios::binary);
	loop:
		f1.seekp(0,ios::beg);
		cout<<"\nEnter the item no. = ";
		 cin>>item_no;
		while(!f1.eof())
		{       pos=f1.tellp();
			f1.read((char*)&s1,sizeof(s1));
			if(s1.getcode()==item_no)
			{    again:
				cout<<"\nEnter Quantity = ";
					 cin>>qty;
				if(s1.getqty()==0)
				{	cout<<"\nOut of Stock ";
					getch();
				}
				else if(qty>s1.getqty())
				{	cout<<"\nAsked quantity exceed the present quantity ";
					cout<<"\nPresent quantity is "<<s1.getqty();
					goto again;
				}
				else
				{
					cost=qty*(s1.getp());
					total_cost+=cost;
					cout<<"\nTotal Amount = "<<cost;
					s1.mod_qty(qty);
					f1.seekp(pos);
					f1.write((char*)&s1,sizeof(s1));
					B.accept(s1,qty);
					f2.write((char*)&B,sizeof(B));
				}
				cout<<"\nDo you want to enter more items to your cart (y/n) = ";
				 cin>>ch;
				if(ch=='y')
					goto loop;
				else
					break;
			}
		}
	f1.close();
	f2.close();
	printBILL();
	cout<<"\n\n\nTotal Amount to be paid by the customer = "<<total_cost;
	today_sale+=total_cost;
	cout<<"\n\nDo you want to go to main menu (y/n) = ";
	 cin>>g;
	if(g=='y')
	{	main_menu();
	}
}
//___________________________________________________________________________
//______________________FUNCTION-to-print-bill_______________________________
//___________________________________________________________________________
void printBILL()
{	clrscr();
	Bill B;
	fstream f;
	f.open("bill.dat",ios::in|ios::binary);
	if(!f)
	{
		cout<<"File opening error ";
		exit(1);
	}
	cout<<"\n********************************************************************";
	cout<<"\n\t\t\t\t\tB I L L";
	cout<<"\n********************************************************************";
	cout<<endl;
	cout<<"|"<<setw(5)<<"Sno |"<<setw(11)<<" Item code |"<<setw(30)<<"          Item name            |"<<setw(10)<<" Quantity |"<<setw(8)<<" Price  |"<<endl;
	cout<<"-------------------------------------------------------------------\n";
	while(1)
	{
		f.read((char*)&B,sizeof(B));
		if(f.eof())
			break;

		B.display();
	}
	cout<<"-------------------------------------------------------------------\n";
	f.close();
}
//___________________________________________________________________________
//___________________________________________________________________________
