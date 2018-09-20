#include<fstream>
#include<iostream>
#include<dos.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>

using namespace std;

int i;

class product
{
	private:

	int   code;                 //product code
	char  name[15];             //product name
	float rate;                 //product rate
	int   qty1,qty2;            //product quantity in list/bill
	long  amount;               //product (rate * quantity)

	int   last_code();	        //returns last code present in the list
	int   product_code(int);    //returns the given code if found
	int   search_code(int);     //returns truth value if code is found
	void  display_product(int); //displays only one entry if found

	void  display_bill(int);    //displays only one entry if found
	int   find_bill(int);       //returns truth value if code is found
	void  modify_entry(int);    //modify function
	void  delete_entry(int);    //delete function

	public:

	void  write_product();      //write or append in the product list
	void   read_product();      //display the product list
	void insert_product();      //insert an entry in the product list
	void delete_product();      //delete an entry from the product list
	void search_product();      //search an entry in the product list
	void modify_product();      //madify an entry in the product list
	void   sort_product();      //sorts the entire product list

	void  write_bill();         //purchase function
	void   read_bill();         //display the bill
	void delete_bill();         //delete an entry from the bill
	void search_bill();         //search an entry in the bill
	void modify_bill();         //modify an entry in the bill
	void   sort_bill();         //sorts the entire bill

	void sales();               //projects sales made so far
	void remove_list();         //dalete "PRODUCT.dat"&"BILL.dat"
	void remove_bill();         //delete "BILL.dat"
};

/*--------------------------------------------------------------------------*/

void product::sales()
{
	system("cls");
	float t1=0,t2=0;
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	if(!list)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Not able to project the sales made \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Either product list or bill or both do not exist \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any ket to go back to main menu...\n";
		for(i=0;i<96;i++) cout<<"-";
		//gotoxy(42,6);
		getch();
		return;
	}
	else
	{
		while(list.read((char*)this,sizeof(product)))
		{
			amount=(qty1*rate);
			t1=t1+amount;
		}
	}
	list.close();
	fstream bill;
	bill.open("BILL.dat",ios::in);
	if(!bill)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Not able to project the sales made \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Either product list or bill or both do not exist \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any ket to go back to main menu...\n";
		for(i=0;i<96;i++) cout<<"-";
		//gotoxy(42,6);
		getch();
		return;
	}
	else
	{
		while(bill.read((char*)this,sizeof(product)))
		{
			amount=(qty2*rate);
			t2=t2+amount;
		}
	}
	bill.close();
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t\t\tSales Announces \n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Before sales :- "<<t1+t2<<" Rs.\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Sold amount  :- "<<t2<<" Rs.\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" After sales  :- "<<t1<<" Rs.\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<endl;
	for(i=0;i<96;i++) cout<<"-";
	cout<<" You have made "<<((t2/(t1+t2))*100)<<" % sale\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to continue \n";
	for(i=0;i<96;i++) cout<<"-";
	//gotoxy(30,14);
	getch();
	return;
}

/*--------------------------------------------------------------------------*/

