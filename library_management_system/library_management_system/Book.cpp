#include "Book.h"
#include<iostream>
#include<fstream>
using namespace std;

Book::Book()
{
	num = 0;
}

void Book::create_book()
{
	cout << "input book name:";
	cin >> name;
	cout << "input book isbn:";
	cin >> isbn;
	while (search_book(isbn))
	{
		cout << "the book already added,input isbn again:" << endl;
		cin >> isbn;
	}
	cout << "input book author:";
	cin >> author;
	cout << "input book num:";
	cin >> num;
	getchar();
	fstream fbook;
	fbook.open("book.dat", ios::out | ios::app | ios::binary);//write and append data
	fbook.write((char*)this, sizeof(Book));
	fbook.close();
}

bool Book::search_book()
{
	fstream fbook;
	Book book;
	char ISBN[14];
	cout << "input isbn you want to search:";
	cin >> ISBN;
	fbook.open("book.dat", ios::in | ios::binary);
	while (fbook.read((char*)&book, sizeof(Book)))
	{
		if (_strcmpi(book.isbn, ISBN) == 0)
		{
			book.display();
			fbook.close();
			return true;
		}
	}
	fbook.close();
	return false;
}

bool Book::search_book(char* ISBN)
{
	fstream fbook;
	Book book;
	fbook.open("book.dat", ios::in | ios::binary);
	while (fbook.read((char*)&book, sizeof(Book)))
	{
		if (_strcmpi(book.isbn, ISBN) == 0)
		{
			book.display();
			fbook.close();
			return true;
		}
	}
	fbook.close();
	return false;
}

bool Book::search_book(char* ISBN, int* cnt)
{
	fstream fbook;
	Book book;
	fbook.open("book.dat", ios::in | ios::binary);
	while (fbook.read((char*)&book, sizeof(Book)))
	{
		(*cnt)++;
		if (_strcmpi(book.isbn, ISBN) == 0)
		{
			//book.display();
			fbook.close();
			return true;
		}
	}
	fbook.close();
	return false;
}

void Book::modify_book()
{
	fstream fbook;
	Book book;
	char p[14];
	int cnt = 0;
	cout << "input isbn of book you want to modify:";
	cin >> p;
	while (!search_book(p, &cnt))
	{
		cout << "not found the isbn,input again:";
		cin >> p;
	}
	//search_book(p, &cnt);
	cout << "input you want to modify"<<endl;
	cout << "input isbn:";
	cin >> book.isbn;
	while (search_book(book.isbn))
	{
		if (_strcmpi(p, book.isbn) == 0)
		{
			break;
		}
		cout << "the isbn already exsits,input isbn again:";
		cin >> book.isbn;
	}
	cout << "input book name:";
	cin >> book.name;
	cout << "input author name:";
	cin >> book.author;
	cout << "input num of book:";
	cin >> book.num;
	fbook.open("book.dat", ios::out | ios::binary|ios::in);
	fbook.seekp(sizeof(Book) * (cnt-1));
	fbook.write((char*)&book, sizeof(Book));
	fbook.close();
}

void Book::delete_book()
{
	fstream fbook,fp;
	Book book;
	char p[14];
	int cnt = 0;
	cout << "input isbn of book you want to delete:";
	cin >> p;
	while (!search_book(p, &cnt))
	{
		cout << "not found the isbn,input again:";
		cin >> p;
	}
	fbook.open("book.dat", ios::out | ios::binary | ios::in);
	fp.open("temp.dat", ios::out | ios::binary | ios::app);
	while (fbook.read((char*)&book, sizeof(Book)))
	{
		if (_strcmpi(book.isbn, p) != 0)
		{
			fp.write((char*)&book, sizeof(Book));
		}
	}
	fbook.close();
	fp.close();
	remove("book.dat");
	rename("temp.dat", "book.dat");
}

void Book::display()
{
	cout << "isbn:" << isbn << "    ";
	cout << "name:" << name << "    ";
	cout << "author:" << author << "    ";
	cout << "num:" << num << endl;
}

void Book::display_all()
{
	Book book;
	fstream fbook;
	fbook.open("book.dat", ios::in | ios::binary);
	while (fbook.read((char*)&book, sizeof(Book)))
	{
		book.display();
	}
	cout << endl;
	fbook.close();
}

void Book::num_reduce()
{
	num--;
}

void Book::num_plus()
{
	num++;
}

int Book::retnum()
{
	return num;
}


