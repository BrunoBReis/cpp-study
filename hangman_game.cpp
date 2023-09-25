#include <iostream>
#include <string>
#include <map>     // dictionary library
#include <vector>  // dinamic list library
#include <fstream> // files library
#include <ctime>   // seed for random
#include <cstdlib> // random
using namespace std;

// global variables
string secret_word = "MELANCIA";
map<char, bool> guessed;
vector<char> wrong_guess;
const string file_name = "words.txt";

bool word_verify(char guess);
bool word_verify_new(char guess);
bool verify_vector(char guess, vector<char> name);
bool dont_get_right();
bool dont_hangman();
void screen_game();
void show_wrong_guesses();
void show_word_size();
void get_word();
void end_game_message();
vector<string> read_file();
void randomize_words();

int main()
{

    screen_game();

    read_file();
    randomize_words();

    cout << secret_word << endl;

    // bool dont_get_right = true;
    // bool dont_hangman = true;

    // creating a loop for the game
    while (dont_get_right() && dont_hangman())
    {

        // print wrong letters

        show_wrong_guesses();

        cout << endl;

        // print word's size and letters complete

        show_word_size();

        cout << endl;

        cout << "What is your guess? ";

        get_word();
    }

    cout << "End game." << endl;

    end_game_message();

    return 0;
}

bool word_verify(char guess)
{
    // verify input letter in secret_word
    for (int i = 0; i < secret_word.size(); i++)
    {
        if (guess == secret_word[i])
        {
            return true;
        }
    }
    return false;
}

bool word_verify_new(char guess)
{
    // verify input letter in secret_word with new formatation
    for (char letter : secret_word)
    {
        if (guess == letter)
        {
            return true;
        }
    }
    return false;
}

bool verify_vector(char guess, vector<char> name)
{
    // verify if letter was alredy store in vector
    for (int i = 0; i < name.size(); i++)
    {
        if (guess == name[i])
        {
            return false;
        }
    }
    return true;
}

bool dont_get_right()
{
    // verify if all word was written
    for (int i = 0; i < secret_word.size(); i++)
    {
        if (!guessed[secret_word[i]])
        {
            return true;
        }
    }
    return false;
}

bool dont_hangman()
{
    // verify all tries
    if (wrong_guess.size() < 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void screen_game()
{
    // print screen game note
    cout << "********************" << endl;
    cout << "*** Hangman game ***" << endl;
    cout << "********************" << endl;
    cout << endl;
}

void show_wrong_guesses()
{
    // show all wrong guesses
    cout << "Wrong guesses: " << endl;
    for (int i = 0; i < wrong_guess.size(); i++)
    {
        cout << wrong_guess[i] << " ";
    }
}

void show_word_size()
{
    // show word's size
    for (int i = 0; i < secret_word.size(); i++)
    {
        if (guessed[secret_word[i]])
        {
            cout << secret_word[i] << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
}

void get_word()
{
    // get word from user and verifies it
    char guess;
    cin >> guess;

    guess = toupper(guess);

    guessed[guess] = true;

    cout << "Your guess was " << guess << endl;

    // verify input letter
    if (word_verify(guess))
    {
        cout << "You guessed right!" << endl;
    }
    else
    {
        cout << "You guessed wrong." << endl;
        if (verify_vector(guess, wrong_guess))
        {
            wrong_guess.push_back(guess);
        }
        else
        {
            cout << "This letter was already used. " << endl;
        }
    }
    cout << endl;
}

void end_game_message()
{
    // end game message
    if (dont_get_right())
    {
        cout << "Try again" << endl;
        cout << "The secret word is " << secret_word << "!" << endl;
    }
    else
    {
        cout << "Congrats! The secret word is " << secret_word << "." << endl;
    }
}

vector<string> read_file()
{
    ifstream file; // type of variable that reads files

    file.open(file_name);

    int count_words;
    file >> count_words;

    vector<string> words_file;

    for (int i = 0; i < count_words; i++)
    {
        string word;
        file >> word;
        words_file.push_back(word);
    }
    return words_file;
}

void randomize_words()
{
    vector<string> words = read_file(); // is this some kind of polimorfism?

    srand(time(NULL));

    int sort;
    sort = rand() % words.size();

    secret_word = words[sort];
}