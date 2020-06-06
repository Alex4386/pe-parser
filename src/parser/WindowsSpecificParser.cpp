#include "parser.hpp"
#include <string>
#include <iomanip>
#include <sstream>

WindowsSpecificParser::WindowsSpecificParser(WindowsSpecificHeader header) {
  this->windowsSpecificHeader = header;

  this->windowsSpecificHeader.imageBase = this->windowsSpecificHeader.imageBase;
  this->windowsSpecificHeader.sectionAlignment = this->windowsSpecificHeader.sectionAlignment;
  this->windowsSpecificHeader.fileAlignment = this->windowsSpecificHeader.fileAlignment;
  this->windowsSpecificHeader.osMinorVersion = this->windowsSpecificHeader.osMinorVersion;
  this->windowsSpecificHeader.osMajorVersion = this->windowsSpecificHeader.osMajorVersion;
  this->windowsSpecificHeader.imageMinorVersion = this->windowsSpecificHeader.imageMinorVersion;
  this->windowsSpecificHeader.imageMajorVersion = this->windowsSpecificHeader.imageMajorVersion;
  this->windowsSpecificHeader.subsystemMinorVersion = this->windowsSpecificHeader.subsystemMinorVersion;
  this->windowsSpecificHeader.subsystemMajorVersion = this->windowsSpecificHeader.subsystemMajorVersion;
  this->windowsSpecificHeader.sizeOfHeaders = this->windowsSpecificHeader.sizeOfHeaders;
  this->windowsSpecificHeader.checksum = this->windowsSpecificHeader.checksum;
  this->windowsSpecificHeader.subsystem = this->windowsSpecificHeader.subsystem;
  this->windowsSpecificHeader.dllCharacteristics = this->windowsSpecificHeader.dllCharacteristics;
  this->windowsSpecificHeader.sizeOfStackReserve = this->windowsSpecificHeader.sizeOfStackReserve;
  this->windowsSpecificHeader.sizeOfStackCommit = this->windowsSpecificHeader.sizeOfStackCommit;
  this->windowsSpecificHeader.sizeOfHeapReserve = this->windowsSpecificHeader.sizeOfHeapReserve;
  this->windowsSpecificHeader.sizeOfHeapCommit = this->windowsSpecificHeader.sizeOfHeapCommit;
  this->windowsSpecificHeader.loaderFlags = this->windowsSpecificHeader.loaderFlags;
  this->windowsSpecificHeader.numberOfRvaAndSizes = this->windowsSpecificHeader.numberOfRvaAndSizes;
}

bool WindowsSpecificParser::checkFileAlignmentAndSectionAlignment() {
  return (this->windowsSpecificHeader.sectionAlignment % this->windowsSpecificHeader.fileAlignment == 0);  
}

std::string WindowsSpecificParser::getHumanReadableSubsystem() {
  return getSubSystemString(this->windowsSpecificHeader.subsystem);
}

std::string WindowsSpecificParser::getHumanReadableDLLCharacteristics() {
  std::ostringstream str;
  bool result[16] = {false, };
  for (int i = 0; i < 16; i++) {    
      result[i] = (this->windowsSpecificHeader.dllCharacteristics / (1 << i)) & 0b1;
      if (getDLLCharacteristic(i).compare("Reserved")) {
          str << std::setw(50) << getDLLCharacteristic(i);
          str << ": " << std::boolalpha << result[i] << std::endl;
      }
  }
  return str.str();
}
