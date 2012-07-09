#include "Decoder.hxx"

#include "Processor.hxx"
#include "InstructionsProvider.hxx"
#include "Memory.hxx"

#include <stdexcept>

#include <QtCore/QFile>

Decoder::Decoder(QObject *parent) :
    QObject(parent), _processor(nullptr),_memory(nullptr),
    _instructionsProvider(new InstructionsProvider),_wantStop(true)
{
}

void Decoder::setProcessor(Processor *processor)
{
    _processor=processor;
    _instructionsProvider->setProcessor(_processor);
}

void Decoder::setMemory(Memory *memory)
{
    _memory=memory;
    _instructionsProvider->setMemory(memory);
}

QString Decoder::decodeInstructionAt(Register::Type address)
{
    Q_CHECK_PTR(_processor);
    Q_CHECK_PTR(_memory);
    Register::Type opcode=_memory->getMemoryCeil(address);
    if(opcode==0)
    {
        return tr("Zatrzymaj maszynę");
    }
    else if((opcode&(~(0xfU)))==0x10)
    {
        Register::Type arg1=_memory->getMemoryCeil(address+1);
        return tr("Załaduj ")+QString::number(arg1)+tr(" do ")+"R"+
                QString::number((opcode&0xf)+1);
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
    Register::Type opcode=_instructionsProvider->nextOpCode();
    if(opcode==0)
    {
        stop();
    }
    else if((opcode&(~(0xfU)))==0x10)
    {
        Register::Type arg1=_instructionsProvider->nextOpCode();
        uint8_t destinationRegister=opcode&0xf;
        _processor->_loadToRegister(destinationRegister,arg1);
    }
    else
    {
        stop();
    }
}

void Decoder::start()
{
    _wantStop=false;
    emit starting();
    makeIteration();
}

void Decoder::stop()
{
    _wantStop=true;
}

void Decoder::step()
{
    makeSingleStep();
}

void Decoder::makeIteration()
{
    for(std::size_t i=0;i<1000;++i)
    {
        if(_wantStop)
        {
            emit stopped();
            return;
        }
        makeSingleStep();
    }
    QMetaObject::invokeMethod(this,"makeIteration",Qt::QueuedConnection);
}
