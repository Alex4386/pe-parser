// Pay1oad PE Parser
// FileLoad Class
//
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <fstream>
#include <sys/stat.h>
#include "fileload.h"

bool FileLoad::isLoaded() { return this->loaded; }

void FileLoad::setFile(char* fileName) {
    this->fileName = fileName;
}

int FileLoad::loadFile() {
    if (this->isLoaded()) {
        return 1;
    }
    struct stat fileSizeResult;
    if (stat(this->fileName, &fileSizeResult) != 0) {
        //std::cout << "ERROR: " << fileName << ", No Such File detected" << std::endl;
        return 11;
    }
    this->fileSize = fileSizeResult.st_size;
    
    this->fileStream.open(this->fileName, std::ios::in | std::ios::binary);
    this->data = new char[this->fileSize];

    if (!this->fileStream) {
        return 12;
    }

    if (!fileStream.read(this->data, this->fileSize)) {
        //std::cout << "FileRead ERROR!" << std::endl;
        return 13;
    }

    fileStream.close();
    loaded = true;
    return 0;
}

char* FileLoad::getRawBytes() {
    if (!this->isLoaded()) { return nullptr; }
    return this->data;
}

int FileLoad::getFileSize() {
    if (!this->isLoaded()) { return -1; }
    return this->fileSize;
}

char* FileLoad::getFileName() {
    return this->fileName;
}

unsigned char* FileLoad::readBinary(int size, int address) {
    if (!this->isLoaded()) { return nullptr; }
    unsigned char* retu = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        retu[i] = this->data[address+i];
    }
    return retu;
}