void product::write_bill()
{
      z:
      int bought=0,valid,qty,found,tcode,t;
      char t_code[5],ch;
      product p;
      do
      {
	system("cls");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press <Enter> to see the product list             Press <0> to go back to menu\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter the product code of product which you want to purchase : ";
	valid=1;
	gets(t_code);
	if(t_code[0]=='0')
	break;
	t=atoi(t_code);
	tcode=t;
	if(tcode==0)
	{
		p.product::read_product();
		goto z;
	}
	found=product::search_code(tcode);
	if(found!=0)
	{
		product::display_product(tcode);
		cout<<" Do you want to buy this product (y/n) ? : ";
		ch=getche();
		cout<<"\n--------------------------------------------------------------------------------";
		ch=toupper(ch);
		if(ch=='Y')
		{
			int check=1;
			fstream bill;
			bill.open("BILL.dat",ios::in);
			while(bill.read((char*)this,sizeof(product)))
			{
				if(code==tcode)
				{
					check=0;
					cout<<" \aYou have already bought this product once \n";
					for(i=0;i<96;i++) cout<<"-";
					cout<<" Select <3> in bill edit menu to modify the entry \n";
					for(i=0;i<96;i++) cout<<"-";
					break;
				}
			}
			if(check)
			{
				found=product::product_code(tcode);
				do
				{
					valid=1;
					cout<<" Enter the quantity : ";
					cin>>qty;
					if(qty<0||qty>qty1)
					{
						valid=0;
						//gotoxy(1,12);
						//clreol();
					}
				}while(!valid);
				amount=(int)(rate*qty);
				for(i=0;i<96;i++) cout<<"-";
				cout<<" Code\t\tName\t\tCost Price\tQuantity(pcs.)\tTotal(Rs.)\n";
				for(i=0;i<96;i++) cout<<"-";
				cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty<<"\t\t"<<amount<<"\n";
				for(i=0;i<96;i++) cout<<"-";
				qty2=qty;
				cout<<" Are you sure you want to add it to bill ? (y/n) : ";
				ch=getche();
				for(i=0;i<96;i++) cout<<"-";
				for(i=0;i<96;i++) cout<<"-";
				ch=toupper(ch);
				if(ch=='Y')
				{
					int location;
					bought=1;
					fstream bill;
					bill.open("BILL.dat",ios::out|ios::app);
					bill.write((char*)this,sizeof(product));
					bill.close();
					fstream list;
					list.open("PRODUCT.dat",ios::in);
					while(list.read((char*)this,sizeof(product)))
					{
						if(code==tcode)
						{
							qty1=(qty1-qty);
							amount=(qty1*rate);
							break;
						}
					}
					list.close();
					list.open("PRODUCT.dat",ios::out|ios::ate);
					location=(tcode-1)*sizeof(product);
					list.seekp(location);
					list.write((char*)this,sizeof(product));
					list.close();
					product::sort_product();
				}
				else if(ch=='N')
				valid=0;
				else
				break;
			}
		}
		else
		valid=0;
	}
	else
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Product does not exist\n";
		for(i=0;i<96;i++) cout<<"-";
		valid=0;
	}
	cout<<" Do you want to buy anything else (y/n) ? : ";
	ch=getche();
	ch=toupper(ch);
	if(ch=='Y')
	valid=0;
	else
	break;
    }while(!valid);
    if(bought)
    p.product::read_bill();
    return;
}

void product::read_bill()
{
	system("cls");
	fstream bill;
	bill.open("BILL.dat",ios::in);
	bill.seekg(0);
	int found=0;
	float total=0;
	int item=0;
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Code           Name            Rate            Quantity        Total\n";
	for(i=0;i<96;i++) cout<<"-";
	while(bill.read((char*)this,sizeof(product)))
	{
		found=1;
		item=(item+qty2);
		total=(int)(total+amount);
		cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty2<<"\t\t"<<amount<<" Rs.\n";
		for(i=0;i<96;i++) cout<<"-";
	}
	if(!found)
	{
		cout<<"\a First Purchase Something \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Select <1> in the menu to add records \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
	}
	else if(found==1)
	{
		cout<<"\t\t\t\t\t\t"<<item<<"\t\t"<<total<<" Rs.\n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
	}
	getch();
	return;
}

int product::find_bill(int tcode)
{
	fstream bill;
	bill.open("BILL.dat",ios::in);
	bill.seekg(0,ios::beg);
	int found=0;
	while(bill.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			found++;
			break;
		}
	}
	bill.close();
	return found;
}

void product::display_bill(int tcode)
{
	fstream bill;
	bill.open("BILL.dat",ios::in);
	bill.seekg(0,ios::beg);
	while(bill.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Code\t\tName\t\tRate\t\tQuantity\tTotal\n";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty2<<"\t\t"<<amount<<" Rs.\n";
			for(i=0;i<96;i++) cout<<"-";
			break;
		}
	}
	bill.close();
}

void product::search_bill()
{
	system("cls");
	int tcode,found;
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter the product code to be searched in the bill : ";
	cin>>tcode;
	found=find_bill(tcode);
	if(found==0)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Product not found! \n";
		for(i=0;i<96;i++) cout<<"-";
	}
	display_bill(tcode);
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

void product::remove_bill()
{
	system("cls");
	fstream bill;
	bill.open("BILL.dat",ios::in);
	if(!bill)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Bill does not exist \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
	}
	else
	{
		product::read_bill();
		char ch;
		cout<<" Are you sure you want to delete this bill (y/n) ? : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='Y')
		{
			remove("BILL.dat");
			for(i=0;i<96;i++) cout<<"-";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" The specified bill has been deleted \n";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Press any key to continue \n";
			for(i=0;i<96;i++) cout<<"-";
			getch();
		}
		else
		return;
	}
}

