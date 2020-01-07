#ifndef _COMMON_HPP
#define _COMMON_HPP

#include <string>
#include <iostream>
#include <fstream>

typedef struct MZHeader {
  uint16_t magicNumber; // 0x0
  uint16_t lastPageBytes; // 0x2
  uint16_t howManyPages; // 0x4
  uint16_t relocations; // 0x6
  uint16_t headerSize; // 0x8
  uint16_t minMemory; // 0xa
  uint16_t maxMemory; // 0xc
  uint16_t initStackSegment; // 0xe
  uint16_t initStackPointer; // 0x10
  uint16_t checksum; // 0x12
  uint16_t initInstructionPointer; // 0x14
  uint16_t initCodeSegment; // 0x16
  uint16_t relocationTableAddress; // 0x18
  uint16_t howManyOverlays; // 0x1a
  uint16_t reserved1[4]; // 0x1c
  uint16_t oemId; // 0x24
  uint16_t oemInfo; // 0x26
  uint16_t reserved2[10]; // 0x28
  uint32_t peHeaderPointer; // 0x3c
} MZHeader;

typedef struct COFFHeader {
  uint32_t signature;
  uint16_t machineCode;
  uint16_t numberOfSections;
  uint32_t timeStamp;
  uint32_t pointerToSymbolTable;
  uint32_t numberOfSymbolTable;
  uint16_t sizeOfOptionalHeader;
  uint16_t fileCharacteristics;
} COFFHeader;

typedef struct StandardCOFFHeader {
  uint16_t magicValue;
  uint8_t linkerMajorVersion;
  uint8_t linkerMinorVersion;
  uint32_t sizeOfCode;
  uint32_t sizeOfInitializedData;
  uint32_t sizeOfUninitializedData;
  uint32_t addressOfEntryPoint;
  uint32_t baseOfCode;
  uint32_t baseOfData;
} StandardCOFFHeader;

typedef struct WindowsSpecificHeader {
  uint32_t imageBase;
  uint32_t sectionAlignment;
  uint32_t fileAlignment;
  uint16_t osMajorVersion;
  uint16_t osMinorVersion;
  uint16_t imageMajorVersion;
  uint16_t imageMinorVersion;
  uint16_t subsystemMajorVersion;
  uint16_t subsystemMinorVersion;
  uint32_t win32VersionValue;
  uint32_t sizeOfImage;
  uint32_t sizeOfHeaders;
  uint32_t checksum;
  uint16_t subsystem;
  uint16_t dllCharacteristics;
  uint32_t sizeOfStackReserve;
  uint32_t sizeOfStackCommit;
  uint32_t sizeOfHeapReserve;
  uint32_t sizeOfHeapCommit;
  uint32_t loaderFlags;
  uint32_t numberOfRvaAndSizes;
} WindowsSpecificHeader;

typedef struct PEHeader {
  COFFHeader coffHeader;
  StandardCOFFHeader standardCoffHeader;
  WindowsSpecificHeader windowsSpecificHeader;
} PEHeader;

// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl

template <class T>
T toLittleEndian(T c) {
  T result = 0;
  for (int i = 0; i < sizeof(T); i++) {
    result = (((c >> (i * 8)) & 0xFF) << ((sizeof(T) - (i+1)) * 8)) | result;
  }
  return result;
}

template <class T>
T* safeMemoryAllocation(int size) {
  T* t = (T*)malloc(sizeof(T) * size);

  if (t == NULL) {
    printf("ERROR: Failed to allocate memory! Is it out of memory?\n");
    exit(1);
  }
  return t;
}

template <class T>
T *readFile2Class(std::string fileName, int offset = 0) {
  std::fstream file;
  T *t = safeMemoryAllocation<T>(1);

  file.open(fileName, std::ios::in | std::ios::binary);
  file.seekg(offset, std::ios_base::beg);

  file.read((char *)t, sizeof(T));
  file.close();

  return t;
}

size_t getFileSize(std::string fileName);

std::string outputBool(bool a);

#endif
