#include "DecoderStateWidget.hxx"

#include "Decoder.hxx"

#include <stdexcept>

#include <QtCore/QFile>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

DecoderStateWidget::DecoderStateWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connectSignalsAndSlots();
}

void DecoderStateWidget::setDecoder(Decoder *decoder)
{
    _decoder=decoder;
    connectDecoderToThis();
}

void DecoderStateWidget::connectDecoderToThis()
{
    connect(stepPushButton,SIGNAL(clicked()),_decoder,SLOT(makeSingleStep()));
}

void DecoderStateWidget::connectSignalsAndSlots()
{
    connect(loadImagePushButton,SIGNAL(clicked()),this,SLOT(loadImage()));
}

void DecoderStateWidget::loadImage()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if(dialog.exec())
    {
        QFile file(dialog.selectedFiles().first());
        try
        {
            _decoder->setImage(&file);
        }
        catch(std::runtime_error e)
        {
            QMessageBox::critical(this,"Błąd podczas ładowania obrazu",e.what());
        }
    }
}
