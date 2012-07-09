#ifndef MEMORY_HXX
#define MEMORY_HXX

#include <QObject>

#include "Register.hxx"

#include <array>

class QFile;

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = 0);

    Register::Type getMemoryCeil(Register::Type address) const;
    void setMemoryCeil(Register::Type address, Register::Type value);

signals:
    void imageLoaded();
    void imageLoadingError(const QString &message);

public slots:
    void loadImage(const QString & imageName);

private:
    std::array<
        Register::Type,
        std::numeric_limits<Register::Type>::max()+1
        > _memory;
};

#endif // MEMORY_HXX
