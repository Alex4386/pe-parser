#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include "extension.h"

void helpScreen(char* fileName);

void printIntro();
void printLine();
void licenseShort();
void licenseFull();

int mergeCharsToIntLittleEndian(char a, char b, char c, char d);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        helpScreen(argv[0]);
        return 0;
    } else if (argc == 2) {
        char* fileName = argv[1];

        // Read file Size
        struct stat fileSizeResult;
        if (stat(fileName, &fileSizeResult) != 0) {
            std::cout << "ERROR: " << fileName << ", No Such File detected" << std::endl;
            return 11;
        }
        printIntro();
        licenseFull();
        std::cout << "Reading File Info: " << fileName << std::endl;
        int fileSize = fileSizeResult.st_size;
        std::cout << "FileSize: " << fileSize;
        printf(" (0x%08x)", fileSize);
        std::cout << std::endl << std::endl;

        std::cout << "Attaching FileStream...." << std::endl;
        std::fstream fileStream;
        fileStream.open(fileName, std::ios::in | std::ios::binary);

        std::cout << "Creating buffer...." << std::endl;
        char* buffer = new char[fileSize];
        if (!fileStream) {
            std::cout << "FileStream ERROR!" << std::endl;
            return 12;
        }

        std::cout << "FileStream Ready!" << std::endl;
        if (!fileStream.read(buffer, fileSize)) {
            std::cout << "FileRead ERROR!" << std::endl;
            return 13;
        }
        std::cout << "FileRead Complete!" << std::endl;
        fileStream.close();

        std::cout << std::endl;
        std::cout << "Checking FileSize..." << std::endl;

        if (fileSize <= 0x3F) {
            std::cout << "The program is too small." << std::endl;
            std::cout << "This is unlikely to be a PE program." << std::endl;
            return 1;
        }
        std::cout << "OK!" << std::endl << std::endl;

        std::cout << "Checking PE Executable Signature" << std::endl;
        if (!(buffer[0x00] == 'M' && buffer[0x01] == 'Z')) {
            std::cout << "The PE Executable Signature is Missing!" << std::endl;
            return 2;
        }
        std::cout << "PE Executable Signature Found!!" << std::endl << std::endl;

        std::cout << "Finding NT Header Pointer" << std::endl;
        int peHeaderPointer = mergeCharsToIntLittleEndian(buffer[0x3C], buffer[0x3D], buffer[0x3E], buffer[0x3F]);
        std::cout << "NT Header Pointer: ";
        printf("0x%08x\n\n", peHeaderPointer);

        if (peHeaderPointer > fileSize) {
            std::cout << "The NT Header is Locating outside of file." << std::endl;
            return 3;
        }

        std::cout << "Finding NT Header Signature" << std::endl;
        if (!(buffer[peHeaderPointer+0x00] == '\x50' &&
              buffer[peHeaderPointer+0x01] == '\x45' &&
              buffer[peHeaderPointer+0x02] == 0 &&
              buffer[peHeaderPointer+0x03] == 0
            )) {
                std::cout << "The NT Header Signature is Missing!!!" << std::endl;
                return 4;
            }
        std::cout << "The NT Header Signature Found!!!" << std::endl << std::endl;

        std::cout << "NT Header Details:" << std::endl;
        int machineCode = mergeCharsToIntLittleEndian(buffer[peHeaderPointer+0x04], buffer[peHeaderPointer+0x05], 0, 0);
        printf("machineCode: 0x%08x (%s)\n", machineCode, printMachineTypeByMachineCode(machineCode).c_str());

        int sectionCount = mergeCharsToIntLittleEndian(buffer[peHeaderPointer+0x06], buffer[peHeaderPointer+0x07], 0, 0);
        std::cout << "Number of Sections: " << sectionCount << std::endl;

        int timeStamp = mergeCharsToIntLittleEndian(buffer[peHeaderPointer+0x08], buffer[peHeaderPointer+0x09], buffer[peHeaderPointer+0x10], buffer[peHeaderPointer+0x11]);
        std::cout << "created Time: " << timeStamp << " (" << timeStampToHumanReadble(timeStamp) << ")" << std::endl;

        int character = mergeCharsToIntLittleEndian(buffer[peHeaderPointer+0x16], buffer[peHeaderPointer+0x17], 0, 0);
        printf("characteristic: 0x%08x\n\n", character);
        std::cout << "Characteristic Details:" << std::endl;
        bool result[16] = {false, };
        for (int i = 0; i < 16; i++) {
            result[i] = (character / (1 << i)) % 2;
            std::cout << getCharacteristic(i) << ": " << std::boolalpha << result[i] << std::endl;
        }

        std::cout << std::endl;
        int standardCOFF = peHeaderPointer+0x18;
        int COFFtype = 32;

        std::cout << "Finding Standard COFF Signature" << std::endl;
        if (!(buffer[standardCOFF+0x00] == '\x0b')) {
            std::cout << "Standard COFF Signature Not Found!" << std::endl;
        }
        if (!(buffer[standardCOFF+0x01] == '\x01')) {
            std::cout << "This Standard COFF Header is IMAGE_OPTIONAL_HEADER32" << std::endl;
            COFFtype = 32;
        } else if (!(buffer[standardCOFF+0x01] == '\x02')) {
            std::cout << "This Standard COFF Header is IMAGE_OPTIONAL_HEADER64" << std::endl;
            COFFtype = 64;
        } else {
            std::cout << "Could not determine which type of Standard COFF Header is" << std::endl;
            return 5;
        }
        std::cout << "Standard COFF Signature Found!" << std::endl;
        std::cout << std::endl;
        std::cout << "Linker Version: " << (int)buffer[standardCOFF+0x02] << "." << (int)buffer[standardCOFF+0x03] << std::endl;

        int sizeOfCode = mergeCharsToIntLittleEndian(
            buffer[standardCOFF+0x04],
            buffer[standardCOFF+0x05],
            buffer[standardCOFF+0x06],
            buffer[standardCOFF+0x07]
        );

        std::cout << "Size Of Code: " << sizeOfCode;
        printf(" (0x%08x)\n", sizeOfCode);


        int entryPoint = mergeCharsToIntLittleEndian(
            buffer[standardCOFF+0x10],
            buffer[standardCOFF+0x11],
            buffer[standardCOFF+0x12],
            buffer[standardCOFF+0x13]
        );
        printf("entryPoint: 0x%08x\n", entryPoint);

        int winSpecificCOFF = peHeaderPointer+0x34;

        int imageBase = mergeCharsToIntLittleEndian(
            buffer[winSpecificCOFF+0x00],
            buffer[winSpecificCOFF+0x01],
            buffer[winSpecificCOFF+0x02],
            buffer[winSpecificCOFF+0x03]
        );
        printf("ImageBase: 0x%08x\n", imageBase);

        int sectionAlignment = mergeCharsToIntLittleEndian(
            buffer[winSpecificCOFF+0x04],
            buffer[winSpecificCOFF+0x05],
            buffer[winSpecificCOFF+0x06],
            buffer[winSpecificCOFF+0x07]
        );
        printf("SectionAlignment: 0x%08x\n", sectionAlignment);

        int fileAlignment = mergeCharsToIntLittleEndian(
            buffer[winSpecificCOFF+0x08],
            buffer[winSpecificCOFF+0x09],
            buffer[winSpecificCOFF+0x0A],
            buffer[winSpecificCOFF+0x0B]
        );
        printf("FileAlignment: 0x%08x\n", fileAlignment);

        std::cout << "OS Version: " << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x0C],buffer[standardCOFF+0x0D],0,0) << "." << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x0E],buffer[standardCOFF+0x0F],0,0) << std::endl;
        std::cout << "Image Version: " << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x10],buffer[standardCOFF+0x11],0,0) << "." << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x12],buffer[standardCOFF+0x13],0,0) << std::endl;
        std::cout << "SubSystem Version: " << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x14],buffer[standardCOFF+0x15],0,0) << "." << mergeCharsToIntLittleEndian(buffer[standardCOFF+0x16],buffer[standardCOFF+0x17],0,0) << std::endl;

        int sizeOfImage = mergeCharsToIntLittleEndian(
            buffer[winSpecificCOFF+0x1C],
            buffer[winSpecificCOFF+0x1D],
            buffer[winSpecificCOFF+0x1E],
            buffer[winSpecificCOFF+0x1F]            
        );
        printf("SizeOfImage: 0x%08x\n", sizeOfImage);

        
    } else {
        std::cout << "Too much argument detected!" << std::endl;
    }
}

int mergeCharsToIntLittleEndian(char a, char b, char c, char d) {
    return ((int) ((unsigned char)a) << 0) |
           ((int) ((unsigned char)b) << 8) |
           ((int) ((unsigned char)c) << 16)  |
           ((int) ((unsigned char)d) << 24);
}

void helpScreen(char* fileName) {
    printIntro();
    licenseFull();
    std::cout << "Usage:" << std::endl;
    std::cout << fileName << " fileName" << std::endl;
}

void printLine() {
    std::cout << "=============================================" << std::endl;
}

void printIntro() {
    std::cout << "PE Parser by Alex4386" << std::endl;
    printLine();
}

void licenseShort() {
    std::cout << "Distributed under MIT and HRPL" << std::endl << std::endl;
}

void licenseFull() {
    std::cout << "Distributed under MIT License" << std::endl;
    std::cout << "and Hakurei Reimu Public License" << std::endl << std::endl;
    std::cout << "Copyright (c) Alex4386" << std::endl;
    std::cout << "https://github.com/Alex4386/Pay1oad-PE-Parser" << std::endl;
    printLine();
}
