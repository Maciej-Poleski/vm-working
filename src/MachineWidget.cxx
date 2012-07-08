#include "MachineWidget.hxx"

#include "ProcessorStateWidget.hxx"
#include "DecoderStateWidget.hxx"
#include "DecoderWidget.hxx"
#include "Machine.hxx"

MachineWidget::MachineWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    _processorStateWidget=new ProcessorStateWidget(this);
    _decoderStateWidget=new DecoderStateWidget(this);
    _decoderWidget=new DecoderWidget(this);
    rightColumnLayout->addWidget(_processorStateWidget);
    rightColumnLayout->addWidget(_decoderStateWidget);
    leftColumnLayout->addWidget(_decoderWidget);


    rightColumnLayout->addStretch(1);
}

void MachineWidget::setMachine(Machine *machine)
{
    _machine=machine;
    _processorStateWidget->setProcessor(machine->processor());
    _decoderStateWidget->setDecoder(machine->decoder());
    _decoderWidget->setDecoder(machine->decoder());
    connectMachineToThis();
}

void MachineWidget::connectMachineToThis()
{

}
