// PE Parser
// MZ Parser Core
//
// Copyright (c) Alex4386 and PE-Parser Contributors
//
// Source Code is distributed under HRPL.

#include "mzParser.h"
#include "extension.h"

int MZParser::parseFile() {
    if (!file->isLoaded()) {
        return 1;
    }

    lastPageBytes = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x02));
    howManyPages = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x04));
    
    if (!validateTotalSize()) {
        return 11;
    }

    relocations = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x06));
    headerSize = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x08));
    minMemory = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x0A));
    maxMemory = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x0C));
    initStackSegment = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x0E));
    initStackPointer = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x10));
    checksum = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x12));
    initInstructionPointer = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x14));
    initCodeSegment = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x16));
    relocationTableAddress = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x18));
    howManyOverlays = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x1A));
    oemId = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x24));
    oemInfo = mergeCharArrayToShortLittleEndian(file->readBinary(2,0x26));

    parsed = true;

    return 0;
}

unsigned int MZParser::getFileSize() {
    return file->getFileSize();
}

char* MZParser::getFileName() {
    return file->getFileName();
}


bool MZParser::validateTotalSize() {
    return getTotalSize() <= file->getFileSize();
}

unsigned int MZParser::getTotalSize() {
    return 512 * (howManyPages - 1) + lastPageBytes;
}

unsigned short MZParser::getHowManyPages() {
    if (!parsed) {
        return 0;
    }
    return howManyPages;
}

unsigned short MZParser::getLastPageBytes() {
    if (!parsed) {
        return 0;
    }
    return lastPageBytes;
}

unsigned short MZParser::getRelocations() {
    if (!parsed) {
        return 0;
    }
    return relocations;
}

unsigned short MZParser::getHeaderSize() {
    if (!parsed) {
        return 0;
    }
    return headerSize;
}

unsigned short MZParser::getMinMemory() {
    if (!parsed) {
        return 0;
    }
    return minMemory;
}

unsigned short MZParser::getMaxMemory() {
    if (!parsed) {
        return 0;
    }
    return maxMemory;
}

unsigned short MZParser::getChecksum() {
    if (!parsed) {
        return 0;
    }
    return checksum;
}

unsigned short MZParser::getInitStackSegment() {
    if (!parsed) {
        return 0;
    }
    return initStackSegment;
}

unsigned short MZParser::getInitStackPointer() {
    if (!parsed) {
        return 0;
    }
    return initStackPointer;
}

unsigned short MZParser::getInitInstructionPointer() {
    if (!parsed) {
        return 0;
    }
    return initInstructionPointer;
}

unsigned short MZParser::getInitCodeSegment() {
    if (!parsed) {
        return 0;
    }
    return initCodeSegment;
}

unsigned short MZParser::getRelocationTableAddress() {
    if (!parsed) {
        return 0;
    }
    return relocationTableAddress;
}

unsigned short MZParser::getHowManyOverlays() {
    if (!parsed) {
        return 0;
    }
    return howManyOverlays;
}

unsigned short MZParser::getOemId() {
    if (!parsed) {
        return 0;
    }
    return oemId;
}

unsigned short MZParser::getOemInfo() {
    if (!parsed) {
        return 0;
    }
    return oemInfo;
}

unsigned short MZParser::getEntryPoint() {
    if (!parsed) {
        return 0;
    }
    return headerSize * 0x10;
}
