// PE Parser
// FileLoad Class Header 
//
// Copyright (c) Alex4386 and PE-Parser Contributors
//
// Source Code is distributed under HRPL.

#pragma once
#include <fstream>

class FileLoad {
    private:
        char* fileName;
        char* data;
        int fileSize;
        std::fstream fileStream;
        bool loaded;        
    public:
        FileLoad();
        FileLoad(char* fileName) {
            loaded = false;
            this->fileName = fileName;
        }
        bool isLoaded();
        void setFile(char* fileName);
        int loadFile();
        char* getRawBytes();
        int getFileSize();
        char* getFileName();
        unsigned char* readBinary(int size, int address);
};
