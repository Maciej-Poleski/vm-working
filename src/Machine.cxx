#include "Machine.hxx"

#include "Processor.hxx"
#include "Decoder.hxx"
#include "InstructionsProvider.hxx"
#include "Memory.hxx"

Machine::Machine(QObject *parent) :
    QObject(parent), _processor(new Processor(this)),
    _decoder(new Decoder(this)), _memory(new Memory(this))
{
    _decoder->setProcessor(_processor);
    _decoder->setMemory(_memory);
    moveToThread(&thread);
    thread.start();
    connectSignalsAndSlots();
}

Processor* Machine::processor()
{
    return _processor;
}

Decoder* Machine::decoder()
{
    return _decoder;
}

Memory* Machine::memory()
{
    return _memory;
}

void Machine::connectSignalsAndSlots()
{
    connect(_decoder,SIGNAL(stopped()),this,SIGNAL(stopped()));
    connect(this,SIGNAL(stopped()),_processor,SLOT(flushSignals()));
    connect(_memory,SIGNAL(imageLoaded()),_processor,SLOT(reinitialize()));
}

void Machine::start()
{
    emit starting();
    _decoder->start();
}

void Machine::stop()
{
    _decoder->stop();
}

void Machine::makeSingleStep()
{
    emit starting();
    _decoder->step();
    emit stopped();
}
