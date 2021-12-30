#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

int choice = 0;
int n = 1000, k = 0;


struct product_info
{
    int id = 0;
    string name = " ";
    int price = 0;
    int count = 0;
}*products;

int menu();
void load();
void show_list();
void add_product();
void edit_product();
void erase_product();
void search_product();
bool search_product(int id, int &index);
void purchase_product();
void add_to_file(product_info );
void buy();
void write_to_file();

int main()
{
	products = new product_info[n];
	load();
    while (choice != 8 )
    {
        menu();
        switch (choice)
        {
        case 1:
        	add_product();
            break;
        case 2:
        	edit_product();
            break;
        case 3:
        	erase_product();
            break;
        case 4:
        	search_product();
            break;
        case 5:
        	buy();
            break;
        case 6:
            break;
        case 7:
        	show_list();
        	getch();
        	system("cls");
            break;
        case 8:
            break;
        }
    }
    return 0;
}



int menu()
{
	system("cls");
    cout << "\n\t\t\t\t**STORE MENU**\n1-Add Product\n2-Edit Product\n3-Delete Product\n4-Search\n5-Buy\n6-Sort\n7-Show\n8-Exit\n";
    cout << "\nEnter your choise : ";
	cin >> choice;
    return choice;
}


void load()
{

    string line;
    ifstream products_file;
    products_file.open("products.txt", ios::in);
    k = 0;
    while (getline(products_file,line))
    {
    	line += ',';
//    	cout << line << "\n";
        string array[4];
        int j = 0;
		string t;
        for (int i=0; i<line.size(); i++)
        {
            if ( line[i] != ',')
            {
            	array [j] = array [j] + line [i];
			}      
            else
            {
                switch(j)
                {
	                case 0:
	                    products[k].id = stoi(array[j]);
	                    break;
	                case 1:
	                    products[k].name = array[j];
	                    break;
	                case 2:
	                    products[k].price = stoi(array[j]);
	                    break;
	                case 3:
	                    products[k].count = stoi(array[j]);
	                    break;
                }
                j++;
            }
        }
      k++;  
	}
}

void show_list()
{

    cout <<  "\nLIST:\n";
    for (int i = 0; i < k ; i++)
	{
		cout << "\nProduct " << i+1;
        cout << "\n\t id:" << products[i].id;
        cout << "\n\t name:" << products[i].name;
        cout << "\n\t price:" << products[i].price;
        cout << "\n\t count:" << products[i].count;
	}
	cout << "\n\n";
        
}

void add_product()
{
	
	system("cls");
	product_info p;
	cout << "Enter product id : ";
	cin >> p.id;
	cout << "Enter product name : ";
	getline(cin, p.name);
	getline(cin, p.name);
	cout << "Enter product price : ";
	cin >> p.price;
	cout << "Enter product count : ";
	cin >>p.count;
	add_to_file(p);
	getch();
}

void add_to_file(product_info p)
{
	ofstream w;
	w.open("products.txt", ios::app);
	w << "\n" << p.id << "," << p.name << "," << p.price << "," << p.count;
	w.close();
	cout << "Product added successfully ... \n";
	load();
	return;
}

void edit_product()
{
	system("cls");
	int ID;
	cout << "\nEnter product id to edit : ";
	cin >> ID;
	
	bool find = false;
	for(int i = 0; i < k; i++)
	{
		if(products[i].id == ID)
		{
			find = true;
			cout << "\n\tEnter new name : ";
			getline(cin, products[i].name);
			getline(cin, products[i].name);
			cout << "\n\tEnter new price : ";
			cin >> products[i].price;
			cout << "\n\tEtner new count : ";
			cin >> products[i].count;
			break;
		}
	}
	if(!find)
	{
		cout << "\nProduct not found !!\n";
	}
	else
	{
		write_to_file();
		load();
		cout << "Product edited successfully ..\n";
	}
	getch();
	return;
}

void write_to_file()
{
	ofstream w;
	w.open("products.txt", ios::out);
	for(int i = 0; i < k; i++)
	{
		w << products[i].id << "," << products[i].name << "," << products[i].price << "," << products[i].count << '\n';
	}
	w.close();
}

void erase_product()
{
	system("cls");
	int ID;
	cout << "\nEnter product id to erase: ";
	cin >> ID;
	
	ofstream w;
	w.open("products.txt", ios::out);

	bool find = false;
	for(int i = 0; i < k; i++)
	{
		if(products[i].id == ID)
		{
			find = true;
		}
		else
		{
			w << products[i].id << "," << products[i].name << "," << products[i].price << "," << products[i].count << '\n';
		}
	}
	w.close();
	load();
	if(!find)
	{
		cout << "\nProduct not found !!\n";
	}
	else
	{	
		cout << "Product deleted successfully ..\n";
	}
	getch();
	return;
}
void search_product()
{
	system("cls");
	int ID;
	cout << "\nEnter product id to search: ";
	cin >> ID;
	cout << "\n";
	bool find = false;
	for(int i = 0; i < k; i++)
	{
		if(products[i].id == ID)
		{
			find = true;
			cout << "Product found ...\n";
			cout << "\n\t id:" << products[i].id;
		    cout << "\n\t name:" << products[i].name;
		    cout << "\n\t price:" << products[i].price;
		    cout << "\n\t count:" << products[i].count;
			cout << "\n\n";
		}
	}
	if(!find)
	{
		cout << "\nProduct not found !!\n";
	}
	getch();
	return;
}
bool search_product(int ID, int &index)
{
	for(int i = 0; i < k; i++)
		if(products[i].id == ID)
		{
			index = i;
			return true;
		}
			
		
	return false;
}


void buy()
{
	system("cls");
	int wannaBuy = 1;
	cout << "\n";
	product_info purcahses[100];
	int idx = 0;
	do
	{
		int ID;
		cout << "\nEnter product id to buy: ";
		cin >> ID;
		int index = -1;
		if(!search_product(ID, index))
		{
			cout << "Product not found !!\n";
		}
		else
		{
			cout << "Enter number to buy : ";
			int num;
			cin >> num;
			if(products[index].count < num)
			{
				cout << "Balance is not enoght !!\n";
			}
			else
			{
				products[index].count -= num;
				purcahses[idx] = products[index];
				purcahses[idx++].count = num;
				cout << "Purchase done successfully ..\n";	
			}
		}
		cout << "\nWanna continue ? [1/0] : ";
		cin >> wannaBuy;
	}while(wannaBuy);
	write_to_file();
	load();
	ofstream save;
	save.open("buys.txt", ios::app);
	int total_price = 0;
	for(int i = 0; i < idx; i++){
		save << "\n" << purcahses[i].id << "," << purcahses[i].name << "," << purcahses[i].price << "," << purcahses[i].count << "," << purcahses[i].count * purcahses[i].price;
		total_price += purcahses[i].count * purcahses[i].price;
	}
	save << "\nTotal Price = " << total_price << "\n";
	cout << "Factors saved in file \n";	
	save.close();	
	getch();
}
