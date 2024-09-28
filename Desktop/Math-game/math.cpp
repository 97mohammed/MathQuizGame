#include <iostream>
#include <string>
using namespace std;


enum enQuestionLevel { Easy=1,Med=2,Hard=3,Mix=4 };
enum enOperationType {Add=1,Sub=2,Mul=3,Div=4,MixOp=5};



int ReadHowManyQuestions()
{

    
        int Number;
        cout << "How Many Questions do you want to answer ? ";
        cin >> Number;


        return Number;


    }



enQuestionLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;

    do
    {

        cout << "\n Enter Questions Level   [1]:Easy, [2]:Med. [3]:Hard. [4]:Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel >4);

    return (enQuestionLevel)QuestionLevel;

}


enOperationType ReadOperationsType()
{
    short Type;

    do
    {

        cout << "\n Enter Questions Level   [1]:Add, [2]:Sub. [3]:Mul. [4]:Div. [5]:Mix ? ";
        cin >> Type;

    } while (Type < 1 || Type >5);

    return (enOperationType)Type;




}


int RandNumber(int from, int to)
{
    int randN = rand() % (to - from + 1) + from;


    return  randN;
}


string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mul:
        return "x";
    case Div:
        return "/";

    default:
        return "MixOp";
    }

}


string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med", "Hard", "Mix" };

    return arrQuestionLevelText[QuestionLevel - 1];


}

void SetScreenColor(bool Right)
{
    if (Right)
    {
        system("color 2F");   //turn screen to green 
    }
    else
    {
        system("color 4F");  //turn screen to red
    }

}



struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType  OperationsType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};


struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool isPass = false;
};



int SimpleCalculater(int Number1, int Number2, enOperationType OpType)
{

    switch (OpType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mul:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;

    default:
        return Number1 + Number2;

    }
}

enOperationType GetRandomOperationType()
{
    int OP = RandNumber(1, 4);

    return(enOperationType)OP;

}



stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
    {
        QuestionLevel = (enQuestionLevel)RandNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationsType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1=RandNumber(1, 50);
        Question.Number2= RandNumber(1, 50);

        Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationsType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Med:
        Question.Number1 = RandNumber(50, 500);
        Question.Number2 = RandNumber(50, 500);

        Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationsType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::Hard:
        Question.Number1 = RandNumber(500, 5000);
        Question.Number2 = RandNumber(500, 5000);

        Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationsType);

        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;


}


void GenerateQuizzQuetions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions;Question ++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }

}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;

}


void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [ " << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";

    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationsType);
    cout << "\n----------"<< endl;
}



void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "Wrong Answer :-(  \n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :-) \n";
    }

    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}


void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
    for (short QuestionNumber  = 0;   QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {

        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);

    }

    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}



string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return"Fail :-(";
    
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "-------------------------------------\n\n";
    cout << " Final Results is  " << GetFinalResultsText(Quizz.isPass);
    cout << "-------------------------------------\n\n";

    cout << "Number of Question: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level   : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;

    cout <<  "OpType          : " << GetOpTypeSymbol(Quizz.OpType) << endl;

    cout << "Number of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answer: " << Quizz.NumberOfWrongAnswer << endl;

    cout << "-------------------------------------\n\n";


}


void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOperationsType();

    GenerateQuizzQuetions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResults(Quizz);
}


void ResetScreen()
{
    system("cls");
    system("color 0F");
}




void StartGame()
{
    char playAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();       

        cout << endl  << "Do you want to play again? Y/N? ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}