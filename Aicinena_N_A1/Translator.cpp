#include "Translator.h"

Translator::Translator() {
    myModel = new Model; //add myModel to the heap
}

Translator::~Translator() {
    delete myModel; //garbage collect by deleting myModel object with the destructor
}

string Translator::translateEnglishWord(string word) {
    string translatedWord = "";
    for(int i = 0; i < word.size(); ++i) {
        if(myModel->isVowel(word[i])) { //go through whole string and check if its a vowel or cons.
            //translate each accordingly to robber rules
            translatedWord += myModel->translateSingleVowel(word[i]);
        } else {
            translatedWord += myModel->translateSingleConsonant(word[i]);
        }
    }
    return translatedWord; //return robber translation
}

string Translator::translateEnglishSentence(string sentence) {
    string translatedSentence = "";
    for(int i = 0; i < sentence.size(); ++i) { //same as translateEnglishWord so far
        if(myModel->isVowel(sentence[i])) {
                translatedSentence += myModel->translateSingleVowel(sentence[i]);
        } else {
            if(sentence[i] == ' ') { //this method must check for spaces because the string is a sentence
                translatedSentence += " "; //when the char is a space, add a space to the translation
            } else { 
                translatedSentence += myModel->translateSingleConsonant(sentence[i]); //if no space then translate as usual
            }
        }
    }
    return translatedSentence; //return robber translation
}