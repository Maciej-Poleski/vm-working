#ifndef DECODERSTATEWIDGET_HXX
#define DECODERSTATEWIDGET_HXX

#include "ui_DecoderStateWidget.h"

class Decoder;

class DecoderStateWidget : public QWidget, private Ui::DecoderStateWidget
{
    Q_OBJECT

public:
    explicit DecoderStateWidget(QWidget *parent = 0);

    void setDecoder(Decoder *decoder);

private slots:
    void loadImage();

private:
    void connectDecoderToThis();
    void connectSignalsAndSlots();

    Decoder *_decoder;
};

#endif // DECODERSTATEWIDGET_HXX
