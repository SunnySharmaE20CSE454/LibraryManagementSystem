#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

class book
{
	char bno[6]; //bookno.
	char bname[50]; //bookname
	char aname[20]; //authorname
public:
	void createbook()
	{
		cout << "\nNEW BOOK ENTRY...\n";
		cout << "\nENTER BOOK NO.";
		cin >> bno;
		cin.ignore(); // Ignore the newline character in the input buffer
		cout << "\nENTER BOOK NAME: ";
		cin.getline(bname, 50);
		cout << "\nENTER AUTHOR NAME: ";
		cin.getline(aname, 20);
		cout << "\n\n\nBook Created..";
	}
	void showbook()
	{
		cout << "\nBook Number: " << bno;
		cout << "\nBook Name: " << bname;
		cout << "\nBook Author Name: " << aname;
	}
	void modifybook()
	{
		cout << "\nBook Number: " << bno;
		cout << "\nModify Book Name: ";
		cin.ignore();
		cin.getline(bname, 50);
		cout << "\nModify Author's Name: ";
		cin.getline(aname, 20);
	}

	char* retbno() //string return
	{
		return bno;
	}
	void report()
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
}; //class ends here

class student
{
	char admno[6]; //admission no.
	char name[20];
	char stbno[6]; // student book no
	int token; //total book of student
public:
	void createstudent()
	{
		cout << "\nNEW STUDENT ENTRY...\n";
		cout << "\nEnter The Admission No. ";
		cin >> admno;
		cin.ignore(); // Ignore the newline character in the input buffer
		cout << "Enter The Student Name: ";
		cin.getline(name, 20);
		token = 0;
		stbno[0] = '\0';
		cout << "\n\nStudent Record Created...";
	}
	void showstudent()
	{
		cout << "\nAdmission Number: " << admno;
		cout << "\nStudent Name: " << name;
		cout << "\nNo of Book Issued: " << token;
		if (token == 1)
		{
			cout << "\nBook Number: " << stbno;
		}
	}
	void modifystudent()
	{
		cout << "\nAdmission No. " << admno;
		cout << "\nModify Student Name: ";
		cin.ignore();
		cin.getline(name, 20);
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token = 1;
	}
	void resettoken()
	{
		token = 0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno, t);
	}
	void report()
	{
		cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
	}
}; //class ends here

fstream fp, fp1; //object
book bk; //book class object
student st; //student class object

