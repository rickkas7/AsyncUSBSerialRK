# AsyncUSBSerialRK

**Asynchronous USB Serial (CDC) for the Particle P2 and Photon 2**

- Github: https://github.com/rickkas7/AsyncUSBSerialRK
- License: MIT (free for use in open source or closed source projects, including commercial projects)

On the P2 and Photon 2, writing to the USB serial appears significantly slower than on other devices. This is because writing to USB CDC serial is synchronous on the P2 and Photon 2 (RTL8721D), but on other platforms there is a ring buffer. This class adds a buffer so Serial writes are fast.

Note that this is only for USB CDC `Serial`, not UART serial (such as `Serial1`), which is already buffered.

## Example

The examples/1-simple example is simple:

```cpp
#include "AsyncUSBSerialRK.h"

SYSTEM_THREAD(ENABLED);


void setup() {
    // Replaces: Serial.begin();
    AsyncUSBSerialRK::instance().begin();
}

void loop() {
    static unsigned long lastRun = 0;

    unsigned long start = millis();
    AsyncUSBSerialRK::instance().printlnf("test %lu", lastRun);
    lastRun = millis() - start;

    delay(1000);
}
```

- Instead of calling `Serial.begin` call:

```
AsyncUSBSerialRK::instance().begin();
```

You can optionally pass a baud rate, but it's ignored just like it is for `Serial.begin()`.

- You can use all standard methods for Serial, such as `println`, `printlnf`, `write`, etc.

- Also you can read from this object.

- Instead of using `Serial.` use `AsyncUSBSerialRK::instance().`

If this seems to verbose, assign it to a variable:

```
AsyncUSBSerialRK ASerial = AsyncUSBSerialRK::instance();
```

Then instead of using `Serial.` or `AsyncUSBSerialRK::instance().` you instead can just use `ASerial.`.

- The reason for the `instance()` thing (the singleton pattern) is in case you need to use the async serial from multiple source files.

- By default the ring buffer is 256 bytes. If you want to make it bigger, pass the size as the parameter to instance() in the first place that the instance is created, typically during setup.

```
AsyncUSBSerialRK::instance(512).begin();
```

- The `blockOnOverrun()` in `Serial` is supported. The default is true which is to block execution when the ring buffer is full. If you set it to false, data that will overflow the buffer is discarded.

