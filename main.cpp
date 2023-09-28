#include "World.h"
#include "engine/Application.h"
#include <iostream>

int main(int argc, char* argv[]) {

    std::string pathToFile("..\\data\\smile.txt");

    try {
        World w(pathToFile);
        //Код ниже запускает выполнение приложения.
        Application app("Football");
        app.run(w);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}