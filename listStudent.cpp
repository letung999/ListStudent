#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct Date {
	int day;
	int month;
	int year;
};
struct Student {
	string fullName;
	string mssv;
	Date dateOfBirth;
	float mark;
};
struct Node {
	Student data;
	Node* next;
};
struct List {
	Node* pHead;
	Node* pTail;
};
void createList(List &l) {
	l.pHead = NULL;
	l.pTail = NULL;
}
Node* createNode(Student data) {
	Node* p = new Node();
	if (p == NULL) {
		return NULL;
	}
	else {
		p->data = data;
		p->next = NULL;
	}
	return p;
}
void addNodeLastInList(List &l, Node* p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		l.pTail->next = p;
		l.pTail = p;
	}
}
void readDateOfBirth(fstream &fs, Date &date) {
	fs >> date.day;
	fs.seekg(1, 1);
	fs >> date.month;
	fs.seekg(1, 1);
	fs >> date.year;
}
void readListAstudentInFile(fstream &fs, Student &student) {
	getline(fs, student.fullName, ',');
	fs.seekg(1, 1);
	getline(fs, student.mssv, ',');
	fs.seekg(1, 1);
	readDateOfBirth(fs, student.dateOfBirth);
	fs.seekg(1, 1);
	fs >> student.mark;
}
void readInfomationStudentsAndAddInList(List &l, fstream &fs) {
	while (!fs.eof()) {
		Student student;
		readListAstudentInFile(fs, student);
		Node* p = createNode(student);
		addNodeLastInList(l, p);
	}
	fs.close();
}
void writeAstudentInfile(fstream &ofs, Student &student) {
	ofs << student.fullName << endl;
	ofs << student.mssv << endl;
	ofs << student.dateOfBirth.day << "/" << student.dateOfBirth.month << "/" << student.dateOfBirth.year << "/" << endl;
	ofs << student.mark << endl;
}
void writeStudentsfromListStudent(List&l, fstream &ofs) {
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		writeAstudentInfile(ofs, k->data);
	}
	ofs.close();
}
void Swap(Student &x, Student &y) {
	Student tmp = x;
	x = y;
	y = tmp;
}
void SortMark(List &l) {
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		for (Node* h = k->next; h != NULL; h = h->next) {
			if (h->data.mark < k->data.mark) {
				Swap(h->data, k->data);
			}
		}
	}

}
int SearchMarkHighest(List &l) {
	int highestMark = l.pHead->data.mark;
	for (Node* k = l.pHead->next; k != NULL; k = k->next) {
		if (highestMark < k->data.mark) {
			highestMark = k->data.mark;
		}
	}
	return highestMark;
}
void writeSortMarkFromListInFile(List&l, fstream &ofs) {
	SortMark(l);
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		writeAstudentInfile(ofs, k->data);
	}
	ofs.close();
}

void showInforAstudent(Student student) {
	cout << "fullName is: " << student.fullName << endl;
	cout << "Mssv is: " << student.mssv << endl;
	cout << "Date Of Birth: " << student.dateOfBirth.day << "/" << student.dateOfBirth.month << "/" << student.dateOfBirth.year << endl;
	cout << "Mark is: " << student.mark << endl;
	cout << "_____________________________________________________________________" << endl;
}
void showInformationInList(List &l) {
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		showInforAstudent(k->data);
	}
}
void writeHighestMarkFromListInFile(List &l, fstream &ofs) {
	int highestMark = SearchMarkHighest(l);
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		if (k->data.mark == highestMark) {
			writeAstudentInfile(ofs, k->data);
			showInforAstudent(k->data);
		}
	}
	ofs.close();
}
void searchMssv(List &l, string mssv) {
	bool check = false;
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		if (_strcmpi((char*)mssv.c_str(), (char*)k->data.mssv.c_str()) == 0) {
			showInforAstudent(k->data);
		}
	}

}
string cutName(string name) {
	int i;
	for ( i = name.length() - 1; i >= 0; i--) {
		if (name[i] ==' ') {
			break;
		}
	}
	return name.substr(i + 1);
}
void seachName(List &l, string name) {
	bool check = false;
	for (Node* k = l.pHead; k != NULL; k = k->next) {
		string resName = cutName(k->data.fullName);
		if (_strcmpi((char*)name.c_str(), (char*)resName.c_str()) == 0) {
			check = true;
			showInforAstudent(k->data);
		}
	}
	if (check == false) {
		cout << "no find Infomation in List" << endl;
	}
}
void menu() {
	List l;
	createList(l);
	fstream fs("student.txt", ios::in);
	fstream ofs("InfomationStudent.txt", ios::out);
	fstream ofs1("InformationStudentSortMark.txt", ios::out);
	fstream ofs2("InfomationStudentHighestMark.txt", ios::out);
	int choose;
	do
	{
		cout << "\n**************************MENU*************************" << endl;
		cout << "1.read Information In List" << endl;
		cout << "2.write infomation Student from List" << endl;
		cout << "3.write Information Student have Mark is Sort" << endl;
		cout << "4.write Information Student have highestMark and show Information this" << endl;
		cout << "5.search mssv in List" << endl;
		cout << "6.Search name in List" << endl;
		cout << "7.show Infomation In List" << endl;
		cout << "0.Exist! " << endl;
		cout << "you choose! ";
		cin >> choose;
		switch (choose)
		{
		case 0: {
			cout << "the program is end, thank you you use my service !" << endl;
			break;
		}
		case 1: {
			readInfomationStudentsAndAddInList(l,fs);
			break;
		}
		case 2: {
			readInfomationStudentsAndAddInList(l,fs);
			writeStudentsfromListStudent(l, ofs);
			break;
		}
		case 3: {
			readInfomationStudentsAndAddInList(l, fs);
			writeSortMarkFromListInFile(l, ofs1);
			break;
		}
		case 4: {
			readInfomationStudentsAndAddInList(l, fs);
			writeHighestMarkFromListInFile(l, ofs2);
			break;
		}
		case 5: {
			string mssv;
			cout << "in put mssv to Search" << endl;
			cin.ignore();
			getline(cin, mssv);
			searchMssv(l, mssv);
			break;
		}
		case 6: {
			readInfomationStudentsAndAddInList(l, fs);
			string name;
			cout << "input name to search in List" << endl;
			cin.ignore();
			getline(cin, name);
			seachName(l, name);
			break;
		}
		case 7: {
			showInformationInList(l);
			break;
		}
		default:
			cout << "please choose the option in the menu" << endl;
			break;
		}

	} while (choose != 0);
}
int main() {
	menu();
	return 0;
}