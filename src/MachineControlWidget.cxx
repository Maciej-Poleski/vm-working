#include "MachineControlWidget.hxx"

#include "Machine.hxx"

MachineControlWidget::MachineControlWidget(QWidget* parent) :
    QWidget(parent), _machine(nullptr)
{
    setupUi(this);
}

void MachineControlWidget::setMachine(Machine* machine)
{
    if(_machine)
        disconnectMachineFromThis();
    _machine = machine;
    if(_machine)
        connectMachineToThis();
}

void MachineControlWidget::connectMachineToThis()
{
    Q_CHECK_PTR(_machine);
    connect(startPushButton, SIGNAL(clicked()),
            _machine, SLOT(start()));
    connect(stopPushButton, SIGNAL(clicked()),
            _machine, SLOT(stop()));
    connect(singleStepPushButton, SIGNAL(clicked()),
            _machine, SLOT(makeSingleStep()));
    connect(_machine, SIGNAL(starting()),
            this, SLOT(machineStarting()));
    connect(_machine, SIGNAL(stopped()),
            this, SLOT(machineStopped()));
}

void MachineControlWidget::disconnectMachineFromThis()
{
    Q_CHECK_PTR(_machine);
    disconnect(startPushButton, SIGNAL(clicked()),
               _machine, SLOT(start()));
    disconnect(stopPushButton, SIGNAL(clicked()),
               _machine, SLOT(stop()));
    disconnect(singleStepPushButton, SIGNAL(clicked()),
               _machine, SLOT(makeSingleStep()));
    disconnect(_machine, SIGNAL(starting()),
               this, SLOT(machineStarting()));
    disconnect(_machine, SIGNAL(stopped()),
               this, SLOT(machineStopped()));
}

void MachineControlWidget::machineStarting()
{
    singleStepPushButton->setDisabled(true);
}

void MachineControlWidget::machineStopped()
{
    singleStepPushButton->setEnabled(true);
}
