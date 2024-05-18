#include "CommandIO.h"

CommandIO IO;

struct Command currentCommand;

void setup() {

  IO = CommandIO();
}

void loop() {

  struct Command newCommand = IO.readCommand();

  if (newCommand.key != "") {

    if (currentCommand.key != "") {
      interruptCommand();
    }

    executeCommand(newCommand);
  }
}

void interruptCommand() {
  if (currentCommand.key != "") {
    return;
  }
}

void executeCommand(struct Command command) {
  if (command.key == "") {
    return;
  }
  
  Serial.println("Key: " + command.key);
  Serial.println("Value: " + String(command.value));
}


void completeCommand() {
  currentCommand.key = "";
  currentCommand.value = 0;

  Serial.println("OK");
}
