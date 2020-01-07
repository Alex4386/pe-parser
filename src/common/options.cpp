#include "common.hpp"
#include <cstring>
#include "options.hpp"

char** optionRemover(int argc, char *argv[]) {
  char** wa = safeMemoryAllocation<char *>(argc);
  wa[0] = NULL;
  for (int i = 1, j = 0; i < argc; i++) {
    wa[i] = NULL;
    if (isItValidOptions(argv[i])) {
      continue;
    } else {
      wa[j] = argv[i];
      j++;
    }
  }

  return wa;
}

int getNonOptionArgc(int argc, char *argv[]) {
  int i = 0;

  for (i = 0; i < argc && argv[i] != NULL; i++) {} 
  return i;
}

const int validOptionCount = 8;
char validOptions[validOptionCount][10] = {
  "--json",
  "--mute",
  "--quiet",
  "-q",
  "--help",
  "-h",
  "-v",
  "--verbose"
};

bool isItValidOptions(char* optionString) {
  for (int i = 0; i < validOptionCount; i++) {
    if (strcmp(optionString, validOptions[i]) == 0) return true;
  }
  
  return false;
}

CommandLineOptions readOptions(int argc, char *argv[]) {
  CommandLineOptions option = {false, };

  // should not include filename
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "--json") == 0) {
        option.outputAsJson = true;
      } else if (strcmp(argv[i], "--mute") == 0 ||
                 strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
        option.mute = true;
      } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
        option.showHelp = true;
      } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
        option.verbose = true;
      }
    } else {
      break;
    }
  }

  return option;
}


