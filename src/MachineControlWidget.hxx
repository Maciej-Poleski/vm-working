#ifndef MACHINECONTROLWIDGET_HXX
#define MACHINECONTROLWIDGET_HXX

#include "ui_MachineControlWidget.h"

class Machine;

class MachineControlWidget : public QWidget, private Ui::MachineControlWidget
{
    Q_OBJECT

public:
    explicit MachineControlWidget(QWidget* parent = 0);

    void setMachine(Machine* machine);

private slots:
    void machineStarting();
    void machineStopped();

private:
    void connectMachineToThis();
    void disconnectMachineFromThis();

    Machine* _machine;
};

#endif // MACHINECONTROLWIDGET_HXX
