#ifndef _PARSER_HPP
#define _PARSER_HPP

#include <string>

#include "../common/common.hpp"
#include "../common/humanConverter.hpp"

class COFFParser {
  public: 
    COFFHeader coffHeader;
    COFFParser(COFFHeader header);

    bool checkPESignature();
    std::string getHumanReadableFileCharacteristics();
    std::string getMachineTypeString();
    std::string getHumanReadableTimestamp();
};
class StandardCOFFParser {
  public:
    StandardCOFFHeader standardCoffHeader;

    StandardCOFFParser(StandardCOFFHeader header);

};
class WindowsSpecificParser {
  public:
    WindowsSpecificHeader windowsSpecificHeader;

    WindowsSpecificParser(WindowsSpecificHeader header);

    bool checkFileAlignmentAndSectionAlignment();
    std::string getHumanReadableSubsystem();
    std::string getHumanReadableDLLCharacteristics();
};

class PEParser {
  public:
    COFFParser *coffParser;
    StandardCOFFParser *standardCoffParser;
    WindowsSpecificParser *windowsSpecificParser;

    PEParser(PEHeader header);
};
class MZParser {
  public:
    MZHeader mzHeader;

    MZParser(MZHeader header);
    bool hasValidPEHeader(size_t fileSize);
};

#endif