// PE Parser
// Terminal Namespace
//
// Copyright (c) Alex4386 and PE-Parser Contributors
//
// Source Code is distributed under HRPL.

#ifndef _TERMINAL_HPP
#define _TERMINAL_HPP

#include <string>

class Terminal
{
    public:
    
        const static std::string repositoryUrl;
        const static std::string copyrightNotice;

        static void printLogo();

        static void licenseFull();

        static void helpScreen(char* fileName);

        static void printLine();

        static void printIntro();

        static void printIntroQuick();

        static void licenseShort();

};

#endif