void product::delete_bill()
{
	char t_code[5],ch;
	int t,tcode;
	d:
	system("cls");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press <ENTER> to see the bill\t\t       Press <0> to go back to the menu\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter Product code of the product to be deleted : ";
	gets(t_code);
	t=atoi(t_code);
	tcode=t;
	if(t_code[0]=='0')
	return;
	if(tcode==0)
	{
		read_bill();
		goto d;
	}
	if(!find_bill(tcode))
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Record not found \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to go back to menu \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		return;
	}
	display_bill(tcode);
	do
	{
		//gotoxy(1,10);
		//clreol();
		cout<<" Do you want to delete this record (y/n) ? : ";
		ch=getche();
		for(i=0;i<96;i++) cout<<"-";
		ch=toupper(ch);
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	delete_entry(tcode);
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Record Deleted \n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

void product::delete_entry(int tcode)
{
	int qty,location;
	fstream bill;
	bill.open("BILL.dat",ios::in);
	fstream temp;
	temp.open("TEMPORARY.dat",ios::out);
	bill.seekg(0,ios::beg);
	while(!bill.eof())
	{
		bill.read((char*)this,sizeof(product));
		if(bill.eof())
		break;
		if(code!=tcode)
		temp.write((char*)this,sizeof(product));
		else if(code==tcode)
		qty=qty2;
	}
	bill.close();
	temp.close();
	bill.open("BILL.dat",ios::out);
	temp.open("TEMPORARY.dat",ios::in);
	temp.seekg(0,ios::beg);
	while(!temp.eof())
	{
		temp.read((char*)this,sizeof(product));
		if(temp.eof())
		break;
		bill.write((char*)this,sizeof(product));
	}
	bill.close();
	temp.close();
	remove("TEMPORARY.dat");
	fstream list;
	list.open("PRODUCT.dat",ios::in|ios::out);
	while(list.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			qty1=qty1+qty;
			amount=(rate*qty1);
			location=(tcode-1)*sizeof(product);
			list.seekp(location);
			list.write((char*)this,sizeof(product));
			break;
		}
	}
	list.close();
}

void product::modify_bill()
{
	char t_code[5],ch;
	int t,tcode,qty;
	e:
	system("cls");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press <ENTER> to see the bill\t\t\t   Press <0> to go back to menu ";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter Product Code of the product to be modified : ";
	gets(t_code);
	t=atoi(t_code);
	tcode=t;
	if(t_code[0]=='0')
	return;
	if(tcode==0)
	{
		read_bill();
		goto e;
	}
	if(!find_bill(tcode))
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Record not found \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to go back to menu \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		return;
	}
	display_bill(tcode);
	do
	{
		cout<<" Do you want to modify this record (y/n) ? : ";
		ch=getche();
		for(i=0;i<96;i++) cout<<"-";
		ch=toupper(ch);
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	//gotoxy(1,4);  //clreol();
	//gotoxy(1,10); //clreol();
	//gotoxy(1,3);
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter the new amount | Store's current status :- \n";
	int location;
	fstream bill;
	bill.open("BILL.dat",ios::in);
	while(bill.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			qty=qty2;
			qty2=0;
			amount=rate*qty2;
			break;
		}
	}
	bill.close();
	bill.open("BILL.dat",ios::out|ios::ate);
	location=(tcode-1)*sizeof(product);
	bill.seekp(location);
	bill.write((char*)this,sizeof(product));
	bill.close();
	product::sort_bill();
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	while(list.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			qty1=qty1+qty;
			amount=rate*qty1;
			break;
		}
	}
	list.close();
	list.open("PRODUCT.dat",ios::out|ios::ate);
	location=(tcode-1)*sizeof(product);
	list.seekp(location);
	list.write((char*)this,sizeof(product));
	list.close();
	product::sort_product();
	display_product(tcode);
	modify_entry(tcode);
}

