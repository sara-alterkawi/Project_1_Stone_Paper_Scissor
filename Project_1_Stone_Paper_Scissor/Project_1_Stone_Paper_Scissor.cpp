// Write a small game program for Stone_Paper_Scissor
// Requirements:
// Aask for how many rounds the game will be.
// Start each round Player Vs Computer.
// Show the results with each round.
// If computer wins the round ring a bill, and screen red.
// If player won the round show green screen.
// If there is no winer show yellow screen.
// After all round show game over the print game results,
// then ask the user if s/he want to play again?
// Ex: input
// 
// 

#include <iostream>
#include <string>
using namespace std;

// Enum to store game Choices
enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };

// Enum to store winner information
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

// Structur round information 
struct stRoundInfo
{
    int RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName = "";
};

// Structur game results
struct stGameResults
{
    int GameRounds = 0;
    int PlayerWinTimes = 0;
    int ComputerWinTimes = 0;
    int DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

// Returns a random integer between From and To (inclusive).
int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

// Generates and returns a random choice for the computer.
enGameChoice GetComputerChoice()
{
    return enGameChoice(RandomNumber(1, 3));
}

// Clears the console and resets screen color to default.
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

// Function returns the string name of a given game choice.
string ChoiceName(enGameChoice choice)
{
    string arrGameChoices[3] = { "Stone","Paper","Scissor" };
    return arrGameChoices[choice - 1];
}

// Returns the winner's name as a string (Player, Computer, No Winner).
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player","Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}

// Determines the round winner based on player and computer choices.
enWinner WhoWonTheRound(stRoundInfo roundInfo)
{
    if (roundInfo.PlayerChoice == roundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (roundInfo.PlayerChoice)
    {
    case enGameChoice::Paper:
        if (roundInfo.ComputerChoice == enGameChoice::Scissor)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissor:
        if (roundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Stone:
        if (roundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

// Determines the overall game winner after all rounds.
enWinner WhoWonTheGame(int playerWinTimes, int computerWinTimes)
{
    if (playerWinTimes > computerWinTimes)
        return enWinner::Player;
    else if (playerWinTimes < computerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

// Returns a string containing the given number of tab characters.
string Tabs(int numberOfTabs)
{
    return string(numberOfTabs, '\t');
}

// Reads and validates the player's choice (1=Stone, 2=Paper, 3=Scissor).
enGameChoice ReadPlayerChoice()
{
    int choice = 1;
    do
    {
        cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissor? ";
        cin >> choice;

    } while (choice < 1 || choice >3);
    return enGameChoice(choice);
}


// Reads and validates how many rounds the user wants to play (1–10).
int ReadHowManyRounds()
{
    int gameRounds = 1;
    do
    {
        cout << "How many Rounds 1 to 10 ? ";
        cin >> gameRounds;
    } while (gameRounds < 1 || gameRounds > 10);
    return gameRounds;
}

// Sets the console color (green if player wins, red with beep if computer wins, yellow for draw).
void SetWinnerScreenColor(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
    }
}

// Prints the details and winner of the current round.
void PrintRoundResults(stRoundInfo roundInfo)
{
    cout << "____________________ Round [" << roundInfo.RoundNumber << "] __________________" << endl;
    cout << "Player1 Choice : " << ChoiceName(roundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(roundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << roundInfo.WinnerName << "]" << endl;
    cout << "_________________________________________________" << endl;
    SetWinnerScreenColor(roundInfo.RoundWinner);
}

// Displays the "Game Over" screen.
void PrintGameOverScreen()
{
    cout << Tabs(1) << "_____________________________________________________________________\n";
    cout << Tabs(1) << "                        +++ G a m e  O v e r +++" << endl;
    cout << Tabs(1) << "_____________________________________________________________________\n\n";
}

// Prints the summary of the entire game (rounds, wins, draws, final winner).
void PrintFinalGameResults(stGameResults gameResults)
{
    cout << Tabs(1) << "__________________________ [Game Results] ___________________________\n\n";
    cout << Tabs(1) << "Game Rounds        : " << gameResults.GameRounds << endl;
    cout << Tabs(1) << "Player1 win times  : " << gameResults.PlayerWinTimes << endl;
    cout << Tabs(1) << "Computer win times : " << gameResults.ComputerWinTimes << endl;
    cout << Tabs(1) << "Draw Times         : " << gameResults.DrawTimes << endl;
    cout << Tabs(1) << "Final Winner       : " << gameResults.WinnerName << endl;
    cout << Tabs(1) << "_____________________________________________________________________\n";
    SetWinnerScreenColor(gameResults.GameWinner);
}

// Populates and returns the final game results struct.
stGameResults FillGameResults(int gameRounds, int playerWinTimes, int computerWinTimes, int drawTimes)
{
    stGameResults gameResults;
    gameResults.GameRounds = gameRounds;
    gameResults.PlayerWinTimes = playerWinTimes;
    gameResults.ComputerWinTimes = computerWinTimes;
    gameResults.DrawTimes = drawTimes;
    gameResults.GameWinner = WhoWonTheGame(playerWinTimes, computerWinTimes);
    gameResults.WinnerName = WinnerName(gameResults.GameWinner);
    return gameResults;
}

// Plays the game for the given number of rounds and returns the results.
stGameResults PlayGame(int howManyRounds)
{
    stRoundInfo roundInfo;
    int playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;

    for (int gameRound = 1; gameRound <= howManyRounds; gameRound++)
    {
        cout << "Round [" << gameRound << "] begins: " << endl;
        roundInfo.RoundNumber = gameRound;
        roundInfo.PlayerChoice = ReadPlayerChoice();
        roundInfo.ComputerChoice = GetComputerChoice();
        roundInfo.RoundWinner = WhoWonTheRound(roundInfo);
        roundInfo.WinnerName = WinnerName(roundInfo.RoundWinner);

        if (roundInfo.RoundWinner == enWinner::Player)
            playerWinTimes++;
        else if (roundInfo.RoundWinner == enWinner::Computer)
            computerWinTimes++;
        else
            drawTimes++;
        PrintRoundResults(roundInfo);
    }
    return FillGameResults(howManyRounds, playerWinTimes, computerWinTimes, drawTimes);
}

// Main game loop: plays games until the user decides to quit.
void StartGame()
{
    char playAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults gameResults = PlayGame(ReadHowManyRounds());
        PrintGameOverScreen();
        PrintFinalGameResults(gameResults);
        cout << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
}

// Main function
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}