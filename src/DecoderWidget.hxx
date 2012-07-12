#ifndef DECODERWIDGET_HXX
#define DECODERWIDGET_HXX

#include "ui_DecoderWidget.h"

class Decoder;

class DecoderWidget : public QWidget, private Ui::DecoderWidget
{
    Q_OBJECT

public:
    explicit DecoderWidget(QWidget* parent = 0);

    void setDecoder(Decoder* decoder);

private slots:
    void populateTextBrowser();

private:
    void connectDecoderToThis();
    void disconnectDecoderFromThis();

    Decoder* _decoder;
};

#endif // DECODERWIDGET_HXX
