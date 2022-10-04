#include "AsyncUSBSerialRK.h"


AsyncUSBSerialRK *AsyncUSBSerialRK::_instance;

// [static] 
AsyncUSBSerialRK &AsyncUSBSerialRK::instance(size_t bufSize) {
    if (!_instance) {
        _instance = new AsyncUSBSerialRK(bufSize);
    }  
    return *_instance;
}


AsyncUSBSerialRK::AsyncUSBSerialRK(size_t bufSize) {
    buffer = new uint8_t(bufSize);

    ringBuffer = new RingBuffer<uint8_t>(buffer, bufSize);
}


void AsyncUSBSerialRK::begin(long speed) {
    Serial.begin(speed);

    new Thread("asyncusb", threadFunctionStatic, this, OS_THREAD_PRIORITY_DEFAULT, OS_THREAD_STACK_SIZE_DEFAULT);
}


size_t AsyncUSBSerialRK::write(uint8_t byte) {

    while(true) {
        if (ringBuffer->write(&byte)) {
            return 1;
        }

        if (!_blockOnOverrun) {
            return 0;
        }

        delay(1);
    }
}

int AsyncUSBSerialRK::availableForWrite(void) {
    return bufSize - ringBuffer->availableForRead();
}

os_thread_return_t AsyncUSBSerialRK::threadFunction() {
    while(true) {
        uint8_t c;
        if (ringBuffer->read(&c)) {
            Serial.write(c);
        }
        os_thread_yield();
    }
}

// [static]
os_thread_return_t AsyncUSBSerialRK::threadFunctionStatic(void* param) {
    ((AsyncUSBSerialRK *)param)->threadFunction();
}



