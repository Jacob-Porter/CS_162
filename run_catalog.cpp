#include "catalog.h"

using namespace std;


/**************************************************
 * Name: PromptPlayer()
 * Description: Uses functions provided in header and catalog.cpp to display
 * 				options, get user input, do seomthing based on input, and prompt
 * 				again until quited
 * Parameters: Team* - the Team array
 *             int - size of <Team*> array
 *             ofstream& - address of output stream
 * Pre-conditions: <ofstream&> isn't currently open
 * Post-conditions: loops ends when "quit" option is selected (5)
 ***********************************************/
void PromptPlayer(Team* teamArray, int numTeams, ofstream& stream) {

	bool running = true;
	do {

		int option = DisplayOptions();

		if (option == 1){ // team info

			PrintInfo(GetTeam(teamArray, numTeams), DisplayInfo(), stream);
		} else if (option == 2){ // top scorers

			PrintInfo(GetScorers(teamArray, numTeams), DisplayInfo(), stream);
		} else if (option == 3){ // playaer with same nationality

			PrintInfo(GetNation(teamArray, numTeams), DisplayInfo(), stream);
		} else if (option == 4){ // teams PPG

			PrintInfo(GetPPG(teamArray, numTeams), DisplayInfo(), stream);
		} else if (option == 5){ // quit

			running = false;
		}
	} while (running);
} // END FUNC


int main()
{
	// declaration of input/output streams
	ifstream inputStream;
	ofstream outputStream;

	// prompt user for file name to be read (.txt)
	string _fileName;
	cout << "Enter the team info file name: ";
	cin >> _fileName;
	cout << endl;

	// opens file of user-entered _fileName
	inputStream.open(_fileName);

	if (!inputStream.fail()){	// if file was found, else close program

		// init and populate <Team*> array
		int numTeams = 0;
		inputStream >> numTeams;
		Team* teamsArray = create_teams(numTeams);
		populate_team_data(teamsArray, numTeams, inputStream);

		// loop player in program
		PromptPlayer(teamsArray, numTeams, outputStream);

		// empty heap, program closed message
		delete_info(teamsArray, numTeams);
		cout << endl << "Bye, bye :)" << endl << endl;
		
	} else { // user-entered _fileName wasn't found, program closed

		cout << "Error: File not found!" << endl << "program exited" << endl << endl;
	}
} // END FUNC