void product::modify_entry(int tcode)
{
	int location,recordno,valid=0,qty;
	recordno=product_code(tcode);
	char ch;
	do
	{
		valid=1;
		//gotoxy(1,10);
		//clreol();
		cout<<" Quantity : ";
		cin>>qty;
		if(qty<0||qty>qty1)
		valid=0;
	}
	while(!valid);
	do
	{
		for(i=0;i<96;i++) cout<<"-";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Do you want to save the changes (y/n) ? : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='0')
		return;
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	qty2=qty;
	amount=(rate*qty2);
	for(i=0;i<96;i++) cout<<"-";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Code\t\tName\t\tRate\t\tQuantity\tAmount(Rs.)\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty2<<"\t\t"<<amount<<"\n";
	for(i=0;i<96;i++) cout<<"-";
	fstream bill;
	bill.open("BILL.dat",ios::out|ios::ate);
	location=(recordno-1)*sizeof(product);
	bill.seekp(location);
	bill.write((char*)this,sizeof(product));
	bill.close();
	sort_bill();
	qty1=qty1-qty2;
	amount=rate*qty1;
	fstream list;
	list.open("PRODUCT.dat",ios::out|ios::ate);
	location=(recordno-1)*sizeof(product);
	list.seekp(location);
	list.write((char*)this,sizeof(product));
	bill.close();
	sort_product();
	cout<<" Record modified \n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

void product::sort_bill()
{
	int i=0,j;
	product arr[100];
	product temp;
	fstream bill;
	bill.open("BILL.dat",ios::in);
	bill.seekg(0,ios::beg);
	while(bill.read((char*)&arr[i],sizeof(product)))
	i++;
	int size;
	size=i;
	bill.close();
	for(i=1;i<size;i++)
	for(j=0;j<size-i;j++)
	{
		if(arr[j].code>arr[j+1].code)
		{
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
	}
	bill.open("BILL.dat",ios::out);
	for(i=0;i<size;i++)
	bill.write((char *)&arr[i],sizeof(product));
	bill.close();
}

/*--------------------------------------------------------------------------*/

int product::last_code()
{
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0,ios::beg);
	int t=0;
	while(list.read((char*)this,sizeof(product)))
	t=code;
	list.close();
	return t;
}

void product::read_product()
{
	system("cls");
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0);
	int found=0;
	float t1=0,t2=0;
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Code\t\tName\t\tRate\t\tStock(pcs.)\tTotal Value(Rs.)";
	for(i=0;i<96;i++) cout<<"-";
	while(list.read((char*)this,sizeof(product)))
	{
		found=1;
		cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty1<<"\t\t"<<amount<<"\n";
		for(i=0;i<96;i++) cout<<"-";
		t1=t1+qty1;
		t2=t2+amount;
	}
	if(found)
	{
		cout<<"\t\t\t\t\t\t"<<t1<<"\t\t"<<t2<<"\n";
		for(i=0;i<96;i++) cout<<"-";
	}
	else if(!found)
	{
		cout<<"\a Records not found \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Select <1> in the product menu to add records \n";
		for(i=0;i<96;i++) cout<<"-";
	}
	cout<<" Press any key to continue... \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
	list.close();
}

void product::write_product()
{
	int tcode,valid;
	char ch;
	tcode=last_code();
	tcode++;
	do
	{
		system("cls");
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Enter details for product "<<tcode<<" :- \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Code       : "<<tcode<<endl<<endl;
		do
		{
			valid=1;
			cout<<" Name       : ";
			gets(name);
			strupr(name);
			if((strlen(name)<1)||(strlen(name)>7))
			{
				valid=0;
				//gotoxy(1,6);
				//clreol();
			}
		}while(!valid);
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Rate       : ";
			cin>>rate;
			if(rate<1||rate>25000)
			{
				valid=0;
				//gotoxy(1,8);
				//clreol();
			}
		}while(!valid);
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Stock      : ";
			cin>>qty1;
			if(qty1<0||qty1>10000)
			{
				valid=0;
				//gotoxy(1,10);
				//clreol();
			}
		}while(!valid);
		do
		{
			//gotoxy(1,12);//clreol();
			//gotoxy(1,11);
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Do you want to save this record (y/n) ? : ";
			ch=getche();
			ch=toupper(ch);
		}while(ch!='N'&&ch!='Y');
		if(ch=='Y')
		{
			code=tcode;
			amount=(qty1*rate);
			fstream list;
			list.open("PRODUCT.dat",ios::out|ios::app);
			list.write((char*)this,sizeof(product));
			list.close();
			tcode++;
		}
		do
		{
			//gotoxy(1,14);//clreol();
			//gotoxy(1,13);
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Do you want to add more records (y/n) ? : \n";
			for(i=0;i<96;i++) cout<<"-";
			//gotoxy(44,14);
			ch=getche();
			ch=toupper(ch);
		}while(ch!='N'&&ch!='Y');
	}while(ch=='Y');
}

