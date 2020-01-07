#include "parser.hpp"

PEParser::PEParser(PEHeader header) {
  this->coffParser = new COFFParser(header.coffHeader);
  this->standardCoffParser = new StandardCOFFParser(header.standardCoffHeader);
  this->windowsSpecificParser = new WindowsSpecificParser(header.windowsSpecificHeader);
}