#include <iostream>
#include <string>
using namespace std;

// Enumerations for question levels and operation types
enum enQuestionLevel { Easy=1, Med=2, Hard=3, Mix=4 };
enum enOperationType { Add=1, Sub=2, Mul=3, Div=4, MixOp=5 };

// Function to read the number of questions the user wants to answer
int ReadHowManyQuestions() {
    int Number;
    cout << "How Many Questions do you want to answer? ";
    cin >> Number;
    return Number;
}

// Function to read the difficulty level of the questions
enQuestionLevel ReadQuestionsLevel() {
    short QuestionLevel = 0;
    do {
        cout << "\nEnter Questions Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

// Function to read the type of operations for the questions
enOperationType ReadOperationsType() {
    short Type;
    do {
        cout << "\nEnter Operations Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix? ";
        cin >> Type;
    } while (Type < 1 || Type > 5);
    return (enOperationType)Type;
}

// Function to generate a random number within a specified range
int RandNumber(int from, int to) {
    int randN = rand() % (to - from + 1) + from;
    return randN;
}

// Function to get the symbol of the operation type
string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType) {
        case Add: return "+";
        case Sub: return "-";
        case Mul: return "x";
        case Div: return "/";
        default: return "MixOp";
    }
}

// Function to get the text representation of the question level
string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

// Function to set the screen color based on the correctness of the answer
void SetScreenColor(bool Right) {
    if (Right) {
        system("color 2F"); // turn screen to green
    } else {
        system("color 4F"); // turn screen to red
    }
}

// Struct to represent a question
struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationsType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

// Struct to represent a quiz
struct stQuizz {
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool isPass = false;
};

// Function to perform a basic calculation based on the operation type
int SimpleCalculater(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
        case Add: return Number1 + Number2;
        case Sub: return Number1 - Number2;
        case Mul: return Number1 * Number2;
        case Div: return Number1 / Number2;
        default: return Number1 + Number2;
    }
}

// Function to get a random operation type
enOperationType GetRandomOperationType() {
    int OP = RandNumber(1, 4);
    return (enOperationType)OP;
}

// Function to generate a question based on the question level and operation type
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix) {
        QuestionLevel = (enQuestionLevel)RandNumber(1, 3);
    }
    if (OpType == enOperationType::MixOp) {
        OpType = GetRandomOperationType();
    }
    Question.OperationsType = OpType;

    switch (QuestionLevel) {
        case enQuestionLevel::Easy:
            Question.Number1 = RandNumber(1, 50);
            Question.Number2 = RandNumber(1, 50);
            break;
        case enQuestionLevel::Med:
            Question.Number1 = RandNumber(50, 500);
            Question.Number2 = RandNumber(50, 500);
            break;
        case enQuestionLevel::Hard:
            Question.Number1 = RandNumber(500, 5000);
            Question.Number2 = RandNumber(500, 5000);
            break;
    }
    Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationsType);
    Question.QuestionLevel = QuestionLevel;
    return Question;
}

// Function to generate quiz questions
void GenerateQuizzQuetions(stQuizz& Quizz) {
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

// Function to read the user's answer to a question
int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

// Function to print a quiz question
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << " " << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationsType) << " " << Quizz.QuestionList[QuestionNumber].Number2 << "\n----------\n";
}

// Function to correct the user's answer to a question
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    } else {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :-)\n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

// Function to ask and correct all quiz questions
void AskAndCorrectQuestionListAnswer(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

// Function to get the final results text
string GetFinalResultsText(bool Pass) {
    return Pass ? "PASS :-)" : "Fail :-(";
}

// Function to print the quiz results
void PrintQuizzResults(stQuizz Quizz) {
    cout << "\n-------------------------------------\n\n";
    cout << "Final Results: " << GetFinalResultsText(Quizz.isPass) << "\n";
    cout << "-------------------------------------\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level: " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type: " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswer << endl;
    cout << "-------------------------------------\n\n";
}

// Function to play the math game
void PlayMathGame() {
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOperationsType();
    GenerateQuizzQuetions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResults(Quizz);
}

// Function to reset the screen
void ResetScreen() {
    system("cls");
    system("color 0F");
}

// Function to start the game and handle replay
void StartGame() {
    char playAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();       
        cout << "\nDo you want to play again? Y/N? ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL)); // Seed the random number generator
    StartGame(); // Start the game
    return 0;
}
