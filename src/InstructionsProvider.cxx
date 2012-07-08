#include "InstructionsProvider.hxx"

#include "Processor.hxx"

InstructionsProvider::InstructionsProvider() :
    _processor(nullptr)
{
}

void InstructionsProvider::setProcessor(Processor *processor)
{
    _processor=processor;
}

void InstructionsProvider::setMemory(const std::vector<Register::Type> &memory)
{
    _memory=memory;
}

void InstructionsProvider::setMemory(std::vector<Register::Type> &&memory)
{
    _memory=std::move(memory);
}

Register::Type InstructionsProvider::nextOpCode()
{
    Q_CHECK_PTR(_processor);
    Register::Type result=_memory.at(_processor->instructionPointer());
    _processor->advanceInstructionPointer();
    return result;
}

Register::Type InstructionsProvider::getOpCodeAt(Register::Type address)
{
    return _memory.at(address);
}
