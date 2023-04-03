#include <iostream>
#include <fstream>
#include "Pipeline.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " '<command1> [| <command2> | ...]'" << std::endl;
        return 1;
    }
    try {
        Pipeline pipeline((std::string(argv[1])));
        pipeline.Execute();
    } catch (std::exception& exc) {
        std::cout << exc.what();
    }
    return 0;
}
