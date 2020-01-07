#ifndef _HUMANREADABLE_HPP

#define _HUMANREADABLE_HPP

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

std::string getMachineTypeByMachineCode(unsigned short machineCode);
std::string getFileCharacteristic(int i);
std::string timeStampToHumanReadable(const time_t rawtime);
std::string getSubSystemString(int subsystem);
std::string getDLLCharacteristic(int i);
std::string getStandardCOFFHeaderName(unsigned char* c);

template <class T>
std::string decimalWithHex(T t, std::string unit = "") {
  std::ostringstream str;
  str << std::dec << t;
  if (unit.compare("") != 0) {
   str << " " << unit;
  }
  str << " (0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << t;
  
  if (unit.compare("") != 0) {
    str << " " << unit;
  } 
  str << ")" << std::dec;

  return str.str();
}

template <class T>
std::string outputHex(T t, std::string unit = "") {
  std::ostringstream str;
  str << std::hex << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << t;
  if (unit.compare("") != 0) {
    str << " " << unit;
  } 
  str << std::dec;

  return str.str();
}

template <class T>
std::string outputDec(T t, std::string unit = "") {
  std::ostringstream str;
  str << std::dec << t;
  if (unit.compare("") != 0) {
    str << " " << unit;
  } 
  str << std::dec;

  return str.str();
}


#endif
