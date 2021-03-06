// NaffaaOmar_Project1.cpp

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

struct Student {
	int identification;
	char grade;
	double score;
};

double DetermineMean(Student mArray[], int SIZE);
double StdDeviation(Student mArray[], int SIZE, double mean);
void AssignInformation(Student mArrayOne[], Student mArraytwo[], int sizeOne, int sizeTwo);
void AssignGrade(Student mArray[], int SIZE, double mean, double deviation);
void OutputData(Student s1[], Student s2[], int sizeOne, int sizeTwo, double meanOne, double meanTwo, double deviationOne, double deviationTwo);
void WriteData(Student s1[], Student s2[], int sizeOne, int sizeTwo, double meanOne, double meanTwo, double deviationOne, double deviationTwo);

int main()
{
	// Create dynamic arrays for session 1 and session 2 using Student struct
	Student* session1_students;
	Student* session2_students;

	int sOneSize = 44;
	int sTwoSize = 38;

	session1_students = new Student[sOneSize];
	session2_students = new Student[sTwoSize];

	// Assign the student identification as well as the grades for each section
	AssignInformation(session1_students, session2_students, sOneSize, sTwoSize);

	// Determine the mean for each section
	double meanOne = DetermineMean(session1_students, sOneSize);
	double meanTwo = DetermineMean(session2_students, sTwoSize);

	// Calculate the standard deviation for each section
	double stdDevOne = StdDeviation(session1_students, sOneSize, meanOne);
	double stdDevTwo = StdDeviation(session2_students, sTwoSize, meanTwo);

	// Assign the students a grade based on their section mean and standard deviation
	AssignGrade(session1_students, sOneSize, meanOne, stdDevOne);
	AssignGrade(session2_students, sTwoSize, meanTwo, stdDevTwo);

	// Output the data to the console and write it to a .txt file
	OutputData(session1_students, session2_students, sOneSize, sTwoSize, meanOne, meanTwo, stdDevOne, stdDevTwo);
	WriteData(session1_students, session2_students, sOneSize, sTwoSize, meanOne, meanTwo, stdDevOne, stdDevTwo);

    return 0;
}

void AssignInformation(Student mArrayOne[], Student mArrayTwo[], int sizeOne, int sizeTwo) {

	time_t _time;
	srand((unsigned) time(&_time));
	double randScores;

	// iterate through each student in session 1
	for (int i = 0; i < sizeOne; i++) {

		randScores = rand() % (100 + 1 - 50) + 50; // random number between 50 - 100 inclusive
		mArrayOne[i].identification = i; // assign a student number
		mArrayOne[i].score = randScores; // assign a student grade

	}

	// iterate through each student in session 2
	for (int j = 0; j < sizeTwo; j++) {

		randScores = rand() % (100 + 1 - 50) + 50; // random number between 50 - 100 inclusive
		mArrayTwo[j].identification = j; // assign a student number
		mArrayTwo[j].score = randScores; // assign a student grade

	}

}

void AssignGrade(Student mArray[], int SIZE, double mean, double deviation) {

	for (int i = 0; i < SIZE; i++) {

		if ((mean + (3/2)*deviation) <= mArray[i].score) {
			mArray[i].grade = 'A';
		}
		else if ((mean + (1/2)*deviation) <= mArray[i].score && mArray[i].score < (mean + (3/2)*deviation)) {
			mArray[i].grade = 'B';
		}
		else if ((mean - (1/2)*deviation) <= mArray[i].score && mArray[i].score < (mean + (1/2)*deviation)) {
			mArray[i].grade = 'C';
		}
		else if ((mean - (3/2)*deviation) <= mArray[i].score && mArray[i].score < (mean - (1/2)*deviation)) {
			mArray[i].grade = 'D';
		}
		else {
			mArray[i].grade = 'F';
		}

	}

}

double DetermineMean(Student mArray[], int SIZE) {

	double scoreTotal = 0;

	// get the total grade
	for (int i = 0; i < SIZE; i++)
		scoreTotal += mArray[i].score;

	// divide the grade by the number of students to get the mean
	return (scoreTotal / SIZE);

}

double StdDeviation(Student mArray[], int SIZE, double mean)
{
	double sum = 0;
	double stdDev = 0;

	// for each student subtract their grade from the mean and square it
	for (int i = 0; i < SIZE; i++)
		sum += (mArray[i].score - mean) * (mArray[i].score - mean);

	// calculate and return the standard deviation
	stdDev = sqrt(sum / SIZE);
	return stdDev;
}

void OutputData(Student s1[], Student s2[], int sizeOne, int sizeTwo, double meanOne, double meanTwo, double deviationOne, double deviationTwo) {

	// section 1 console output
	cout << "Section 1:" << endl;
	cout << "Mean: " << meanOne << ", Standard Deviation: " << deviationOne << endl;

	for (int i = 0; i < sizeOne; i++)
		cout << left << setw(12) << "Student ID:" << setw(6) << s1[i].identification << setw(6) << "Score:" << setw(6) << s1[i].score << setw(14) << "Letter Grade: " << s1[i].grade << endl;

	// section 2 console output
	cout << "\nSection 2:\n";
	cout << "Mean: " << meanTwo << ", Standard Deviation: " << deviationTwo << endl;

	for (int j = 0; j < sizeTwo; j++)
		cout << left << setw(12) << "Student ID:" << setw(6) << s2[j].identification << setw(6) << "Score:" << setw(6) << s2[j].score << setw(14) << "Letter Grade: " << s2[j].grade << endl;

	cout << endl; // spacing

}

void WriteData(Student s1[], Student s2[], int sizeOne, int sizeTwo, double meanOne, double meanTwo, double deviationOne, double deviationTwo) {

	// Create the .txt document to store the session data
	ofstream dataFile("Session_Information.txt");

	// Write the information to the file
	dataFile << "Section 1:" << endl;
	dataFile << "Mean: " << meanOne << ", Standard Deviation: " << deviationOne << endl;

	for (int i = 0; i < sizeOne; i++)
		dataFile << left << setw(12) << "Student ID:" << setw(6) << s1[i].identification << setw(6) << "Score:" << setw(6) << s1[i].score << setw(14) << "Letter Grade: " << s1[i].grade << endl;

	dataFile << "\nSection 2:" << endl;
	dataFile << "Mean: " << meanTwo << ", Standard Deviation: " << deviationTwo << endl;

	for (int j = 0; j < sizeTwo; j++)
		dataFile << left << setw(12) << "Student ID:" << setw(6) << s2[j].identification << setw(6) << "Score:" << setw(6) << s2[j].score << setw(14) << "Letter Grade: " << s2[j].grade << endl;

	dataFile.close();

}