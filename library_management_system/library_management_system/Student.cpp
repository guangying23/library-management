#include "Student.h"
#include<fstream>
#include<iostream>
using namespace std;

Student::Student()
{
	num = 0;
	name[0] = '\0';
	no[0] = '\0';
	//char p[14] = "\0";
	isbn1[0] = '\0';
	isbn2[0] = '\0';
	isbn3[0] = '\0';
	isbn4[0] = '\0';
	isbn5[0] = '\0';
}

void Student::ceate_student()
{
	cout << "input student number:";
	cin >> no;
	while (search_student(no))
	{
		cout << "the student already added,input id again:" << endl;
		cin >> no;
	}
	cout << "input student name:";
	cin >> name;
	getchar();
	fstream fstudent;
	fstudent.open("student.dat", ios::out | ios::app | ios::binary);//write and append data
	fstudent.write((char*)this, sizeof(Student));
	fstudent.close();
}

void Student::delete_student()
{
	fstream fstudent, fp;
	Student student;
	char p[6];
	int cnt = 0;
	cout << "input id of student you want to delete:";
	cin >> p;
	while (!search_student(p, &cnt))
	{
		cout << "not found the id,input again:";
		cin >> p;
	}
	fstudent.open("student.dat", ios::out | ios::binary | ios::in);
	fp.open("temp.dat", ios::out | ios::binary | ios::app);
	while (fstudent.read((char*)&student, sizeof(Student)))
	{
		if (_strcmpi(student.no, p) != 0)
		{
			fp.write((char*)&student, sizeof(Student));
		}
	}
	fstudent.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat", "student.dat");
}

void Student::modify_student()
{
	fstream fstudent;
	Student student;
	char p[6];
	int cnt = 0;
	cout << "input id of student you want to modify:";
	cin >> p;
	while (!search_student(p, &cnt))
	{
		cout << "not found the isbn,input again:";
		cin >> p;
	}
	int t = cnt;
	cout << "input you want to modify" << endl;
	cout << "input id:";
	cin >> student.no;
	while (search_student(student.no))
	{
		if (_strcmpi(p, student.no) == 0)
		{
			break;
		}
		cout << "the id already exsits,input id again:";
		cin >> student.no;
	}
	cout << "input student name:";
	cin >> student.name;
	cout << "input num of book student borrowed:";
	cin >> student.num;
	for (int i = 0; i < student.num; i++)
	{
		cout << "input isbn student borrowed " << i + 1<<":";

		switch (i + 1) {
		case 1:
			cin >> student.isbn1;
			break;
		case 2:
			cin >> student.isbn2;
			break;
		case 3:
			cin >> student.isbn3;
			break;
		case 4:
			cin >> student.isbn4;
			break;
		case 5:
			cin >> student.isbn5;
			break;
		}
	}
	fstudent.open("student.dat", ios::out | ios::binary | ios::in);
	fstudent.seekp(sizeof(Student) * (t - 1));
	fstudent.write((char*)&student, sizeof(Student));
	fstudent.close();
}

bool Student::search_student(char* ID , int* cnt)
{
	fstream fstudent;
	Student student;
	fstudent.open("student.dat", ios::in | ios::binary);
	while (fstudent.read((char*)&student, sizeof(Student)))
	{
		if (cnt)
		{
			(*cnt)++;
		}
		if (_strcmpi(student.no, ID) == 0)
		{
			student.display();
			cout << endl;
			fstudent.close();
			return true;
		}
	}
	fstudent.close();
	return false;
}

void Student::display()
{
	cout << "id:" << no << "    ";
	cout << "name:" << name << "    ";
	cout << "isbn:";
	for (int i = 0; i < num; i++)
	{
		switch (i+1) {
		case 1:
			cout << isbn1 << "    ";
			break;
		case 2:
			cout << isbn2 << "    ";
			break;
		case 3:
			cout << isbn3 << "    ";
			break;
		case 4:
			cout << isbn4 << "    ";
			break;
		case 5:
			cout << isbn5 << endl;
			break;
		}
	}
	cout << "    num:" << num << endl;
}

void Student::display_all()
{
	Student student;
	fstream fstudent;
	fstudent.open("student.dat", ios::in | ios::binary);
	while (fstudent.read((char*)&student, sizeof(Student)))
	{
		student.display();
	}
	fstudent.close();
	cout << endl;
}

void Student::num_plus()
{
	num++;
}

void Student::num_reduce()
{
	num--;
}

void Student::add_isbn(char* p, int num)
{
	switch (num) {
	case 1:
		memcpy(isbn1, p, sizeof(p));
		break;
	case 2:
		memcpy(isbn2, p, sizeof(p));
		break;
	case 3:
		memcpy(isbn3, p, sizeof(p));
		break;
	case 4:
		memcpy(isbn4, p, sizeof(p));
		break;
	case 5:
		memcpy(isbn5, p, sizeof(p));
		break;
	}
}

int Student::retnum()
{
	return num;
}

void Student::modify_isbn(char* p,int num)
{
	if (_strcmpi(isbn1, p) == 0)
	{
		memcpy(isbn1, isbn2, sizeof(isbn2));
		memcpy(isbn2, isbn3, sizeof(isbn3));
		memcpy(isbn3, isbn4, sizeof(isbn4));
		memcpy(isbn4, isbn5, sizeof(isbn5));
		isbn5[0] = '\0';
	}
	else if (_strcmpi(isbn2, p) == 0)
	{
		memcpy(isbn2, isbn3, sizeof(isbn3));
		memcpy(isbn3, isbn4, sizeof(isbn4));
		memcpy(isbn4, isbn5, sizeof(isbn5));
		isbn5[0] = '\0';
	}
	else if (_strcmpi(isbn3, p) == 0)
	{
		memcpy(isbn3, isbn4, sizeof(isbn4));
		memcpy(isbn4, isbn5, sizeof(isbn5));
		isbn5[0] = '\0';
	}
	else if (_strcmpi(isbn4, p) == 0)
	{
		memcpy(isbn4, isbn5, sizeof(isbn5));
		isbn5[0] = '\0';
	}
	else if (_strcmpi(isbn5, p) == 0)
	{
		isbn5[0] = '\0';
	}
	else
	{
		cout << "you did't borrow the book" << endl;
	}
}
