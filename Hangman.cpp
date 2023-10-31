#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<char> randomWord(vector<char>&guessedLetters)
{
    int numberOfLines=0;
    fstream file;
    vector<char> wordVector;
    string word;
    file.open("words.txt");
    if (file.is_open())
    {
        while (!file.eof()) 
        {
            getline(file, word);
            numberOfLines++;
        }
        int randomLineNumber;
        srand((unsigned)time(NULL));
        randomLineNumber = 1 + rand() % numberOfLines;
        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 1; i <= randomLineNumber; i++)
        {
            getline(file, word);               
        }
        for (int i = 0; i < word.size(); i++)
        {
            wordVector.push_back(toupper(word[i]));
            guessedLetters.push_back('-');
        }
        return wordVector;
    }
}
int alreadyUsed(vector<char>& guessedLetters, vector<char>& missedLetters, char input)
{
        for (int i = 0; i < guessedLetters.size(); i++)
        {
            if (guessedLetters[i] == input)
            {
                return 1;
            }
        }
    if(missedLetters.size() != 0)
    {
        for (int i = 0; i < missedLetters.size(); i++)
        {
            if (missedLetters[i] == input)
            {
                return 2;
            }
        }
    }
    return 0;
}
bool letterGuesser(vector<char>& wordVector, vector<char>& guessedLetters, vector<char>& missedLetters)
{
    bool ifGuessed = false;
    char input;
    cout << "Pick a letter:" << endl;
    cin >> input;
    input = toupper(input);
    while (!isalpha(input) || alreadyUsed(guessedLetters, missedLetters, input) != 0)
    {
        if (!isalpha(input))
        {
            cout << "That's not a letter, please choose a letter" << endl;

        }
        if (alreadyUsed(guessedLetters, missedLetters, input) == 1)
        {
            cout << "You guessed this letter already, try another one" << endl;
        }
        if (alreadyUsed(guessedLetters, missedLetters, input) == 2)
        {
            cout << "This letter is already in Missed letters list, try another one" << endl;
        }
        cin >> input;
        input = toupper(input);
    }
    for (int i = 0; i < wordVector.size(); i++)
    {
        if (wordVector[i] == input)
        {
            guessedLetters[i] = input;
            ifGuessed = true;
        }
    }
    if (ifGuessed == true)
    {
        return true;
    }
    missedLetters.push_back(input);
    return false;
}
void printVector(vector<char>word)
{
    for (int i = 0; i < word.size(); i++)
    {
        cout << word[i];
    }
    cout << endl;
}
void printHangman(int mistakes, vector<char>& guessedLetters, vector<char>& missedLetters, bool ifWon)
{
    cout << "    HANGMAN GAME" << endl;
    if (mistakes > 0)
    {
        cout << "       -";
    }
    if (mistakes > 1)
    {
        cout << "-";
    }
    if (mistakes > 2)
    {
        cout << "o";
    }
    if (mistakes > 3)
    {
        cout << endl << "         |";
    }
    if (mistakes > 4)
    {
        cout << endl << "         o";
    }
    if (mistakes > 5)
    {
        cout << endl << "        /";
    }
    if (mistakes > 6)
    {
        cout << "|";
    }
    if (mistakes > 7)
    {
        cout << "\\";
    }
    if (mistakes > 8)
    {
        cout << endl << "        /";
    }
    if (mistakes > 9)
    {
        cout  << " \\" << endl;
        cout << "     GAME OVER" << endl;
    }
    if (ifWon == true)
    {
        cout <<endl<< "     YOU WIN" << endl;
    }
    cout << endl << "  Chances Left: " << 10 - mistakes;
    cout << endl << endl << "     Your word:  ";
    cout << endl;
    int spacesToCenter;
    spacesToCenter = 9 - guessedLetters.size() / 2;
    while (spacesToCenter != 0)
    {
        cout << " ";
        spacesToCenter--;
    }
    printVector(guessedLetters);
    cout << "   Missed letters:  "<<endl;
    spacesToCenter = 9 - missedLetters.size() / 2;
    while (spacesToCenter != 0)
    {
        cout << " ";
        spacesToCenter--;
    }
    printVector(missedLetters);
    cout << endl;

}
int main()
{
    vector<char> wordVector;
    vector<char> guessedLetters;
    vector<char> missedLetters;
    wordVector = randomWord(guessedLetters);
    int chancesLeft = 10;
    bool ifWon = false;
    while(chancesLeft != 0 && wordVector != guessedLetters)
    {
        printHangman(10-chancesLeft, guessedLetters, missedLetters, ifWon);

        if (letterGuesser(wordVector, guessedLetters, missedLetters) == 0)
        {
            chancesLeft--;
        }
        if (wordVector == guessedLetters)
        {
            ifWon = true;
        }
        system("cls");
        
    }
    printHangman(10 - chancesLeft, guessedLetters, missedLetters, ifWon);
}