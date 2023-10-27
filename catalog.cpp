#include "catalog.h"

using namespace std;

/**************************************************
 * Name: FloatToString()
 * Description: This function turns a float to a string based on number of decimals (doesn't round)
 * Parameters: float - number to be converted
 *             int - decimal place
 * Pre-conditions: Used in a context that requires a string
 * Post-conditions: Returns a string of the float to the provided decimal place
 ***********************************************/
string FloatToString(float num, int dec) {

    string output = to_string(num);
    int index = 0;

    // find index of decimal point "."
    while(true) {

        if (output[index] != '.') {

            index += 1;
        } else {

            break;
        }
    }

    // return indexed string
    return output.substr(0, index + 1 + dec);

}

/**************************************************
 * Name: ErrorMessage()
 * Description: This function displays an error message to the user and resests "cin"
 * Parameters: string - error message to user to see
 * Pre-conditions: Used in a context that requires a string
 * Post-conditions: Returns a string of the float to the provided decimal place
 ***********************************************/
void ErrorMessage(string message){

    cout << endl << message << endl << endl;     
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
} // END FUNC


// create teams array
Team* create_teams(int numTeams){

  Team* arr = new Team[numTeams];

  return arr;
} // END FUNC

// create players array
Player* create_players(int numPlayers){

  Player* arr = new Player[numPlayers];

  return arr;
} // END FUNC

// fill <Player> with data from file
void populate_player_data(Player* arr, int numPlayers, ifstream& stream){

        for (int i = 0; i < numPlayers; i++) {

            // set player vars
            stream >> arr[i].name;
            stream >> arr[i].age;
            stream >> arr[i].nation;
            stream >> arr[i].ppg;
            stream >> arr[i].fg;
    }
} // END FUNC

// fill <Team> with data from file
void populate_team_data(Team* arr, int numTeams, ifstream& stream){

    for (int i = 0; i < numTeams; i++) {

        // set team vars
        stream >> arr[i].name;
        stream >> arr[i].owner;
        stream >> arr[i].market_value;
        int numPlayers = 0;
        stream >> numPlayers;
        arr[i].num_player = numPlayers;
        arr[i].p = create_players(numPlayers);
        arr[i].total_ppg = 0;

        populate_player_data(arr[i].p, numPlayers, stream);
    }
} // END FUNC

// delete <Team> and <Player> ararys from heap
void delete_info(Team* teamsArr, int numTeams) {

    for (int i = 0; i < numTeams; i++) {

        delete [] teamsArr[i].p;
    }
    delete [] teamsArr;
}  // END FUNC


// displays program options to user and takes in user input
int DisplayOptions () {

    cout << "--------------------------------------------------------------------" << endl;

    string option1 = "1. Search team by its name";
    string option2 = "2. Display the top scorer of each team";
    string option3 = "3. Search players by nationality";
    string option4 = "4. Display teams PPG (descending order)";
    string option5 = "5. Quit";

    int numOptions = 5, input = -1;  

    // get user input
    while (true) {

        cin.clear();

        cout << "Which option would you like to choose?" << endl;
        cout << option1 << endl << option2 << endl << option3 << endl << option4 << endl << option5 << endl << endl;
        cout << "Your choice: "; 

        // if of correct type and within range, return
        if (cin >> input && 0 < input && input <= numOptions){

            cout << endl << "--------------------------------------------------------------------" << endl;
            return input;
        } 

        ErrorMessage("Invalid input, try again.");
    }
}

// displays program output options to user and takes in input
int DisplayInfo () {

    string option1 = "1. Print to screen";
    string option2 = "2. Print to file";

    int numOptions = 2, input = -1;  

    // get user input
    while (true) {

        cin.clear();
        cout << "Which option would you like to choose?" << endl;
        cout << option1 << endl << option2 << endl << endl;
        cout << "Your choice: "; 

        // if of correct type and within range, return
        if (cin >> input && 0 < input && input <= numOptions){

            cout << endl << "--------------------------------------------------------------------" << endl;
            return input;
        } 

        ErrorMessage("Invalid input, try again.");
    }
}

