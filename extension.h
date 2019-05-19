// Pay1oad PE Parser
// Extensions Header
//
// Copyright (c) Alex4386
// Source Code is distributed under HRPL.

std::string getMachineTypeByMachineCode(unsigned short machineCode);
std::string getCharacteristic(int i);
std::string timeStampToHumanReadble(const time_t rawtime);
std::string getSubSystemString(int subsystem);
std::string getDLLCharacteristic(int i);
int mergeCharsToIntLittleEndian(char a, char b, char c, char d);
unsigned int mergeCharArrayToIntLittleEndian(unsigned char* c);
unsigned short mergeCharArrayToShortLittleEndian(unsigned char* c);
std::string getStandardCOFFHeaderName(unsigned char* c);
