#ifndef MACHINEWIDGET_HXX
#define MACHINEWIDGET_HXX

#include <QtGui/QWidget>

#include "ui_MachineWidget.h"

class ProcessorStateWidget;
class DecoderStateWidget;
class DecoderWidget;
class Machine;

class MachineWidget : public QWidget, private Ui::MachineWidget
{
    Q_OBJECT
public:
    explicit MachineWidget(QWidget *parent = 0);

    void setMachine(Machine *machine);

signals:

public slots:

private:
    void connectMachineToThis();

    ProcessorStateWidget *_processorStateWidget;
    DecoderStateWidget *_decoderStateWidget;
    DecoderWidget *_decoderWidget;
    Machine *_machine;
};

#endif // MACHINEWIDGET_HXX
