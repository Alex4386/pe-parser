#ifndef _ANALYZE_HPP
#define _ANALYZE_HPP

#include <string>
#include "../common/options.hpp"

int analyze(std::string fileName, CommandLineOptions options);

int analyzeMZ(MZParser mzParser, CommandLineOptions options);
int analyzeMZJson(MZHeader parsedHeader);
int analyzeMZTerminal(MZHeader parsedHeader);

int analyzePE(PEParser peParser, CommandLineOptions options);
int analyzePETerminal(COFFParser coffParser, StandardCOFFParser standardCoffParser, WindowsSpecificParser windowsSpecificParser);
int analyzePEJson(COFFParser coffParser, StandardCOFFParser standardCoffParser, WindowsSpecificParser windowsSpecificParser);

#endif