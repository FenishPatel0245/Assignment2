#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

struct STUDENT_DATA
{
    string firstName;
    string lastName;

#ifdef PRE_RELEASE
    string email;
#endif
};

int main()
{
    // Match the encoding of the supplied data files.
    SetConsoleOutputCP(1252);

    vector<STUDENT_DATA> students;

#ifdef PRE_RELEASE
    cout << "Running Pre-Release Version" << endl;
    const string fileName = "StudentData_Emails.txt";
#else
    cout << "Running Standard Version" << endl;
    const string fileName = "StudentData.txt";
#endif

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open " << fileName << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream record(line);
        STUDENT_DATA student;

        getline(record, student.lastName, ',');

#ifdef PRE_RELEASE
        getline(record >> ws, student.firstName, ',');
        getline(record >> ws, student.email);
#else
        getline(record >> ws, student.firstName);
#endif

        students.push_back(student);
    }

    inputFile.close();

#ifdef _DEBUG
    cout << "\nStudent information:" << endl;
    cout << "--------------------" << endl;

    for (const STUDENT_DATA& student : students)
    {
        cout << student.firstName << " "
            << student.lastName;

#ifdef PRE_RELEASE
        cout << " | " << student.email;
#endif

        cout << endl;
    }
#endif

    return 0;
}