/*********************************************************************
** Program Filename: Basketball_Sim.cpp
** Author: Jacob Porter
** Date: 10/9/23
** Description: Simulates the NBA 3 point contest. User can enter 
                number of players and during each players turn they can
                choose a "money rack". After every players rack is simulated,
                a winner is decided and the user gets prompted to play again.
** Input: Number of players (int), moneyball rack position (int), play again (int).
** Output: Simmed rack results, winner, player again prompt
*********************************************************************/

#include <iostream>
#include <ctime>
#include <limits>

using namespace std;


/*********************************************************************
** Function: SimShot()
** Description: Simulates the basketball shot, 50/50 chance.
** Parameters: None.
** Pre-Conditions: Random seed is reset prior for variety of return value.
** Post-Conditions: Returns 1 for shot made, and 0 for shot missed.
*********************************************************************/
// Simulate shot
bool SimShot(){

    // 50/50 (0-miss or 1-make)
    return rand() % 2;
} // END FUNC


/*********************************************************************
** Function: GetMoneyBallPosition(<int>, <int>)
** Description: Prompts user to enter which rack is to be their
                "money-ball" rack. Adds 1's to "pos" based on how
                many "starry balls" came before it and then returns "pos".
** Parameters: Frequency of "starry balls", number of non-starry ball racks.
** Pre-Conditions: Valid parameter types.
** Post-Conditions: Value returned of type <int> within 0-NUMROWS.
*********************************************************************/
int GetMoneyballPostion (int sFreq, int regRacks) {

    int pos = -1;

    while (true){

        cin.clear();
        cout << "Where do you want to put your money-ball rack? Enter 1-5: ";

        // Increment pos (+1) every 2
        if (cin >> pos && 1 <= pos && pos <= regRacks){
            
            int temp = pos - 1;
            while (temp >= sFreq - 1){

                temp -= sFreq - 1;
                pos += 1;
            }

            cout << endl;
            return pos - 1;

        } else {

            cout << endl << "Invalid input, try again." << endl << endl;     
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
} // END FUNC


/*********************************************************************
** Function: PlayAgain()
** Description: Asks user if they wish to play again (0-no, 1-yes).
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: User entered valid int value (0/1).
*********************************************************************/
bool PlayAgain () {

    int num = 0;

    while (true){

        cin.clear();
        cout << "Do you want to play again? (1-yes, 0-no): ";

        // play again
        if (cin >> num) {
            
            cout << endl;

            if (num == 1){

                return num;
            } 
            else if (num == 0){

                cout << "Bye bye :)" << endl;
                return num;
            }
        }

        cout << endl << "Invalid input, try again." << endl << endl;     
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }
} // END FUNC


/*********************************************************************
** Function: GetPlayers()
** Description: Asks user how many players and returns the value only if
                it's more than 1.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: Returns value of type <int>.
*********************************************************************/
int GetPlayers(){

    int n = 0;

    while (true) {
        cout << "Enter number of players (2 or more): ";

        if (cin >> n && n > 1){

            return n;

        } else {

            cout << endl << "Invalid input, try again." << endl << endl;     
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

} // END FUNC

/*********************************************************************
** Function: PrintTie(<int>, <int> <int*>, <int>)
** Description: Prints out which players tied and with what score.
** Parameters: Number of tied players, the point total the players tied with,
               the array of all players scores, and the number of players in total
** Pre-Conditions: Valid parameter types.
** Post-Conditions: None.
*********************************************************************/
void PrintTie(int tiedCount, int tiedScore, int* arr, int numPlayers){

        // array length of tied players
    int tiedPlayers[tiedCount];
    int count = 0;

    cout << "!! There was a tie between Players "; 

    // add tied players number to "tiedPlayers" in order ("Player" [1, 3, 99])
    for (int i = 0; i < numPlayers; i++){

        if (arr[i] == tiedScore){

            tiedPlayers[count] = i + 1;
            count += 1;
        }
    }

        // print the tied players and the score they tied with
    for (int i = 0; i < tiedCount; i++){

            // if last in "tiedPlayers" array
        if (i == tiedCount - 1){

            cout << "and " << tiedPlayers[i] << " with a score of " << tiedScore << " !!" << endl << endl;
            return;
        }
        cout << tiedPlayers[i] << ", ";
    }
} // END FUNC


/*********************************************************************
** Function: PrintWinner(<int*>, <int>)
** Description: Goes through player scores and print out the winner unless
                there was a tie. If tie, goes through extra steps to determine
                which players tied, adn then prints it.
** Parameters: 1D-array of player scores, size of player scores array.
** Pre-Conditions: Valid parameter types.
** Post-Conditions: None.
*********************************************************************/
void PrintWinner(int* scoresArray, int size){

    // print winner
    int highestNum = -1;
    int winner = -1;

    for (int i = 0; i < size; i++){

        if (scoresArray[i] > highestNum){

            highestNum = scoresArray[i];
            winner = i + 1;
        }
    }

    // check if muliple players had the same "highestNum"
    int tiedCount = 0;
    for (int i = 0; i < size; i++) {

        if (scoresArray[i] == highestNum){

            tiedCount += 1;
        }
    }

    // if there was a tie
    if (tiedCount > 1){

        PrintTie(tiedCount, highestNum, scoresArray, size);
        return;
    }

    cout << "!! The winner is Player " << winner << " with a score of "<< highestNum << " !!" << endl << endl;
} // END FUNC


/*********************************************************************
** Function: GenArray(<int>, <int>, <int>)
** Description: Creates a 2D array, fills it with 0's, and returns the pointer.
** Parameters: Number of rows, number of columns, frequency of starry balls in rack.
** Pre-Conditions: Valid parameter types.
** Post-Conditions: Returns value of type <int**>.
*********************************************************************/
// Creates new rack array
int** GenArray(int row, int col, int freq)
{
    int** arr = new int*[row];
    for (int i = 0; i < row; ++i) {

        // starry ball
        if (i == freq - 1){

            arr[i] = new int[1];
            arr[i][0] = 0;

        // reg rack
        } else {

            arr[i] = new int[col];
            for (int k = 0; k < col; ++k) {

            arr[i][k] = 0;
            }
        }
    }
    
    return arr;
} // END FUNC


/*********************************************************************
** Function: SimRacks(<int>, <int>, <int>, <int>, <int>, <int>, <int>)
** Description: Creates a new 2D-array "simulatedRack" using GenArray(), 
                resets the random seed, goes through "simulatedRack" and
                uses SimShot() to then decide if the value in "simulatedRack" (0)
                should be updated to a score (1, 2, 3) based on either: position in rack,
                if it's the moneyball-rack, or it's a starry ball. Returns 
                "simulatedRack" after every shot has been simulated.
** Parameters: Moneyball-rack position, point value for a regular shot make (1),
               point value for moneyball shot make (2), or point value for
               starry ball make (3).
** Pre-Conditions: SimShot() returns a value of either true/false or 0/1, 
                   GenArray() returns a 2D array, valid parameter types.
** Post-Conditions: Returns value of type <int**>.
*********************************************************************/
int** SimRacks (int mPos, int reg, int money, int starry, int sFreq, int row, int col) {
    
    // 2D array filled with 0's
    int** simulatedRack = GenArray(row, col, sFreq);

    // reset random seed
    srand(time(NULL));

    // Outer loop
    for (int i = 0; i < row; i++){

        // Inner loop
        for (int k = 0; k < col; k++){

            // Starry Shots
            if ((i + 1) % sFreq == 0){
                if (SimShot()){
                    simulatedRack[i][0] = starry;
                }
                break;
            }

            // Moneyball Rack
            if (i == mPos){
                if (SimShot()){
                    simulatedRack[i][k] = money;
                }

            } else{

                // Reg Rack
                if (SimShot()){

                    // If on moneyball (last in rack)
                    if (k == col - 1){
                        
                        simulatedRack[i][k] = money;
                    } else {
                        simulatedRack[i][k] = reg;
                    }
                }
            }
        } // Inner loop

    } // Outer loop

    // simulated 2D-array of racks
    return simulatedRack;
} // END FUNC


/*********************************************************************
** Function: PrintRack(<int**>, <int>, <int>, <int>, <int>, <int>, <int>)
** Description: Prints a single racks results based on the point value held
                in 2D-array ("rack"), replacing the point value with letter indicators.
                Adds up total score for rack and returns it.
** Parameters: 2D-array of racks, current rack value (0 based),
               point value for a regular shot make (1), point value for moneyball 
               shot make (2), or point value for starry ball make (3), frequency
               of starry balls, number of balls in rack.
** Pre-Conditions: Valid parameter types, "rack" columns and "col" are equal.
** Post-Conditions: Returns value of type <int>
*********************************************************************/
int PrintRack (int** rack, int pos, int reg, int money, int starry, int sFreq, int col) {

    string miss = "X ";
    string madeReg = "O ";
    string madeMoney = "M ";
    string madeStarry = "W ";

    int totalRackPts = 0;

    // Print single rack
            for (int i = 0; i < col; ++i) {

                // make (reg)
                if (rack[pos][i] == reg){

                    totalRackPts += reg;
                    cout << madeReg;
                
                // make (money)
                } else if (rack[pos][i] == money){

                    totalRackPts += money;
                    cout << madeMoney;
                
                // make (starry)
                } else if (rack[pos][i] == starry){

                    cout << madeStarry;
                    return starry;

                // miss (not starry)
                } else if (!((pos + 1) % sFreq == 0)){

                    cout << miss;

                // miss (starry)
                } else {

                    cout << miss;
                    break;
                }
            } 
    return totalRackPts;
} // END FUNC


/*********************************************************************
** Function: PrintAllRacks(<int**>, <int>, <int>, <int>, <int>, <int>, <int>)
** Description: Titles current rack, prints rack results using PrintRack(),
                tracks "totalRackPoints", repeats for all racks, and returns
                "totalRackPoints".
** Parameters: 2D-array of racks, 2D-array of racks, current rack value (0 based),
               point value for a regular shot make (1), point value for moneyball 
               shot make (2), or point value for starry ball make (3), frequency
               of starry balls, number of racks (including starry balls), number of balls in rack.
** Pre-Conditions: Valid parameter types, "rack" rows and columns are equal
                   to "row" and "col" respectively, PrintRack() returns value of type <int>.
** Post-Conditions: Returns value of type <int>.
*********************************************************************/
int PrintAllRacks(int** rack, int reg, int money, int starry, int sFreq, int row, int col){

    int totalRackPoints = 0;

    for (int i = 0; i < row; ++i) {

        if ((i + 1) % sFreq == 0){

            cout << "Starry: ";
        } else {

            cout << "Rack " << i - (i / sFreq) + 1 << ": ";            
        }

        int tempCount = PrintRack(rack, i, reg, money, starry, sFreq, col);

        // If starry
        if ((i + 1) % sFreq == 0){

            cout << "        | " << tempCount << " pts" << endl;
            totalRackPoints += tempCount;
        
        // Not starry
        } else{
            cout << "| " << tempCount << " pts" << endl;
            totalRackPoints += tempCount;
        }
    }

    cout << endl;
    return totalRackPoints;
} // END FUNC

// MAIN
int main() {

    // CONSTANTS
    const int ARRAYROWS = 7;
    const int ARRAYCOLS = 5;

    // made shot points
    int madeShot_Reg = 1;
    int madeShot_Money = 2;
    int madeShot_Starry = 3;

    // misc vars
    int numRegRacks = 5;
    int starryFreq = 3;


    // GAMELOOP
    do {

        // INTRO
        cout << endl << "---------------------------------------" << endl;
        cout << "Welcome to the basketball shooting contest!" << endl << endl;

        // get number of players and create 1D-array to hold scores
        int numPlayers = GetPlayers();
        int* playersArray = new int[numPlayers];

        // repeats for each player
        for (int player = 0; player < numPlayers; player++) {        

            // PREP
            cout << endl << "Player " << player + 1 << ":" << endl;

            // get money-ball rack position
            int moneyballRack = GetMoneyballPostion(starryFreq, numRegRacks);

            // SIM
            int** rack = SimRacks(moneyballRack, madeShot_Reg, madeShot_Money, madeShot_Starry, starryFreq, ARRAYROWS, ARRAYCOLS);

            // prints sim results and sets player score in array
            playersArray[player] = PrintAllRacks(rack, madeShot_Reg, madeShot_Money, madeShot_Starry, starryFreq, ARRAYROWS, ARRAYCOLS);
            cout << "Total: " << playersArray[player] << " pts" << endl << endl;

            // deletes "rack" from heap
            for (int i = 0; i < ARRAYROWS; i++){

                delete [] rack[i];
            }
            delete [] rack;

        }

        // prints winner or tie
        PrintWinner(playersArray, numPlayers);

        // delete "playersArray" from heap
        delete [] playersArray;

    // ask to play again
    } while (PlayAgain());

} // END MAIN