void product::delete_product()
{
	char t_code[5],ch;
	int t,tcode;
	y:
	system("cls");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press <ENTER> to see the list\t\t       Press <0> to go back to the menu\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter Product Code of the product to be deleted : " ;
	gets(t_code);
	t=atoi(t_code);
	tcode=t;
	if(t_code[0]=='0')
	return;
	if(tcode==0)
	{
		read_product();
		goto y;
	}
	if(!product_code(tcode))
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Record not found \n" ;
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to go back to menu \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		return;
	}
	display_product(tcode);
	do
	{
		//gotoxy(1,10);
		//clreol();
		cout<<" Do you want to delete this record (y/n) : ";
		ch=getche();
		for(i=0;i<96;i++) cout<<"-";
		ch=toupper(ch);
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	fstream temp;
	temp.open("TEMPORARY.dat",ios::out);
	list.seekg(0,ios::beg);
	while(!list.eof())
	{
		list.read((char*)this,sizeof(product));
		if(list.eof())
		break;
		if(code!=tcode)
		temp.write((char*)this,sizeof(product));
	}
	list.close();
	temp.close();
	remove("PRODUCT.dat");
	rename("TEMPORARY.dat","PRODUCT.dat");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Record Deleted \n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

void product::display_product(int tcode)
{
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0,ios::beg);
	while (list.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Code\t\tName\t\tSell Price\tStock(pcs.)\tTotal Value(Rs.)";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty1<<"\t\t"<<amount<<"\n";
			for(i=0;i<96;i++) cout<<"-";
			break;
		}
	}
	list.close();
}

void product::modify_product()
{
	char t_code[5],ch;
	int t,tcode;
	w:
	system("cls");
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press <ENTER> to see the list\t\t\t   Press <0> to go back to menu\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter Product Code of the item to be Modified : ";
	gets(t_code);
	t=atoi(t_code);
	tcode=t;
	if(t_code[0]=='0')
	return ;
	if(tcode==0)
	{
		read_product();
		goto w;
	}
	if(!product_code(tcode))
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Record not found \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to back to menu \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		return;
	}
	display_product(tcode);
	do
	{
		cout<<" Do you want to Modify this record (y/n) : ";
		ch=getche();
		cout<<"\n--------------------------------------------------------------------------------";
		ch=toupper(ch);
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	int valid=0;
	cout<<" Code     : ";
	cout<<endl<<endl;
	cout<<" Name     : ";
	cout<<endl<<endl;
	cout<<" Rate     : ";
	cout<<endl<<endl;
	cout<<" Stock    : ";
	int C,Q;
	char N[10];
	float R;
	C=code;
	strcpy(N,name);
	R=rate;
	Q=qty1;
	do
	{
		//gotoxy(13,12);
		//clreol();
		cout<<"Change (y/n) : ";
		ch=getche() ;
		ch=toupper(ch) ;
		if(ch=='0')
		return;
	}while(ch!='N'&&ch!='Y');
	while(ch=='Y'&&!valid)
	{
		valid=1;
		//gotoxy(1,12);
		//clreol();
		cout<<" Code     : ";
		cin>>C;
		if(C<=0||C>=51)
		{
			valid=0;
			//gotoxy(1,4);
			//clreol();
		}
		if(search_code(C))
		{
			valid=0;
			//gotoxy(1,4);
			//clreol();
		}
	}
	do
	{
		//gotoxy(13,14);
		//clreol() ;
		cout<<"Change (y/n) : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='0')
		return;
	}while(ch!='N'&&ch!='Y');
	valid=0;
	while(ch=='Y'&&!valid)
	{
		valid=1;
		//gotoxy(1,14);
		//clreol();
		cout<<" Name     : ";
		gets(N);
		strupr(N);
		if((strlen(N)<1)||(strlen(N)>7))
		valid=0;
	}
	do
	{
		//gotoxy(13,16);
		//clreol();
		cout<<"Change (y/n) : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='0')
		return;
	}while(ch!='N'&&ch!='Y');
	valid=0;
	while(ch=='Y'&&!valid)
	{
		valid=1;
		//gotoxy(1,16);
		//clreol();
		cout<<" Rate     : ";
		cin>>R;
		if(R<1||R>25000)
		valid=0;
	}
	do
	{
		//gotoxy(13,18);
		//clreol();
		cout<<"Change (y/n) : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='0')
		return;
	}while(ch!='N'&&ch!='Y');
	valid=0;
	while(ch=='Y'&&!valid)
	{
		valid=1;
		//gotoxy(1,18);
		//clreol();
		cout<<" Stock    : ";
		cin>>Q;
		if(Q<0||Q>10000)
		valid=0;
	}
	do
	{
		for(i=0;i<96;i++) cout<<"-";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Do you want to save the changes (y/n) : ";
		ch=getche() ;
		ch=toupper(ch);
		if(ch=='0')
		return ;
	}while(ch!='N'&&ch!='Y');
	if(ch=='N')
	return;
	fstream list,temp;
	list.open("PRODUCT.dat",ios::in);
	temp.open("TEMPORARY.dat",ios::out);
	list.seekg(0,ios::beg);
	while(!list.eof())
	{
		list.read((char*)this,sizeof(product));
		if(list.eof())
		break;
		if(code!=tcode)
		temp.write((char*)this,sizeof(product));
	}
	list.close();
	temp.close();
	remove("PRODUCT.dat");
	rename("TEMPORARY.dat","PRODUCT.dat");
	code=C;
	strcpy(name,N);
	rate=R;
	qty1=Q;
	amount=(rate*qty1);
	list.open("PRODUCT.dat",ios::out|ios::app);
	list.write((char*)this,sizeof(product));
	sort_product();
	for(i=0;i<96;i++) cout<<"-";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Code\t\tName\t\tRate\t\tStock(pcs.)\tTotal value(Rs.)";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" "<<code<<"\t\t"<<name<<"\t\t"<<rate<<"/-\t\t"<<qty1<<"\t\t"<<amount<<"\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Record Modified \n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

int product::product_code(int tcode)
{
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0,ios::beg);
	int found=0;
	while(list.read((char*)this,sizeof(product)))
	{
		found++;
		if(code==tcode)
		break;
	}
	list.close();
	return found;
}

