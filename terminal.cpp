// Pay1oad PE Parser
// Terminal Class Header
//
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <iostream>
#include <iomanip>
#include "main.h"
#include "terminal.h"

namespace Terminal
{

    void printLogo() {
        printLine();
        std::cout << "A pay1oad Project :                          " << std::endl;
        std::cout << " ____  _____   ____                          " << std::endl;
        std::cout << "|  _ \\| ____| |  _ \\ __ _ _ __ ___  ___ _ __ " << std::endl;
        std::cout << "| |_) |  _|   | |_) / _` | '__/ __|/ _ \\ '__|" << std::endl;
        std::cout << "|  __/| |___  |  __/ (_| | |  \\__ \\  __/ |   " << std::endl;
        std::cout << "|_|   |_____| |_|   \\__,_|_|  |___/\\___|_|   " << std::endl << std::endl;
        std::cout << std::setw(59) << "brought to you by Alex4386" << std::endl;
        std::cout << std::setw(59) << VERSION << std::endl << std::endl;
    }

    void licenseFull() {
        std::cout << "Distributed under Hakurei Reimu Public License" << std::endl;
        std::cout << "Copyright (c) Alex4386" << std::endl;
        std::cout << "https://github.com/Alex4386/Pay1oad-PE-Parser" << std::endl;
        printLine();
    }

    void helpScreen(char* fileName) {
        printIntro();
        std::cout << "Usage:" << std::endl;
        std::cout << fileName << " fileName" << std::endl;
        std::cout << std::endl;
        std::cout << "This PE Parser comes with Fantasy Seal(tm) Technology." << std::endl;
    }

    void printLine() {
        std::cout << "===========================================================" << std::endl;
    }

    void printIntro() {
        printLogo();
        licenseFull();
    }

    void printIntroQuick() {
        printLogo();
        licenseShort();
    }

    void licenseShort() {
        std::cout << "Copyright (c) Alex4386, Distributed under HRPL" << std::endl;
        std::cout << "https://github.com/Alex4386/Payload-PE-Parser" << std::endl;
        printLine();
    }

};

