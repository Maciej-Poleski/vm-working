#ifndef DECODER_HXX
#define DECODER_HXX

#include <QObject>

#include "Register.hxx"

class Processor;
class InstructionsProvider;
class QFile;
class Memory;

class Decoder : public QObject
{
    Q_OBJECT
public:
    explicit Decoder(QObject* parent = 0);

    void setProcessor(Processor* processor);
    void setMemory(Memory* memory);
    QString decodeInstructionAt(Register::Type address);

signals:
    void imageLoaded();
    void starting();
    void stopped();

public slots:
    void start();
    void stop();
    void step();

private slots:
    void makeIteration();

private:
    void makeSingleStep();

    Processor* _processor;
    Memory* _memory;
    InstructionsProvider* const _instructionsProvider;
    bool _wantStop;
};

#endif // DECODER_HXX
