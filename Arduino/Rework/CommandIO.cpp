#include "Arduino.h"
#include "CommandIO.h"

CommandIO::CommandIO() {
  Serial.begin(9600);
}

// читает один символ из
struct Command CommandIO::readCommand() {
  struct Command result;

  String newCommand = readSerial();
  if (newCommand != "") {
    result = parseCommand(newCommand);
  }

  return result;
}

// читает все символы до '\n' и добавляет их в буффер. Если символ означает конец команды - возвращает всю команду БЕЗ ЭТОГО СИМВОЛА.
String CommandIO::readSerial() {
  if (!Serial.available()) {
    return "";
  }

  char symbol = char(Serial.read());

  if (symbol == '\n') {
    String _commandBuffer = commandBuffer;
    commandBuffer = "";
    return _commandBuffer;
  }

  commandBuffer += symbol;

  return "";
}

// разбивает строку на ключ и значение команды. Если передана неверная команда (пустой ключ или в значении не только цифры), то возвращает структуру с key = "" и value = 0;
struct Command CommandIO::parseCommand(String command) {
  struct Command output;
  output.key = "";
  output.value = 0;

  if (command == "") {
    return output;
  }

  String valueStr = "";
  bool isWritingValue = false;
  for (int i = 0; i < command.length(); ++i) {
    char c = command.charAt(i);

    if (isWritingValue) {
      if (isDigit(c)) {
        valueStr += c;
      }
      else {
        output.key = "";
        return output;
      }
    }
    else {
      if (isDigit(c)) {
        isWritingValue = true;
        valueStr += c;
      }
      else {
        output.key += c;
      }
    }
  }

  if (output.key == "") {
    output.value = 0;
    return output;
  }

  if (valueStr != "") {
    output.value = valueStr.toInt();
  }
  
  return output;
}