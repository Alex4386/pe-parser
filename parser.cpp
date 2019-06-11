// Pay1oad PE Parser
// PE Parser Core
//
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include "parser.h"
#include "extension.h"
#include <string>
#include <iomanip>
#include <sstream>

int PEParser::parseFile() {
    if (!file->isLoaded()) {
        return 1;
    }
    if (!checkFileSize()) {
        return 11;
    }
    if (!checkPESignature()) {
        return 12;
    }
    ntHeaderPointer = mergeCharArrayToIntLittleEndian(file->readBinary(4, 0x3C));
    if (!checkNTHeaderPointer()) {
        return 13;
    }    
    if (!checkNTHeaderSignature()) {
        return 14;
    }
    machineCode = mergeCharArrayToShortLittleEndian(file->readBinary(2, ntHeaderPointer+0x04));
    sectionCount = mergeCharArrayToShortLittleEndian(file->readBinary(2, ntHeaderPointer+0x06));
    timeStamp = mergeCharArrayToIntLittleEndian(file->readBinary(4, ntHeaderPointer+0x08));
    fileCharacteristics = mergeCharArrayToShortLittleEndian(file->readBinary(2, ntHeaderPointer+0x16));
    standardCOFFPointer = ntHeaderPointer+0x18;
    linkerMajorVersion = file->readBinary(1, standardCOFFPointer+0x02)[0];
    linkerMinorVersion = file->readBinary(1, standardCOFFPointer+0x03)[0];
    sizeOfCode = mergeCharArrayToIntLittleEndian(file->readBinary(4, standardCOFFPointer+0x04));
    entryPoint = mergeCharArrayToIntLittleEndian(file->readBinary(4, standardCOFFPointer+0x10));
    winSpecificCOFF = ntHeaderPointer+0x34;
    imageBase = mergeCharArrayToIntLittleEndian(file->readBinary(4, winSpecificCOFF));
    sectionAlignment = mergeCharArrayToIntLittleEndian(file->readBinary(4, winSpecificCOFF+0x04));
    fileAlignment = mergeCharArrayToIntLittleEndian(file->readBinary(4, winSpecificCOFF+0x08));
    osMajorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x0C));
    osMinorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x0E));
    imageMajorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x10));
    imageMinorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x12));
    subSystemMajorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x14));
    subSystemMinorVersion = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x16));
    sizeOfImage = mergeCharArrayToIntLittleEndian(file->readBinary(4, winSpecificCOFF+0x1C));
    subSystem = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x28));
    dllCharacteristics = mergeCharArrayToShortLittleEndian(file->readBinary(2, winSpecificCOFF+0x2A));


    parsed = true;
    return 0;
}

bool PEParser::checkFileSize() {
    return (file->getFileSize() > 0x3F);
}

unsigned int PEParser::getFileSize() {
    return file->getFileSize();
}

char* PEParser::getFileName() {
    return file->getFileName();
}

bool PEParser::checkPESignature() {
    if (!file->isLoaded()) { return false; }
    unsigned char* signature = file->readBinary(2, 0x00);
    return (signature[0] == 'M' && signature[1] == 'Z');
}

bool PEParser::checkNTHeaderPointer() {
    if (!file->isLoaded()) { return false; }
    return (ntHeaderPointer < file->getFileSize());
}

bool PEParser::checkNTHeaderSignature() {
    if (!file->isLoaded()) { return false; }
    unsigned char* sign = file->readBinary(4, ntHeaderPointer);
    return (sign[0] == '\x50' && sign[1] == '\x45' && sign[2] == 0 && sign[3] == 0 );
}

unsigned char* PEParser::getStandardCOFFSignature() {
    if (!file->isLoaded()) { return nullptr; }
    return file->readBinary(2, standardCOFFPointer);
}

std::string PEParser::getStandardCOFFHeaderType() {
    if (!file->isLoaded()) { return ""; }
    return getStandardCOFFHeaderName(getStandardCOFFSignature());
}

unsigned int PEParser::getNTHeaderPointer() {
    if (!parsed) { return 0; }
    return ntHeaderPointer;
}

