// Pay1oad PE Parser
// MZ Parser Header
//
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <string>
#include "fileload.h"

class MZParser {
    private:
        FileLoad* file;
        char* fileName;
        bool parsed;

        unsigned short lastPageBytes;
        unsigned short howManyPages;
        unsigned short relocations;
        unsigned short headerSize;
        unsigned short minMemory;
        unsigned short maxMemory;
        unsigned short initStackSegment; // relative
        unsigned short initStackPointer;
        unsigned short checksum;
        unsigned short initInstructionPointer;
        unsigned short initCodeSegment; // relative
        unsigned short relocationTableAddress;
        unsigned short howManyOverlays;
        unsigned short oemId;
        unsigned short oemInfo;

    public:
        MZParser(char* fileName) {
            this->file = new FileLoad(fileName);
            file->loadFile();

            parsed = false;
        }

        char* getFileName();
        unsigned int getFileSize();
        int parseFile();
        unsigned short getLastPageBytes();
        unsigned short getHowManyPages();
        unsigned int getTotalSize();
        bool validateTotalSize();
        unsigned short getRelocations();
        unsigned short getHeaderSize();
        unsigned short getMinMemory();
        unsigned short getMaxMemory();
        unsigned short getInitStackSegment();
        unsigned short getInitStackPointer();
        unsigned short getChecksum();
        unsigned short getInitInstructionPointer();
        unsigned short getInitCodeSegment();
        unsigned short getRelocationTableAddress();
        unsigned short getHowManyOverlays();
        unsigned short getOemId();
        unsigned short getOemInfo();
        unsigned short getEntryPoint();


};
