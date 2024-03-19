#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student {
    double studentID; // Changed to double to match the struct definition
    string fullname;
    string birthday;
    string address;
    char gender;
    string degreeProgram; // Changed to string to match the struct definition
    int yearLevel;
};
void addRecord() {
    Student student;
    ofstream outfile;
	outfile.open("student_record.txt", ios::binary|ios::app);

  //If file is not created, return error
  if(!outfile){
    cout<<"Error in file creation!";
  }else{ //File is created
    cout<<"File Creation successfull.";
  }
    if (!outfile) {
        cout << "Error opening file!" << endl;
        return;
    }
    

    cout<<"Enter Student ID: ";
    cin>>student.studentID;

    cin.ignore();
    cout<<"Enter Full Name: ";getline(cin, student.fullname);

    cout<<"Enter Birthday: ";getline(cin, student.birthday);

    cout<<"Enter Address: ";getline(cin, student.address);

    cout<<"Enter Gender: ";cin>>student.gender;

    cin.ignore();
    cout<<"Enter Degree Program: ";getline(cin, student.degreeProgram);

    cout<<"Enter Year Level: ";cin>>student.yearLevel;

    outfile.seekp(0, ios::end);
    outfile.write(reinterpret_cast<const char *>(&student), sizeof(student));

    outfile<<"Full Name: "<<student.fullname<<endl;
    outfile<<"Birthday: "<<student.birthday<<endl;
    outfile<<"Address: "<<student.address<<endl;
    outfile<<"Gender: "<<student.gender<<endl;
    outfile<<"Degree Program: "<<student.degreeProgram<<endl;
    outfile<<"Year Level: "<<student.yearLevel<<endl;

    cout<<"Student record added successfully!"<<endl; 

    outfile.close();
}

int main() { // Changed main() to int main()
    char choice;
    do {
        // Main Menu
        cout << "Welcome to Group Programmers Student Information System" << endl;
        cout << "What do you want to do?" << endl;
        cout << "1. Add New Record\n2. Search Record\n3. Display All Records\n4. Display Specific Record\n5. Delete Record\n6. Exit" << endl;
        cout << "Please type your selection: ";
        cin >> choice;

        switch (choice) {
        case '1':
            cout<<"Add New Record"<<endl;
            addRecord(); // Pass file as reference to the function
            break;
        case '2':
            cout<<"Search Record"<<endl;
            break;
        case '3':
            cout << "Display All Records" << endl;
            break;
        case '4':
            cout << "Display Specific Record" << endl;
            break;
        case '5':
            cout << "Delete Record" << endl;
            break;
        case '6':
            cout << "Exit" << endl;
            return 0;
        default:
            cout << "Invalid Input! Please try again." << endl;
            break;
        }
    } while (choice != '6');

    return 0;
}

