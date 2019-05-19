// Pay1oad PE Parser
// FileLoad Class Header 
//
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <string>
#include "fileload.h"

class PEParser {
    private:
        FileLoad* file;
        char* fileName;
        bool parsed;
        unsigned int ntHeaderPointer;
        unsigned short machineCode;
        unsigned int sectionCount;
        long timeStamp;
        unsigned short fileCharacteristics;
        unsigned int standardCOFFPointer;
        unsigned char linkerMajorVersion;
        unsigned char linkerMinorVersion;
        unsigned int sizeOfCode;
        unsigned int entryPoint;
        unsigned int imageBase;
        unsigned int winSpecificCOFF;
        unsigned int sectionAlignment;
        unsigned int fileAlignment;
        unsigned short osMajorVersion;
        unsigned short osMinorVersion;
        unsigned short imageMajorVersion;
        unsigned short imageMinorVersion;
        unsigned short subSystemMajorVersion;
        unsigned short subSystemMinorVersion;
        unsigned int sizeOfImage;
        unsigned short subSystem;
        unsigned short dllCharacteristics;

    public:
        PEParser(char* fileName) {
            this->file = new FileLoad(fileName);
            file->loadFile();

            parsed = false;
        }
        int parseFile();

        bool checkFileSize();
        char* getFileName();
        unsigned int getFileSize();
        bool checkPESignature();
        unsigned int getNTHeaderPointer();
        bool checkNTHeaderPointer();
        bool checkNTHeaderSignature();
        unsigned short getMachineCode();
        std::string getMachineTypeFromMachineCode();
        unsigned int getSectionCount();
        long getTimeStamp();
        std::string getHumanReadableTimeStamp();
        unsigned short getFileCharacteristics();
        std::string getHumanReadableFileCharacteristics();
        unsigned char* getStandardCOFFSignature();
        std::string getStandardCOFFHeaderType();
        unsigned char getLinkerMajorVersion();
        unsigned char getLinkerMinorVersion();
        unsigned int getSizeOfCode();
        unsigned int getEntryPoint();
        unsigned int getImageBase();
        unsigned int getSectionAlignment();
        unsigned int getFileAlignment();
        bool checkSectionAlignmentAndFileAlignment();
        unsigned short getOSMajorVersion();
        unsigned short getOSMinorVersion();
        unsigned short getImageMajorVersion();
        unsigned short getImageMinorVersion();
        unsigned short getSubSystemMajorVersion();
        unsigned short getSubSystemMinorVersion();
        unsigned int getSizeOfImage();
        unsigned short getSubSystem();
        std::string getHumanReadableSubSystem();
        unsigned short getDLLCharacteristics();
        std::string getHumanReadableDLLCharacteristics();



};