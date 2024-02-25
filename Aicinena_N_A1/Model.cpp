#include "Model.h"

Model::Model() {

}

Model::~Model() {

}

string Model::translateSingleConsonant(char consonant) {
    string translation;
    if(isupper(consonant)) { //checks if the letter is uppercase
        //if its upper, make the first letter uppercase and the duplicate letter lowercase
        //ex) L -> Lol
        translation = string(1, consonant) + 'o' + string(1, tolower(consonant)); //converting char to string for concatenation
    } else {
        //otherwise make both lowercase
        //ex) l -> lol
        translation = string(1, consonant) + 'o' + string(1, consonant);
    }
    return translation; //return the robber translation
}

string Model::translateSingleVowel(char vowel) {
    //vowels do not double up so no need to do the same condition in translateSingleConsonant
    string translation;
    translation = string(1, vowel);
    return translation;
}

bool Model::isVowel(char letter) {
    if(tolower(letter) == 'a' || tolower(letter) == 'e' || tolower(letter) == 'i' 
        || tolower(letter) == 'o' || tolower(letter) == 'u') { //checking if letter is any of these vowels
            return true;
        }
    return false;
}
