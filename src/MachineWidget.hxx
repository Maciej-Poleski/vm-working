#ifndef MACHINEWIDGET_HXX
#define MACHINEWIDGET_HXX

#include <QtGui/QWidget>

#include "ui_MachineWidget.h"

class ProcessorStateWidget;
class DecoderStateWidget;
class MemoryStateWidget;
class MemoryControlWidget;
class MachineControlWidget;
class Machine;

class MachineWidget : public QWidget, private Ui::MachineWidget
{
    Q_OBJECT
public:
    explicit MachineWidget(QWidget* parent = 0);

    void setMachine(Machine* machine);

signals:

public slots:
    void repopulateGui();

private:
    void connectMachineToThis();
    void disconnectMachineFromThis();

    ProcessorStateWidget* _processorStateWidget;
    DecoderStateWidget* _decoderStateWidget;
    MemoryControlWidget* _memoryControlWidget;
    MemoryStateWidget* _memoryStateWidget;
    MachineControlWidget* _machineControlWidget;
    Machine* _machine;
};

#endif // MACHINEWIDGET_HXX
