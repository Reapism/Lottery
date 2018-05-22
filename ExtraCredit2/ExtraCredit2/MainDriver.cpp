/*
Extra Credit: 2
I just wanted to explore a bit more with this program.
Used pointers, overloaded functions, thread sleeping, and one of my randomization
methods used in my other personal project RSG.

@author: Anthony Jaghab
*/

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <windows.h>

using namespace std;

// instance variables

const int LOTTERY_SIZE = 7; // the number lottery numbers to play, can change to anything
// and program will handle any integer from (INT_MAX / 2) - 1 because the same vector
// is used for the guesses.

// prototypes
void seedRnd();
void menu();
void playLottery(bool);
void playLottery();
void inputLottery(vector<int>&, const int*);
vector<bool> checkLottery(vector<int>, const int*);
void sort(vector<int>&, const int*);

/*
Seeds the rand() function with the current computer time 
(common practice for c++).
*/
void seedRnd() {
	srand(time(NULL));
}

/*
Display a menu
*/
void menu() {
	system("CLS");
	system("Color 74");

	cout << " Do you want to play the lottery?\n";
	cout << "\n\n Enter 0-2 (0 no, 1 yes, 2 much more random): ";

	// gets input
	int in = NULL;
	cin >> in;
	
	switch (in) {
	case 0:	
		exit(0);
		break;	
	case 1:
		playLottery(); // defualt function
		break;
	case 2: 
		playLottery(true); // overloaded function
		break;
	default:
		exit(0); // else break
		break;
	}
}

/*
Adds random numbers to a vector and then
sorts and asks user for their numbers of
LOTTERY_SIZE times by reseeding every iteration
*/
void playLottery(bool veryRandom) {
	system("CLS");
	system("Color 72");

	vector<int> rndNum;
	seedRnd();
	for (int i = 0; i < LOTTERY_SIZE; i++) {
		seedRnd(); // seed the rand() function every iteration
		int r = rand() % 21; // between 0-RAND_MAX, returns 0-20
		if (r == 0) r = 1; // change 0 to 1
		rndNum.push_back(r); // return 1-20
		Sleep(1000); // pauses main execution thread 1 second to ensure new time() for seedRnd()
		cout << " Generate " << " number " << i + 1 << ". Using reap-random. Waits a second.\n";

	}

	sort(rndNum, &LOTTERY_SIZE); // sort the random numbers in the vector
	inputLottery(rndNum, &LOTTERY_SIZE); // add the input number to the same vector
}

/*
Adds random numbers to a vector and then
sorts and asks user for their numbers of
LOTTERY_SIZE times.
*/
void playLottery() {
	system("CLS");
	system("Color 72");
	
	seedRnd(); // seed the rand() function

	vector<int> rndNum;

	for (int i = 0; i < LOTTERY_SIZE; i++) {
		int r = rand() % 21; // between 0-RAND_MAX, returns 0-20
		if (r == 0) r = 1; // change 0 to 1
		rndNum.push_back(r); // return 1-20
	}

	sort(rndNum, &LOTTERY_SIZE); // sort the vector to LOTTERY_SIZE elements
	inputLottery(rndNum, &LOTTERY_SIZE);
}

/*
Sorts an int vector ascendinging using bubble sort.
*/
void sort(vector<int>& v, const int* size) {
	int in, out, oldTmp; // inner, outer loop for bubble sort.

	for (out = *size - 1; out > 0; out--) { // OUTER LOOP: starts from end
		for (in = 0; in < out; in++) { // INNER LOOP: starts from beginning 
			if (v[in] > v[in + 1]) {
				// swap old
				oldTmp = v[in];
				v[in] = v[in + 1];
				v[in + 1] = oldTmp;
			}
		}
	}
}

/*
Takes int number of inputs you want to make in pointer form.
*/
void inputLottery(vector<int>& v, const int* size) {
	system("CLS");
	system("Color 72");

	int in; // input 
	
	for (int i = 0; i < *size; i++) { // loop through the playing size 7 times.
		cout << " Please enter a number  1-20: ";
		cin >> in;
	
		while (in < 1 || in > 20) { // if out of range
			cout << in << " is not a valid number... enter 1-20: ";
			cin >> in;
		}
			v.push_back(in); // if while loop is escaped, add the element to vector	
	}

	system("CLS");
	system("Color 72");

	vector<bool> b = checkLottery(v, size); // create boolean vector [b] and set it to the result of checkLottery
	int i = 0, numWrong = 0; // iterator, and number of wrong guesses

	for (bool c : b) {
		//output whether the guess was correct or incorrect
		if (c == true) {
			cout << " Number " << i + 1 << " was " << v[i] << ". --> You picked : " << v[i + *size] << " RIGHT :]\n"; // uses same vector to store the guesses
		} else {
			cout << " Number " << i + 1 << " was " << v[i] << ". --> You picked : " << v[i + *size] << " WRONG :[\n";
			numWrong++; // add number of wrong guesses
		}
		i++;

	}
	// determines if you won or not based on numWrongs value
	if (numWrong > 0) {
		cout << "\n\n You've lost because you got " << numWrong << " guesses wrong! :[";
	} else {
		cout << "\n\n YOU WON!!!" << "The chances are 1 / 20^7.";
		}

	cout << "\n\n Play again? Enter 0 for no, 1 for yes! ";
	short play = 0;
	cin >> play;

	// if user selects one, call menu, else exit program.
	if (play == 1) menu(); else exit(0);

}

/*
Checks a <int> vector and returns another vector with type
bool to see if v[i] == v[i + *size]
*/
vector<bool> checkLottery(vector<int> v, const int* size) {
	vector <bool> b; // new bool vector

	for (int i = 0; i < *size; i++) { // iterate through parameter vector
		if (v[i] == v[i + *size]) { // check to see if v[i] == v[i + Size elements]
			b.push_back(true); // add a true bool
		} else {
			b.push_back(false); // add a false bool
		}
	}

	return b; // returns the new vector
}

/*
Driver function
*/
int main() {
	menu(); // all you need to start this program.
}