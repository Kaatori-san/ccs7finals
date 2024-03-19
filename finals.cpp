#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

struct Student {
    string studentID;
    string fullname;
    string birthday;
    string address;
    char gender;
    string degreeProgram;
    string yearLevel;
};
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
void addRecord() {
    Student student;
    ofstream file("records.txt", ios::app);

    clearScreen();
    cout<<"Add new record"<<endl;
    cout<<"Enter Student ID: ";cin>>student.studentID;
    cin.ignore();

    cout<<"Enter Full Name: ";getline(cin, student.fullname);
    transform(student.fullname.begin(), student.fullname.end(), student.fullname.begin(),::toupper); 

    cout<<"Enter Birthdate (mm/dd/yyyy): ";getline(cin, student.birthday);
    transform(student.birthday.begin(), student.birthday.end(), student.birthday.begin(),::toupper);

    cout<<"Enter Address: ";getline(cin, student.address);
    transform(student.address.begin(), student.address.end(), student.address.begin(),::toupper);

    cout<<"Enter Gender (M/F): ";cin>>student.gender;
    student.gender=toupper(student.gender);
    cin.ignore();

    cout<<"Enter Degree Program: ";getline(cin, student.degreeProgram);
    transform(student.degreeProgram.begin(), student.degreeProgram.end(), student.degreeProgram.begin(),::toupper);

    cout<<"Enter Year Level (1/2/3/4/Irregular): ";cin>>student.yearLevel;
    transform(student.yearLevel.begin(), student.yearLevel.end(), student.yearLevel.begin(),::toupper);
    cin.ignore();
    
    if (file.is_open())
    {
        file<<"Student ID: "<<student.studentID<<endl;
        file<<"Full Name: "<<student.fullname<<endl;
        file<<"Birthday: "<<student.birthday<<endl;
        file<<"Address: "<<student.address<<endl;
        file<<"Gender: "<<student.gender<<endl;
        file<<"Degree Program: "<<student.degreeProgram<<endl;
        file<<"Year Level (1/2/3/4/Irregular): "<<student.yearLevel<<endl;
        file<<"-----------------"<<endl;
        cout<<"Record Added! Press enter to continue. ";
        cin.ignore();
        file.close();
    }else{
        cout<<"Error in file creation!"<<endl;
    }
}
void searchRecord() {
    string searchID, line;
    bool found = false;

    clearScreen();
    cout << "Search Record" << endl;
    cout << "Enter Student ID to search: ";
    cin >> searchID;
    transform(searchID.begin(), searchID.end(), searchID.begin(), ::toupper);
    cin.ignore();

    ifstream file("records.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("Student ID: " + searchID) != string::npos) {
                found = true;
                cout << "\nRecord Found:\n";
                cout << line << endl; // Student ID
                for (int i = 0; i < 6; ++i) { // There are 6 more lines for each record
                    getline(file, line);
                    cout << line << endl;
                }
                cout << "-----------------" << endl;
                break;
            }
        }
        if (!found) {
            cout << "No record found with Student ID: " << searchID << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file." << endl;
    }
    cout << "Press enter to continue. ";
    cin.get();
}

main()
{
    int choice;
    do
    {
        clearScreen();
        cout<<"1. Add Record\n2. Search Record\n3. Delete Record\n4. Display Records\n5. Exit"<<endl;
        cout<<"Please type your selection: ";cin>>choice;
        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            searchRecord();
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (choice!=5);
    return 0;
}