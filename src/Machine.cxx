#include "Machine.hxx"

#include "Processor.hxx"
#include "Decoder.hxx"
#include "InstructionsProvider.hxx"

Machine::Machine(QObject *parent) :
    QObject(parent), _processor(new Processor(this)),
    _decoder(new Decoder(this))
{
    _decoder->setProcessor(_processor);
}

Processor* Machine::processor()
{
    return _processor;
}

Decoder* Machine::decoder()
{
    return _decoder;
}
