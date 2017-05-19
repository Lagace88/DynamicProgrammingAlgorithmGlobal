// Tyler Lagace
// CSC - 314
// Final Project - Option A - Number 2

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

// Functions

// Menus
vector<string> MainMenu();
int AlignmentMenu();

// Sequence retrival
vector<string> ReadFromOneFile();
vector<string> ReadFromTwoFiles();
vector<string> EnterManually();
vector<string> GetSequences(string fileName);
vector<string> GetSequences(string fileNameOne, string fileNameTwo);
string CleanSequence(string sequence);

// Dynamic Programming Work
int DynamicProgrammingAlgorithm(int matrix[300][300][2], int x, int y, vector<string> sequences);
int GapColumn(int score);
int GapRow(int score);
int MatchMissmatch(int score, vector<string> sequences, int x, int y);

// Alignment Work
void GlobalWork(vector<string> sequences);
vector<string> Traceback(int matrix[300][300][2], vector<string> sequences, int optimalX, int optimalY);
string Reverse(string work);

// Display
void DisplayResults(int OptimalAlignmentScore, vector<string> sequences);

int main() {
	vector<string> sequences;
	string test;

start:
	sequences = MainMenu();

	// If the user backed out, restart MainMenu
	while (sequences.size() < 2) {
		// If the user wishes to exit
		if (sequences[0] == "Exit") {
			return 0;
		}
		if (sequences[0] == "0") {
			sequences.clear();
			goto start;
		}
		if (sequences[0] == "Not Found") {
			sequences.clear();
			goto start;
		}
	}

	GlobalWork(sequences);

	return 0;
}

// Menus

vector<string> MainMenu() {
	// Main Menu
	int selection = 0;
	vector<string> sequences;

	// Clear Consol
	system("cls");

	cout << string(20, ' ') << "Welcome to the Global Optimal Pairwise Alignment Application" << endl;
	cout << string(37, ' ') << "Programed by: Tyler Lagace\n" << endl;
	cout << string(45, ' ') << "Main Menu\n" << endl;
	cout << string(20, ' ') << string(60, '-') << endl << endl;
	cout << string(30, ' ') << "(1) Upload Sequences From One File" << endl;
	cout << string(30, ' ') << "(2) Upload Sequences From Two Different Files" << endl;
	cout << string(30, ' ') << "(3) Enter Sequences Manually" << endl;
	cout << string(30, ' ') << "(4) Exit\n" << endl;
	cout << string(30, ' ') << "Selection: ";
	cin >> selection;
	while (selection != 1 && selection != 2 && selection != 3 && selection != 4) {
		cout << "Please enter a valid selection." << endl;
		cout << "Selection: ";
		cin >> selection;
	}

	switch (selection) {

	case 1:
		sequences = ReadFromOneFile();
		break;

	case 2:
		sequences = ReadFromTwoFiles();
		break;

	case 3:
		sequences = EnterManually();
		break;
	case 4:
		sequences.push_back("Exit");
		break;
	}

	return sequences;
}

// Sequence retrival

vector<string> ReadFromOneFile() {
	string fileName = "";
	vector<string> sequences;

	// Clear Consol
	system("cls");

	cout << string(35, ' ') << "Read In Sequences From One File\n" << endl;
	cout << string(30, ' ') << string(41, '-') << endl << endl;
	while (fileName.length() < 5) {
		cout << string(25, ' ') << "Please enter the text file name that contains the" << endl;
		cout << string(25, ' ') << "sequences or enter 0 to go back: ";
		cin >> fileName;

		if (fileName == "0") {
			// Clear Consol
			system("cls");

			sequences.push_back("0");
			return sequences;
		}

		if (fileName.length() >= 5) {
			// Will automaticaly add the .txt file extention if the user has not.
			if (fileName.substr(fileName.length() - 4) != ".txt")
			{
				fileName += ".txt";
			}
		}
		else {
			// File entry must be at least five chars long. Example: a.txt
			cout << "\n" << string(25, ' ') << "The file must be at least five characters long in order to be a vaild file." << endl;
			cout << string(25, ' ') << "Be sure to include the file extention .txt if you have not.\n" << endl;
		}
	}

	// This will retrive the sequences.
	sequences = GetSequences(fileName);

	return sequences;
}

