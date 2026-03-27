#pragma once

#include <Arduino.h>
#include "SC16IS752.h"

// Stream wrapper for a single SC16IS752 UART channel.
// This allows channel A or B to be used with Arduino APIs expecting a Stream object.
class SC16IS752_Stream : public Stream
{
public:
    SC16IS752_Stream(SC16IS752 &bridge, uint8_t channel)
        : _bridge(bridge), _channel(channel)
    {
    }

    virtual int available() override
    {
        return _bridge.available(_channel);
    }

    virtual int read() override
    {
        return _bridge.read(_channel);
    }

    virtual int peek() override
    {
        return _bridge.peek(_channel);
    }

    virtual void flush() override
    {
        _bridge.flush(_channel);
    }

    virtual size_t write(uint8_t b) override
    {
        return _bridge.write(_channel, b);
    }

    virtual size_t write(const uint8_t *buffer, size_t size) override
    {
        if (!buffer || size == 0)
            return 0;

        size_t written = 0;
        for (size_t i = 0; i < size; ++i)
        {
            written += _bridge.write(_channel, buffer[i]);
        }
        return written;
    }

    uint8_t channel() const
    {
        return _channel;
    }

    SC16IS752 &bridge()
    {
        return _bridge;
    }

private:
    SC16IS752 &_bridge;
    uint8_t _channel;
};