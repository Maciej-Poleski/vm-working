#include "DecoderStateWidget.hxx"

#include "Decoder.hxx"

#include <stdexcept>

#include <QtCore/QFile>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

DecoderStateWidget::DecoderStateWidget(QWidget *parent) :
    QWidget(parent),_decoder(nullptr)
{
    setupUi(this);
    connectSignalsAndSlots();
}

void DecoderStateWidget::setDecoder(Decoder *decoder)
{
    if(_decoder!=nullptr)
        disconnectDecoderFromThis();
    _decoder=decoder;
    if(_decoder!=nullptr)
        connectDecoderToThis();
}

void DecoderStateWidget::connectDecoderToThis()
{
}

void DecoderStateWidget::disconnectDecoderFromThis()
{
}

void DecoderStateWidget::connectSignalsAndSlots()
{

}

void DecoderStateWidget::repopulateGui()
{
// DO NOTHING
}
