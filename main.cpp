#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Course_Grades
{
public:
    float grades;
};
class Student_info
{
public:
    int id;
    string name;
    int age;
    float gpa;
    Student_info* next_pointer;
    Course_Grades grades[5];
};
//To Make Sure It Is Empty
Student_info* head = nullptr;
//To Make Sure that The Name Does Not Include numbers
bool Valid_Name(string name)
{
    if (name.length() == 0)
        return false;
    for (int i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]) )
        {
            return false;
        }
        else if (!isspace(name[i]))
        {
           return true ;
        }

    }
    return true;
}
//To Make Sure that The Name is saved correctly
string Format_Name(string name)
{
    string fixedName = "";
    bool newWord = true;
    for (int i = 0; i < name.length(); i++)
    {
        if (isspace(name[i]))
        {//
            if (!fixedName.empty() && fixedName.back() != ' ')
            {
                fixedName += ' ';
                newWord = true;
            }
        }
        else if (isalpha(name[i]))
        {
            if (newWord)
            {
                fixedName += toupper(name[i]);
                newWord = false;
            }
            else
            {
                fixedName += tolower(name[i]);
            }
        }
    }
    if (!fixedName.empty() && fixedName.back() == ' ')
        fixedName.pop_back();
//pop_back delete the last
//back look the last it was space or not
    return fixedName;
}
//Make sure all the numbers are correct; they are numbers only, not decimals.
int Valid_Int()
{
    string line;
    while (true)
    {
        // getline read the line
        getline(cin, line);
        string cleanLine = "";
        for (char c : line) {
            if (!isspace(c)) {
                cleanLine += c;
            }
        }
        // clean line sure the input is not space
        if (cleanLine.empty()) {
            cout << "Invalid input. Please Enter a number only: ";
            continue;
        }
        bool valid = true;
        for (char c : cleanLine) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid input. Please Enter a number only (no letters): ";
            continue;
        }
        // stoi swap string to int
        return stoi(cleanLine);
    }
}
//Make sure all numbers are correct, decimal numbers only.
float Valid_Float()
{
    string line;
    while (true)
    {
        getline(cin, line);
        if (line.empty())
        {
            cout << "Invalid input. Please Enter a float number: ";
            continue;
        }
        bool valid = true;
        int dotCount = 0;
        int digitCount = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (isspace(line[i])) continue;
            if (line[i] == '.')
            {
                dotCount++;
                if (dotCount > 1) { valid = false; break; }
            }
            else if (!isdigit(line[i]))
            {
                valid = false;
                break;
            }
            else
            {
                digitCount++;
            }
        }
        if (!valid || digitCount == 0)
        {
            cout << "Invalid input. Please Enter a float number only: ";
            continue;
        }
         // stof swap string to int
        float value = stof(line);
        if (value < 0)
        {
            cout << "Number cannot be Negative. Try again: ";
            continue;
        }
        return value;
    }
}
//Make sure all ID is diffrant
int  ID_IS_Unique(int id)
{
    Student_info* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return false;
        }
        temp = temp->next_pointer;
    }
    return true;
}
//Add new Student or the first student
//using linked list
// using insert last
void Add_Student()
{
    Student_info* newStudent = new Student_info;

     cout << "\n Add New Student\n";

     do
     {
            cout << "Enter student ID: ";
            newStudent->id = Valid_Int();

        if (!ID_IS_Unique(newStudent->id))
        {
        cout << "\n This Student With This ID Is Already Exist\n";
        delete newStudent;
        return;

        }

     }
    while(!ID_IS_Unique(newStudent->id));

    do
    {
        cout << "Enter Name :";
        getline(cin, newStudent->name);

        if (!Valid_Name(newStudent->name))
        {
            cout << "Invalid Name Please letters only\n";
        }

        else
        {
            newStudent->name = Format_Name(newStudent->name);
        }

    }
     while (!Valid_Name(newStudent->name));
     //make sure the age is 17 < age < 50
     do
     {
         cout << "Enter Age: ";
         newStudent->age = Valid_Int();
         if(newStudent->age<17||newStudent->age>50)
         {
             cout<<"Age Cannot Be More Than 50 Or less than 17 \n";
         }


     }
     while(newStudent->age<17||newStudent->age>50);


//make sure the GPA is < 4.0
    do
    {
        cout << "Enter GPA : ";
        newStudent->gpa = Valid_Float();
        if (newStudent->gpa > 4.0) {
            cout << " GPA cannot be more than 4.0. Try again.\n";
        }
    }
    while (newStudent->gpa > 4.0);

    cout << "Enter 5 Course Grade:\n";
    for (int i = 0; i < 5; i++)
    {
        do {
            cout << "Grade for Subject " << (i + 1) << ": ";
            float g = Valid_Float();

            if (g > 100) {
                cout << " Grade cannot be more than 100. Try again.\n";
            } else {
                newStudent->grades[i].grades = g;
                break;
            }
        } while (true);
    }

    newStudent->next_pointer = nullptr;

    if (head == nullptr)
    {
        head = newStudent;
    }
    else
    {
        Student_info* temp = head;
        while (temp->next_pointer != nullptr)
        {
            temp = temp->next_pointer;
        }
        temp->next_pointer = newStudent;
    }
    cout << "\n The Student added successfully\n";
}
// show the user all student in the system
// using outer loop look at linked list
//using inner loop look at Arry
void Display_Student()
{
    if (head == nullptr)
    {
        cout << "No Student in the list\n";
        return;
    }

    Student_info* temp = head;
    int studentCount = 0;

    cout << "====\n All Student List\n====\n";

    while (temp != nullptr)
    {
        // Time Complexity to show all student one by one
        studentCount++;

        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "GPA: " << temp->gpa << endl;

        cout << "Grades:\n";

        for (int i = 0; i < 5; i++)
        {
            cout << "Subject " << i + 1 << ": "
                 << temp->grades[i].grades << endl;
        }

        cout << "----------------------\n";

        temp = temp->next_pointer;
    }

    cout << "Total Number of Students: " << studentCount << endl;
    cout << "============================\n";
}
//Search student with liner Search
void Search_Student()
{
    if (head == nullptr)
    {
        cout << "No Student in the list\n";
        return;
    }
    int choice;
    cout << "1. Enter Student ID\n";
    cout << "2. Enter Student Name\n";
    cout << "Enter your Choice: ";
    choice = Valid_Int();

    Student_info* temp = head;
    bool found = false;

    if (choice == 1)
    {
        int tagetID;
        cout << "Enter ID to Search: ";
        tagetID = Valid_Int();
        while (temp != nullptr)
        {
            if (temp->id == tagetID)
            {
                found = true;
                break;
            }
            temp = temp->next_pointer;
        }
    }
    else if (choice == 2)
    {
        string targetName;
        do
        {
            cout << "Enter Name to Search: ";
            getline(cin, targetName);
            if (!Valid_Name(targetName))
                cout << "Invalid input Please Try Again\n";
        } while (!Valid_Name(targetName));
// worst case
        while (temp != nullptr)
        {
            if (temp->name == targetName)
            {
                found = true;
                break;
            }
            temp = temp->next_pointer;
        }
    }
    else
    {
        cout << "Invalid input Please Try Again\n";
        return;
    }

    if (found)
    {
        cout << "\n---- Student Found -----\n";
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "GPA: " << temp->gpa << endl;

        cout << "Grades: ";
        for (int i = 0; i < 5; i++)
        {
            cout << temp->grades[i].grades << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "\nStudent Not Found!\n";
    }
    cout << "============================\n";
}

void Delete_Student()
{
    if (head == nullptr)
    {
        cout << "List is Empty cannot delete\n";
        return;
    }
    cout << "\n==== Delete Student ====\n";
    cout << "Enter the Student ID to Delete: ";
    int targetID = Valid_Int();
// delete first
    if (head->id == targetID)
    {
        Student_info* temp = head;
        head = head->next_pointer;
        delete temp;
        cout << "The Student Deleted Successfully\n";
        return;
    }
    Student_info* current = head;
    Student_info* prev = nullptr;

    while (current != nullptr && current->id != targetID)
    {
        prev = current;
        current = current->next_pointer;
    }
    if (current == nullptr)
    {
        cout << "\n Student with ID " << targetID << " Not Found \n";
        return;
    }
    //delete middle and last
    prev->next_pointer = current->next_pointer;
    delete current;
    cout << " Student Deleted Successfully\n";
}
// update the student information

void Update_Student()
{
    if(head == nullptr)
    {
        cout << "The List Is Empty Cannot Update\n";
        return;
    }
    cout << "==== Update Student ====\n";
    cout << "Enter ID Student to Update: ";
    int targetID = Valid_Int();

    Student_info* temp = head;
    bool found = false;
    // using liner search
    while(temp != nullptr)
    {
        // worst case if the student in the last of list
        if(temp->id == targetID)
        {

            found = true;
            cout << "Found The Student Enter The Info\n";

            do
            {
                cout << "Enter New Name: ";
                getline(cin, temp->name);
                if(!Valid_Name(temp->name))
                {
                    cout << "Invalid Input Please Try Again\n";
                }
                else
                {
                    temp->name = Format_Name(temp->name);
                }
            }
            while(!Valid_Name(temp->name));
            do
            {
                cout << "Enter Age: ";
                temp->age = Valid_Int();
                if(temp->age<17||temp->age>50)
                    {
                        cout<<"Age Cannot Be More Than 50 Or less than 17 \n";
                    }
            }
            while(temp->age<17||temp->age>50);

            do
            {
                cout << "Enter New GPA : ";
                temp->gpa = Valid_Float();
                if (temp->gpa > 4.0) cout << " GPA cannot be more than 4.0.\n";
            }
            while (temp->gpa > 4.0);

            cout << "Enter New 5 Grades:\n";
            for(int i = 0; i < 5; i++)
            {
                do {
                    cout << "Grades for Subject " << (i + 1) << ": ";
                    float g = Valid_Float();
                    if (g > 100) cout << " Grade max is 100.\n";
                    else {
                        temp->grades[i].grades = g;
                        break;
                    }
                } while (true);
            }
            cout << "Student Update Successfully\n";
            break;
        }
        temp = temp->next_pointer;
    }

    if(!found)
    {
        cout << "Student with ID " << targetID << " Not Found\n";
    }
}
// sort the student with bubble sort
void Sort_Student()
{
    if (head == nullptr || head->next_pointer == nullptr)
    {
        cout << "No sorting needed.\n";
        return;
    }

    int criteria, order;
    cout << "1. Sort by Name\n";
    cout << "2. Sort by GPA\n";
    cout << "Choice: ";
    criteria = Valid_Int();
// sort Ascending or Descending
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    cout << "Choice: ";
    order = Valid_Int();

    Student_info* current;
    bool swapped;

    do
    {
        swapped = false;
        current = head;

        while (current->next_pointer != nullptr)
        {
            bool needSwap = false;

            if (criteria == 1)
            {
                if (order == 1)
                    needSwap = current->name > current->next_pointer->name;
                else
                    needSwap = current->name < current->next_pointer->name;
            }

            else if (criteria == 2)
            {
                if (order == 1)
                    needSwap = current->gpa > current->next_pointer->gpa;
                else
                    needSwap = current->gpa < current->next_pointer->gpa;
            }

            if (needSwap)
            {
                swap(current->id, current->next_pointer->id);
                swap(current->name, current->next_pointer->name);
                swap(current->age, current->next_pointer->age);
                swap(current->gpa, current->next_pointer->gpa);

                for (int i = 0; i < 5; i++)
                    swap(current->grades[i].grades,
                         current->next_pointer->grades[i].grades);

                swapped = true;
            }

            current = current->next_pointer;
        }

    } while (swapped);

    cout << "Students sorted successfully.\n";
}
// Filter Student by GPA
void Filter_Students()
{
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    float minGPA;
    cout << "==== Filter Students ====";
    cout << "Enter Minimum GPA to Display: ";
    minGPA = Valid_Float();

    Student_info* temp = head;
    bool found = false;

    cout << "\n--- Students with GPA >= " << minGPA << " ---\n";
    while (temp != nullptr)
    {
        if (temp->gpa >= minGPA)
        {
            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | GPA: " << temp->gpa << endl;
            found = true;
        }
        temp = temp->next_pointer;
    }

    if (!found) cout << "No students found with GPA higher than " << minGPA << "\n";
    cout << "---------------------------\n";
}
// Cleaning up to stop Memory Leaks
void Free_Memory()
{
    Student_info*temp=head;
    while(head!=nullptr)
    {
        temp=head;
        head=head->next_pointer;
        delete temp;

    }


}
// save data and creates  file Excel
void Save_Data()
{
    if(head==nullptr)
    {
        cout<<"==== No Data To Save ====";
        return;
    }
    // to write the Information in Excel file
    ofstream outFile("Student.csv");
    if(!outFile)
    {
        cout<<"Opening File to Save";
        return;

    }
    outFile << "ID,Name,Age,GPA, Subject 1,Subject 2,Subject 3,Subject 4,Subject 5" << endl;
    Student_info*temp=head;
    while(temp!=nullptr)
    {

        outFile<<temp->id<<",";
        outFile<<temp->name<<",";
        outFile<<temp->age<<",";
        outFile<<temp->gpa<<",";

        for(int i=0;i<5;i++)
        {

            outFile<<temp->grades[i].grades<<" ";
            if (i < 4) outFile << ",";
        }
        outFile<<endl;
        temp=temp->next_pointer;

    }
    outFile.close();
    cout<<" Data Save Successfully";

}
// load data from file and read the Information
void Load_Data()
{
    Free_Memory();
    // to read the Information in the file
    ifstream inFile("Student.csv");
    if(!inFile)
    {
        cout << "File not found or unable to open.\n";
        return;
    }
    string header;
    getline(inFile, header);
    Student_info* newStudent = nullptr;
    char comma;
    // peek-> To make sure there's incoming data before you start reading,
    // you're performing a "Check" to see if there's a new student or if we've reached the end of the file.
    // EOF-> End Of File to make sure we arrive the end of file
    while(inFile.peek() != EOF)
    {
        if (inFile.peek() == '\n' || inFile.peek() == ' ')
        {
            // ignore To "cleaning tool" that guides the reading indicator to the correct data.
            inFile.ignore();
            continue;
        }
        newStudent = new Student_info;
        if(!(inFile >> newStudent->id))
        {
            delete newStudent;
            break;
        }
        inFile >> comma;
        getline(inFile, newStudent->name, ',');
        inFile >> newStudent->age >> comma;
        inFile >> newStudent->gpa >> comma;
        for(int i = 0; i < 5; i++)
        {
            inFile >> newStudent->grades[i].grades;
            if(i < 4) inFile >> comma;
        }
        inFile.ignore(1000, '\n');
        newStudent->next_pointer = nullptr;
        if(head == nullptr)
        {
            head = newStudent;
        }
        else
        {
            Student_info* temp = head;
            while(temp->next_pointer != nullptr)
            {
                temp = temp->next_pointer;
            }
            temp->next_pointer = newStudent;
        }
    }
    inFile.close();
    cout << " Data Loaded Successfully. \n";
}
// the menu

int main()
{
    int choice;
    do {
        cout << "\n===============================";
        cout << "\n   STUDENT MANAGEMENT SYSTEM   ";
        cout << "\n===============================";
        cout << "\n 1. Add New Student";
        cout << "\n 2. Sort Student List";
        cout << "\n 3. Search For Student";
        cout << "\n 4. Filter by GPA";
        cout << "\n 5. Update Student Info";
        cout << "\n 6. Display All Students";
        cout << "\n 7. Delete Student";
        cout << "\n 8. Save Data";
        cout << "\n 9. Load Data";
        cout << "\n 0. Exit";
        cout << "\n===============================";
        cout << "\n Enter Choice: ";

        choice=Valid_Int();

        switch(choice)
        {

            case 1:Add_Student();
            break;
            case 2:Sort_Student();
            break;
            case 3:Search_Student();
            break;
            case 4:Filter_Students();
            break;
            case 5:Update_Student();
            break;
            case 6:Display_Student();
            break;
            case 7:Delete_Student();
            break;
            case 8:Save_Data();
            break;
            case 9:Load_Data();
            break;
            case 0:
                Free_Memory();
                cout << "\n Exiting System";
                break;

                default: cout << "\n Invalid choice! Please try again.\n";
        }
     }
     while(choice!=0);


    return 0;
}
