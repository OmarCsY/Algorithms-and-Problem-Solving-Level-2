
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enChoice 
{
    Stone = 1,
    Paper = 2,
    Scissor = 3
};

enum enWinner
{
    Player = 1,
    Computer = 2,
    Tie = 3
};

struct stRoundInfo
{
    enChoice ComputerChoice;
    enChoice PlayerChoice;
    enWinner Winner;
};

struct stCountWinners
{
    short ComputerCount = 0;
    short PlayerCount = 0;
    short TieCount = 0;
};

int ReadPositiveNumber(string Message)
{
    int Number = 0;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number <= 0);

    return Number;
}

int ReadNumberInRange(string Message, int From, int To)
{
    int Number = 0;

    do
    {
        Number = ReadPositiveNumber(Message);
    } while (Number < From || Number > To);

    return Number;
}

int RandomNumber(int From, int To)
{

    int RandNumber = rand() % (To - From + 1) + From;

    return RandNumber;
}

enChoice ConvertNumberToChoice(int Number)
{
    return (enChoice)Number;
}

string ConvertWinnerToString(enWinner Winner)
{
    if (Winner == enWinner::Player)
        return "Player";

    else if (Winner == enWinner::Computer)
        return "Computer";

    else
        return "No Winner";
}

string ConvertChoiceToString(enChoice Choice)
{
    if (Choice == enChoice::Paper)
        return "Paper";

    else if (Choice == enChoice::Scissor)
        return "Scissor";

    else
        return "Stone";
}

enChoice ComputerChoice()
{
    short Choice = RandomNumber(1, 3);

    return ConvertNumberToChoice(Choice);
}

enWinner RoundWinner(enChoice ComputerChoice, enChoice PlayerChoice, stCountWinners& CountWinners)
{

    if (ComputerChoice == enChoice::Stone)
    {
        if (PlayerChoice == enChoice::Paper) {
            CountWinners.PlayerCount++;
            return enWinner::Player;
        }

        if (PlayerChoice == enChoice::Scissor) {
            CountWinners.ComputerCount++;
            return enWinner::Computer;
        }
    }

    if (ComputerChoice == enChoice::Paper)
    {
        
        if (PlayerChoice == enChoice::Stone) {
            CountWinners.ComputerCount++;
            return enWinner::Computer;
        }

        if (PlayerChoice == enChoice::Scissor) {
            CountWinners.PlayerCount++;
            return enWinner::Player;
        }
    }

    if (ComputerChoice == enChoice::Scissor)
    {

        if (PlayerChoice == enChoice::Paper) {
            CountWinners.ComputerCount++;
            return enWinner::Computer;
        }

        if (PlayerChoice == enChoice::Stone) {
            CountWinners.PlayerCount++;
            return enWinner::Player;
        }
    }

    CountWinners.TieCount++;
    return enWinner::Tie;
}

enWinner GameWinner(stCountWinners& CountWinners)
{
    enWinner Winner = enWinner::Tie;

    if (CountWinners.ComputerCount > CountWinners.PlayerCount)
        Winner = enWinner::Computer;
    
    else if (CountWinners.PlayerCount > CountWinners.ComputerCount)
        Winner = enWinner::Player;

    return Winner;
}

stRoundInfo ReadRoundInfo(stCountWinners& CountWinners)
{

    stRoundInfo InfoRound;

    int PlayerChoiceNumber = ReadNumberInRange("Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ", 1, 3);

    InfoRound.PlayerChoice = ConvertNumberToChoice(PlayerChoiceNumber);

    InfoRound.ComputerChoice = ComputerChoice();

    InfoRound.Winner = RoundWinner(InfoRound.ComputerChoice, InfoRound.PlayerChoice, CountWinners);

    return InfoRound;
}

string ColorScreen(enWinner Winner)
{
    string Color = "";

    if (Winner == enWinner::Computer)
        Color = "color 47";
    else if (Winner == enWinner::Player)
        Color = "color 20";
    else
        Color = "color 60";

    return Color;
}

void PrintRoundInfo(stRoundInfo RoundInfo, int NumberOfRound)
{
    system(ColorScreen(RoundInfo.Winner).c_str());

    cout << "\n____________________Round [" << NumberOfRound << "]____________________\n\n";

    cout << "Player   Choice: " << ConvertChoiceToString(RoundInfo.PlayerChoice) << "\n";
    cout << "Computer Choice: " << ConvertChoiceToString(RoundInfo.ComputerChoice) << "\n";
    cout << "Round Winner   : " << ConvertWinnerToString(RoundInfo.Winner) << "\n";

}

int ReadNumberOfRound()
{
    int NumberOfRound = ReadPositiveNumber("Please Enter Number Of Round? ");

    return NumberOfRound;
}

void PrintGameInfo(stCountWinners &CountWinners, int NumberOfRounds)
{
    cout << "\n\t\t________________________________________________\n";
    cout << "\n\t\t\t\t+++ Game Over +++";
    cout << "\n\t\t________________________________________________\n";

    cout << "\n\t\t_______________ [Game Results] _________________\n\n";


    cout << "\t\tGame Rounds        : " << NumberOfRounds << "\n";
    cout << "\t\tPlayer won times   : " << CountWinners.PlayerCount << "\n";
    cout << "\t\tComputer won times : " << CountWinners.ComputerCount << "\n";
    cout << "\t\tDraw times         : " << CountWinners.TieCount << "\n";
    cout << "\t\tFinal Winner       : " << ConvertWinnerToString(GameWinner(CountWinners)) << endl;

    cout << "\n\t\t________________________________________________\n\n";

}

stCountWinners NewRound(stCountWinners& CountWinners, int NumberOfRound)
{

    stRoundInfo RoundInfo;

    RoundInfo = ReadRoundInfo(CountWinners);

    PrintRoundInfo(RoundInfo, NumberOfRound);

    return CountWinners;
}

void NewGame()
{

    system("cls");
    system("color 07");

    int NumberOfRound = ReadNumberOfRound();
    stCountWinners CountWinners;

    
    for (int i = 1; i <= NumberOfRound; i++)
    {
        NewRound(CountWinners, i);
    }

    PrintGameInfo(CountWinners, NumberOfRound);
    system(ColorScreen(GameWinner(CountWinners)).c_str());
}

void StartGame()
{
    char PlayAgain = 'y';

    do
    {
        NewGame();

        cout << "\t\tDo You Want Play Again? Enter [Y] For Yes, [N] For No" << endl;
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');

    system("color 07");
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}
