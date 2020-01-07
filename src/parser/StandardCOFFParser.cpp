#include "parser.hpp"

StandardCOFFParser::StandardCOFFParser(StandardCOFFHeader header) {
  this->standardCoffHeader = header;

  this->standardCoffHeader.linkerMajorVersion = this->standardCoffHeader.linkerMajorVersion;
  this->standardCoffHeader.linkerMinorVersion = this->standardCoffHeader.linkerMinorVersion;
  this->standardCoffHeader.sizeOfCode = this->standardCoffHeader.sizeOfCode;
  this->standardCoffHeader.sizeOfInitializedData = this->standardCoffHeader.sizeOfInitializedData;
  this->standardCoffHeader.sizeOfUninitializedData = this->standardCoffHeader.sizeOfUninitializedData;
  this->standardCoffHeader.addressOfEntryPoint = this->standardCoffHeader.addressOfEntryPoint;
  this->standardCoffHeader.baseOfCode = this->standardCoffHeader.baseOfCode;
  this->standardCoffHeader.baseOfData = this->standardCoffHeader.baseOfData;
}
