#include "ProcessorStateWidget.hxx"

#include <QtCore/QLocale>

#include "Processor.hxx"

ProcessorStateWidget::ProcessorStateWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUi(this);
}

void ProcessorStateWidget::setProcessor(Processor* processor)
{
    _processor = processor;
    connectProcesorToThis();
}

void ProcessorStateWidget::connectProcesorToThis()
{
    connect(_processor, SIGNAL(instructionPointerChanged()),
            this, SLOT(disableInstructionPointerLineEdit()));
    connect(_processor, SIGNAL(instructionPointerChanged(Register::Type)),
            this, SLOT(updateInstructionPointerLineEdit(Register::Type)));
    updateInstructionPointerLineEdit(_processor->instructionPointer());
    connect(_processor, SIGNAL(registerChanged(uint8_t)),
            this, SLOT(disableRegisterLineEdit(uint8_t)));
    connect(_processor, SIGNAL(registerChanged(uint8_t, Register::Type)),
            this, SLOT(updateRegisterLineEdit(uint8_t, Register::Type)));
    for(uint8_t i = 1; i <= 16; ++i)
        updateRegisterLineEdit(i, _processor->getRegister(i));
}

void ProcessorStateWidget::disableInstructionPointerLineEdit()
{
    ipLineEdit->setDisabled(true);
}

void
ProcessorStateWidget::updateInstructionPointerLineEdit(Register::Type newValue)
{
    ipLineEdit->setText(QString::number(newValue));
    ipLineEdit->setEnabled(true);
}

void ProcessorStateWidget::disableRegisterLineEdit(uint8_t index)
{
    switch(index)
    {
    case 1:
        r1LineEdit->setDisabled(true);
        break;
    case 2:
        r2LineEdit->setDisabled(true);
        break;
    case 3:
        r3LineEdit->setDisabled(true);
        break;
    case 4:
        r4LineEdit->setDisabled(true);
        break;
    case 5:
        r5LineEdit->setDisabled(true);
        break;
    case 6:
        r6LineEdit->setDisabled(true);
        break;
    case 7:
        r7LineEdit->setDisabled(true);
        break;
    case 8:
        r8LineEdit->setDisabled(true);
        break;
    case 9:
        r9LineEdit->setDisabled(true);
        break;
    case 10:
        r10LineEdit->setDisabled(true);
        break;
    case 11:
        r11LineEdit->setDisabled(true);
        break;
    case 12:
        r12LineEdit->setDisabled(true);
        break;
    case 13:
        r13LineEdit->setDisabled(true);
        break;
    case 14:
        r14LineEdit->setDisabled(true);
        break;
    case 15:
        r15LineEdit->setDisabled(true);
        break;
    default:
        Q_ASSERT(index == 16);
        r16LineEdit->setDisabled(true);
        break;
    }
}

void
ProcessorStateWidget::updateRegisterLineEdit(uint8_t index,
        Register::Type newValue)
{
    switch(index)
    {
    case 1:
        r1LineEdit->setText(QString::number(newValue));
        r1LineEdit->setEnabled(true);
        break;
    case 2:
        r2LineEdit->setText(QString::number(newValue));
        r2LineEdit->setEnabled(true);
        break;
    case 3:
        r3LineEdit->setText(QString::number(newValue));
        r3LineEdit->setEnabled(true);
        break;
    case 4:
        r4LineEdit->setText(QString::number(newValue));
        r4LineEdit->setEnabled(true);
        break;
    case 5:
        r5LineEdit->setText(QString::number(newValue));
        r5LineEdit->setEnabled(true);
        break;
    case 6:
        r6LineEdit->setText(QString::number(newValue));
        r6LineEdit->setEnabled(true);
        break;
    case 7:
        r7LineEdit->setText(QString::number(newValue));
        r7LineEdit->setEnabled(true);
        break;
    case 8:
        r8LineEdit->setText(QString::number(newValue));
        r8LineEdit->setEnabled(true);
        break;
    case 9:
        r9LineEdit->setText(QString::number(newValue));
        r9LineEdit->setEnabled(true);
        break;
    case 10:
        r10LineEdit->setText(QString::number(newValue));
        r10LineEdit->setEnabled(true);
        break;
    case 11:
        r11LineEdit->setText(QString::number(newValue));
        r11LineEdit->setEnabled(true);
        break;
    case 12:
        r12LineEdit->setText(QString::number(newValue));
        r12LineEdit->setEnabled(true);
        break;
    case 13:
        r13LineEdit->setText(QString::number(newValue));
        r13LineEdit->setEnabled(true);
        break;
    case 14:
        r14LineEdit->setText(QString::number(newValue));
        r14LineEdit->setEnabled(true);
        break;
    case 15:
        r15LineEdit->setText(QString::number(newValue));
        r15LineEdit->setEnabled(true);
        break;
    default:
        Q_ASSERT(index == 16);
        r16LineEdit->setText(QString::number(newValue));
        r16LineEdit->setEnabled(true);
        break;
    }
}

void ProcessorStateWidget::repopulateGui()
{
    for(uint8_t i = 1; i <= 16; ++i)
        updateRegisterLineEdit(i, _processor->getRegister(i));
}
