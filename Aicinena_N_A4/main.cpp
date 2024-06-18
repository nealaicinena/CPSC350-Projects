#include <string>
#include <iostream>
#include "ServiceCenter.h"

using namespace std;

int main(int argc, char **argv){
    ServiceCenter* sc = new ServiceCenter("input.txt");
    sc->serviceCenterSimulation();
    
    delete sc;

    return 0;
}