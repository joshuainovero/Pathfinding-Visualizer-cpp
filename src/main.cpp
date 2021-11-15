#include "utils/App.hpp"
#include <time.h>

int main(){
    srand(time(0));
    App app(45);
    app.run();
}