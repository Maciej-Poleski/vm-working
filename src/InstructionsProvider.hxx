#ifndef INSTRUCTIONSPROVIDER_HXX
#define INSTRUCTIONSPROVIDER_HXX

#include <vector>

#include "Register.hxx"

class Processor;

class InstructionsProvider
{
public:
    InstructionsProvider();

    void setProcessor(Processor *processor);
    void setMemory(const std::vector<Register::Type> &memory);
    void setMemory(std::vector<Register::Type> && memory);
    Register::Type nextOpCode();
    Register::Type getOpCodeAt(Register::Type address);

private:
    Processor *_processor;
    std::vector<Register::Type> _memory;
};

#endif // INSTRUCTIONSPROVIDER_HXX
