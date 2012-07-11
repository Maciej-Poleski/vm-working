#include "Register.hxx"

Register::Register(QObject* parent) :
    QObject(parent)
{
}

Register::Register(Type value, QObject* parent) :
    QObject(parent), _value(value)
{

}

void Register::setValue(Type newValue)
{
    if(_value != newValue)
    {
        _value = newValue;
        emit valueChanged(newValue);
    }
}

Register::operator uint16_t() const
{
    return _value;
}


Register& Register::operator =(const Register& o)
{
    _value = o._value;
    return *this;
}
