#include "../common/common.hpp"
#include "../parser/parser.hpp"
#include "../common/options.hpp"

#include "analyze.hpp"

int analyze(std::string fileName, CommandLineOptions options) {
  if (!options.mute || options.outputAsJson) {
    std::cout << "Filename: " << fileName << std::endl;
  }
  size_t fileSize = getFileSize(fileName);

  if (fileSize < sizeof(MZHeader)) {
    // can not analyze due to small size
    std::cout << "ERROR: Filesize is too small to check " << std::endl;

  } else if (fileSize < sizeof(PEHeader)) {
    // can not analyze PE due to small size, fallback to MZ
    if (!(options.mute || options.outputAsJson)) {
      std::cout << "ERROR: Inadequate size for PE header, Fallback to MZ..." << std::endl;
      if (options.verbose) {
        std::cout << fileSize << " compared to " << sizeof(PEHeader) << std::endl;
      }
    }

    MZHeader *mzHeader = readFile2Class<MZHeader>(fileName, 0);
    MZParser mzParser(*mzHeader);

    analyzeMZ(mzParser, options);

    

  } else {
    // It's time for analyze.
    if (!(options.mute || options.outputAsJson)) {
      std::cout << "It's Enough" << std::endl;
    }

    MZHeader *mzHeader = readFile2Class<MZHeader>(fileName, 0);
    MZParser mzParser(*mzHeader);

    if (!mzParser.hasValidPEHeader(fileSize)) {
      if (!(options.mute || options.outputAsJson)) {
        std::cout << "ERROR: Invalid PE Pointer detected, Fallback to MZ..." << std::endl;
        if (options.verbose) {
          std::cout << fileSize << " compared to " << sizeof(PEHeader) << std::endl;
        }
      }

      analyzeMZ(mzParser, options);
    } else {
      PEHeader *peHeader = readFile2Class<PEHeader>(fileName, mzParser.mzHeader.peHeaderPointer);
      PEParser peParser(*peHeader);

      analyzePE(peParser, options);
    }
  }

  return 0;
}