int product::search_code(int tcode)
{
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0,ios::beg);
	int found=0;
	while(list.read((char*)this,sizeof(product)))
	{
		if(code==tcode)
		{
			found++;
			break;
		}
	}
	list.close();
	return found;
}

void product::sort_product()
{
	int i=0,j;
	product arr[100];
	product temp;
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	list.seekg(0,ios::beg);
	while(list.read((char*)&arr[i],sizeof(product)))
	i++;
	int size;
	size=i;
	list.close();
	for(i=1;i<size;i++)
	for(j=0;j<size-i;j++)
	{
		if(arr[j].code>arr[j+1].code)
		{
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
	}
	list.open("PRODUCT.dat",ios::out);
	for(i=0;i<size;i++)
	list.write((char *)&arr[i],sizeof(product));
	list.close();
}

void product::search_product()
{
	system("cls");
	int tcode,found;
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Enter the product code which is to be searched in the list : ";
	cin>>tcode;
	found=search_code(tcode);
	if(found==0)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\a Product not found \n";
	}
	display_product(tcode);
	for(i=0;i<96;i++) cout<<"-";
	cout<<" Press any key to go back to menu \n";
	for(i=0;i<96;i++) cout<<"-";
	getch();
}

void product::remove_list()
{
	system("cls");
	fstream list;
	list.open("PRODUCT.dat",ios::in);
	if(!list)
	{
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Product list does not exist \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
	}
	else
	{
		product::read_product();
		char ch;
		cout<<" Are you sure you want to delete this product list (y/n) ? : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='Y')
		{
			remove("PRODUCT.dat");
			remove("BILL.dat");
			for(i=0;i<96;i++) cout<<"-";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" The specified product list has been deleted \n";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Press any key to continue \n";
			for(i=0;i<96;i++) cout<<"-";
			getch();
		}
		else
		return;
	}
}

