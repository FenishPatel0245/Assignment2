#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA
{
    string firstName;
    string lastName;
};

int main()
{
    vector<STUDENT_DATA> students;
    ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open StudentData.txt." << endl;
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
        getline(record >> ws, student.firstName);

        students.push_back(student);
    }

    inputFile.close();

#ifdef _DEBUG
    cout << "Student information:" << endl;
    cout << "-------------------" << endl;
    for (const STUDENT_DATA& student : students)
    {
        cout << student.firstName << " "
            << student.lastName << endl;
    }
#endif

    return 0;
}