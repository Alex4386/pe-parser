#ifndef _OPTIONS_HPP
#define _OPTIONS_HPP

typedef struct CommandLineOptions {
  bool outputAsJson;
  bool mute;
  bool showHelp;
  bool verbose;
} CommandLineOptions;

char** optionRemover(int argc, char *argv[]);
int getNonOptionArgc(int argc, char *argv[]);
bool isItValidOptions(char* optionString);
CommandLineOptions readOptions(int argc, char *argv[]);

#endif
