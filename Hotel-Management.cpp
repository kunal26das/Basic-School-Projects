#include<iostream>
#include<fstream>-
#include<conio.h>---
#include<ctype.h>---
#include<process.h>-
#include<stdio.h>---
#include<stdlib.h>--
#include<string.h>--
#include<time.h>----

using namespace std;

class hotel
{
	private :

	int serial,adult,child,room,days,y1,m1,d1,y2,m2,d2;
	char name[15],addr[15],contact[10];
	float total,hours;

	private :

	int last_serial();
	int find_serial(int);
	int find_room(int);
	void display_entry(int);
	void sort_list();

	public :

	void date_1();
	void date_2();
	void billing();

	void deleter(int);

	void write_function();
	void read_function();
	void search_function();
	void insert_function();
	void modify_function();
	void delete_function();

}h;

int hotel::last_serial()
{
	fstream list;
	list.open("HOTEL.dat",ios::in);
	list.seekg(0,ios::beg);
	int s=100;
	while(list.read((char*)this,sizeof(hotel)))
	s=serial;
	list.close();
	return s;
}

int hotel::find_serial(int s)
{
	fstream list;
	list.open("HOTEL.dat",ios::in);
	list.seekg(0,ios::beg);
	int found=0;
	while(list.read((char*)this,sizeof(hotel)))
	if(serial==s)
	{
		found=1;
		break;
	}
	list.close();
	return found;
}

int hotel::find_room(int r)
{
	fstream list;
	list.open("HOTEL.dat",ios::in);
	list.seekg(0,ios::beg);
	int found=0;
	while(list.read((char*)this,sizeof(hotel)))
	{
		if(room==r)
		{
			found=1;
			break;
		}
	}
	return found;
}

void hotel::display_entry(int s)
{
	float total=0;
	fstream list;
	list.open("HOTEL.dat",ios::in);
	list.seekg(0,ios::beg);
	while(list.read((char*)this,sizeof(hotel)))
	{
		if(serial==s)
		{
			cout<<"\n Serial : "<<serial;
			cout<<"\n Name : ";puts(name);
			cout<<" Address : ";puts(addr);
			cout<<" Contact : ";puts(contact);
			cout<<" Adult : "<<adult;
			cout<<"\n Child : "<<child;
			cout<<"\n Stay of : ";
			if(hours!=-24)
			cout<<hours<<" hour(s)";
			if(days!=-7)
			cout<<days<<" day(s)";
			cout<<"\n Room number : "<<room;
			cout<<"\n Arrival date : "<<d1<<"-"<<m1<<"-"<<y1;
			if(total!=0)
			cout<<"\n Total amount : "<<total<<" Rs.";
			if(d2!=0)
			cout<<"\n Leaving date : "<<d2<<"-"<<m2<<"-"<<y2;
		}
	}
	return;
}
void hotel::deleter(int s)
{
	fstream list,temp;
	list.open("HOTEL.dat",ios::in);
	temp.open("TEMPORARY.dat",ios::out);
	list.seekg(0,ios::beg);
	while(!list.eof())
	{
		list.read((char*)this,sizeof(hotel));
		if(list.eof())
		break;
		if(serial!=s)
		temp.write((char*)this,sizeof(hotel));
	}
	list.close();
	temp.close();
	remove("HOTEL.dat");
	rename("TEMPORARY.dat","HOTEL.dat");
	return;
}

void hotel::date_1()
{
	time_t t=time(0);
	struct tm*now=localtime(&t);
	h.y1=(now->tm_year+1900);
	h.m1=(now->tm_mon+1);
	h.d1=(now->tm_mday);
	return;
}

void hotel::date_2()
{
	if(hours!=-24)
	{
		h.d2=h.d1;
		h.m2=h.m1;
		h.y2=h.y1;
	}
	else if(days!=-7)
	{
		h.d2=h.d1+(days-1);
		h.m2=h.m1;
		h.y2=h.y1;
		if(h.m2==2)
		{
			if(h.d2>29)
			{
				h.d2=h.d2-29;
				++h.m2;
			}
		}
		if(h.d2>31)
		{
			h.d2=h.d2-31;
			++h.m2;
		}
	}
}

