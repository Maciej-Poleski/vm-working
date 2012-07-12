#include "MachineWidget.hxx"

#include "ProcessorStateWidget.hxx"
#include "DecoderStateWidget.hxx"
#include "MemoryStateWidget.hxx"
#include "MemoryControlWidget.hxx"
#include "MachineControlWidget.hxx"
#include "Machine.hxx"

MachineWidget::MachineWidget(QWidget* parent) :
    QWidget(parent), _processorStateWidget(new ProcessorStateWidget(this)),
    _decoderStateWidget(new DecoderStateWidget(this)),
    _memoryControlWidget(new MemoryControlWidget(this)),
    _memoryStateWidget(new MemoryStateWidget(_memoryControlWidget, this)),
    _machineControlWidget(new MachineControlWidget(this)),
    _machine(nullptr)
{
    setupUi(this);
    rightColumnLayout->addWidget(_processorStateWidget);
    rightColumnLayout->addWidget(_decoderStateWidget);
    rightColumnLayout->addWidget(_machineControlWidget);
    rightColumnLayout->addWidget(_memoryControlWidget);
    leftColumnLayout->addWidget(_memoryStateWidget);


    rightColumnLayout->addStretch(1);
}

void MachineWidget::setMachine(Machine* machine)
{
    Q_CHECK_PTR(machine);
    if(_machine != nullptr)
        disconnectMachineFromThis();
    _machine = machine;
    _processorStateWidget->setProcessor(machine->processor());
    _decoderStateWidget->setDecoder(machine->decoder());
    _memoryStateWidget->setMemory(machine->memory());
    _memoryStateWidget->setDecoder(machine->decoder());
    _memoryControlWidget->setMemory(machine->memory());
    _machineControlWidget->setMachine(machine);
    connectMachineToThis();
}

void MachineWidget::connectMachineToThis()
{
    connect(_machine, SIGNAL(stopped()), this, SLOT(repopulateGui()));
}

void MachineWidget::disconnectMachineFromThis()
{
    disconnect(_machine, SIGNAL(stopped()), this, SLOT(repopulateGui()));
}

void MachineWidget::repopulateGui()
{
    _processorStateWidget->repopulateGui();
    _memoryStateWidget->repopulateGui();
}