vector<string> ReadFromTwoFiles() {
	string fileNameOne = "";
	string fileNameTwo = "";
	vector<string> sequences;

	// Clear Consol
	system("cls");

	cout << string(25, ' ') << "Read In Sequences From Two Seperate Files" << endl;
	cout << string(20, ' ') << string(51, '-') << endl;
	// Get first file name
	while (fileNameOne.length() < 5) {
		cout << endl << string(20, ' ') << "Please enter the text file name for the first file" << endl;
		cout << string(20, ' ') << "that contains the sequences or enter 0 to go back: ";
		cin >> fileNameOne;

		if (fileNameOne == "0") {
			sequences.push_back("0");
			system("cls");
			return sequences;
		}

		if (fileNameOne.length() >= 5) {
			// Will automaticaly add the .txt file extention if the user has not.
			if (fileNameOne.substr(fileNameOne.length() - 4) != ".txt")
			{
				fileNameOne += ".txt";
			}
		}
		else {
			// File entry must be at least five chars long. Example: a.txt
			cout << endl << string(20, ' ') << "The file must be at least five characters long in order to be" << endl;
			cout << string(20, ' ') << "a vaild file. Be sure to include the file extention .txt if you have not." << endl;
		}
	}

	// Get second file name
	while (fileNameTwo.length() < 5) {
		cout << endl << string(20, ' ') << "Please enter the text file name for the next file" << endl;
		cout << string(20, ' ') << " that contains the sequences or enter 0 to go back: ";
		cin >> fileNameTwo;

		if (fileNameTwo == "0") {
			sequences.push_back("0");
			system("cls");
			return sequences;
		}

		if (fileNameTwo.length() >= 5) {
			// Will automaticaly add the .txt file extention if the user has not.
			if (fileNameTwo.substr(fileNameTwo.length() - 4) != ".txt")
				fileNameTwo += ".txt";
		}
		else {
			// File entry must be at least five chars long. Example: a.txt
			cout << endl << string(20, ' ') << "The file must be at least five characters long in order to be a vaild file." << endl;
			cout << string(20, ' ') << "Be sure to include the file extention .txt if you have not." << endl;
		}
	}

	sequences = GetSequences(fileNameOne, fileNameTwo);

	return sequences;
}

vector<string> EnterManually() {
	vector<string> sequences;
	string sequence;
	char correct = 'n';

	system("cls");

	cout << string(35, ' ') << "Enter Sequences Manually\n" << endl;
	cout << string(30, ' ') << string(35, '-') << endl;

	// Collect first sequence
	while (correct == 'n') {
		cout << endl << string(32, ' ') << "Please enter the first sequence: ";
		cin >> sequence;

		sequence = CleanSequence(sequence);

		cout << string(32, ' ') << "Is " << sequence << " correct?(y/n): ";
		cin >> correct;
		correct = tolower(correct);
		while (correct != 'n' && correct != 'y') {
			cout << string(32, ' ') << "Please enter a valid option (y/n): ";
			cin >> correct;
			correct = tolower(correct);
		}
	}

	sequences.push_back(sequence);
	sequence = "";
	correct = 'n';

	// Collect second sequence
	while (correct == 'n') {
		cout << endl << string(32, ' ') << "Please enter the second sequence: ";
		cin >> sequence;

		sequence = CleanSequence(sequence);

		cout << string(32, ' ') << "Is " << sequence << " correct?(y/n): ";
		cin >> correct;
		correct = tolower(correct);
		while (correct != 'n' && correct != 'y') {
			cout << string(32, ' ') << "Please enter a valid option (y/n): ";
			cin >> correct;
			correct = tolower(correct);
		}
	}

	sequences.push_back(sequence);

	return sequences;
}

vector<string> GetSequences(string fileName) {
	// Open file and collect data.
	vector<string> sequences;
	string sequence;

	ifstream File(fileName);

	if (File.is_open()) {
		string line;

		while (getline(File, line)) {
			if (line.substr(0, 1) != ">" && line.substr(0, 1) != "") {
				// Not a header, add to sequence
				sequence += line;
			}
			else {
				if (sequence != "") {
					sequences.push_back(sequence);
					sequence = "";
				}
			}
		}
	}
	else {
		cout << endl << string(25, ' ') << fileName << " could not be found.\n" << endl;
		cout << string(25, ' ') << "Please hit any key to continue..." << endl;
		sequences.push_back("Not Found");
		while (!_kbhit()) {
			// Wait for user to hit a key.
		}

		return sequences;
	}

	File.close();

	for (unsigned int x = 0; x < sequences.size(); x++) {
		sequences[x] = CleanSequence(sequences[x]);
	}
	return sequences;
}

