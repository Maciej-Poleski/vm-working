#ifndef MEMORYSTATEWIDGET_HXX
#define MEMORYSTATEWIDGET_HXX

#include "ui_MemoryStateWidget.h"

class MemoryControlWidget;
class Memory;
class Decoder;

class MemoryStateWidget : public QWidget, private Ui::MemoryStateWidget
{
    Q_OBJECT

public:
    explicit MemoryStateWidget(MemoryControlWidget *memoryControlWidget,
                               QWidget *parent = 0);

    void setMemory(Memory *memory);
    void setDecoder(Decoder *decoder);

public slots:
    void repopulateGui();

private:
    void connectMemoryToThis();
    void disconnectMemoryFromThis();

    Memory *_memory;
    MemoryControlWidget *_memoryControlWidget;
    Decoder *_decoder;
};

#endif // MEMORYSTATEWIDGET_HXX
