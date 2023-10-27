#ifndef INCLUDES
#define INCLUDES
// includes
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
#endif

#ifndef TEAM
#define TEAM
//a struct to hold info of a team
struct Team {
  string name;        //name of the team
  string owner;       //owner of the team
  int market_value;   //market value of the team
  int num_player;     //number of players in the team
  struct Player *p;   //an array that holds all players
  float total_ppg;    //total points per game
};
#endif


#ifndef PLAYER
#define PLAYER
//a struct to hold info of a player
struct Player {
  string name;      //name of the player
  int age;          //age of the player
  string nation;    //nationality of the player
  float ppg;        //points per game of the player
  float fg;         //field goal percentage
};
#endif


/**************************************************
 * Name: create_teams()
 * Description: This function will dynamically allocate
                an array of teams (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Team array of requested size is created and return
 ***********************************************/
Team* create_teams(int);


/**************************************************
 * Name: populate_team_data()
 * Description: This function will fill a single team struct 
                with information that is read in from the file
 * Parameters:  Team* - pointer to the Team array
                int - index of the Team in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Team array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Team at provided index is populated
 ***********************************************/
void populate_team_data(Team*, int, ifstream&); 


/**************************************************
 * Name: create_players()
 * Description: This function will dynamically allocate
                an array of players (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Player array of requested size is created and return
 ***********************************************/
Player* create_players(int);

/**************************************************
 * Name: populate_player_data()
 * Description: This function will fill a single player struct 
                with information that is read in from the file
 * Parameters:  Player* - pointer to the Player array
                int - index of the Player in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Player array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Player at provided index is populated
 ***********************************************/
void populate_player_data(Player*, int, ifstream&); 


/**************************************************
 * Name: delete_info()
 * Description: This function will delete all the memory that was dynamically allocated
 * Parameters: Team* - the Team array
 * Pre-conditions: the provided Team array hasn't been freed yet
 * Post-conditions: the Team array, with all Players inside, is freed
 ***********************************************/
void delete_info(Team*, int);



/**************************************************
 * Name: DisplayOptions()
 * Description: This function prompts the user with program options
 *              and returns the user input as an <int>
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: returns <int> of desired range
 ***********************************************/
int DisplayOptions ();


/**************************************************
 * Name: DisplayInfo()
 * Description: This function prompts the user with where requested info
 *              can be displayed for them. Takes in input and returns
 *              as type <int>
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: returns <int> of desired range
 ***********************************************/
int DisplayInfo ();


/**************************************************
 * Name: GetTeam()
 * Description: This function prompts the user to enter a Team name and returns a string
 *              of the entered Teams and its Players info
 * Parameters: Team* - the Team array
 *             int - size of <Team*> array
 * Pre-conditions: Both the <Team*> and <Player*> array inside referenced
 *                 <Team*> array have been populated
 * Post-conditions: returns <string> of Team and its Players info
 ***********************************************/
string GetTeam(Team*, int);


/**************************************************
 * Name: GetScorers()
 * Description: Goes through Team array and then the current Teams Players
 *              to determine the player with the highest ppg to be appended to
 *              returned <string>
 * Parameters: Team* - the Team array
 *             int - size of <Team*> array
 * Pre-conditions: Both the <Team*> and <Player*> array inside referenced
 *                 <Team*> array have been populated
 * Post-conditions: returns <string> of top scorers for each Team
 ***********************************************/
string GetScorers(Team*, int);


/**************************************************
 * Name: GetNation()
 * Description: Prompts user to enter the name of a nation and searches through
 *              Team array and the Player array inside to append players
 *              with entered nations name and age to returned <string>
 * Parameters: Team* - the Team array
 *             int - size of <Team*> array
 * Pre-conditions: Both the <Team*> and <Player*> array inside referenced
 *                 <Team*> array have been populated
 * Post-conditions: returns <string> of user inputed nation of Players names and age
 ***********************************************/
string GetNation(Team*, int);


/**************************************************
 * Name: GetPPG()
 * Description: Sorts Team array into desceding order based on total_ppg
 *              and returns a <string> of the Teams names and total_ppg in
 *              descending order
 * Parameters: Team* - the Team array
 *             int - size of <Team*> array
 * Pre-conditions: Both the <Team*> and <Player*> array inside referenced
 *                 <Team*> array have been populated
 * Post-conditions: Sorts Team array and returns string of Team names and thier total_ppg
 *                  in descending order
 ***********************************************/
string GetPPG(Team*, int);


/**************************************************
 * Name: PrintInfo()
 * Description: Displays info in appropriate location based on user input
 *              (screen or file). If file, prompts user for file
 *              name and appends to file if found, else creates new file of entered name.
 * Parameters: string - to be printed
 *             int - where to be printed (1 = screen, 2 = file)
 *             ofstream& - address of output stream
 * Pre-conditions: <ofstream&> isn't currently open
 * Post-conditions: file type is ".txt", or prints to screen
 ***********************************************/
void PrintInfo(string, int, ofstream&);