vector<string> GetSequences(string fileNameOne, string fileNameTwo) {
	// Open files and collect data.
	vector<string> sequences;
	string sequence;

	ifstream FileOne(fileNameOne);

	if (FileOne.is_open()) {
		string line;
		while (getline(FileOne, line)) {
			if (line.substr(0, 1) != ">" && line.substr(0, 1) != "") {
				// Not a header, add to sequence
				sequence += line;
			}
			else if (sequence != "") {
				sequences.push_back(sequence);
				sequence = "";
			}
		}
	}
	else {
		cout << "\n" << string(25, ' ') << fileNameOne << " could not be found.\n" << endl;
		cout << string(25, ' ') << "Please hit and key to continue..." << endl;
		sequences.push_back("Not Found");
		while (!_kbhit()) {
			// Wait for user to hit a key.
		}

		return sequences;
	}

	FileOne.close();

	ifstream FileTwo(fileNameTwo);

	if (FileTwo.is_open()) {
		string line;
		while (getline(FileTwo, line)) {
			if (line.substr(0, 1) != ">" && line.substr(0, 1) != "") {
				// Not a header, add to sequence
				sequence += line;
			}
			else if (sequence != "") {
				sequences.push_back(sequence);
				sequence = "";
			}
		}
	}
	else {
		cout << "\n" << string(25, ' ') << fileNameTwo << " could not be found.\n" << endl;
		cout << string(25, ' ') << "Please hit any key to continue..." << endl;
		sequences.clear();
		sequences.push_back("Not Found");
		while (!_kbhit()) {
			// Wait for user to hit a key.
		}

		return sequences;
	}

	FileTwo.close();

	for (unsigned int x = 0; x < sequences.size(); x++) {
		sequences[x] = CleanSequence(sequences[x]);
	}

	return sequences;
}

string CleanSequence(string sequence) {
	// Will convert each char to lowercase and make sure each
	// char is valid

	for (unsigned int x = 0; x < sequence.length(); x++) {
		// Check to make sure char is a letter
		if (isalpha(sequence[x])) {
			sequence[x] = tolower(sequence[x]);
			// Check to make sure it is a valid amino acid code
			// http://zhanglab.ccmb.med.umich.edu/FASTA/
			if (sequence[x] == 'j' || sequence[x] == 'o') {
				// # will represent an invalid character
				sequence[x] = '#';
			}
		}
		else {
			sequence[x] = '#';
		}
	}

	return sequence;
}

// Dynamic Programming Work

void GlobalWork(vector<string> sequences) {
	// We create our matrix here, the first two are for the cordinets.
	// The third will keep track of score and where the score came from.
	// 0 = mismatch 1 = match 2 = column gap 3 = row gap
	int matrix[300][300][2];
	matrix[0][0][0] = 0;

	for (unsigned int x = 1; x <= sequences[0].size(); x++) {
		// Insert initial gap penalties for column
		matrix[0][x][0] = matrix[0][x - 1][0] - 4;
		matrix[0][x][1] = 2;
	}

	for (unsigned int x = 1; x <= sequences[1].size(); x++) {
		// Insert inistial gap penalties for row
		matrix[x][0][0] = matrix[x - 1][0][0] - 4;
		matrix[x][0][1] = 3;
	}

	// Fill matrix 
	for (unsigned int x = 1; x <= sequences[1].size(); x++) {
		for (unsigned int y = 1; y <= sequences[0].size(); y++) {
			matrix[x][y][0] = DynamicProgrammingAlgorithm(matrix, x, y, sequences);
		}
	}

	vector<string> Alignment = Traceback(matrix, sequences, sequences[0].size(), sequences[1].size());
	DisplayResults(matrix[sequences[1].size()][sequences[0].size()][0], Alignment);
}

int DynamicProgrammingAlgorithm(int matrix[300][300][2], int x, int y, vector<string> sequences) {
	int score;

	score = max(GapColumn(matrix[x - 1][y][0]), GapRow(matrix[x][y - 1][0]));
	if (GapColumn(matrix[x - 1][y][0]) > GapRow(matrix[x][y - 1][0])) {
		matrix[x][y][1] = 2;
	}
	else {
		matrix[x][y][1] = 3;
	}
	if (MatchMissmatch(matrix[x - 1][y - 1][0], sequences, x, y) > score) {
		if (MatchMissmatch(matrix[x - 1][y - 1][0], sequences, x, y) > matrix[x - 1][y - 1][0]) {
			matrix[x][y][1] = 1;
		}
		else {
			matrix[x][y][1] = 0;
		}
	}
	score = max(score, MatchMissmatch(matrix[x - 1][y - 1][0], sequences, x, y));

	return score;
}

