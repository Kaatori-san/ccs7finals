#include<iostream>
#include<fstream>
using namespace std;

struct studentInfo
{
    double studentID;
    string fullname;
    // needs birthdate initialization here
    string address;
    char gender;
    char degreeProgram;
    int yearLevel;

};
void addRecord()
{
    studentInfo student;
    fopen("student.txt","a");
    ofstream fout;
    fout.open("student.txt",ios::app);
    cout<<"Enter Student ID: ";cin>>student.studentID;
    cout<<"Enter Full Name: ";cin>>student.fullname;
    cout<<"Enter Address: ";cin>>student.address;
    cout<<"Enter Gender: ";cin>>student.gender;
    cout<<"Enter Degree Program: ";cin>>student.degreeProgram;
    cout<<"Enter Year Level: ";cin>>student.yearLevel;
    fout.write((char*)&student,sizeof(student));
    fout.close();
}
main()
{
    char choice;
    do
    {
        // Main Menu
        cout<<"Welcome to Group Programmers Student Information System"<<endl;
        cout<<"What do you want to do?"<<endl;
        cout<<"1. Add New Record\n2. Search Record\n3. Display All Records\n4. Display Specific Record\n5. Delete Record\n6. Exit"<<endl;
        cout<<"Please type your selection: ";cin>>choice;

        switch(choice)
        {
        case '1':
            cout<<"Add New Record"<<endl;
            addRecord();
            break;
        case '2':
            cout<<"Search Record"<<endl;
            break;
        case '3':
            cout<<"Display All Records"<<endl;
            break;
        case '4':
            cout<<"Display Specific Record"<<endl;
            break;
        case '5':
            cout<<"Delete Record"<<endl;
            break;
        case '6':
            cout<<"Exit"<<endl;
            return 0;
        default:
            cout<<"Invalid Input! Please try again."<<endl;
            break;
        }
    } while (choice != '6');   
}