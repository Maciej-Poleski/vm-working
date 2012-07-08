#ifndef REGISTER_HXX
#define REGISTER_HXX

#include <cstdint>

#include <QObject>

class Register : public QObject
{
    Q_OBJECT
public:
    typedef uint16_t Type;

    explicit Register(QObject *parent = nullptr);
    explicit Register(Type value,QObject *parent=nullptr);

    Register& operator=(const Register &o);
    operator uint16_t() const;

signals:
    void valueChanged(Register::Type newValue);

public slots:
    void setValue(Register::Type newValue);

private:
    Type _value;
};

#endif // REGISTER_HXX
