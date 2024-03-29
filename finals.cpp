#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
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

    studentID:
    cout<<"Enter Student ID: ";cin>>newStudent.studentID;
    cin.ignore();
    for(int i=0;i<newStudent.studentID.length();i++)
    {
        if(!isdigit(newStudent.studentID[i]))
        {
            cout<<"Invalid input. Student ID must be a number."<<endl;
            goto studentID;
        }
    }

    fullName:
    cout<<"Enter Full Name: ";getline(cin, newStudent.fullName);
    transform(newStudent.fullName.begin(), newStudent.fullName.end(), newStudent.fullName.begin(),::toupper);
    for(int i=0;i<newStudent.fullName.length();i++)
    {
        if(isdigit(newStudent.fullName[i]))
        {
            cout<<"Invalid input. Full Name must not contain numbers."<<endl;
            goto fullName;
        }
    }

    birthdate:
    cout<<"Enter Birthdate (mm/dd/yyyy): ";getline(cin, newStudent.birthday);
    stringstream ss(newStudent.birthday);
    int day, month, year;
    char slash;
    ss>>month>>slash>>day>>slash>>year;
    if(!ss)
    {
        cout<<"Invalid input. Birthdate must be in mm/dd/yyyy format."<<endl;
        goto birthdate;
    }

    cout<<"Enter Address: ";getline(cin, newStudent.address);
    transform(newStudent.address.begin(), newStudent.address.end(), newStudent.address.begin(),::toupper);

    gender:
    cout<<"Enter Gender (M/F): ";cin>>newStudent.gender;
    cin.ignore();
    if (newStudent.gender != 'M' && newStudent.gender != 'F' && newStudent.gender != 'm' && newStudent.gender != 'f')
    {
        cout<<"Invalid input. Gender must be either 'M' or 'F'."<<endl;
        goto gender;
    }

    cout<<"Enter Degree Program: ";getline(cin, newStudent.degreeProgram);
    transform(newStudent.degreeProgram.begin(), newStudent.degreeProgram.end(), newStudent.degreeProgram.begin(),::toupper);
    while(any_of(newStudent.degreeProgram.begin(), newStudent.degreeProgram.end(), ::isdigit)){
    cout<<"Error: Degree program cannot contain numbers. Please try again."<<endl;
    cin.ignore();
    cout<<"Enter Degree Program: ";
    getline(cin, newStudent.degreeProgram);
    transform(newStudent.degreeProgram.begin(), newStudent.degreeProgram.end(), newStudent.degreeProgram.begin(), ::toupper);
}

    yearLevel:
    cout<<"Enter Year Level (1/2/3/4/Irregular): ";cin>>newStudent.yearLevel;
    transform(newStudent.yearLevel.begin(), newStudent.yearLevel.end(), newStudent.yearLevel.begin(),::toupper);
    cin.ignore();
    if (newStudent.yearLevel != "1" && newStudent.yearLevel != "2" && newStudent.yearLevel != "3" && newStudent.yearLevel != "4" && newStudent.yearLevel != "IRREGULAR")
    {
        cout<<"Invalid input. Year Level must be either '1', '2', '3', '4' or 'IRREGULAR'."<<endl;
        goto yearLevel;
    }
    
    if (file.is_open())
    {
        file<<"Student ID: "<<newStudent.studentID<<endl;
        file<<"Name: "<<newStudent.fullName<<endl;
        file<<"Birthday: "<<newStudent.birthday<<endl;
        file<<"Address: "<<newStudent.address<<endl;
        if (newStudent.gender == 'M'||newStudent.gender == 'm')
        {
            file<<"Gender: MALE"<<endl;
        }else if (newStudent.gender == 'F'||newStudent.gender == 'f')
        {
            file<<"Gender: FEMALE"<<endl;
        }
        file<<"Degree Program: "<<newStudent.degreeProgram<<endl;
        file<<"Year Level (1/2/3/4/Irregular): "<<newStudent.yearLevel<<endl;
        file<<"-----------------"<<endl;
        cout<<"Record Added! Press enter to continue... ";
        cin.ignore();
        file.close();
    }else{
        cout<<"Error in file creation!"<<endl;
    }
    students[numberRecords] = newStudent;
    numberRecords++;
}

void displayAllRecords() {
    clearScreen();
    cout << "Displaying All Records:" << endl;
    ifstream file("records.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open records.txt" << endl;
    }
    cout << "Press enter to continue... ";
    cin.ignore();
    cin.get();
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
        case 1: // Search by Full Name
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
                    if (line.find("Name: " + searchID) != string::npos) 
                    {
                        found = true;
                        cout << "\nRecord Found:\n";
                        cout << line << endl;
                        for (int i = 0; i < 6; ++i) 
                        {
                            getline(file, line);
                            cout << line << endl;
                        }
                        break;
                    }
                }
                if (!found) 
                {
                    cout << "No record found with Name: " << searchID << endl;
                }
                file.close();
            }
            cout << "Press enter to continue... ";
            cin.get();
            break;
        }
        case 2: // Search by ID
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
            cout << "Press enter to continue... ";
            cin.get();
            break;
        }
    }

}

void deleteRecord(Student* students, int& numberRecords) {
    string deleteId;
    clearScreen();
    cout << "Enter Student ID to delete: ";
    cin >> deleteId;
    int deleteIndex = -1;

    for (int i = 0; i < numberRecords; i++) {
        if (students[i].studentID == deleteId) {
            deleteIndex = i;
            cout << "Record deleted! Please enter any key to continue... ";
            cin.get();
            break; 
        }
    }

    if (deleteIndex == -1) {
        cout << "Record not found!" << endl;
        cout << "Please enter any key to continue... ";
        cin.get();
        cin.get(); 
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
        cout << "Welcome to LaZed Group Student Information System" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. Search Record" << endl;
        cout << "3. Delete Record" << endl;
        cout << "4. Display Records" << endl;
        cout << "5. Exit" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Please enter your selection: ";cin >> choice;
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
            displayAllRecords();
            break;
        case 5:
            cout<<"Thank you for using our system. Have a good day!"<<endl;
            break;
        default:
            cout<<"Invalid choice. Please try again."<<endl;
            cin.get();
            cin.get();
            break;
            
        }
    } while (choice!=5);
    return 0;
}