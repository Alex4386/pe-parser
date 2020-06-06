#include "parser.hpp"

MZParser::MZParser(MZHeader header) {
  this->mzHeader = header;

  this->mzHeader.lastPageBytes = this->mzHeader.lastPageBytes;
  this->mzHeader.howManyPages = this->mzHeader.howManyPages;
  this->mzHeader.relocations = this->mzHeader.relocations;
  this->mzHeader.headerSize = this->mzHeader.headerSize;
  this->mzHeader.minMemory = this->mzHeader.minMemory;
  this->mzHeader.maxMemory = this->mzHeader.maxMemory;
  this->mzHeader.initStackSegment = this->mzHeader.initStackSegment;
  this->mzHeader.initStackPointer = this->mzHeader.initStackPointer;
  this->mzHeader.checksum = this->mzHeader.checksum;
  this->mzHeader.initInstructionPointer = this->mzHeader.initInstructionPointer;
  this->mzHeader.initCodeSegment = this->mzHeader.initCodeSegment;
  this->mzHeader.relocationTableAddress = this->mzHeader.relocationTableAddress;
  this->mzHeader.howManyOverlays = this->mzHeader.howManyOverlays;
  this->mzHeader.oemId = this->mzHeader.oemId;
  this->mzHeader.oemInfo = this->mzHeader.oemInfo;

  this->mzHeader.peHeaderPointer = this->mzHeader.peHeaderPointer;
}

bool MZParser::hasValidPEHeader(size_t fileSize) {
  return sizeof(COFFHeader) + this->mzHeader.peHeaderPointer <= fileSize;
}