// promts user for a team name and returns a string of the team and its players info
string GetTeam(Team* array, int size) {

    string output = "";
    string input = "";
    int teamIndex = -1;
    bool notFound = true;

    // get user input
    while (notFound) {
        cin.clear();
        cout << "Enter the team's name: ";
        cin >> input;
        cout << endl;

        // finds team with name entered and saves index to be used for output appending
        for (int i = 0; i < size; i++) {

            if (array[i].name == input){
                notFound = false;
                teamIndex = i;
                break;
            }
        }
        if (notFound){

            return "Team not found.\n";
        } 
    }

    // Team info
    output.append("Team Name: " + array[teamIndex].name + " | Owner: " + array[teamIndex].owner + " | Market Value: $" + to_string(array[teamIndex].market_value) + " | Players on team: " + to_string((array[teamIndex].num_player)) + "\n");

    // Player info
    int numPlayers = array[teamIndex].num_player;
    for (int i = 0; i < numPlayers; i++) {

        output.append("Name: " + array[teamIndex].p[i].name + " | Age:  " + to_string(array[teamIndex].p[i].age) + " | Nationality: " + array[teamIndex].p[i].nation + " | PPG: " + FloatToString(array[teamIndex].p[i].ppg, 1) + " | FG: " + FloatToString(array[teamIndex].p[i].fg * 100, 2) + "%\n");

    }

    return output;

} // END FUNC

// returns a string of the top scorers of each team
string GetScorers(Team* array, int size) {

    string output = "";

    // Team for loop
    for (int i = 0; i < size; i ++) {

    int index = -1;
    int highestPPG = -1;
    
        // Player for loop
        for (int j = 0; i < array[i].num_player; i++) {

            if (array[i].p[j].ppg > highestPPG) {
                index = j;
                highestPPG = array[i].p[j].ppg;
            }

            output.append("Team Name: " + array[i].name + " | Player Name: " + array[i].p[index].name + " | PPG: " + FloatToString(array[i].p[index].ppg, 1) + "\n");
        }
    }

    return output;
}

// promts user to enter a nationality and returns string of players the share the users input
string GetNation(Team* array, int size) {

    string output = "";
    string input = "";
    int teamIndex = -1;
    bool notFound = true;

    cout << "Enter the nationality you would like to search for: ";
    cin >> input;
    cout << endl;

    // Team for loop
    for (int i = 0; i < size; i++) {
        int numPlayers = array[i].num_player;

        // Player for loop
        for (int j = 0; j < numPlayers; j++) {

            if (array[i].p[j].nation == input){

                output.append("Player Name: " + array[i].p[j].name + " | Age: " + to_string(array[i].p[j].age) + "\n");
            }
        }
    }

    // if input not found
    if (output == ""){

        return "No players are from \"" + input + "\".\n";
    }

    return output;
} // END FUNC

/**************************************************
 * Name: SortTeams_TotalPPG()
 * Description: This function sorts a <Team*> array by total_ppg in descending order
 * Parameters: Team* - array of <Team>'s
 *             int - size of <Team*> array
 * Pre-conditions: none.
 * Post-conditions: none.
 ***********************************************/
void SortTeams_TotalPPG_Desc(Team* array, int size){

    // bubble sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {

            if (array[j].total_ppg < array[j+1].total_ppg){

                Team temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;

            }
        }
    }
} // END FUNC

// returns string of team names and total_ppg in descending order
string GetPPG(Team* array, int size) {

    string output = "";

    // Team for loop
    for (int i = 0; i < size; i++) {
        int teamPlayers = array[i].num_player;

        // Player for loop
        for (int j = 0; j < teamPlayers; j++) { 

            array[i].total_ppg += array[i].p[j].ppg;
        }
    } 

    // sort teams by total_ppg
    SortTeams_TotalPPG_Desc(array, size);

    // string of teams and thier total_ppg to return
    for (int i = 0; i < size; i++) {

        output.append(to_string(i + 1) + ". " + array[i].name + " | PPG: " + FloatToString(array[i].total_ppg, 1) + "\n");
    }

    return output;
}

// displays info to desired location based on user input (option)
void PrintInfo(string toPrint, int option, ofstream& stream){

    // print to file
    if (option == 2) {
    
    // user input
    string input = "";
    cout << "Please provide desired filename (include \".txt\"): ";
    cin >> input;
    cout << endl;

    // create/append file
    stream.open(input, ios::app);
    stream << toPrint << endl << endl;
    cout << "File appended" << endl << endl;
    stream.close();

    return;
    }

    // print to screen
    cout << toPrint << endl;
} // END FUNC
