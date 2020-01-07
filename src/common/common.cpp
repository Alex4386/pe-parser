#include <string>
#include <iostream>
#include <fstream>

size_t getFileSize(std::string fileName) {
  std::fstream file;

  file.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
  size_t size = file.tellg();

  file.close();

  return size;
}
