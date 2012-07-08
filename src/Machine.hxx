#ifndef MACHINE_HXX
#define MACHINE_HXX

#include <QObject>

class Processor;
class Decoder;

class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject *parent = 0);

    Processor *processor();
    Decoder *decoder();

signals:

public slots:

private:
    Processor *_processor;
    Decoder *_decoder;
};

#endif // MACHINE_HXX
