#include "MemoryStateWidget.hxx"

#include "Memory.hxx"
#include "MemoryControlWidget.hxx"
#include "Decoder.hxx"

MemoryStateWidget::MemoryStateWidget(MemoryControlWidget *memoryControlWidget,
                                     QWidget *parent) :
    QWidget(parent),_memory(nullptr),_memoryControlWidget(memoryControlWidget),
    _decoder(nullptr)
{
    Q_CHECK_PTR(_memoryControlWidget);
    setupUi(this);
}

void MemoryStateWidget::setMemory(Memory *memory)
{
    if(_memory!=nullptr)
        disconnectMemoryFromThis();
    _memory=memory;
    if(_memory!=nullptr)
        connectMemoryToThis();
}

void MemoryStateWidget::setDecoder(Decoder *decoder)
{
    _decoder=decoder;
}

void MemoryStateWidget::connectMemoryToThis()
{
    connect(_memory,SIGNAL(imageLoaded()),this,SLOT(repopulateGui()));
}

void MemoryStateWidget::disconnectMemoryFromThis()
{
    disconnect(_memory,SIGNAL(imageLoaded()),this,SLOT(repopulateGui()));
}

void MemoryStateWidget::repopulateGui()
{
    Q_CHECK_PTR(_decoder);
    QString text;
    for(size_t i=0,e=_memoryControlWidget->lengthOfCodeView();i<=e;++i)
    {
        text+=QString::number(i)+":\t"+
                QString::number(_memory->getMemoryCeil(i),16)+"\t"+
                _decoder->decodeInstructionAt(i)+"\n";
    }
    memoryStateTextBrowser->setText(text);
}
