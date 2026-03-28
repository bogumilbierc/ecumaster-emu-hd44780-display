#ifndef EDL_SERIAL_H
#define EDL_SERIAL_H

#include <Arduino.h>
#include "EDLTypes.h"

class EDLSerial {
public:
  void begin(Stream &stream);
  bool update();
  const EDLFrame &getFrame() const;

private:
  Stream *_stream;
  uint8_t _buffer[260];
  size_t _index = 0;
  EDLFrame _frame;
  bool parseFrame(uint8_t *data, EDLFrame &frame);
};

#endif