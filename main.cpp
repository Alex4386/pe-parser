// Pay1oad PE Parser
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include "extension.h"
#include "parser.h"
#include "terminal.h"

void analysisSession(PEParser parser);
int parseDos(char* fileName);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        Terminal::helpScreen(argv[0]);
        return 0;
    } else if (argc >= 2) {
        Terminal::printIntroQuick();
        for (int i = argc-1; i >= 1; i--) {
            PEParser parser(argv[i]);
            int error = parser.parseFile();
            if (error != 0) {
                bool errorHandled = false;
                int nestedError = -1;
                std::cout << "ERROR!!" << std::endl;
                switch(error) {
                    case 1:
                        std::cout << "Failed to Load File!!" << std::endl;
                        break;
                    case 11:
                        std::cout << "Filesize is too small to be valid PE File" << std::endl;
                        break;
                    case 12:
                        std::cout << "Invalid PE Signature!" << std::endl;
                        break;
                    case 13:
                        std::cout << "NT Header Pointer is pointing outside of file" << std::endl;
                        Terminal::printLine();
                        std::cout << "Fallback to MZ Parser...." << std::endl;
                        Terminal::printLine();
                        nestedError = parseDos(argv[i]);
                        if (nestedError == 0) { errorHandled = true; }
                        break;
                    case 14:
                        std::cout << "Invalid NT Header Signature!" << std::endl;
                        break;
                    default:
                        std::cout << "Unknown Error!" << std::endl;
                }
                Terminal::printLine();
                if (!errorHandled) {
                    return 1;
                }
            } else {
                analysisSession(parser);
            }
            if (i != 1) {
                std::cout << std::endl << std::endl;
                Terminal::printLine();
                std::cout << "Analysing Next File: " << argv[i-1] << std::endl;
                Terminal::printLine();
            }
        }
        
    } else {
        std::cout << "Too much argument detected!" << std::endl;
    }
}

void analysisSession(PEParser parser) {
    std::cout << "Pre-Analysis:" << std::endl;
    std::cout << "Requested File: " << parser.getFileName() << std::endl;
    std::cout << "File Size: " << parser.getFileSize() << " bytes (0x";
    std::cout << std::setfill('0') << std::setw(8) << std::hex << parser.getFileSize() << ")" << std::endl;
    Terminal::printLine();
    std::cout << "NT Header (COFF Header):" << std::endl;
    std::cout << "NT Header Address: " << "0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getNTHeaderPointer() << std::endl;
    std::cout << "Machine Code: " << "0x" << std::setfill('0') << std::setw(4) << std::hex << parser.getMachineCode();
    std::cout << " (" << parser.getMachineTypeFromMachineCode() << ")" << std::endl;
    std::cout << "Number of Sections: " << parser.getSectionCount() << std::endl;
    std::cout << "File Creation Time: " << parser.getHumanReadableTimeStamp() << std::endl;
    std::cout << "File Characteristics: " << std::dec << parser.getFileCharacteristics();
    std::cout << " (0x" << std::setfill('0') << std::setw(4) << std::hex << parser.getFileCharacteristics() << ")" << std::endl;
    std::cout << parser.getHumanReadableFileCharacteristics() << std::endl;
    Terminal::printLine();
    std::cout << "Standard COFF Header:" << std::endl;
    std::cout << "COFF Header Type: " << parser.getStandardCOFFHeaderType() << std::endl;
    std::cout << "Linker Version: " << std::dec << (int)parser.getLinkerMajorVersion() << "." << (int)parser.getLinkerMinorVersion() << std::endl; 
    std::cout << "Size Of Code: " << std::dec << parser.getSizeOfCode() << " bytes (0x";
    std::cout << std::setfill('0') << std::setw(8) << std::hex << parser.getSizeOfCode() << ")" << std::endl;
    std::cout << "EntryPoint: 0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getEntryPoint() << std::endl;
    Terminal::printLine();
    std::cout << "Optional COFF Header (Windows Apps Only):" << std::endl;
    std::cout << "Image Base: 0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getImageBase() << std::endl;
    std::cout << "Section Alignment: 0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getSectionAlignment() << std::endl;
    std::cout << "File Alignment: 0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getFileAlignment() << std::endl;
    std::cout << "File Alignment and Section Alignment Validity: " << std::boolalpha << parser.checkSectionAlignmentAndFileAlignment() << std::endl;
    std::cout << "OS Version: " << std::dec << (int)parser.getOSMajorVersion() << "." << (int)parser.getOSMinorVersion() << std::endl; 
    std::cout << "Image Version: " << std::dec << (int)parser.getImageMajorVersion() << "." << (int)parser.getImageMinorVersion() << std::endl; 
    std::cout << "SubSystem Version: " << std::dec << (int)parser.getSubSystemMajorVersion() << "." << (int)parser.getSubSystemMinorVersion() << std::endl; 
    std::cout << "Size Of Image: " << std::dec << parser.getSizeOfImage() << " bytes (0x";
    std::cout << std::setfill('0') << std::setw(8) << std::hex << parser.getSizeOfImage() << ")" << std::endl;
    std::cout << "Subsystem: " << std::dec << parser.getSubSystem() << " (" << parser.getHumanReadableSubSystem() << ")" << std::endl;
    std::cout << "DLL Characteristics: " << std::dec << parser.getDLLCharacteristics();
    std::cout << " (0x" << std::setfill('0') << std::setw(4) << std::hex << parser.getDLLCharacteristics() << ")" << std::endl;
    std::cout << parser.getHumanReadableDLLCharacteristics();
    Terminal::printLine();
    std::cout << "Parsing Complete." << std::endl;
}

int parseDos(char* fileName) {
    MZParser parser(fileName);
    int error = parser.parseFile();
    if (error != 0) {
        std::cout << "ERROR!!" << std::endl;
        switch(error) {
            case 1:
                std::cout << "Failed to Load File!!" << std::endl;
                break;
            case 11:
                std::cout << parser.getTotalSize() << " " << parser.getFileSize() << std::endl;
                std::cout << "Filesize is too small to be valid MZ File" << std::endl;
                break;
            default:
                std::cout << "Unknown Error!" << std::endl;
        }
        return error;
    }

    std::cout << "Pre-Analysis:" << std::endl;
    std::cout << "Requested File: " << parser.getFileName() << std::endl;
    std::cout << "File Size: " << parser.getFileSize() << " bytes (0x";
    std::cout << std::setfill('0') << std::setw(8) << std::hex << parser.getFileSize() << ")" << std::endl;
    Terminal::printLine();
    std::cout << "MZ Header:" << std::endl;
    std::cout << "Page Count: " << parser.getHowManyPages() << std::endl;
    std::cout << "Last Page Size: " << parser.getLastPageBytes() << " bytes";
    std::cout << " (0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getLastPageBytes() << ")" << std::endl;
    std::cout << "Total Executable Size: " << std::dec << parser.getTotalSize() << " bytes";
    std::cout << " (0x" << std::setfill('0') << std::setw(8) << std::hex << parser.getTotalSize() << ")" << std::endl;

}
