#include "InstructionsProvider.hxx"

#include "Processor.hxx"
#include "Memory.hxx"

InstructionsProvider::InstructionsProvider() :
    _processor(nullptr), _memory(nullptr)
{
}

void InstructionsProvider::setProcessor(Processor* processor)
{
    _processor = processor;
}

void InstructionsProvider::setMemory(Memory* memory)
{
    _memory = memory;
}

Register::Type InstructionsProvider::nextOpCode()
{
    Q_CHECK_PTR(_processor);
    Q_CHECK_PTR(_memory);
    Register::Type result =
        _memory->getMemoryCeil(_processor->instructionPointer());
    _processor->advanceInstructionPointer();
    return result;
}
