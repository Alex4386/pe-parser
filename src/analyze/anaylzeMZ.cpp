#include "../common/common.hpp"
#include "../parser/parser.hpp"
#include "../common/options.hpp"

#include "analyze.hpp"

int analyzeMZ(MZParser mzParser, CommandLineOptions options) {
  MZHeader parsedHeader = mzParser.mzHeader;
  if (!options.outputAsJson) {
    analyzeMZTerminal(parsedHeader);
  } else {
    analyzeMZJson(parsedHeader);
  }

  return 0;
}

int analyzeMZTerminal(MZHeader parsedHeader) {
  std::cout << "MZ Header:" << std::endl;
  std::cout << "  Page Count: " << parsedHeader.howManyPages << std::endl;
  std::cout << "  Last Page Size: " << decimalWithHex(parsedHeader.lastPageBytes, "bytes") << std::endl;
  std::cout << "  Relocations: " << parsedHeader.relocations << std::endl;
  std::cout << "  Header Size: " << decimalWithHex(parsedHeader.headerSize, "bytes") << std::endl;
  std::cout << "  Minimum Memory: " << decimalWithHex(parsedHeader.minMemory, "bytes") << std::endl;
  std::cout << "  Maximum Memory: " << decimalWithHex(parsedHeader.maxMemory, "bytes") << std::endl;
  std::cout << "  Init StackSegment: " << decimalWithHex(parsedHeader.initStackSegment) << std::endl;
  std::cout << "  Init StackPointer: " << decimalWithHex(parsedHeader.initStackPointer) << std::endl;
  std::cout << "  Checksum: " << decimalWithHex(parsedHeader.checksum) << std::endl;
  std::cout << "  Init IP: " << outputHex(parsedHeader.initInstructionPointer) << std::endl;
  std::cout << "  Init CS: " << outputHex(parsedHeader.initCodeSegment) << std::endl;
  std::cout << "  Reloc. Table Addr: " << outputHex(parsedHeader.relocationTableAddress) << std::endl;
  std::cout << "  Overlay counts: " << outputHex(parsedHeader.howManyOverlays) << std::endl;
  std::cout << "  Oem ID: " << outputHex(parsedHeader.howManyOverlays) << std::endl;
  std::cout << "  Oem Info: " << outputHex(parsedHeader.howManyOverlays) << std::endl;
  std::cout << "  PE Header Address: " << outputHex(parsedHeader.peHeaderPointer) << std::endl;
  std::cout << "" << std::endl;
  std::cout << "MZ Header Extra:" << std::endl;
  std::cout << "    Entrypoint: " << outputHex(parsedHeader.headerSize * 0x10) << std::endl;

  return 0;
}

int analyzeMZJson(MZHeader parsedHeader) {
  std::cout << "\"mzHeader\": {";
  std::cout << "\"pageCount\": " << parsedHeader.howManyPages << ", ";
  std::cout << "\"lastPageSize\": " << parsedHeader.lastPageBytes << ", ";
  std::cout << "\"relocationCount\": " << parsedHeader.relocations << ", ";
  std::cout << "\"headerSize\": " << parsedHeader.headerSize << ", ";
  std::cout << "\"minMemory\": " << parsedHeader.minMemory << ", ";
  std::cout << "\"maxMemory\": " << parsedHeader.maxMemory << ", ";
  std::cout << "\"initSS\": " << parsedHeader.initStackSegment << ", ";
  std::cout << "\"initSP\": " << parsedHeader.initStackPointer << ", ";
  std::cout << "\"checksum\": " << parsedHeader.checksum << ", ";
  std::cout << "\"initIP\": " << parsedHeader.initInstructionPointer << ", ";
  std::cout << "\"initCS\": " << parsedHeader.initCodeSegment << ", ";
  std::cout << "\"relocationTableAddress\": " << parsedHeader.relocationTableAddress << ", ";
  std::cout << "\"overlayCount\": " << parsedHeader.howManyOverlays << ", ";
  std::cout << "\"oemId\": " << parsedHeader.oemId << ", ";
  std::cout << "\"oemInfo\": " << parsedHeader.oemInfo << ", ";
  std::cout << "\"peHeaderPointer\": " << parsedHeader.oemInfo << "} ";

  return 0;
}
