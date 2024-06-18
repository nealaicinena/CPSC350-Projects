#include "SpeakerView.h"
#include "MonoStack.h"

int main(int argc, char **argv) {
    SpeakerView *mySpeakerView = new SpeakerView("input.txt");
    cout << mySpeakerView->checkColumns() << endl; //output to console all the column checks
    delete mySpeakerView; //deallocate memory

    return 0;
}