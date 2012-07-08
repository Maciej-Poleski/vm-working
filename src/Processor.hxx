#ifndef PROCESSOR_HXX
#define PROCESSOR_HXX

#include <cstdint>

#include <QObject>

#include "Register.hxx"

/**
 * @brief Klasa obsługująca podstawowe funkcjonalności procesora.
 *
 * Przyjmuje polecenia z dekodera
 */
class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QObject *parent = 0);
    void nop();

    Register::Type instructionPointer() const;
    Register::Type getRegister(uint8_t index) const;
    void advanceInstructionPointer();

    void copyToRegister(uint8_t index, Register::Type value);

signals:
    void registerChanged(uint8_t index,Register::Type newValue);
    void registerChanged(uint8_t index);
    void instructionPointerChanged(Register::Type newValue);
    void instructionPointerChanged();

public slots:
    void flushSignals();

private slots:
    void dispatchRegisterChange(Register::Type newValue);
    void dispatchInstructionPointerChange(Register::Type newValue);

private:
    void connectSignalsAndSlots();

    Register *_registers[16];
    bool _registers_changed[16];
    Register *_instructionPointer;
    bool _instructionPointer_changed;
};

#endif // PROCESSOR_HXX