void hotel::sort_list()
{
	int size,i=0,j;
	hotel arr[100];
	hotel temp;
	fstream list;
	list.open("HOTEL.dat",ios::in);
	list.seekg(0,ios::beg);
	while(list.read((char*)&arr[i],sizeof(hotel)))
	i++;
	size=i;
	list.close();
	for(i=1;i<size;i++)
	for(j=0;j<size-i;j++)
	{
		if(arr[j].serial>arr[j+1].serial)
		{
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
	}
	list.open("HOTEL.dat",ios::out);
	for(i=0;i<size;i++)
	list.write((char*)&arr[i],sizeof(hotel));
	list.close();
	return;
}
void hotel::billing()
{
	char ch;
	int s;
//	clrscr();
	cout<<"\n \t\t\t\t\t\t\t\t (back = 0)\n\n";
	cout<<"=====================================================";
	cout<<"\n Enter the serial for billing : ";
	cin>>s;
	if(s==0)
	return;
	display_entry(s);
	cout<<"\n\n Do you want to prepare bill ? : ";
	ch=getche();ch=toupper(ch);
	if(ch!='Y')
	return;
	fstream list;
	list.open("HOTEL.dat",ios::in);
	while(!list.eof())
	{
		list.read((char*)&h,sizeof(hotel));
		if(h.serial==s)
		break;
	}
	list.close();
	if(d2==0)
	h.hotel::date_2();
	if(total==0)
	{
		h.total=(h.adult*500)+(h.child*100);
		if(h.days!=-7)
		h.total=h.total+(h.days*1500);
		if(h.hours!=-24)
		h.total=h.total+(h.hours*150);
	}
	else
	cout<<"\n\n The person left on "<<d2<<"-"<<m2<<"-"<<y2;
	if(ch=='Y')
	{
		list.open("HOTEL.dat",ios::out,ios::ate);
		int location=(s-1)*sizeof(hotel);
		list.seekp(location);
		list.write((char*)&h,sizeof(hotel));
		list.close();
	}
	cout<<"\n\n Total amount = "<<h.total<<" Rs.";
	cout<<"\n\n Press any key to go back to menu ";
	getch();
	return;
}

void hotel::write_function()
{
	int s,r,valid,choice;
	char ch;
	s=last_serial();
	++s;
	clrscr();
	cout<<"\n Enter the details: \n";
	cout<<"\n Serial : "<<s;
	cout<<endl;
	do
	{
		valid=1;
		cout<<" Name : ";
		gets(h.name);
		strupr(h.name);
		if((strlen(h.name)<1)||(strlen(h.name)>15))
		{
			gotoxy(1,5);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Address : ";
		gets(h.addr);
		strupr(h.addr);
		if((strlen(h.addr)<1)||(strlen(h.addr)>15))
		{
			gotoxy(1,6);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Contact : ";
		gets(h.contact);
		if((strlen(h.contact)<1)||(strlen(h.contact)>10))
		{
			gotoxy(1,7);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Number of adults : ";
		cin>>h.adult;
		if(h.adult<=0||h.adult>4)
		{
			gotoxy(1,8);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Number of child : ";
		cin>>h.child;
		if(h.child<0||h.child>2)
		{
			gotoxy(1,9);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Room number : ";
		cin>>r;
		if(r<1||r>50)
		{
			gotoxy(1,10);
			clreol();
			valid=0;
		}
		if(find_room(r))
		{
			gotoxy(1,10);
			clreol();
			valid=0;
		}
		else
		h.room=r;
	}while(!valid);
	cout<<endl;
	do
	{
		valid=1;
		cout<<" Stay as per : \n";
		cout<<" 1. Hours \n";
		cout<<" 2. Days \n";
		gotoxy(21,12);
		cin>>choice;
		if(choice<=0||choice>2)
		{
			gotoxy(1,12);
			clreol();
			valid=0;
		}
		if(choice==1)
		{
			do
			{
				valid=1;
				h.days=-7;
				gotoxy(1,13);clreol();
				cout<<" 1. How many ? : ";
				cin>>h.hours;
				if(h.hours<=0||h.hours>24)
				valid=0;
			}while(!valid);
		}
		if(choice==2)
		{
			do
			{
				valid=1;
				h.hours=-24;
				gotoxy(1,14);clreol();
				cout<<" 2. How many ? : ";
				cin>>h.days;
				if(h.days<=0||h.days>30)
				valid=0;
			}while(!valid);
		}
	}while(!valid);
	do
	{
		gotoxy(1,16);clreol();
		cout<<" Do you want to save this record ? : ";
		cin>>ch;
		ch=toupper(ch);
		if(ch=='Y')
		{
			h.total=0;
			h.serial=s;
			h.hotel::date_1();
			h.d2=h.m2=h.y2=0;
			fstream list;
			list.open("HOTEL.dat",ios::out|ios::app);
			list.write((char*)&h,sizeof(hotel));
			list.close();
			++s;
		}
	}while(ch!='N'&&ch!='Y');
	return;
}

void hotel::read_function()
{
	int s,X=0,found=0;
	fstream list;
	do
	{
		fstream list;
		list.open("HOTEL.dat",ios::in);
		list.seekg(0,ios::beg);
		clrscr();
		cout<<endl;
		while(!list.eof())
		{
			list.read((char*)this,sizeof(hotel));
			found=1;

				cout<<" "<<serial<<" ";
				puts(name);
				cout<<"\n";

		}
		for(int i=1;i<26;i++)
		{
			gotoxy(40,i);
			cout<<"|";
		}
		gotoxy(2,24);
		cout<<"(BACK = 0) ENTER SERIAL NUMBER : ";
		cin>>s;
		if(s==0)
		return;
		found=find_serial(s);
		if(found)
		{
			gotoxy(42,2);
			cout<<"SERIAL : "<<serial;
			gotoxy(42,4);
			cout<<"NAME : ";puts(name);
			gotoxy(42,6);
			cout<<"ADDRESS : ";puts(addr);
			gotoxy(42,8);
			cout<<"CONTACT : ";puts(contact);
			gotoxy(42,10);
			cout<<"ADULT : "<<adult;
			gotoxy(42,12);
			cout<<"CHILD : "<<child;
			gotoxy(42,14);
			cout<<"ROOM NO. : "<<room;
			gotoxy(42,16);
			cout<<"STAY OF : ";
			if(hours!=-24)
			cout<<hours<<" HOUR(S)";
			else if(days!=-7)
			cout<<days<<" DAY(S)";
			gotoxy(42,18);
			cout<<"ARRIVAL DATE : "<<d1<<"-"<<m1<<"-"<<y1;
			gotoxy(42,20);
			if(total!=0)
			cout<<"TOTAL : "<<total;
			gotoxy(42,22);
			if(d2!=0)
			cout<<"LEAVING DATE : "<<d2<<"-"<<m2<<"-"<<y2;
		}
		else if(!found)
		{
			gotoxy(41,2);
			cout<<" ENTRY NOT FOUND !";
		}
		gotoxy(42,24);
		cout<<"PRESS ANY KEY ";
		getch();
	}while(X==0);
	list.close();
	return;
}

void hotel::search_function()
{
	clrscr();
	int s,found;
	cout<<"\n \t\t\t\t\t\t\t\t (back = 0) \n";
	cout<<"=====================================================";
	cout<<"\n Enter the serial code which you want to search : ";
	cin>>s;
	if(s==0)
	return;
	if(!find_serial(s))
	cout<<"\n Entry not found ! ";
	else
	display_entry(s);
	cout<<"\n\n Press any key to go back to menu";
	getch();
	return;
}

void hotel::insert_function()
{
	char ch;
	int r,valid,choice;
	clrscr();
	cout<<"\n Enter the details of the customer : (Back = 0)\n\n";
	cout<<"=====================================================";
	cout<<endl;
	do
	{
		valid=1;
		cout<<" Serial : ";
		cin>>h.serial;
		if(h.serial==0)
		return;
		if((h.serial<=100)||(h.serial>150))
		{
			gotoxy(1,6);
			clreol();
			valid=0;
		}
		if(find_serial(h.serial))
		{
			gotoxy(1,6);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Name : ";
		gets(h.name);
		strupr(h.name);
		if((strlen(h.name)<1)||(strlen(h.name)>15))
		{
			gotoxy(1,7);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Address : ";
		gets(h.addr);
		strupr(h.addr);
		if((strlen(h.addr)<1)||(strlen(h.addr)>15))
		{
			gotoxy(1,8);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Contact : ";
		gets(h.contact);
		if((strlen(h.contact)<1)||(strlen(h.contact)>10))
		{
			gotoxy(1,9);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Number of adults : ";
		cin>>h.adult;
		if(h.adult<=0||h.adult>4)
		{
			gotoxy(1,10);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Number of child : ";
		cin>>h.child;
		if(h.child<0||h.child>2)
		{
			gotoxy(1,11);
			clreol();
			valid=0;
		}
	}while(!valid);
	do
	{
		valid=1;
		cout<<" Room number : ";
		cin>>r;
		if(r<1||r>50)
		{
			gotoxy(1,12);
			clreol();
			valid=0;
		}
		if(find_room(r))
		{
			gotoxy(1,12);
			clreol();
			valid=0;
		}
		else
		h.room=r;
	}while(!valid);
	cout<<endl;
	do
	{
		valid=1;
		cout<<" Stay as per : \n";
		cout<<" 1. Hours \n";
		cout<<" 2. Days \n";
		gotoxy(21,14);
		cin>>choice;
		if(choice<=0||choice>2)
		{
			gotoxy(1,14);
			clreol();
			valid=0;
		}
		if(choice==1)
		{
			do
			{
				valid=1;
				h.days=-7;
				gotoxy(1,15);clreol();
				cout<<" 1. How many ? : ";
				cin>>h.hours;
				if(h.hours<=0||h.hours>24)
				valid=0;
			}while(!valid);
		}
		if(choice==2)
		{
			do
			{
				valid=1;
				h.hours=-24;
				gotoxy(1,16);clreol();
				cout<<" 2. How many ? : ";
				cin>>h.days;
				if(h.days<=0||h.days>30)
				valid=0;
			}while(!valid);
		}
	}while(!valid);
	do
	{
		gotoxy(1,18);clreol();
		cout<<" Do you want to save this record ? : ";
		cin>>ch;
		ch=toupper(ch);
		if(ch=='Y')
		{
			h.total=0;
			h.hotel::date_1();
			h.d2=h.m2=h.y2=0;
			fstream list;
			list.open("HOTEL.dat",ios::out|ios::app);
			list.write((char*)&h,sizeof(h));
			list.close();
			sort_list();
		}
	}while(ch!='N'&&ch!='Y');
	return;
}

void hotel::modify_function()
{
	char ch;
	int s;
	clrscr();
	cout<<"\n \t\t\t\t\t\t\t\t (Back = 0) \n";
	cout<<"=====================================================";
	cout<<"\n Enter the serial to modify : ";
	cin>>s;
	if(s==0)
	return;
	display_entry(s);
	cout<<"\n\n Do you want to modify this entry ? : ";
	ch=getche();ch=toupper(ch);
	if(ch=='N')
	return;

	fstream list;
	list.open("HOTEL.dat",ios::in);
	while(!list.eof())
	{
		list.read((char*)&h,sizeof(hotel));
		if(h.serial==s)
		break;
	}

	gotoxy(17,8);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,8);
	clreol();
	if(ch=='Y')
	cin>>h.serial;
	if(ch=='N')
	cout<<h.serial;

	gotoxy(17,9);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,9);
	clreol();
	if(ch=='Y')
	gets(h.name);
	if(ch=='N')
	puts(h.name);

	gotoxy(17,10);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,10);
	clreol();
	if(ch=='Y')
	gets(h.addr);
	if(ch=='N')
	puts(h.addr);

	gotoxy(17,11);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,11);
	clreol();
	if(ch=='Y')
	gets(h.contact);
	if(ch=='N')
	puts(h.contact);

	gotoxy(17,12);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,12);
	clreol();
	if(ch=='Y')
	cin>>h.adult;
	if(ch=='N')
	cout<<h.adult;

	gotoxy(17,13);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,13);
	clreol();
	if(ch=='Y')
	cin>>h.child;
	if(ch=='N')
	cout<<h.child;

	gotoxy(17,14);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,14);
	clreol();
	if(ch=='Y')
	{
		if(hours!=-24)
		cin>>h.hours;
		if(days!=-7)
		cin>>h.days;
	}
	if(ch=='N')
	{
		if(hours!=-24)
		cout<<h.hours;
		if(days!=-7)
		cout<<h.days;
	}

	gotoxy(17,15);clreol();cout<<"modify (y/n) : ";ch=getche();ch=toupper(ch);
	gotoxy(17,15);
	clreol();
	if(ch=='Y')
	cin>>h.room;
	if(ch=='N')
	cout<<h.room;

	if(h.total!=0)
	{
		h.total=(h.adult*500)+(h.child*100);
		if(h.hours!=-24)
		h.total=h.total+(h.hours*150);
		if(h.days!=-7)
		h.total=h.total+(h.days*1500);
	}

	if(d2!=0)
	getch();

	list.close();
	gotoxy(1,21);
	cout<<"\n Do you want to save the changes ? : ";
	ch=getche();ch=toupper(ch);
	if(ch=='N')
	return;
	if(ch=='Y')
	{
		int location=(s-1)*sizeof(hotel);
		list.open("HOTEL.dat",ios::out|ios::ate);
		list.seekp(location);
		list.write((char*)&h,sizeof(hotel));
		list.close();
	}
}

void hotel::delete_function()
{
	clrscr();
	char ch;
	int s,found;
	cout<<"\n \t\t\t\t\t\t\t\t (Back = 0) \n";
	cout<<"=====================================================";
	cout<<"\n Enter the serial code which you want to delete : ";
	cin>>s;
	if(s==0)
	return;
	if(!find_serial(s))
	{
		cout<<"\n Entry not found ! ";
		cout<<"\n\n Press any key to go back to menu ";
	}
	else
	{
		display_entry(s);
		cout<<"\n\n Are you sure you want to delete this entry ? : ";
		ch=getche();ch=toupper(ch);
		if(ch=='Y')
		{
			deleter(s);
			cout<<"\n\n The specified entry has been deleted ";
		}
	}
	cout<<"\n\n Press any key to go back to menu ";
	getch();
	return;
}

void intro()
{
	cout<<"\n\n\n";
	cout<<"=====================================================";
	cout<<"\n\t JAWAHARLAL NEHRU SCHOOL \n\n";
	cout<<"=====================================================";
	cout<<"\n";
	cout<<"\t\t\t SESSION = 2012-13 \n\n";
	cout<<"\t\t\t CLASS = XII 'A' \n\n";
	cout<<"\t\t\t NAME = SHRIKANT DUBEY \n\n";
	cout<<"\t\t\t PROJECT = HOTEL MANAGEMENT \n\n";
	cout<<"=====================================================";
	cout<<"\n\t\t\t Press any key to continue\n\n";
	cout<<"=====================================================";
	gotoxy(55,20);
	getch();
}

void edit_menu()
{
	b:
	clrscr();
	int ch;
	cout<<"\n\n\n";
	cout<<"=====================================================";
	cout<<"\n\t\t RECORDS MENU \n\n";
	cout<<"=====================================================";
	cout<<"\n";
	cout<<"\t\t\t 1. SEARCH AN EXISTING ENTRY \n\n";
	cout<<"\t\t\t 2. INSERT A NEW ENTRY \n\n";
	cout<<"\t\t\t 3. MODIFY AN EXISTING ENTRY \n\n";
	cout<<"\t\t\t 4. DELETE AN EXISTING ENTRY \n\n";
	cout<<"=====================================================";
	cout<<"\n (Back = Backspace) Enter your choice :\t\t\t (Exit = 0)\n\n";
	cout<<"=====================================================";
	gotoxy(49,20);
	ch=getche();

	if(ch=='1')
	{
		hotel h;
		h.hotel::search_function();
		goto b;
	}

	if(ch=='2')
	{
		hotel h;
		h.hotel::insert_function();
		goto b;
	}

	if(ch=='3')
	{
		hotel h;
		h.hotel::modify_function();
		goto b;
	}

	if(ch=='4')
	{
		hotel h;
		h.hotel::delete_function();
		goto b;
	}

	if(ch=='\b')
	return;

	if(ch=='0')
	exit(0);

	else
	goto b;
}

void main_menu()
{
	a:
	clrscr();
	int ch;
	cout<<"\n\n\n";
	cout<<"=====================================================";
	cout<<"\n\t\t MAIN MENU \n\n";
	cout<<"=====================================================";
	cout<<"\n";
	cout<<"\t\t\t 1. ADD NEW ENTRY \n\n";
	cout<<"\t\t\t 2. RECORDS \n\n";
	cout<<"\t\t\t 3. BILLING \n\n";
	cout<<"\t\t\t 4. EDIT MENU \n\n";
	cout<<"=====================================================";
	cout<<"\n\t\t\t Enter your choice :\t\t\t (Exit = 0)\n\n";
	cout<<"=====================================================";
	gotoxy(49,20);
	ch=getche();

	if(ch=='1')
	{
		hotel h;
		h.hotel::write_function();
		goto a;
	}

	if(ch=='2')
	{
		hotel h;
		h.hotel::read_function();
		goto a;
	}

	if(ch=='3')
	{
		hotel h;
		h.hotel::billing();
		goto a;
	}

	if(ch=='4')
	{
		edit_menu();
		goto a;
	}

	if(ch=='0')
	return;

	else
	goto a;
}

void main()
{
	clrscr();
	intro();
	main_menu();
}
