//HEADER FILES USED
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>

    // CLASS USED IN PROJECT

    class product
    {
	int pno;
	char name[50];
	float price, qty, tax, dis;
	public:
	    void create_product()
	    {
		cout << "\nPlease Enter The Product No. of The Product ";
		cin >> pno;
		cout << "\n\nPlease Enter The Name of The Product ";
		gets(name);
		cout << "\nPlease Enter The Price of The Product ";
		cin >> price;
		cout << "\nPlease Enter The Discount (%) ";
		cin >> dis;
	    }

	void show_product()
	{
	    cout << "\nThe Product No. of The Product : " << pno;
	    cout << "\nThe Name of The Product : ";
	    puts(name);
	    cout << "\nThe Price of The Product : " << price;
	    cout << "\nDiscount : " << dis;
	}

	int retpno()
	{
	    return pno;
	}

	float retprice()
	{
	    return price;
	}

	char * retname()
	{
	    return name;
	}

	int retdis()
	{
	    return dis;
	}

    }; //class ends here

// global declaration for stream object, object

fstream fp;
product pr;
// writing function

void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
    getch();
}
// reading function
void display_all()
{
    clrscr();
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product)))
    {
	pr.show_product();
	cout << "\n\n====================================\n";
	getch();
    }
    fp.close();
    getch();
}
//modification function
void modify_product()
{
    int no, found = 0;
    clrscr();
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0)
    {
	if (pr.retpno() == no)
	{
	    pr.show_product();
	    cout << "\nPlease Enter The New Details of Product" << endl;
	    pr.create_product();
	    int pos = -1 * sizeof(pr);
	    fp.seekp(pos, ios::cur);
	    fp.write((char * ) & pr, sizeof(product));
	    cout << "\n\n\t Record Updated";
	    found = 1;
	}
    }
    fp.close();
    if (found == 0)
	cout << "\n\n Record Not Found ";
    getch();
}
// deletion function
void delete_product()
{
    int no;
    clrscr();
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product)))
    {
	if (pr.retpno() != no)
	{
	    fp2.write((char * ) & pr, sizeof(product));
	}
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}

void menu()
{
    clrscr();
    fp.open("Shop.dat", ios:: in );
    if (!fp)
    {
	cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create file";

	cout << "\n\n\n Program is closing ....";
	getch();
	exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product)))
    {
	cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
}

// function to place order and generating bill for Products

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
	cout << "\n\nEnter The Product No. Of The Product : ";
	cin >> order_arr[c];
	cout << "\nQuantity in number : ";
	cin >> quan[c];
	c++;
	cout << "\nDo You Want To Order Another Product ? (y/n)";
	cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";
    getch();
    clrscr();
    cout << "\n\n                      BILL                 \n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount ";
    for (int i= 0; i<= c; i++)
    {
	fp.open("Shop.dat", ios:: in );
	fp.read((char * ) & pr, sizeof(product));
	while (!fp.eof())
	{
	    if (pr.retpno() == order_arr[i])
	    {
		amt = pr.retprice() * quan[i];
		damt = amt - (amt * pr.retdis() / 100);
		cout << "\n" << order_arr[i] << "\t" << pr.retname() <<
		    "\t" << quan[i] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
		total += damt;
	    }
	    fp.read((char * ) & pr, sizeof(product));
	}

	fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    getch();
}

// ADMINSTRATOR MENU FUNCTION
void admin_menu()
{
    clrscr();
    char ch2;
    cout << "\n\n\n\tADMIN MENU";
    cout << "\n\n\t1.CREATE PRODUCT";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.MODIFY PRODUCT";
    cout << "\n\n\t4.DELETE PRODUCT";
    cout << "\n\n\t5.VIEW PRODUCT MENU";
    cout << "\n\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) ";
    ch2 = getche();
    switch (ch2)
    {
    case '1':
	clrscr();
	write_product();
	break;
    case '2':
	display_all();
	break;
    case '3':
	modify_product();
	break;
    case '4':
	delete_product();
	break;
    case '5':
	menu();
	getch();
    case '6':
	break;
    default:
	cout << "\a";
	admin_menu();
    }
}
// THE MAIN FUNCTION OF PROGRAM
void main()
{
    clrscr();
    char ch;
    do
    {
	clrscr();
	char pwd[20];
	cout << "\n\n\n\tMAIN MENU";
	cout << "\n\n\t01. CUSTOMER";
	cout << "\n\n\t02. ADMINISTRATOR";
	cout << "\n\n\t03. EXIT";
	cout << "\n\n\tPlease Select Your Option (1-3) ";
	ch = getche();
	switch (ch)
	{
	case '1':
	    clrscr();
	    place_order();
	    getch();
	    break;
	case '2':
	   cout<<"\nPLEASE ENTER YOUR PASSWORD";
	    gets(pwd);
	    if(strcmp(pwd,"abcd")==0)
	  {
	    admin_menu();
	  }

      
	  break;
	case '3':
	    exit(0);
	default:
	    cout << "\a";
	}
    } while (ch != '3');


getch();
}

// END OF PROJECT