unsigned short PEParser::getMachineCode() {
    if (!parsed) { return 0; }
    return machineCode;
}

std::string PEParser::getMachineTypeFromMachineCode() {
    if (!parsed) { return ""; }
    return getMachineTypeByMachineCode(machineCode);
}

unsigned int PEParser::getSectionCount() {
    if (!parsed) { return 0; }
    return sectionCount;
}

long PEParser::getTimeStamp() {
    if (!parsed) { return 0; }
    return timeStamp;
}

std::string PEParser::getHumanReadableTimeStamp() {
    if (!parsed) { return ""; }
    return timeStampToHumanReadble(getTimeStamp());
}

unsigned short PEParser::getFileCharacteristics() {
    if (!parsed) { return 0; }
    return fileCharacteristics;
}

std::string PEParser::getHumanReadableFileCharacteristics() {
    if (!parsed) { return ""; }
    std::ostringstream str;
    bool result[16] = {false, };
    for (unsigned short i = 0; i < 16; i++) {  
        result[i] = (fileCharacteristics / (1 << i)) % 2;  
        str << std::setw(50) << getCharacteristic(i);
        str << ": " << std::boolalpha << result[i] << std::endl;
    }
    return str.str();
}

unsigned char PEParser::getLinkerMajorVersion() {
    if (!parsed) { return 0; }
    return linkerMajorVersion;
}

unsigned char PEParser::getLinkerMinorVersion() {
    if (!parsed) { return 0; }
    return linkerMinorVersion;
}

unsigned int PEParser::getSizeOfCode() {
    if (!parsed) { return 0; }
    return sizeOfCode;
}

unsigned int PEParser::getEntryPoint() {
    if (!parsed) { return 0; }
    return entryPoint;
}

unsigned int PEParser::getImageBase() {
    if (!parsed) { return 0; }
    return imageBase;
}

unsigned int PEParser::getSectionAlignment() {
    if (!parsed) { return 0; }
    return sectionAlignment;
}

unsigned int PEParser::getFileAlignment() {
    if (!parsed) { return 0; }
    return fileAlignment;
}

bool PEParser::checkSectionAlignmentAndFileAlignment() {
    if (!parsed) { return 0; }
    return (sectionAlignment % fileAlignment == 0);    
}

unsigned short PEParser::getOSMajorVersion() {
    if (!parsed) { return 0; }
    return osMajorVersion;
}

unsigned short PEParser::getOSMinorVersion() {
    if (!parsed) { return 0; }
    return osMinorVersion;
}

unsigned short PEParser::getImageMajorVersion() {
    if (!parsed) { return 0; }
    return imageMajorVersion;
}

unsigned short PEParser::getImageMinorVersion() {
    if (!parsed) { return 0; }
    return imageMinorVersion;
}

unsigned short PEParser::getSubSystemMajorVersion() {
    if (!parsed) { return 0; }
    return subSystemMajorVersion;
}

unsigned short PEParser::getSubSystemMinorVersion() {
    if (!parsed) { return 0; }
    return subSystemMinorVersion;
}

unsigned int PEParser::getSizeOfImage() {
    if (!parsed) { return 0; }
    return sizeOfImage;
}

unsigned short PEParser::getSubSystem() {
    if (!parsed) { return 0; }
    return subSystem;
}

std::string PEParser::getHumanReadableSubSystem() {
    if (!parsed) { return 0; }
    return getSubSystemString(getSubSystem());
}

unsigned short PEParser::getDLLCharacteristics() {
    if (!parsed) { return 0; }
    return dllCharacteristics;
}

std::string PEParser::getHumanReadableDLLCharacteristics() {
    if (!parsed) { return ""; }
    std::ostringstream str;
    bool result[16] = {false, };
    for (unsigned short i = 0; i < 16; i++) {    
        result[i] = (dllCharacteristics / (1 << i)) % 2;
        if (getDLLCharacteristic(i).compare("Reserved")) {
            str << std::setw(50) << getDLLCharacteristic(i);
            str << ": " << std::boolalpha << result[i] << std::endl;
        }
    }
    return str.str();
}


