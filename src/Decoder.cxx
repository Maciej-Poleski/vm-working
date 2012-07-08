#include "Decoder.hxx"

#include "Processor.hxx"
#include "InstructionsProvider.hxx"

#include <stdexcept>

#include <QtCore/QFile>

Decoder::Decoder(QObject *parent) :
    QObject(parent), _processor(nullptr),
    _instructionsProvider(new InstructionsProvider)
{
}

void Decoder::setProcessor(Processor *processor)
{
    _processor=processor;
    _instructionsProvider->setProcessor(_processor);
}

void Decoder::setImage(QFile *image)
{
    image->open(QIODevice::ReadOnly);
    if(image->size()>std::numeric_limits<Register::Type>::max())
        throw std::runtime_error("Obraz jest zbyt duży");
    Register::Type size=image->size();
    if(size%sizeof(Register::Type)!=0)
        throw std::runtime_error("Plik obrazu wygląda na obcięty");
    Register::Type* memoryImage =
            reinterpret_cast<Register::Type*>(image->map(0,size));
    if(memoryImage==nullptr)
        throw std::runtime_error("Nie udało się mapować obrazu");
    std::vector<Register::Type> memoryVector
            (memoryImage, memoryImage+size/sizeof(Register::Type));
    _instructionsProvider->setMemory(std::move(memoryVector));
    emit imageLoaded();
}

QString Decoder::decodeInstructionAt(Register::Type address)
{
    return QString::number(_instructionsProvider->getOpCodeAt(address),16);
}

void Decoder::makeSingleStep()
{
    Q_CHECK_PTR(_processor);
    Q_CHECK_PTR(_instructionsProvider);
    _processor->copyToRegister(16,std::numeric_limits<uint16_t>::max());
    _processor->flushSignals();
}
