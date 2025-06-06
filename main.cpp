#include <iostream>
#include <cstdlib>
using namespace std;

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};
enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissor = 3
};

struct stGameResults
{
    int GameRounds = 0;
    int PlayerWinTimes = 0;
    int ComputerWinTimes = 0;
    int DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName;
};

struct stRoundResult
{
    int RoundNumber = 0;
    enWinner Winner;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    string WinnerName;
};

void ResetScreen()
{
    system("cls");
}

int HowManyRounds()
{
    int Rounds = 0;
    cout << "Please Enter How Many Rounds Do You Want To Play From 1 To 10?...";
    cin >> Rounds;

    return Rounds;
}

enGameChoice ReadPlayerChoice()
{
    int Choice = 0;

    do
    {
        cout << "\nYour Choice: [1] Stone, [2] Paper, [3] Scissor? \n";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    int RandomNum = 1 + rand() % 3;

    return (enGameChoice)RandomNum;
}

enWinner WhoWonTheRound(stRoundResult RoundResult)
{
    if (RoundResult.PlayerChoice == RoundResult.ComputerChoice)
    {
        return enWinner::Draw;
    }
    else if ((RoundResult.PlayerChoice == enGameChoice::Paper && RoundResult.ComputerChoice == enGameChoice::Stone) || (RoundResult.PlayerChoice == enGameChoice::Scissor && RoundResult.ComputerChoice == enGameChoice::Paper) || (RoundResult.PlayerChoice == enGameChoice::Stone && RoundResult.ComputerChoice == enGameChoice::Scissor))
    {
        return enWinner::Player;
    }
    else
    {
        return enWinner::Computer;
    }
}

string WinnerName(enWinner Winner)
{
    string WinnerName[3] = {"Player", "Computer", "No Winner"};
    return WinnerName[Winner - 1]; // bec. array is zero based
}

string ChoiceName(enGameChoice Choice)
{
    string ArrayGameChoice[3] = {"Stone", "Paper", "Scissor"};
    return ArrayGameChoice[Choice - 1]; // Array is zero based
}

void PrintRoundResult(stRoundResult RoundResult)
{
    cout << "\n____________Round [" << RoundResult.RoundNumber << "]____________\n\n";
    cout << "Player Choice: " << ChoiceName(RoundResult.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundResult.ComputerChoice) << endl;
    cout << "Winner: " << RoundResult.WinnerName << endl;
    cout << "---------------------------------\n\n";
}

enWinner WhoWonTheGame(int ComputerWinTimes, int PlayerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
    {
        return enWinner::Player;
    }
    else if (ComputerWinTimes > PlayerWinTimes)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::Draw;
    }
}

stGameResults FillGameResults(int HowManyRounds, int PlayerWinTimes, int ComputerWinTimes, int DrawTimes)
{
    stGameResults GameResult;

    GameResult.GameRounds = HowManyRounds;
    GameResult.PlayerWinTimes = PlayerWinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = WhoWonTheGame(ComputerWinTimes, PlayerWinTimes);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResults PlayGame(int NumberOfRounds)
{
    stRoundResult RoundResult;
    int CountPlayerWin = 0, CountComputerWin = 0, CountDraw = 0;

    for (int i = 1; i <= NumberOfRounds; i++)
    {
        cout << "\nRound [" << i << "] begins: \n";

        RoundResult.RoundNumber = i;
        RoundResult.PlayerChoice = ReadPlayerChoice();
        RoundResult.ComputerChoice = GetComputerChoice();
        RoundResult.Winner = WhoWonTheRound(RoundResult);
        RoundResult.WinnerName = WinnerName(RoundResult.Winner);

        if (RoundResult.Winner == enWinner::Player)
        {
            CountPlayerWin++;
        }
        else if (RoundResult.Winner == enWinner::Computer)
        {
            CountComputerWin++;
        }
        else
        {
            CountDraw++;
        }

        PrintRoundResult(RoundResult);
    }

    return FillGameResults(NumberOfRounds, CountPlayerWin, CountComputerWin, CountDraw);
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << "\t\t_____________________ [Game Results]_____________________\n\n";
    cout << "\t\tGame Rounds : " << GameResults.GameRounds << endl;
    cout << "\t\tPlayer won times : " << GameResults.PlayerWinTimes << endl;
    cout << "\t\tComputer won times : " << GameResults.ComputerWinTimes << endl;
    cout << "\t\tDraw times : " << GameResults.DrawTimes << endl;
    cout << "\t\tFinal Winner : " << GameResults.WinnerName << endl;
    cout << "\t\t___________________________________________________________\n";
}

void StartGame()
{
    char PlayMore = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(HowManyRounds());
        ShowFinalGameResults(GameResults);

        cout << "\nDo You Want To Play Again?...";
        cin >> PlayMore;

    } while (PlayMore == 'y' || PlayMore == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}