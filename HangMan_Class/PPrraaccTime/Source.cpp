#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std;

class HangMan
{
private:
    string TheSecretWord;
    string UsedAlready;
    string TheWordFiller;    
    char PlayerGuess{};
    char PlayAgain{};
    int WrongGuess{};
public:
    HangMan();    
    bool FindPlayerGuess(char PlayerGuess, string SecretWord);
    char GetPlayerGuess(string GuessedAlready);
    bool AskToPlayAgain();
    void PlayGame();
    void WelcomeMessage();
    void ASCII_Art();
};

HangMan::HangMan()
{    
    
}

void HangMan::WelcomeMessage()
{
    cout << "***** Welcome to GUESS THE WORD! *****\n\n";
    ASCII_Art();
    cout << "\n\nYou are a SECRET AGENT. Your job is to reveal the SECRET WORD.\n\n";
    cout << "Can you guess the SECRET WORD without running out of lives!\n\n";
    cout << "You will try to guess the SECRET WORD by entering one letter at a time.\n\n";
    cout << "The number of lives given, will depend on the SECRET WORD that is provided.\n\n";
    cout << "GOOD LUCK!!!\n\n"; 
    
}

void HangMan::ASCII_Art()
{
    cout << "                _________                       \n";
    cout << "                |        |                      \n";
    cout << "                |        |                      \n";
    cout << "                |       (O)                     \n";
    cout << "                |      __|__                    \n";
    cout << "                |        |                      \n";
    cout << "                |      _/ \\_                   \n";
    cout << "                |                               \n";
    cout << "            ____|____                           \n";
}

bool HangMan::FindPlayerGuess(char PlayerGuess, string SecretWord)
{
    return (SecretWord.find(PlayerGuess) != string::npos);
}

char HangMan::GetPlayerGuess(string GuessedAlready)
{    
    cout << "Guess a letter please: ";
    cin >> PlayerGuess;
    PlayerGuess = toupper(PlayerGuess);
    system("cls");

    while (FindPlayerGuess(PlayerGuess, UsedAlready))
    {
        cout << PlayerGuess << " has been guessed already! Try another letter!\n";
        cout << "Guess a letter: ";
        cin >> PlayerGuess;
        PlayerGuess = toupper(PlayerGuess);
    }
    if (FindPlayerGuess(PlayerGuess, TheSecretWord))
    {
        cout << "Good job, " << PlayerGuess << " is found in the word!\n\n";

        for (size_t i = 0; i < TheSecretWord.size(); i++)
            if (TheSecretWord[i] == PlayerGuess)
                TheWordFiller[i] = PlayerGuess;       
    }    
    else
    {
        cout << "Very nice try, but " << PlayerGuess << " is not found in the word!\n\n";
        WrongGuess++;
    }
    if (TheWordFiller == TheSecretWord)
    {
        cout << "!!!! GREAT WORK AGENT, YOU HAVE REVEALED THE SECRET WORD !!!!\n\n";
        ASCII_Art();
    }
    return PlayerGuess;    
}

bool HangMan::AskToPlayAgain()
{    
    cout << "Would you like to play again?\n\n";
    cout << "Enter Y or N\n\n";
    cin >> PlayAgain;

    cin.clear();
    cin.ignore();
    
    PlayAgain = toupper(PlayAgain);
   
    system("cls");
    
    return (PlayAgain == 'Y');
}

void HangMan::PlayGame()
{
    do {
        
        vector<string> Words = { "DEVIN", "CAT", "DOG" };
        random_shuffle(Words.begin(), Words.end());
        TheSecretWord = Words[0];
        TheWordFiller = string(TheSecretWord.size(), '*');
        UsedAlready = "";
        WrongGuess = 0;
        int MaxLives = TheSecretWord.size() + 2;

        WelcomeMessage();

        while ((WrongGuess < MaxLives) && (TheWordFiller != TheSecretWord))
        {
            cout << "\nYou have " << (MaxLives - WrongGuess) << " lives remaining...\n\n";
            cout << "\nYou have used the letters...\n" << UsedAlready << endl;
            cout << "\nSo far the word is...\n" << TheWordFiller << "\n\n";

            UsedAlready += GetPlayerGuess(UsedAlready);            
        }
        if (WrongGuess == MaxLives)
        {
            cout << "\nYou have been hung!\n";
            ASCII_Art();
        }
        cout << "\nThe word was " << TheSecretWord << "\n\n";;

    } while (AskToPlayAgain());
}

int main()
{ 
    srand(time(NULL));
    HangMan obj;
    obj.PlayGame();    
   
    cout << endl;
    system("pause");
    return 0; 
}


