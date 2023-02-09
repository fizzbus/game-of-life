#ifndef WORDS_H
#define WORDS_H

#include <QString>
#include <iostream>

using namespace std;

struct GuessLetter {
    QChar letter;
    int pos;
    bool found;
};

class Word
{
public:
    const wchar_t* list[30] = {
        L"кофейник",
        L"ледокол",
        L"авангард",
        L"объявление",
        L"баржа",
        L"инопланетянин",
        L"питомец",
        L"площадь",
        L"кафедра",
        L"крыша",
        L"младенец",
        L"кисель",
        L"барахло",
        L"багажник",
        L"катапульта",
        L"деньги",
        L"одеяло",
        L"контора",
        L"коготь",
        L"водитель",
        L"парламент",
        L"тетрадь",
        L"кассета",
        L"сундук",
        L"портфель",
        L"корень",
        L"жвачка",
        L"кресло",
        L"укроп",
        L"барашек"
    };
    QString selected;
    GuessLetter *guessLetters;
    Word(){};
    void setWord(QString selectedWord) {
        selected = selectedWord;
        guessLetters = (GuessLetter *)malloc(selected.length() * sizeof(GuessLetter));
        for (int i = 0; i < this->selected.length(); i++){
            guessLetters[i].letter = selected.toStdU16String()[i];
            guessLetters[i].pos = i;
            guessLetters[i].found = false;
         }
    }

    QString outputMaskedWord() {
        QString output;
        for(int i = 0; i < selected.length(); i++){
            guessLetters[i].found?
                output.append(guessLetters[i].letter) : output.append('?');
        }
        return output;
    }

    bool tryGuess(QChar c) {
        bool guessSuccess = false;
        for (int i = 0; i < selected.length(); i++){
            if(c == guessLetters[i].letter){
                guessLetters[i].found = true;
                guessSuccess = true;
            }
         }
        return guessSuccess;
    }
    bool isWordGuessed(){
        for(int i = 0; i < selected.length(); i++) {
            if(guessLetters[i].found == false) return false;
        }
        return true;
    }
};

#endif // WORDS_H
