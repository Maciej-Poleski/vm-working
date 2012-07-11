#include "DecoderWidget.hxx"

#include "Decoder.hxx"

#include <stdexcept>

DecoderWidget::DecoderWidget(QWidget* parent) :
    QWidget(parent), _decoder(nullptr)
{
    setupUi(this);
}

void DecoderWidget::setDecoder(Decoder* decoder)
{
    if(_decoder != nullptr)
        disconnectDecoderFromThis();
    _decoder = decoder;
    if(_decoder != nullptr)
        connectDecoderToThis();
}

void DecoderWidget::connectDecoderToThis()
{
    connect(_decoder, SIGNAL(imageLoaded()), this, SLOT(populateTextBrowser()));
}

void DecoderWidget::disconnectDecoderFromThis()
{
    disconnect(_decoder, SIGNAL(imageLoaded()), this, SLOT(populateTextBrowser()));
}

void DecoderWidget::populateTextBrowser()
{
    Q_CHECK_PTR(_decoder);
    QString text;
    for(Register::Type i = 0;; ++i)
    {
        try
        {
            text += _decoder->decodeInstructionAt(i) + "\n";
        }
        catch(std::out_of_range)
        {
            break;
        }
    }
    decoderTextBrowser->setText(text);
}