void writebook()
{
	char ch;
	fp.open("book.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		bk.createbook();
		fp.write((char*)&bk, sizeof(book)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void writestudent()
{
	char ch;
	fp.open("student.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		st.createstudent();
		fp.write((char*)&st, sizeof(student)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void displayspb(char n[])
{
	cout << "\nBOOK DETAILS\n";
	int flag = 0; //book not found
	fp.open("book.dat", ios::in); //read data
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) == 0) //not case sensitive
		{
			bk.showbook();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //book not found
	{
		cout << "\n\nBook does not exist";
	}
	system("pause");
}

void displaysps(char n[])
{
	cout << "\nSTUDENT DETAILS\n";
	int flag = 0; //student not found
	fp.open("student.dat", ios::in); //read data
	while (fp.read((char*)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) == 0) //not case sensitive
		{
			st.showstudent();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //student not found
	{
		cout << "\n\nStudent does not exist";
	}
	system("pause");
}

void modifybook()
{
	char n[6];
	int found = 0; //search book of given data
	system("cls");
	cout << "\n\nMODIFY BOOK RECORD...";
	cout << "\n\nEnter the book no. ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&bk, sizeof(book)) && found == 0)
	{
		if (strcmpi(bk.retbno(), n) == 0)
		{
			bk.showbook();
			cout << "\nEnter the new details of the book";
			bk.modifybook();
			int pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char*)&bk, sizeof(book));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	system("pause"); //press any key to get out
}

void modifystudent()
{
	char n[6];
	int found = 0; //search book of given data
	system("cls");
	cout << "\n\nMODIFY STUDENT RECORD...";
	cout << "\n\nEnter the Admission no. ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), n) == 0)
		{
			st.showstudent();
			cout << "\nEnter the new details of student";
			st.modifystudent();
			int pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char*)&st, sizeof(student));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	system("pause"); //press any key to get out
}

void deletestudent()
{
	char n[6];
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE STUDENT...";
	cout << "\n\nEnter the Admission no> : ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) != 0)
		{
			fp2.write((char*)&st, sizeof(student));
		}
		else
		{
			flag = 1; //student found
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat", "student.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted..";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	system("pause");
}

void deletebook()
{
	char n[6]; //book no.
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE BOOK...";
	cout << "\n\nEnter the Book no> : ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	fstream fp2; //New object
	fp2.open("Temp.dat", ios::out); //temp having data else than that to be deleted
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) != 0)
		{
			fp2.write((char*)&bk, sizeof(book));
		}
		else
		{
			flag = 1; //book found
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat", "book.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted... ";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	system("pause");
}

void displayalls()
{
	system("cls");
	fp.open("student.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		system("pause");
		return; //press any key and return
	}
	cout << "\n\n\t\tStudent List\n\n";
	cout << "==================================================================\n";
	cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
	cout << "==================================================================\n";
	while (fp.read((char*)&st, sizeof(student)))
	{
		st.report();
	}
	fp.close();
	system("pause");
}

void displayallb()
{
	system("cls");
	fp.open("book.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		system("pause");
		return; //press any key and return
	}
	cout << "\n\n\t\tBook List\n\n";
	cout << "==================================================================\n";
	cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
	cout << "==================================================================\n";
	while (fp.read((char*)&bk, sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	system("pause");
}

void bookissue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	system("cls");
	cout << "\n\nBOOK ISSUE...";
	cout << "\n\n\tEnter Admission no.: ";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0) //compare admission no.
		{
			found = 1;
			if (st.rettoken() == 0) //if book not issued
			{
				cout << "\n\n\tEnter The Book No.: ";
				cin >> bn;
				while (fp1.read((char*)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), bn) == 0) //compare book no.
					{
						flag = 1;
						st.addtoken();
						st.getstbno(bk.retbno()); //pass book no.
						int pos = -1 * sizeof(st);
						fp.seekg(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\tBook Issued Successfully\n\nPlease Note The Book Issue Date On Backside Of Your Book And Return Book Within 15 Days, Otherwise Fine Of 15 Rs Per Day.";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exist";
				}
			}
			else
			{
				cout << "You Have Not Returned The Last Book";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Found...";
	}
	fp.close();
	fp1.close();
	system("pause");
}

void bookdeposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	system("cls");
	cout << "\n\nBOOK DEPOSIT...";
	cout << "\n\n\tEnter Admission no. Of Student: ";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0) //compare admission no.
		{
			found = 1;
			if (st.rettoken() == 1) //if book issued
			{
				while (fp1.read((char*)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), st.retstbno()) == 0)
					{
						flag = 1;
						bk.showbook();
						cout << "\n\nBook Deposited In No. Of Days: ";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine = " << fine;
						}
						st.resettoken();
						int pos = -1 * sizeof(st);
						fp.seekg(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\tBook Deposited Successfully";
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exist";
				}
			}
			else
			{
				cout << "No Book Issued";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Found...";
	}
	fp.close();
	fp1.close();
	system("pause");
}

void start()
{
	system("cls");
	cout << "\n\n\tLIBRARY";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\tSYSTEM";
	cout << "\n\n\tby: Chahat";
	system("pause");
}

void adminmenu()
{
	system("cls");
	int ch2;
	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\n\t1. CREATE STUDENT RECORD";
	cout << "\n\n\n\t2. DISPLAY ALL STUDENT RECORD";
	cout << "\n\n\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
	cout << "\n\n\n\t4. MODIFY STUDENT RECORD";
	cout << "\n\n\n\t5. DELETE STUDENT RECORD";
	cout << "\n\n\n\t6. CREATE BOOK";
	cout << "\n\n\n\t7. DISPLAY SPECIFIC BOOK";
	cout << "\n\n\n\t8. MODIFY BOOK RECORD";
	cout << "\n\n\n\t9. DELETE BOOK RECORD";
	cout << "\n\n\n\t10. BACK TO MAIN MENU";
	cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-10): ";
	cin >> ch2;
	switch (ch2)
	{
	case 1:
		writestudent();
		break;
	case 2:
		displayalls();
		break;
	case 3:
		char num[6];
		system("cls");
		cout << "\n\n\t Please enter admission no.: ";
		cin >> num;
		displaysps(num);
		break;
	case 4:
		modifystudent();
		break;
	case 5:
		deletestudent();
		break;
	case 6:
		writebook();
		break;
	case 7:
	{
		char num[6];
		system("cls");
		cout << "\n\n\tPlease enter book no.: ";
		cin >> num;
		displayspb(num);
		break;
	}
	case 8:
		modifybook();
		break;
	case 9:
		deletebook();
		break;
	case 10:
		return;
	default:
		cout << "Invalid choice";
	}
	system("pause");
	adminmenu();
}

int main()
{
	char ch;
	system("cls");
	start();
	do
	{
		system("cls");
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\n\t1. BOOK ISSUE";
		cout << "\n\n\n\t2. BOOK DEPOSIT";
		cout << "\n\n\n\t3. ADMINISTRATOR MENU";
		cout << "\n\n\n\t4. EXIT";
		cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4): ";
		ch = getchar();

		switch (ch)
		{
		case '1':
			bookissue();
			break;
		case '2':
			bookdeposit();
			break;
		case '3':
			adminmenu();
			break;
		case '4':
			exit(0);
			break;
		default:
			cout << "INVALID CHOICE";
		}
	} while (ch != '4');
	return 0;
}
