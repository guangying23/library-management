#include<iostream>
#include"Book.h"
#include"Student.h"
#include<fstream>
using namespace std;

void borrow_book(Book book, Student student);
void return_books(Book book, Student student);

int main()
{
	fstream fbook,fstudent;
	Book book;
	Student student;
	while (1)
	{
		cout << "1.borrow book" << endl;
		cout << "2.return book" << endl;
		cout << "3.add book" << endl;
		cout << "4.modify book" << endl;
		cout << "5.delete book" << endl;
		cout << "6.add student" << endl;
		cout << "7.modify student" << endl;
		cout << "8.delete student" << endl;
		int num;
		book.display_all();
		student.display_all();
		cout << "input the num of list you want to do:";
		cin >> num;
		switch (num) {
		case 1:
			borrow_book(book, student);
			break;
		case 2:
			return_books(book, student);
			break;
		case 3:
			book.create_book();
			break;
		case 4:
			book.modify_book();
			break;
		case 5:
			book.delete_book();
			break;
		case 6:
			student.ceate_student();
			break;
		case 7:
			student.modify_student();
			break;
		case 8:
			student.delete_student();
			break;
		default:
			break;
		}
		system("cls");
	}
	return 0;
}

void borrow_book(Book book, Student student)
{
	char p[14],id[6];
	int cnt = 0,cou=0;
	fstream fbook,fstudent; 
	cout << "input student id:";
	cin >> id;
	while (!student.search_student(id, &cou))
	{
		cout << "the id not found,input again:";
		cin >> id;
	}
	cout << "input the isbn you want to borrow:";
	cin >> p;
	while (!book.search_book(p,&cnt))
	{
		cout << "the isbn not found,input again:";
		cin >> p;
	}
	fbook.open("book.dat", ios::out| ios::binary | ios::in);
	fbook.seekp(sizeof(Book) * (cnt - 1));
	fbook.read((char*)&book, sizeof(Book));
	if (book.retnum() > 0)
	{
		book.num_reduce();
		cout << endl;
		fbook.seekp(sizeof(Book) * (cnt - 1));
		fbook.write((char*)&book, sizeof(Book));
	}
	else
	{
		cout << "all of the books were borrowed" << endl;
	}
	fbook.close();
	fstudent.open("student.dat", ios::out | ios::binary | ios::in);
	fstudent.seekp(sizeof(Student) * (cou - 1));
	fstudent.read((char*)&student, sizeof(Student));
	if (student.retnum() < 5)
	{
		student.num_plus();
		student.add_isbn(p, student.retnum());
		fstudent.seekp(sizeof(Student) * (cou - 1));
		fstudent.write((char*)&student, sizeof(Student));
	}
	else
	{
		cout << "you had borrowed 5 books,you can't borrow more" << endl;
	}
	fstudent.close();
}

void return_books(Book book, Student student)
{
	char p[14], id[6];
	int cnt = 0, cou = 0;
	fstream fbook, fstudent;
	cout << "input student id:";
	cin >> id;
	while (!student.search_student(id, &cou))
	{
		cout << "the id not found,input again:";
		cin >> id;
	}
	cout << "input the isbn you want to return:";
	cin >> p;
	while (!book.search_book(p, &cnt))
	{
		cout << "the isbn not found,input again:";
		cin >> p;
	}
	fbook.open("book.dat", ios::out | ios::binary | ios::in);
	fbook.seekp(sizeof(Book) * (cnt - 1));
	fbook.read((char*)&book, sizeof(Book));
	book.num_plus();
	//cout << endl;
	fbook.seekp(sizeof(Book) * (cnt - 1));
	fbook.write((char*)&book, sizeof(Book));
	fbook.close();
	fstudent.open("student.dat", ios::out | ios::binary | ios::in);
	fstudent.seekp(sizeof(Student) * (cou - 1));
	fstudent.read((char*)&student, sizeof(Student));
	if (student.retnum() > 0)
	{
		student.modify_isbn(p, student.retnum());
		student.num_reduce();
		fstudent.seekp(sizeof(Student) * (cou - 1));
		fstudent.write((char*)&student, sizeof(Student));
	}
	else
	{
		cout << "you had not borrowed book" << endl;
	}
	fstudent.close();
}