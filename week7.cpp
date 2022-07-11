#include<iostream>
#include<string>
#include<fstream>

// Tausif Hussan - This code will calculate a bowling leagues average bowling scores from a txt file using 3 arrays. This will calculate average scores from 5 attempts

using namespace std;

#define MAX_PLAYERS 10 
//constant for the player array
#define MAX_SCORES 5 
//constant for the score array

struct player {
	string playerName;
	int scores[MAX_SCORES];
	int avgScore;
};

//Read the file and retun the player names, scores, count of the player and count of the scores. First the getline function
//is used to get the line from the file and after it I make the string line to stream. After this the for loop is used allong with
// if and else to split the data to read the data upto each space. The score number and player count is used to track the number
//of player inside the array and number of scores for each player
bool GetBowlingData(string filename, player *players, int* playerCount, int* scoreCount) {
	ifstream stream;
	string line;
	*scoreCount = 0; //setting the score count to zero
	*playerCount = 0; //setting the player count zero

	stream.open(filename, ios::in); //opening the file

	if (!stream.good()) { //if can not open the file
		return false;
	}

	while (getline(stream, line)) { //read the lines from the file
		string data = ""; //data variable to store the word in the variable
		bool isName = true; //to check if there is name data or the score data
		*scoreCount = 0; //keeping count of the scores
		for (int i = 0; i < line.size(); i++) { //loop over the complete line
			if (line[i] == ' ' || i == (line.size()-1)) { //if the current char is ' ' or it is the last char then we need to add the data
				if (isName) { 
					players[*playerCount].playerName = data; //if it is the name
					data = ""; //reset data
					isName = false; //all next data should be score
				}
				else {
					if (i == (line.size() - 1)) { //if it is last char
						data += line[i]; //read the last char
					}
					players[*playerCount].scores[*scoreCount] = stoi(data); //add to the ith player jth score
					(*scoreCount)++; //add the count
					data = "";
				}
			}
			else {
				data += line[i]; //append the char to data to make the string
			}
		}

		(*playerCount)++;
	}

	return true; //return true if all is well
}

//calculates the average scores from the player score array and store it in the average score of each player in the array.
// The player count and score count is also passed so we can know how much players are in the array and what are the score 
// counts. After this for each player the score is summed up and 
//divided by the score count to get the average for each player and then it is stored to the average array. The average array
//has same index 'i' for the perticular ith player.
void GetAverageScore(player *players, int playerCount, int scoreCount) {
	int avg = 0;
	for (int i = 0; i < playerCount; i++) { //loop over all the players
		avg = 0; //reset the average for next player
		for (int j = 0; j < scoreCount; j++) { //loop over all the scores of player 'i'
			avg += players[i].scores[j]; //add the score to calculate the sum
		}

		players[i].avgScore = avg /(float) scoreCount; //calculate average for player 'i'
	}
}

//simply print the player name and average score by visiting each player and average data.
void PrettyPrintResults(player *players, int playerCount) {
	cout << "***Average Player Scores***" << endl;

	for (int i = 0; i < playerCount; i++) { //loop over the players 
		cout << "Player Name: " << players[i].playerName << " Average Score: " << players[i].avgScore << endl; //display the average and name of player 'i'
	}
}

int main() {
	//arrays to store the data
	player players[MAX_PLAYERS];
	int playerCount = 0;
	int scoreCount = 0;

	//calling the functions
	bool result = GetBowlingData("BowlingScores.txt", players, &playerCount, &scoreCount);
	GetAverageScore(players, playerCount, scoreCount);
	PrettyPrintResults(players, playerCount);
	
	return 0;
}