int GapColumn(int score) {
	score = score - 4;

	return score;
}

int GapRow(int score) {
	score = score - 4;

	return score;
}

int MatchMissmatch(int score, vector<string> sequences, int x, int y) {
	// If a match
	if (sequences[1][x - 1] == sequences[0][y - 1] && sequences[1][x - 1] != '#') {
		score = score + 3;
	}
	// If mismatch
	else {
		score = score - 1;
	}

	return score;
}

void DisplayResults(int OptimalAlignmentScore, vector<string> Alignment) {
	// Display the results.
	system("cls");

	cout << string(30, ' ') << "The Optimal Alignment Score is: " << OptimalAlignmentScore << endl;
	cout << string(30, ' ') << "The Optimal Alignment" << endl;
	cout << string(20, ' ') << string(50, '-') << endl;

	int x = 0;
	cout << string(20, ' ');
	// We display in increaments of 50 here to a total of 150,
	// as the criteria states that sequences won't be over 100.

	while (x <= 50 && x < Alignment[2].size()) {
		cout << Alignment[2][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 0;

	while (x <= 50 && x < Alignment[1].size()) {
		cout << Alignment[1][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 0;

	while (x <= 50 && x < Alignment[0].size()) {
		cout << Alignment[0][x];
		x++;
	}

	cout << endl << endl << string(20, ' ');
	x = 50;

	while (x <= 100 && x < Alignment[2].size()) {
		cout << Alignment[2][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 50;

	while (x <= 100 && x < Alignment[1].size()) {
		cout << Alignment[1][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 50;

	while (x <= 100 && x < Alignment[0].size()) {
		cout << Alignment[0][x];
		x++;
	}

	cout << endl << endl << string(20, ' ');
	x = 100;

	while (x <= 150 && x < Alignment[2].size()) {
		cout << Alignment[2][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 100;

	while (x <= 150 && x < Alignment[1].size()) {
		cout << Alignment[1][x];
		x++;
	}

	cout << endl << string(20, ' ');
	x = 100;

	while (x <= 150 && x < Alignment[1].size()) {
		cout << Alignment[0][x];
		x++;
	}

	cout << endl << string(20, ' ') << "Press any key to exit.";
	while (!_kbhit()) {

	}
}

vector<string> Traceback(int matrix[300][300][2], vector<string> sequences, int optimalX, int optimalY) {
	// Strings used to hold alignment sequences
	string topAlignment = "";
	string middleAlignment = "";
	string bottomAlignment = "";
	// Vector to hold all strings
	vector<string> Alignment;

	int x = optimalX;;
	int y = optimalY;

	while (x > 0 || y > 0) {
		cout << matrix[y][x][1] << endl;
		switch (matrix[y][x][1]) {
		case 0:
			// Missmatch
			bottomAlignment += sequences[1][y - 1];
			middleAlignment += " ";
			topAlignment += sequences[0][x - 1];
			x = x - 1;
			y = y - 1;
			break;
		case 1:
			// Match
			bottomAlignment += sequences[1][y - 1];
			middleAlignment += "|";
			topAlignment += sequences[0][x - 1];
			x = x - 1;
			y = y - 1;
			break;
		case 2:
			// Column Gap
		columngap:
			if (y == 0) {
				goto rowgap;
			}
			bottomAlignment += sequences[1][y - 1];
			middleAlignment += " ";
			topAlignment += "-";
			y = y - 1;
			break;
		case 3:
			// Row Gap
		rowgap:
			if (x == 0) {
				goto columngap;
			}
			bottomAlignment += "-";
			middleAlignment += " ";
			topAlignment += sequences[0][x - 1];
			x = x - 1;
			break;
		}
	}

	// Reverse strings so the read display in the right order.
	bottomAlignment = Reverse(bottomAlignment);
	middleAlignment = Reverse(middleAlignment);
	topAlignment = Reverse(topAlignment);

	Alignment.push_back(bottomAlignment);
	Alignment.push_back(middleAlignment);
	Alignment.push_back(topAlignment);

	return Alignment;
}

string Reverse(string work) {
	string temp = work;
	for (int x = 0; x < work.length(); x++) {
		work[x] = temp[temp.length() - 1 - x];
	}

	return work;
}