void product::insert_product()
{
	int tcode,valid;
	char ch;
	do
	{
		system("cls");
		for(i=0;i<96;i++) cout<<"-";
		cout<<" Enter details for product which you want to insert :- \n";
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Code       : ";
			cin>>code;
			tcode=code;
			if(code<=0||code>=51)
			{
				valid=0;
				//gotoxy(1,4);
				//clreol();
			}
			if(search_code(code))
			{
				valid=0;
				//gotoxy(1,4);
				//clreol();
				cout<<" Code       : Code already given";
				getch();
				//gotoxy(1,4);
				//clreol();
			}
			code=tcode;
		}while(!valid);
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Name       : ";
			gets(name);
			strupr(name);
			if((strlen(name)<1)||(strlen(name)>7))
			{
				valid=0;
				//gotoxy(1,6);
				//clreol();
			}
		}while(!valid);
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Rate       : ";
			cin>>rate;
			if(rate<1||rate>25000)
			{
				valid=0;
				//gotoxy(1,8);
				//clreol();
			}
		}while(!valid);
		for(i=0;i<96;i++) cout<<"-";
		do
		{
			valid=1;
			cout<<" Stock      : ";
			cin>>qty1;
			if(qty1<0||qty1>10000)
			{
				valid=0;
				//gotoxy(1,10);
				//clreol();
			}
		}while(!valid);
		do
		{
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Do you want to insert this record (y/n) ? : ";
			ch=getche();
			ch=toupper(ch);
		}while(ch!='N'&&ch!='Y');
		if(ch=='Y')
		{
			amount=(qty1*rate);
			fstream list;
			list.open("PRODUCT.dat",ios::out|ios::app);
			list.write((char*)this,sizeof(product));
			list.close();
			sort_product();
		}
		do
		{
			for(i=0;i<96;i++) cout<<"-";
			for(i=0;i<96;i++) cout<<"-";
			cout<<" Do you want to insert more records (y/n) ? : \n";
			for(i=0;i<96;i++) cout<<"-";
			//gotoxy(47,14);
			ch=getche();
			ch=toupper(ch);
		}while(ch!='N'&&ch!='Y');
	}while(ch=='Y');
}

/*--------------------------------------------------------------------------*/

void intro()
{
	cout<<"\n\n\n\n\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t\t     JAWAHARLAL NEHRU SCHOOL\n\n";
	cout<<"\t\t\t         SESSION 2012-13\n\n";
	cout<<"\t\t\t         CLASS - XII 'B'\n\n";
	cout<<"\t\t\t    ACHLENDRA RAJ - KUNAL DAS\n\n";
	cout<<"\t\t\t  C++ PROJECT - SALES ANNOUNCES\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t\t    Press any key to continue \n";
	for(i=0;i<96;i++) cout<<"-";
	//gotoxy(54,17);
	getch();
}

int password()
{
	system("cls");
	char pass[4];
	int  check;
	cout<<"\n\n\n\n\n\n\n\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t\t Enter password = ";
	pass[0]=getche();
	//gotoxy(43,10);cout<<"*";
	pass[1]=getche();
	//gotoxy(44,10);cout<<"*";
	pass[2]=getche();
	//gotoxy(45,10);cout<<"*";
	pass[3]=getche();
	//gotoxy(46,10);cout<<"*";
	for(int i=0;i<4;i++)
	{
		if(pass[i]!='0')
		check=0;
		else
		check=1;
	}
	if(check!=1)
	{
		for(i=0;i<96;i++) cout<<"-";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t Invalid password ! \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t Press any key to go back to main menu \n";
		for(i=0;i<96;i++) cout<<"-";
		//gotoxy(63,14);
		getch();
	}
	return check;
}

void bill_menu()
{
	c:
	char ch;
	system("cls");
	cout<<endl;
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t    BILL MENU\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\n";
	cout<<"\t\t\t 1. Display the bill	       \n\n";
	cout<<"\n\n";
	cout<<"\t\t\t 2. Search an entry in the bill \n\n";
	cout<<"\t\t\t 3. Modify an entry in the bill   \n\n";
	cout<<"\t\t\t 4. Delete an entry from the bill \n\n";
	cout<<"\t\t\t 5. Sort the bill \n\n";
	cout<<"\n\n";
	cout<<"\t\t\t 6. Delete bill		       \n\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" <BACKSPACE> Go Back \t Select = \t\t\t\t       Exit <0>\n";
	for(i=0;i<96;i++) cout<<"-";
	//gotoxy(35,23);
	ch=getche();

	if(ch=='1')//*********************************************************
	{
		product p;
		p.product::read_bill();
		goto c;
	}

	if(ch=='2')//*********************************************************
	{
		product p;
		p.product::search_bill();
		goto c;
	}

	if(ch=='3')//*********************************************************
	{
		product p;
		p.product::modify_bill();
		goto c;
	}

	if(ch=='4')//*********************************************************
	{
		product p;
		p.product::delete_bill();
		goto c;
	}

	if(ch=='5')//*********************************************************
	{
		product p;
		system("cls");
		p.product::read_bill();
		cout<<" Do you want to sort this bill ? : ";
		ch=getche();
		ch=toupper(ch);
		if(ch=='Y')
		{
			p.product::sort_bill();
			system("cls");
			p.product::read_bill();
		}
		goto c;
	}

	if(ch=='6')//*********************************************************
	{
		product p;
		p.product::remove_bill();
		goto c;
	}

	if(ch=='\b')//*********************************************************
	return;

	if(ch=='0')//*********************************************************
	exit(0);

	else       //*********************************************************
	{
		system("cls");
		cout<<"\a\n\n\n\n\n\n\n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Please select from 1 to 0 \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		goto c;
	}
}

