#include "common/terminal.hpp"
#include "common/common.hpp"
#include "common/options.hpp"
#include "parser/parser.hpp"
#include "analyze/analyze.hpp"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    Terminal::helpScreen(argv[0]);
  } else {
    // check for options:
    char** filenamesArgv = optionRemover(argc, argv);
    int filenamesArgc = getNonOptionArgc(argc, filenamesArgv);

    CommandLineOptions options = readOptions(argc, argv);

    if (filenamesArgc <= 0 || options.showHelp) {
      Terminal::helpScreen(argv[0]);
      exit((options.showHelp) ? 0 : 1);
    } else {

      if (!options.mute) {
        Terminal::printIntroQuick();
      } else {
        Terminal::printLine();
      }

      for (int i = 0; i < filenamesArgc; i++) {
        analyze(filenamesArgv[i], options);
      }
    }
  }

  return 0;
}
