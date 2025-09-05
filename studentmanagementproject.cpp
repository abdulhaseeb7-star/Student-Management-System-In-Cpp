#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    float marks[3]; // marks for 3 subjects
};

// Function to input student data
void input(Student s[], int n) {
    cin.ignore(); // clear buffer before getline
    for (int i = 0; i < n; i++) {
        cout << "------- Enter the details of student " << i + 1 << " -------" << endl;

        cout << "Enter the name: ";
        getline(cin, s[i].name);

        cout << "Enter the ID: ";
        cin >> s[i].id;

        for (int j = 0; j < 3; j++) {
            cout << "Enter marks for subject " << j + 1 << ": ";
            cin >> s[i].marks[j];
        }
        cin.ignore(); // clear buffer for next getline
    }
}

// Function to display student data
void output(Student s[], int n) {
    cout << "\n------- Student Details -------" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: " << s[i].name << endl;
        cout << "ID: " << s[i].id << endl;
        cout << "Marks: ";
        for (int j = 0; j < 3; j++) {
            cout << s[i].marks[j] << (j < 2 ? ", " : "");
        }
        cout << endl;
    }
}

// Helper to calculate total marks of a student
float totalMarks(const Student &st) {
    float sum = 0;
    for (int j = 0; j < 3; j++) sum += st.marks[j];
    return sum;
}

// Function to find student with highest total marks
int compare(Student s[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (totalMarks(s[i]) > totalMarks(s[index])) {
            index = i;
        }
    }
    return index;
}

// Function to save student data into a file
void saveToFile(Student s[], int n) {
    ofstream file("students.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        file << "Student " << i + 1 << ":\n";
        file << "Name: " << s[i].name << "\n";
        file << "ID: " << s[i].id << "\n";
        file << "Marks: ";
        for (int j = 0; j < 3; j++) {
            file << s[i].marks[j] << (j < 2 ? ", " : "");
        }
        file << "\nTotal Marks: " << totalMarks(s[i]) << "\n\n";
    }

    file.close();
    cout << "Data saved successfully in students.txt!" << endl;
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    Student *s = new Student[n]; // dynamic memory allocation

    int option;
    do {
        cout << "\n------ MENU ------" << endl;
        cout << "1. Enter student data" << endl;
        cout << "2. Display all students" << endl;
        cout << "3. Find student with highest total marks" << endl;
        cout << "4. Save student data into a file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1:
                input(s, n);
                break;
            case 2:
                output(s, n);
                break;
            case 3: {
                int topperIndex = compare(s, n);
                cout << "\nThe student with the highest marks is: "
                     << s[topperIndex].name << " (ID: " << s[topperIndex].id
                     << ") with total " << totalMarks(s[topperIndex]) << " marks.\n";
                break;
            }
            case 4:
                saveToFile(s, n);
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (option != 5);

    delete[] s; // free memory
    return 0;
}