void product_menu()
{
	b:
	char ch;
	system("cls");
	cout<<endl;
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t PRODUCT MENU\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\n";
	cout<<"\t\t\t 1. Add a Product in the List      \n\n";
	cout<<"\t\t\t 2. Display the Product List       \n\n";
	cout<<"\n";
	cout<<"\t\t\t 3. Insert a Product in th List    \n\n";
	cout<<"\t\t\t 4. Search a Product in the List   \n\n";
	cout<<"\t\t\t 5. Modify a Product in the List   \n\n";
	cout<<"\t\t\t 6. Delete a Product from the list \n\n";
	cout<<"\n";
	cout<<"\t\t\t 7. Delete product list		\n\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<" <BACKSPACE> Go Back\t Select = \t\t\t\t       Exit <0>\n";
	for(i=0;i<96;i++) cout<<"-";
	//gotoxy(35,23);
	ch=getche();

	if(ch=='1')//*********************************************************
	{
		product p;
		p.product::write_product();
		goto b;
	}

	if(ch=='2')//*********************************************************
	{
		product p;
		p.product::read_product();
		goto b;
	}

	if(ch=='3')//*********************************************************
	{
		product p;
		p.product::insert_product();
		goto b;
	}
	if(ch=='4')//*********************************************************
	{
		product p;
		p.product::search_product();
		goto b;
	}

	if(ch=='5')//*********************************************************
	{
		product p;
		p.product::modify_product();
		goto b;
	}

	if(ch=='6')//*********************************************************
	{
		product p;
		p.product::delete_product();
		goto b;
	}

	if(ch=='7')//*********************************************************
	{
		product p;
		p.product::remove_list();
		goto b;
	}

	if(ch=='\b')//*********************************************************
	return;

	if(ch=='0')//*********************************************************
	exit(0);

	else       //*********************************************************
	{
		system("cls");
		cout<<"\a\n\n\n\n\n\n\n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Please select from 1 to 0 \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		goto b;
	}
}

int main()
{
	system("cls");
	//intro();
	a:
	system("cls");
	int check;
	char ch;
	cout<<endl;
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t    MAIN MENU\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\n";
	cout<<"\t\t\t 1. Purchase Products      \n\n";
	cout<<"\n\n";
	cout<<"\t\t\t 2. Display Bill           \n\n";
	cout<<"\t\t\t 3. Display Product List   \n\n";
	cout<<"\t\t\t 4. Display the Sales Made	\n\n";
	cout<<"\n\n";
	cout<<"\t\t\t 5. Products menu          \n\n";
	cout<<"\t\t\t 6. Edit bill menu         \n\n";
	for(i=0;i<96;i++) cout<<"-";
	cout<<"\t\t\t Select = \t\t\t\t       Exit <0>\n";
	for(i=0;i<96;i++) cout<<"-";
	//gotoxy(35,23);
	ch=getche();

	if(ch=='1')/*********************************************************/
	{
		product p;
		p.product::write_bill();
		goto a;
	}

	if(ch=='2')/*********************************************************/
	{
		product p;
		p.product::read_bill();
		goto a;
	}

	if(ch=='3')/*********************************************************/
	{
		product p;
		p.product::read_product();
		goto a;
	}

	if(ch=='4')/*********************************************************/
	{
		product p;
		p.product::sales();
		goto a;
	}

	if(ch=='5')/*********************************************************/
	{
		//check=password();
		//if(check==1)
		product_menu();
		//else
		//goto a;
		goto a;
	}

	if(ch=='6')/*********************************************************/
	{
		//check=password();
		//if(check==1)
		bill_menu();
		//else
		//goto a;
		goto a;
	}

	if(ch=='0')/*********************************************************/
	exit(0);

	else       /*********************************************************/
	{
		system("cls");
		cout<<"\a\n\n\n\n\n\n\n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Please select from 1 to 0 \n";
		for(i=0;i<96;i++) cout<<"-";
		cout<<"\t\t\t    Press any key to continue \n";
		for(i=0;i<96;i++) cout<<"-";
		getch();
		goto a;
	}

	return 1;
}
