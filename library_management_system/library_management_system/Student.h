#pragma once
#include<iostream>
using namespace std;
class Student
{
	char no[6];
	char name[20];
	char isbn1[14];
	char isbn2[14];
	char isbn3[14];
	char isbn4[14];
	char isbn5[14];
	int num;
public:
	Student();
	void ceate_student();
	void delete_student();
	void modify_student();
	bool search_student(char* ID = NULL,int* cnt = 0);
	void display();
	void display_all();
	void num_plus();
	void num_reduce();
	void add_isbn(char* p,int num);
	int retnum();
	void modify_isbn(char* p,int num);
};

