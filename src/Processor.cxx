#include "Processor.hxx"

Processor::Processor(QObject *parent) :
    QObject(parent),
    _registers{new Register(this), new Register(this), new Register(this),
            new Register(this),new Register(this), new Register(this),
            new Register(this),new Register(this),new Register(this),
            new Register(this), new Register(this),new Register(this),
            new Register(this), new Register(this), new Register(this),
            new Register(this)},
    _registers_changed{false,false,false,false,false,false,false,false,false,
                       false,false,false,false,false,false,false},
    _instructionPointer{new Register(0,this)},
    _instructionPointer_changed{false}
{
connectSignalsAndSlots();
}

void Processor::nop()
{
}

void Processor::connectSignalsAndSlots()
{
    connect(_registers[0],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[1],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[2],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[3],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[4],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[5],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[6],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[7],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[8],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[9],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[10],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[11],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[12],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[13],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[14],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_registers[15],SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchRegisterChange(Register::Type)));
    connect(_instructionPointer,SIGNAL(valueChanged(Register::Type)),
            this,SLOT(dispatchInstructionPointerChange(Register::Type)));
}

void Processor::dispatchInstructionPointerChange(Register::Type newValue)
{
    Q_UNUSED(newValue);
    if(_instructionPointer_changed==false)
    {
        _instructionPointer_changed=true;
        emit instructionPointerChanged();
    }
}

void Processor::dispatchRegisterChange(Register::Type newValue)
{
    Q_UNUSED(newValue);
    int8_t index=-1;
    for(std::size_t i=0;i<16;++i)
        if(sender()==_registers[i])
            index=i;
    Q_ASSERT(index>=0);
    if(_registers_changed[index]==false)
    {
        _registers_changed[index]=true;
        emit registerChanged(index+1);
    }
}

void Processor::flushSignals()
{
    if(_instructionPointer_changed)
    {
        _instructionPointer_changed=false;
        emit instructionPointerChanged(*_instructionPointer);
    }
    for(std::size_t i=0;i<16;++i)
        if(_registers_changed[i])
        {
            _registers_changed[i]=false;
            emit registerChanged(i+1,*_registers[i]);
        }
}

Register::Type Processor::instructionPointer() const
{
    return *_instructionPointer;
}

Register::Type Processor::getRegister(uint8_t index) const
{
    Q_ASSERT(index>0);
    Q_ASSERT(index<=16);
    return *_registers[index-1];
}

void Processor::advanceInstructionPointer()
{
    _instructionPointer->setValue(*_instructionPointer+1);
}

void Processor::copyToRegister(uint8_t index, Register::Type value)
{
    _registers[index-1]->setValue(value);
}
