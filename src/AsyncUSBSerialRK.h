#ifndef __ASYNCUSBSERIALRK_H
#define __ASYNCUSBSERIALRK_H

// Github: https://github.com/rickkas7/AsyncUSBSerialRK
// License: MIT (free for use in open source or closed source projects, including commercial projects)
#include "Particle.h"
#include "RingBuffer.h"

class AsyncUSBSerialRK : public Stream
{
public:
    static AsyncUSBSerialRK &instance(size_t bufSize = 256);

	// public methods
    
    unsigned int baud() { return Serial.baud(); };

    operator bool() { return (bool)Serial; };
    bool isEnabled() { return Serial.isEnabled(); };
    bool isConnected() { return Serial.isConnected(); };

	void begin(long speed = 9600);
	void end() { Serial.end(); };
	int peek() { return Serial.peek(); };

	virtual size_t write(uint8_t byte);
	virtual int availableForWrite(void);

	virtual int read() { return Serial.read(); };
	virtual int available() { return Serial.available(); };
	virtual void flush() { return Serial.flush(); };

	virtual void blockOnOverrun(bool value) { _blockOnOverrun = value; };

	bool try_lock() { return Serial.try_lock(); };
	void lock() { Serial.lock(); };
	
	void unlock() { Serial.unlock(); };

	using Print::write;

private:
    AsyncUSBSerialRK(size_t bufSize);
    os_thread_return_t threadFunction();
    static os_thread_return_t threadFunctionStatic(void* param);

    bool _blockOnOverrun = true;
    size_t bufSize = 256;
    uint8_t *buffer = 0;
    RingBuffer<uint8_t> *ringBuffer;
    static AsyncUSBSerialRK *_instance;
};


#endif /* __ASYNCUSBSERIALRK_H */
