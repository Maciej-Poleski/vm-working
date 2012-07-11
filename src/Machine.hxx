#ifndef MACHINE_HXX
#define MACHINE_HXX

#include <QObject>

#include <QtCore/QThread>

class Processor;
class Decoder;
class Memory;

class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject* parent = 0);

    Processor* processor();
    Decoder* decoder();
    Memory* memory();

signals:
    void stopped();
    void starting();

public slots:
    void start();
    void stop();
    void makeSingleStep();

private:
    void connectSignalsAndSlots();

    QThread thread;
    Processor* _processor;
    Decoder* _decoder;
    Memory* _memory;
};

#endif // MACHINE_HXX
