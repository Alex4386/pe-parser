
#include "parser.hpp"
#include <string>
#include <iomanip>
#include <sstream>

COFFParser::COFFParser(COFFHeader header) {
  this->coffHeader = header;

  this->coffHeader.machineCode = this->coffHeader.machineCode;
  this->coffHeader.numberOfSections = this->coffHeader.numberOfSections;
  this->coffHeader.timeStamp = this->coffHeader.timeStamp;
  this->coffHeader.pointerToSymbolTable = this->coffHeader.pointerToSymbolTable;
  this->coffHeader.numberOfSymbolTable = this->coffHeader.numberOfSymbolTable;
  this->coffHeader.sizeOfOptionalHeader = this->coffHeader.sizeOfOptionalHeader;
  this->coffHeader.fileCharacteristics = this->coffHeader.fileCharacteristics;
}

bool COFFParser::checkPESignature() {
  return this->coffHeader.signature == 0x00004550;
}

std::string COFFParser::getHumanReadableFileCharacteristics() {
  std::ostringstream str;
  bool result[16] = {false, };
  for (unsigned short i = 0; i < 16; i++) {  
      result[i] = (this->coffHeader.fileCharacteristics / (1 << i)) % 2;  
      str << std::setw(50) << getFileCharacteristic(i);
      str << ": " << std::boolalpha << result[i] << std::endl;
  }
  return str.str();
}

std::string COFFParser::getMachineTypeString() {
  return getMachineTypeByMachineCode(this->coffHeader.machineCode);
}

std::string COFFParser::getHumanReadableTimestamp() {
  return timeStampToHumanReadable(this->coffHeader.timeStamp);
}
