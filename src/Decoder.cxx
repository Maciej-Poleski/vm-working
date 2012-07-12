#include "Decoder.hxx"

#include "Processor.hxx"
#include "InstructionsProvider.hxx"
#include "Memory.hxx"

#include <stdexcept>

#include <QtCore/QFile>

Decoder::Decoder(QObject* parent) :
    QObject(parent), _processor(nullptr), _memory(nullptr),
    _instructionsProvider(new InstructionsProvider), _wantStop(true)
{
}

void Decoder::setProcessor(Processor* processor)
{
    _processor = processor;
    _instructionsProvider->setProcessor(_processor);
}

void Decoder::setMemory(Memory* memory)
{
    _memory = memory;
    _instructionsProvider->setMemory(memory);
}

QString Decoder::decodeInstructionAt(Register::Type address)
{
    Q_CHECK_PTR(_processor);
    Q_CHECK_PTR(_memory);
    Register::Type opcode = _memory->getMemoryCeil(address);
    if((opcode & 0xf000) == 0)
    {
        // 0000 xxxx xxxx xxxx
        if(opcode & 0x800)
        {
            // 0000 1xxx xxxx xxxx
            return tr("Nieznany opcode");
        }
        else
        {
            // 0000 0xxx xxxx xxxx
            if(opcode & 0x400)
            {
                // 0000 01xx xxxx xxxx
                return tr("Nieznany opcode");
            }
            else
            {
                // 0000 00xx xxxx xxxx
                if(opcode & 0x200)
                {
                    // 0000 001x xxxx xxxx
                    return tr("Nieznany opcode");
                }
                else
                {
                    // 0000 000x xxxx xxxx
                    if(opcode & 0x100)
                    {
                        // 0000 0001 xxxx xxxx
                        return tr("Nieznany opcode");
                    }
                    else
                    {
                        // 0000 0000 xxxx xxxx
                        if(opcode & 0x80)
                        {
                            // 0000 0000 1xxx xxxx
                            return tr("Nieznany opcode");
                        }
                        else
                        {
                            // 0000 0000 0xxx xxxx
                            if(opcode & 0x40)
                            {
                                // 0000 0000 01xx xxxx
                                return tr("Nieznany opcode");
                            }
                            else
                            {
                                // 0000 0000 00xx xxxx
                                if(opcode & 0x20)
                                {
                                    // 0000 0000 001x xxxx
                                    if(opcode & 0x10)
                                    {
                                        // 0000 0000 0011 xxxx
                                        return tr("Nieznany opcode");
                                    }
                                    else
                                    {
                                        // 0000 0000 0010 xxxx
                                        Register::Type arg1 = _memory->getMemoryCeil(address + 1);
                                        return tr("Załaduj z ") + QString::number(arg1) + tr(" do ") + "R" +
                                               QString::number((opcode & 0xf) + 1);
                                    }
                                }
                                else
                                {
                                    // 0000 0000 000x xxxx
                                    if(opcode & 0x10)
                                    {
                                        // 0000 0000 0001 xxxx
                                        Register::Type arg1 = _memory->getMemoryCeil(address + 1);
                                        return tr("Załaduj ") + QString::number(arg1) + tr(" do ") + "R" +
                                               QString::number((opcode & 0xf) + 1);
                                    }
                                    else
                                    {
                                        // 0000 0000 0000 xxxx
                                        if(opcode & 0x8)
                                        {
                                            // 0000 0000 0000 1xxx
                                            return tr("Nieznany opcode");
                                        }
                                        else
                                        {
                                            // 0000 0000 0000 0xxx
                                            if(opcode & 0x4)
                                            {
                                                // 0000 0000 0000 01xx
                                                return tr("Nieznany opcode");
                                            }
                                            else
                                            {
                                                // 0000 0000 0000 00xx
                                                if(opcode & 0x2)
                                                {
                                                    // 0000 0000 0000 001x
                                                    return tr("Nieznany opcode");
                                                }
                                                else
                                                {
                                                    // 0000 0000 0000 000x
                                                    if(opcode & 0x1)
                                                    {
                                                        // 0000 0000 0000 0001
                                                        return tr("Nieznany opcode");
                                                    }
                                                    else
                                                    {
                                                        // 0000 0000 0000 0000
                                                        return tr("Zatrzymaj maszynę");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        return tr("Nieznany opcode");
    }
}

void Decoder::makeSingleStep()
{
    Q_CHECK_PTR(_processor);
    Q_CHECK_PTR(_instructionsProvider);
    Register::Type opcode = _instructionsProvider->nextOpCode();
    if((opcode & 0xf000) == 0)
    {
        // 0000 xxxx xxxx xxxx
        if(opcode & 0x800)
        {
            // 0000 1xxx xxxx xxxx
            stop();
        }
        else
        {
            // 0000 0xxx xxxx xxxx
            if(opcode & 0x400)
            {
                // 0000 01xx xxxx xxxx
                stop();
            }
            else
            {
                // 0000 00xx xxxx xxxx
                if(opcode & 0x200)
                {
                    // 0000 001x xxxx xxxx
                    stop();
                }
                else
                {
                    // 0000 000x xxxx xxxx
                    if(opcode & 0x100)
                    {
                        // 0000 0001 xxxx xxxx
                        stop();
                    }
                    else
                    {
                        // 0000 0000 xxxx xxxx
                        if(opcode & 0x80)
                        {
                            // 0000 0000 1xxx xxxx
                            stop();
                        }
                        else
                        {
                            // 0000 0000 0xxx xxxx
                            if(opcode & 0x40)
                            {
                                // 0000 0000 01xx xxxx
                                stop();
                            }
                            else
                            {
                                // 0000 0000 00xx xxxx
                                if(opcode & 0x20)
                                {
                                    // 0000 0000 001x xxxx
                                    if(opcode & 0x10)
                                    {
                                        // 0000 0000 0011 xxxx
                                        stop();
                                    }
                                    else
                                    {
                                        // 0000 0000 0010 xxxx
                                        Register::Type arg1 = _instructionsProvider->nextOpCode();
                                        uint8_t destinationRegister = opcode & 0xf;
                                        _processor->cpu_loadFromMemoryToRegister(destinationRegister, arg1);
                                    }
                                }
                                else
                                {
                                    // 0000 0000 000x xxxx
                                    if(opcode & 0x10)
                                    {
                                        // 0000 0000 0001 xxxx
                                        Register::Type arg1 = _instructionsProvider->nextOpCode();
                                        uint8_t destinationRegister = opcode & 0xf;
                                        _processor->cpu_loadToRegister(destinationRegister, arg1);
                                    }
                                    else
                                    {
                                        // 0000 0000 0000 xxxx
                                        if(opcode & 0x8)
                                        {
                                            // 0000 0000 0000 1xxx
                                            stop();
                                        }
                                        else
                                        {
                                            // 0000 0000 0000 0xxx
                                            if(opcode & 0x4)
                                            {
                                                // 0000 0000 0000 01xx
                                                stop();
                                            }
                                            else
                                            {
                                                // 0000 0000 0000 00xx
                                                if(opcode & 0x2)
                                                {
                                                    // 0000 0000 0000 001x
                                                    stop();
                                                }
                                                else
                                                {
                                                    // 0000 0000 0000 000x
                                                    if(opcode & 0x1)
                                                    {
                                                        // 0000 0000 0000 0001
                                                        stop();
                                                    }
                                                    else
                                                    {
                                                        // 0000 0000 0000 0000
                                                        stop();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        stop();
    }
}

void Decoder::start()
{
    _wantStop = false;
    emit starting();
    makeIteration();
}

void Decoder::stop()
{
    _wantStop = true;
}

void Decoder::step()
{
    makeSingleStep();
}

void Decoder::makeIteration()
{
    for(std::size_t i = 0; i < 1000; ++i)
    {
        if(_wantStop)
        {
            emit stopped();
            return;
        }
        makeSingleStep();
    }
    QMetaObject::invokeMethod(this, "makeIteration", Qt::QueuedConnection);
}
