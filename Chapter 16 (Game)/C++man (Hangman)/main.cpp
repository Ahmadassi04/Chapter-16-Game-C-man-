#include <iostream>
#include <vector>
#include <string>
#include "Random.h"

namespace Settings
{
    const int wrongGuesses{6};
}

namespace WordList{

    std::vector<std::string> words {"mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};

std::string getRandomWord(){
    return words[Random::get<std::size_t>(0,words.size()-1)];
}
}
class session{
private:
    std::string m_words{WordList::getRandomWord()};
    int m_wrongGuesses {Settings::wrongGuesses};
    std::vector<bool> m_guessed{std::vector<bool>(26)};

    std::size_t toIndex(char c){return static_cast<std::size_t>((c % 32)-1);}

public:

    int wrongGuessesLeft(){ return m_wrongGuesses;}
    void removeGuess() { --m_wrongGuesses;}

    std::string getWord() {return m_words;}
    bool isLetterGuessed(char c){return m_guessed[toIndex(c)];}
    void setLetterGuessed(char c){m_guessed[toIndex(c)]= true;}

    bool isLetterInWord(char c){
        for (auto ch : m_words){
            if (ch == c){
                return true;
            }
        }
    return false;
    }
    bool won(){
        for(auto c : m_words){
            if(!isLetterGuessed(c)){
                return false;
            }
        }
        return true;
    }

};

void sentence( session& s){

    for(auto e : s.getWord()){
        if(s.isLetterGuessed(e)){
            std::cout << e;
        }
        else{
            std::cout << '_';
        }
    }

    std::cout << "   Wrong guesses: ";
    for (int i=0; i < s.wrongGuessesLeft(); ++i)
        std::cout << '+';


    for (char c='a'; c <= 'z'; ++c)
        if (s.isLetterGuessed(c) && !s.isLetterInWord(c))
            std::cout << c;

    std::cout << '\n';
}
char guess(session& s){

    while(true){

        std::cout << "Enter your next letter: ";
        char letter{};
        std::cin >> letter;

    if(!std::cin){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
    }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if ((letter < 'a' || letter > 'z')){
            std::cout << "That wasn't a valid input.  Try again." << '\n';
        continue;
    }
    else{
        std::cout << "You entered : " << letter << '\n';
    }

     if(s.isLetterGuessed(letter)){
        std::cout << "You already guessed that.  Try again.\n";
        continue;
        }
    return letter;
    }

}

void progress(session &s, char c)
{
    s.setLetterGuessed(c);

    if (s.isLetterInWord(c))
    {
        std::cout << "Yes, '" << c << "' is in the word!\n";
        return;
    }

    std::cout << "No, '" << c << "' is not in the word!\n";
    s.removeGuess();
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)" << '\n';
    std::cout << "To win: guess the word.  To lose: run out of pluses." << '\n';
    std::cout << '\n';

    std::cout << "The word: ";
    session s{};

    while(s.wrongGuessesLeft() && !s.won()){

    sentence(s);
    char letter{guess(s)};
    progress(s,letter);

    }
    sentence(s);

     if (!s.wrongGuessesLeft())
        std::cout << "You lost!  The word was: " << s.getWord() << '\n';
    else
        std::cout << "You won!\n";

    return 0;
}
