#ifndef INSTRUCTIONSPROVIDER_HXX
#define INSTRUCTIONSPROVIDER_HXX

#include "Register.hxx"

class Processor;
class Memory;

class InstructionsProvider
{
public:
    InstructionsProvider();

    void setProcessor(Processor* processor);
    void setMemory(Memory* memory);
    Register::Type nextOpCode();

private:
    Processor* _processor;
    Memory* _memory;
};

#endif // INSTRUCTIONSPROVIDER_HXX
