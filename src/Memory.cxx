#include "Memory.hxx"

#include <stdexcept>
#include <algorithm>

#include <QtCore/QFile>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

Memory::Memory(QObject* parent) :
    QObject(parent)
{
}

void Memory::loadImage(const QString& imageName)
{
    QFile file(imageName);
    try
    {
        file.open(QIODevice::ReadOnly);
        if(file.size() > std::numeric_limits<Register::Type>::max())
            throw std::runtime_error("Obraz jest zbyt duży");
        Register::Type size = file.size();
        if(size % sizeof(Register::Type) != 0)
            throw std::runtime_error("Plik obrazu wygląda na obcięty");
        Register::Type* memoryImage =
            reinterpret_cast<Register::Type*>(file.map(0, size));
        if(memoryImage == nullptr)
            throw std::runtime_error("Nie udało się mapować obrazu");
        std::copy(memoryImage,
                  memoryImage + size / sizeof(Register::Type),
                  _memory.begin());
        file.close();
        emit imageLoaded();
    }
    catch(std::runtime_error e)
    {
        emit imageLoadingError(tr("Błąd podczas ładowania obrazu:\n") + e.what());
    }
}

Register::Type Memory::getMemoryCeil(Register::Type address) const
{
    return _memory[address];
}

void Memory::setMemoryCeil(Register::Type address, Register::Type value)
{
    _memory[address] = value;
}
