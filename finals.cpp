#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<algorithm>
using namespace std;

struct Student {
    string studentID;
    string fullName;
    string birthday;
    string address;
    char gender;
    string degreeProgram;
    string yearLevel;
};
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
void addRecord(Student* students,int& numberRecords) {
    Student newStudent;
    Student lastName;
    ofstream file("records.txt", ios::app);
    if (numberRecords >= 100)
    {
        cout<<"Maximum number of records reached."<<endl;
        return;
    }
    clearScreen();
    cout<<"Add new record"<<endl;
    cout<<"Enter Student ID: ";cin>>newStudent.studentID;
    cin.ignore();

    cout<<"Enter Full Name: ";getline(cin, newStudent.fullName);
    transform(newStudent.fullName.begin(), newStudent.fullName.end(), newStudent.fullName.begin(),::toupper); 

    cout<<"Enter Birthdate (mm/dd/yyyy): ";getline(cin, newStudent.birthday);
    transform(newStudent.birthday.begin(), newStudent.birthday.end(), newStudent.birthday.begin(),::toupper);

    cout<<"Enter Address: ";getline(cin, newStudent.address);
    transform(newStudent.address.begin(), newStudent.address.end(), newStudent.address.begin(),::toupper);

    cout<<"Enter Gender (M/F): ";cin>>newStudent.gender;
    newStudent.gender=toupper(newStudent.gender);
    cin.ignore();

    cout<<"Enter Degree Program: ";getline(cin, newStudent.degreeProgram);
    transform(newStudent.degreeProgram.begin(), newStudent.degreeProgram.end(), newStudent.degreeProgram.begin(),::toupper);

    cout<<"Enter Year Level (1/2/3/4/Irregular): ";cin>>newStudent.yearLevel;
    transform(newStudent.yearLevel.begin(), newStudent.yearLevel.end(), newStudent.yearLevel.begin(),::toupper);
    cin.ignore();
    
    if (file.is_open())
    {
        file<<"Student ID: "<<newStudent.studentID<<endl;
        file<<"Full Name: "<<newStudent.fullName<<endl;
        file<<"Birthday: "<<newStudent.birthday<<endl;
        file<<"Address: "<<newStudent.address<<endl;
        file<<"Gender: "<<newStudent.gender<<endl;
        file<<"Degree Program: "<<newStudent.degreeProgram<<endl;
        file<<"Year Level (1/2/3/4/Irregular): "<<newStudent.yearLevel<<endl;
        file<<"-----------------"<<endl;
        cout<<"Record Added! Press enter to continue. ";
        cin.ignore();
        file.close();
    }else{
        cout<<"Error in file creation!"<<endl;
    }
    students[numberRecords] = newStudent;
    numberRecords++;
}
void searchRecord() {
    string searchID, line;
    int choice;
    bool found = false;

    clearScreen();

    cout<<"Search Record"<<endl;
    cout<<"Choose which method to search"<<endl;
    cout<<"1. Search by Name"<<endl;
    cout<<"2. Search by  Student ID"<<endl;
    cout<<"Enter choice: ";cin>>choice;

    switch(choice)
    {
        case 1:
        {
            cout << "Enter Full Name to search: ";
            cin.ignore();
            getline(cin, searchID);
            transform(searchID.begin(), searchID.end(), searchID.begin(), ::toupper);
            ifstream file("records.txt");
            if (file.is_open()) 
            {
                while (getline(file, line)) 
                {
                    if (line.find("Full Name: " + searchID) != string::npos) 
                    {
                        found = true;
                        cout << "\nRecord Found:\n";
                        cout << line << endl;
                        for (int i = 0; i < 6; ++i) 
                        {
                            getline(file, line);
                            cout << line << endl;
                        }
                    cout << "-----------------" << endl;
                    break;
                    }
                }
            }
            break;
        }
        case 2:
        {
            cout << "Enter Student ID to search: ";
            cin >> searchID;
            transform(searchID.begin(), searchID.end(), searchID.begin(), ::toupper);
            cin.ignore();

            ifstream file("records.txt");
            if (file.is_open())
            {
                while (getline(file, line)) 
                {
                    if (line.find("Student ID: " + searchID) != string::npos) 
                    {
                        found = true;
                        cout << "\nRecord Found:\n";
                        cout << line << endl;
                        for (int i = 0; i < 6; ++i) 
                        {
                            getline(file, line);
                            cout << line << endl;
                        }
                        cout << "-----------------" << endl;
                        break;
                    }
                }
                if (!found) 
                {
                    cout << "No record found with Student ID: " << searchID << endl;
                }
                file.close();
            } else 
            {
                cout << "Unable to open file." << endl;
            }
            cout << "Press enter to continue. ";
            cin.get();
            break;
        }
    }

}

void deleteRecord(Student* students, int& numberRecords) {
    string deleteId;
    cout << "Enter Student ID to delete: ";
    cin >> deleteId;
    int deleteIndex = -1;

    for (int i = 0; i < numberRecords; i++) {
        if (students[i].studentID == deleteId) {
            deleteIndex = i;
            cout << "Record deleted! Please enter any key to continue. ";
            cin.get();
            break; 
        }
    }

    if (deleteIndex == -1) {
        cout << "Record not found!" << endl;
    } else {
        for (int i = deleteIndex; i < numberRecords - 1; i++) {
            students[i] = students[i + 1];
        }
        numberRecords--;
        cin.get();

        ofstream file("records.txt", ios::trunc);
        if (file.is_open()) {
            for (int i = 0; i < numberRecords; i++) {
                file << "Student ID: " << students[i].studentID << endl;
                file << "Full Name: " << students[i].fullName << endl;
                file << "Birthday: " << students[i].birthday << endl;
                file << "Address: " << students[i].address << endl;
                file << "Gender: " << students[i].gender << endl;
                file << "Degree Program: " << students[i].degreeProgram << endl;
                file << "Year Level: " << students[i].yearLevel << endl;
                file << "-----------------" << endl;
            }
        }
        file.close();
        
    }

}
main()
{
    int choice;
    Student students[100];
    int numberRecords=0;
    do
    {
        clearScreen();
        cout<<"1. Add Record\n2. Search Record\n3. Delete Record\n4. Display Records\n5. Exit"<<endl;
        cout<<"Please type your selection: ";cin>>choice;
        switch (choice)
        {
        case 1:
            addRecord(students,numberRecords);
            break;
        case 2:
            searchRecord();
            break;
        case 3:
            deleteRecord(students,numberRecords);
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (choice!=5);
    return 0;
}
