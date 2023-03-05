#pragma once
class Book
{
	char isbn[14];
	char name[30];
	char author[20];
	int num;
public:
	Book();
	void create_book();
	bool search_book();
	bool search_book(char* ISBN);
	bool search_book(char* ISBN,int* cnt);
	void modify_book();
	void delete_book();
	void display();
	void display_all();
	void num_reduce();
	void num_plus();
	int retnum();
};

