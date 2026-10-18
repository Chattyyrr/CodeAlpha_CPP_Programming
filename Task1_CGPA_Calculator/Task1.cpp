/*
Internship Task 1: CGPA Calculator
- Take input for the number of courses taken by the student.
- For each course, input the grade and the credit hours.
- Calculate the total credits and total grade points (grade * credit hours).
- Compute the GPA for the semester and then the overall CGPA.
- Display individual course grades and the final CGPA of the user.
*/

#include <iostream>
#include <vector>
#include <iomanip>

struct Course {
    std::string name;
    double gradePoint;
    double creditHours;
};

int main() {
    int numCourses;

    std::cout << "=== CGPA CALCULATOR ===\n";
    std::cout << "Enter the number of courses: ";
    std::cin >> numCourses;

    std::vector<Course> courses(numCourses);
    double totalCredits = 0.0;
    double totalGradePoints = 0.0;

    for (int i = 0; i < numCourses; ++i) {
        std::cout << "\n--- Course " << i + 1 << " ---\n";
        
        std::cout << "Enter course name: ";
        std::cin >> courses[i].name;

        std::cout << "Enter grade points: ";
        std::cin >> courses[i].gradePoint;

        std::cout << "Enter credit hours: ";
        std::cin >> courses[i].creditHours;

        totalCredits += courses[i].creditHours;
        totalGradePoints += courses[i].gradePoint * courses[i].creditHours;
    }

    double cgpa = 0.0;
    if (totalCredits > 0) {
        cgpa = totalGradePoints / totalCredits;
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "Course"
                           << std::setw(15) << "Grade Point"
                           << std::setw(15) << "Credits"
                           << std::setw(15) << "Points"
                                            << '\n';
    std::cout << "------------------------------------------------------------\n";
    
    for (const Course& c : courses) {
        std::cout << std::left << std::setw(15) << c.name
                               << std::setw(15) << c.gradePoint
                               << std::setw(15) << c.creditHours
                               << std::setw(15) << c.gradePoint * c.creditHours
                                                << '\n';
    }

    std::cout << "------------------------------------------------------------\n";

    std::cout << "Total Credits: " << totalCredits << '\n';
    std::cout << "Total Grade Points: " << totalGradePoints << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Final CGPA / GPA: " << cgpa << '\n';

    return 0;
}
