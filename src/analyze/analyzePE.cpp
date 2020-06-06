#include "../common/common.hpp"
#include "../parser/parser.hpp"
#include "../common/options.hpp"

#include "analyze.hpp"

int analyzePE(PEParser peParser, CommandLineOptions options) {
  COFFParser coffParser = *peParser.coffParser;
  StandardCOFFParser standardCoffParser = *peParser.standardCoffParser;
  WindowsSpecificParser windowsSpecificParser = *peParser.windowsSpecificParser;

  if (!options.outputAsJson) {
    analyzePETerminal(coffParser, standardCoffParser, windowsSpecificParser);
  } else {
    analyzePEJson(coffParser, standardCoffParser, windowsSpecificParser);
  }
  return 0;
}

int analyzePETerminal(COFFParser coffParser, StandardCOFFParser standardCoffParser, WindowsSpecificParser windowsSpecificParser) {
  COFFHeader coffHeader = coffParser.coffHeader;
  StandardCOFFHeader standardCOFFHeader = standardCoffParser.standardCoffHeader;
  WindowsSpecificHeader windowsSpecificHeader = windowsSpecificParser.windowsSpecificHeader;

  std::cout << "PE Header:" << std::endl;

  if (!coffParser.checkPESignature()) {
    std::cout << " ERROR: Invalid PE Header Signature Found!!" << std::endl;
    return 1;
  }

  std::cout << "  COFF Header:" << std::endl;
  std::cout << "    Machine Code: " << decimalWithHex(coffHeader.machineCode) << " " << coffParser.getMachineTypeString() << std::endl;
  std::cout << "    Section Count: " << outputDec(coffHeader.numberOfSections) << std::endl;
  std::cout << "    Timestamp: " << decimalWithHex(coffHeader.timeStamp) << "(" << coffParser.getHumanReadableTimestamp() << ")" << std::endl;
  std::cout << "    Symbol Table Addr.: " << outputHex(coffHeader.pointerToSymbolTable) << std::endl;
  std::cout << "    Symbol Table Count: " << outputHex(coffHeader.numberOfSymbolTable) << std::endl;
  std::cout << "    Optional Header Size: " << decimalWithHex(coffHeader.sizeOfOptionalHeader, "bytes") << std::endl;
  std::cout << "    File Characteristics: " << std::endl;
  std::cout << coffParser.getHumanReadableFileCharacteristics();
  std::cout << "  COFF Header Others:" << std::endl;
  std::cout << "    PE Header Valid: " << outputBool(coffParser.checkPESignature()) << std::endl;
  std::cout << "  Standard COFF Header:" << std::endl;
  std::cout << "    Linker Version: " << outputDec(standardCOFFHeader.linkerMajorVersion) << "." << outputDec(standardCOFFHeader.linkerMinorVersion) << std::endl;
  std::cout << "    Size of Code: " << decimalWithHex(standardCOFFHeader.sizeOfCode, "bytes") << std::endl;
  std::cout << "    Size of Init Data: " << decimalWithHex(standardCOFFHeader.sizeOfInitializedData, "bytes") << std::endl;
  std::cout << "    Size of Uninit Data: " << decimalWithHex(standardCOFFHeader.sizeOfUninitializedData, "bytes") << std::endl;
  std::cout << "    Entrypoint: " << outputHex(standardCOFFHeader.addressOfEntryPoint) << std::endl;
  std::cout << "    Base of Code: " << outputHex(standardCOFFHeader.baseOfCode) << std::endl;
  std::cout << "    Base of Data: " << outputHex(standardCOFFHeader.baseOfData) << std::endl;
  std::cout << "  Windows Specific Header:" << std::endl;
  std::cout << "    ImageBase: " << outputHex(windowsSpecificHeader.imageBase) << std::endl;
  std::cout << "    Section Alignment: " << outputHex(windowsSpecificHeader.sectionAlignment) << std::endl;
  std::cout << "    File Alignment: " << outputHex(windowsSpecificHeader.fileAlignment) << std::endl;
  std::cout << "    OS Version: " << outputDec(windowsSpecificHeader.osMajorVersion) << "." << outputDec(windowsSpecificHeader.osMinorVersion) << std::endl;
  std::cout << "    Image Version: " << outputDec(windowsSpecificHeader.imageMajorVersion) << "." << outputDec(windowsSpecificHeader.imageMinorVersion) << std::endl;
  std::cout << "    Subsystem Version: " << outputDec(windowsSpecificHeader.subsystemMajorVersion) << "." << outputDec(windowsSpecificHeader.subsystemMinorVersion) << std::endl;
  std::cout << "    Win32 Version: " << outputDec(windowsSpecificHeader.win32VersionValue) << std::endl;
  std::cout << "    Size Of Image: " << decimalWithHex(windowsSpecificHeader.sizeOfImage, "bytes") << std::endl;
  std::cout << "    Size Of Headers: " << decimalWithHex(windowsSpecificHeader.sizeOfHeaders, "bytes") << std::endl;
  std::cout << "    Checksum: " << outputDec(windowsSpecificHeader.checksum) << std::endl;
  std::cout << "    Subsystem: " << outputDec(windowsSpecificHeader.sizeOfHeaders) << " " << windowsSpecificParser.getHumanReadableSubsystem() << std::endl;
  std::cout << "    DLL Characteristics:" << std::endl;
  std::cout << windowsSpecificParser.getHumanReadableDLLCharacteristics();
  std::cout << "    Size Of Stack Reserve: " << decimalWithHex(windowsSpecificHeader.sizeOfStackReserve, "bytes") << std::endl;
  std::cout << "    Size Of Stack Commit: " << decimalWithHex(windowsSpecificHeader.sizeOfStackCommit, "bytes") << std::endl;
  std::cout << "    Size Of Heap Reserve: " << decimalWithHex(windowsSpecificHeader.sizeOfHeapReserve, "bytes") << std::endl;
  std::cout << "    Size Of Heap Commit: " << decimalWithHex(windowsSpecificHeader.sizeOfHeapCommit, "bytes") << std::endl;
  std::cout << "    Loader Flags: " << decimalWithHex(windowsSpecificHeader.loaderFlags) << std::endl;
  std::cout << "    Number of RVA and Sizes: " << outputDec(windowsSpecificHeader.numberOfRvaAndSizes) << std::endl;

  return 0;
}

int analyzePEJson(COFFParser coffParser, StandardCOFFParser standardCoffParser, WindowsSpecificParser windowsSpecificParser) {
  return 0;
}
