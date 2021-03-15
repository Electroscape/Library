#pragma once

#include <Arduino.h>

#define MAX_CTRL_PIN A0
#define MAX485_WRITE HIGH
#define MAX485_READ LOW

namespace stb_namespace
{
    class Brain
    {
    private:
        /* data */
    public:
        Brain(String BrainName);
        ~Brain();
    };
        
    void printWithHeader(String message, String source);
    void software_Reset();
}