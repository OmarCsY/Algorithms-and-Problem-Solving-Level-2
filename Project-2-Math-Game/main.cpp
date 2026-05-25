#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


enum enQuestionsLevel {Easy = 1, Med = 2, Hard = 3, MixLevel = 4};

enum enOperations {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

enum enPassOrFail { Pass = 1, Fail = 2};

struct stRoundInfo
{
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperations Operation;
    short RightAnswers = 0;
    short WrongAnswers = 0;
    enPassOrFail RoundStatus;
};

struct stQuestionInfo
{
    short FirstNumber = 0;
    short SecondNumber = 0;
    enOperations OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool isCorrect = false;
    enQuestionsLevel QuestionsLevel;
};

int RandomNumber(int From, int To)
{

    int RandNumber = rand() % (To - From + 1) + From;

    return RandNumber;
}

int GetNumberBasedLevel(enQuestionsLevel QuestionLevel)
{
    switch (QuestionLevel)
    {
    case 1:
        return RandomNumber(1, 10);
    case 2:
        return RandomNumber(10, 50);
    case 3:
        return RandomNumber(50, 100);
    case 4:
        return RandomNumber(1, 100);
    }
}

int CalculatResult(int FirstNumber, int SecondNumber, enOperations Operation)
{
    int Result = 0;

    switch (Operation)
    {
        case enOperations::Add:
            Result = FirstNumber + SecondNumber;
            break;
        case enOperations::Sub:
            Result = FirstNumber - SecondNumber;
            break;
        case enOperations::Mul:
            Result = FirstNumber * SecondNumber;
            break;
        case enOperations::Div:
            Result = FirstNumber / SecondNumber;
            break;
    }

    return Result;

}

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

enQuestionsLevel GetRandomQuestionLevel()
{
    return (enQuestionsLevel)RandomNumber(1, 3);
}

enOperations GetRandomOperation()
{
    return (enOperations)RandomNumber(1, 4);
}

string GetFinalResult(enPassOrFail Result)
{
    string arrPassOrFail[2] = { "Pass :-) ", "Fail :-( "};

    return arrPassOrFail[Result - 1];
}

string GetQuestionLevel(enQuestionsLevel QuestionLevel)
{
    string arrLevels[4] = {"Easy", "Med", "Hard", "MixLevel"};
    return arrLevels[QuestionLevel - 1];
}

string GetOpType(enOperations Op)
{
    string arrOperations[5] = {"Add", "Sub", "Mul", "Div", "MixOp"};
    return arrOperations[Op - 1];
}

char GetOpChar(enOperations Op)
{
    char arrOperations[5] = {'+', '-', '*', '/', '?'};
    return arrOperations[Op - 1];
}

enQuestionsLevel ReadQuestionLevel()
{
    short Number = 0;

    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? " << endl;
        cin >> Number;
    } while (Number > 4 || Number < 1);

    return (enQuestionsLevel)Number;
}

enOperations ReadOperation()
{
    short Number = 0;

    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? " << endl;
        cin >> Number;
    } while (Number > 5 || Number < 1);

    return (enOperations)Number;
}

stQuestionInfo GetQuestionInfo(enOperations OpType, enQuestionsLevel QuestionsLevel)
{
    /*
    short FirstNumber = 0;
    short SecondNumber = 0;
    enOperations OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool isCorrect = false;
    enQuestionsLevel QuestionsLevel;
    */

    stQuestionInfo QuestionInfo;

    if (OpType == enOperations::MixOp)
        OpType = GetRandomOperation();

    if (QuestionsLevel == enQuestionsLevel::MixLevel)
        QuestionsLevel = GetRandomQuestionLevel();

    QuestionInfo.OperationType = OpType;
    QuestionInfo.QuestionsLevel = QuestionsLevel;
    QuestionInfo.FirstNumber = GetNumberBasedLevel(QuestionsLevel);
    QuestionInfo.SecondNumber = GetNumberBasedLevel(QuestionsLevel);
    QuestionInfo.CorrectAnswer = CalculatResult(QuestionInfo.FirstNumber, QuestionInfo.SecondNumber, OpType);

    return QuestionInfo;

}

bool isCorrectAns(int CorrectAns, int PlayerAns)
{
    return CorrectAns == PlayerAns;
}

void PlayQuestion(stQuestionInfo& QuestionInfo)
{

    cout << QuestionInfo.FirstNumber << "\n";
    cout << QuestionInfo.SecondNumber << " " << GetOpChar(QuestionInfo.OperationType) << "\n";
    cout << "_____________" << "\n";

    cin >> QuestionInfo.PlayerAnswer;

    QuestionInfo.isCorrect = isCorrectAns(QuestionInfo.CorrectAnswer, QuestionInfo.PlayerAnswer);

}

void PrintQuestionResult(stQuestionInfo QuestionInfo)
{
    cout << "\n";

    if (QuestionInfo.isCorrect)
    {
        system("color 2F");
        cout << "Right Answer :-)" << endl;
    }
    else
    {
        system("color 4F");
        cout << "\a";
        cout << "Wrong Answer :-(" << endl;
        cout << "The right answer is: " << QuestionInfo.CorrectAnswer << endl;
    }
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{

    cout << "__________________________________________\n";
    cout << " Final Results is " << GetFinalResult(RoundInfo.RoundStatus) << "\n";
    cout << "__________________________________________\n\n";
    cout << "Number of Questions: " << RoundInfo.NumberOfQuestions << "\n";
    cout << "Questions Level    : " << GetQuestionLevel(RoundInfo.QuestionsLevel) << "\n";
    cout << "OpType             : " << GetOpType(RoundInfo.Operation) << "\n";
    cout << "Number of Right Answers: " << RoundInfo.RightAnswers << "\n";
    cout << "Number of Wrong Answers: " << RoundInfo.WrongAnswers << "\n";
    cout << "__________________________________________\n";

}

void PassOrFail(stRoundInfo& RoundInfo)
{
    if (RoundInfo.RightAnswers >= RoundInfo.WrongAnswers)
        RoundInfo.RoundStatus = enPassOrFail::Pass;
    else
        RoundInfo.RoundStatus = enPassOrFail::Fail;
}

void PlayMathGame()
{
    stRoundInfo RoundInfo;

    RoundInfo.NumberOfQuestions = ReadPositiveNumber("How Many Questions do you want to answer ?");
    RoundInfo.QuestionsLevel = ReadQuestionLevel();
    RoundInfo.Operation = ReadOperation();

    for (int i = 1; i <= RoundInfo.NumberOfQuestions; i++)
    {
        stQuestionInfo QuestionInfo;

        cout << "\nQuestion [" << i << "/" << RoundInfo.NumberOfQuestions << "]" << endl;

        QuestionInfo = GetQuestionInfo(RoundInfo.Operation, RoundInfo.QuestionsLevel);
        PlayQuestion(QuestionInfo);
        PrintQuestionResult(QuestionInfo);

        if (QuestionInfo.isCorrect)
            RoundInfo.RightAnswers++;
        else
            RoundInfo.WrongAnswers++;
    }

    PassOrFail(RoundInfo);

    system("color 0F");
    PrintRoundInfo(RoundInfo);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartMathGame()
{
    char PlayAgain = 'Y';

    do
    {

        ResetScreen();
        PlayMathGame();

        cout << "\n" << "Do you want to play again? (Y/N) " << endl;
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartMathGame();
}
