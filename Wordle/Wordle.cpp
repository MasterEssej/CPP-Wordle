#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Grey = 7,
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};

void Wordl();
string GetWord();
bool CheckGuess(string guess);
int main()
{
    Wordl();

    return 0;
}

void Wordl()
{
    string input;
    string word;
    bool game = true;
    while (game)
    {
        word = GetWord();
        int tries = 0;

        system("cls");
        cout << "Guess the 5 letter word.\|\n-------------------------" << endl;
        //cout << BACKGROUND(BackgroundColor::Grey, "  ");
        bool correct = false;
        while (!correct)
        {
            if (tries >= 6)
            {
                cout << "Too many tries! The word was: " << word << endl;
                break;
            }

            cin >> input;
            tries++;

            if (input.length() != word.length() || CheckGuess(input) == false)
            {
                cout << "Invalid word." << endl;
            }
            else
            {
                for (int x = 0; x < word.length(); x++)
                {
                    input[x] = toupper(input[x]);
                    word[x] = toupper(word[x]);
                }

                if (input == word)
                {
                    cout << BACKGROUND(BackgroundColor::Green, input);
                    correct = true;
                }
                else
                {
                    for (int i = 0; i < word.length(); i++)
                    {
                        size_t found = word.find(input[i]);
                        if (found != string::npos)
                        {
                            if (input[i] == word[i])
                            {
                                cout << BACKGROUND(BackgroundColor::Green, input[i]);
                            }
                            else
                            {
                                cout << BACKGROUND(BackgroundColor::Yellow, input[i]);
                            }
                        }
                        else
                        {
                            cout << BACKGROUND(BackgroundColor::Red, input[i]);
                        }
                    }
                }
                cout << endl;
            }
        }
        int choice;
        cout << "\nPlay again? (1/2)\n1.Yes\n2.No" << endl;
        while (true)
        {
            cin >> choice;
            if (choice == 1)
            {
                break;
            }
            else if (choice == 2)
            {
                game = false;
                break;
            }
        }
    }
}

string GetWord()
{
    string word;
    srand(time(NULL));
    int random = rand() % 8598 + 1;

    ifstream wordlist("words.txt");
    for (int x = 1; x < random; x++)
    {
        getline(wordlist, word);
    }
    wordlist.close();

    return word;
}

bool CheckGuess(string guess)
{
    string word;

    ifstream wordlist("words.txt");
    for (int x = 1; x < 8598; x++)
    {
        getline(wordlist, word);
        if (word == guess)
        {
            wordlist.close();
            return true;
        }
    }
    wordlist.close();
    return false;
}