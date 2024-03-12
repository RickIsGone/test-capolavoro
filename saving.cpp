#include <fstream>
#include "classes.h"
#define HIGHTIME 30
#define KILLED 40

void game::save(){
    std::ofstream file("saveFile.rktd");
    file<<"tempo sopravvissuto "<<HIGHTIME<<"\n";
    file<<"mostri uccisi "<<KILLED;

    file.close();
}