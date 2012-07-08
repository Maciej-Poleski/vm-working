#ifndef DECODER_HXX
#define DECODER_HXX

#include <QObject>

#include "Register.hxx"

class Processor;
class InstructionsProvider;
class QFile;

class Decoder : public QObject
{
    Q_OBJECT
public:
    explicit Decoder(QObject *parent = 0);

    void setProcessor(Processor *processor);
    void setImage(QFile *image);
    QString decodeInstructionAt(Register::Type address);

signals:
    void imageLoaded();

public slots:
    void makeSingleStep();

private:
    Processor *_processor;
    InstructionsProvider * const _instructionsProvider;
};

#endif // DECODER_HXX
