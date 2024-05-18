#include "Arduino.h"

class CommandIO {
  public:
    CommandIO();
    struct Command readCommand();

  private:
    String commandBuffer = "";
    String readSerial();
    struct Command parseCommand(String newCommand);
};

struct Command {
  String key;
  int value;
};