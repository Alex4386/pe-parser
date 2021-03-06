
#include <iostream>
#include <iomanip>
#include "terminal.hpp"
#define VERSION "v.0.3.0-alpha01"

const std::string Terminal::repositoryUrl = "https://github.com/Alex4386/PE-Parser";
const std::string Terminal::copyrightNotice = "Copyright (c) PE-Parser Contributors";

void Terminal::printLogo() {
    printLine();
    std::cout << " ____  _____   ____                          " << std::endl;
    std::cout << "|  _ \\| ____| |  _ \\ __ _ _ __ ___  ___ _ __ " << std::endl;
    std::cout << "| |_) |  _|   | |_) / _` | '__/ __|/ _ \\ '__|" << std::endl;
    std::cout << "|  __/| |___  |  __/ (_| | |  \\__ \\  __/ |   " << std::endl;
    std::cout << "|_|   |_____| |_|   \\__,_|_|  |___/\\___|_|   " << std::endl << std::endl;
    std::cout << std::setw(59) << "Powered by pay1oad" << std::endl;
    std::cout << std::setw(59) << VERSION << std::endl << std::endl;
}

void Terminal::licenseFull() {
    std::cout << "Distributed under Hakurei Reimu Public License" << std::endl;
    std::cout << copyrightNotice << std::endl;
    std::cout << repositoryUrl << std::endl;
    printLine();
}

void Terminal::helpScreen(char* fileName) {
    printIntro();
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << fileName << " options fileName" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help: Show this help screen" << std::endl;
    std::cout << std::endl;
    std::cout << "This PE Parser comes with Fantasy Seal(tm) Technology." << std::endl;
}

void Terminal::printLine() {
    std::cout << "===========================================================" << std::endl;
}

void Terminal::printIntro() {
    printLogo();
    licenseFull();
}

void Terminal::printIntroQuick() {
    printLogo();
    licenseShort();
}

void Terminal::licenseShort() {
    std::cout << "Copyright (c) Alex4386, Distributed under HRPL" << std::endl;
    std::cout << "https://github.com/Alex4386/PE-Parser" << std::endl;
    printLine();
}


