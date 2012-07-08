#ifndef PROCESSORSTATEWIDGET_HXX
#define PROCESSORSTATEWIDGET_HXX

#include "ui_ProcessorStateWidget.h"

#include <cstdint>

#include "Register.hxx"

class Processor;

class ProcessorStateWidget : public QWidget, private Ui::ProcessorStateWidget
{
    Q_OBJECT

public:
    explicit ProcessorStateWidget(QWidget *parent = 0);

    void setProcessor(Processor *processor);

private slots:
    void disableInstructionPointerLineEdit();
    void updateInstructionPointerLineEdit(Register::Type newValue);
    void disableRegisterLineEdit(uint8_t index);
    void updateRegisterLineEdit(uint8_t index,Register::Type newValue);

private:
    void connectProcesorToThis();

    Processor *_processor;
};

#endif // PROCESSORSTATEWIDGET_HXX
