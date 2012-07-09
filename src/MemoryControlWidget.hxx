#ifndef MEMORYCONTROLWIDGET_HXX
#define MEMORYCONTROLWIDGET_HXX

#include "ui_MemoryControlWidget.h"

#include "Register.hxx"

class Memory;

class MemoryControlWidget : public QWidget, private Ui::MemoryControlWidget
{
    Q_OBJECT

public:
    explicit MemoryControlWidget(QWidget *parent = 0);

    void setMemory(Memory *memory);
    Register::Type lengthOfCodeView() const;

private slots:
    void loadImage();
    void imageLoadingError(const QString &message);

private:
    void connectMemoryToThis();
    void disconnectMemoryFromThis();

    Memory *_memory;
};

#endif // MEMORYCONTROLWIDGET_HXX
