#include "MemoryControlWidget.hxx"

#include "Memory.hxx"

#include <stdexcept>

#include <QtCore/QFile>
#include <QtCore/QMetaObject>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QSpinBox>

MemoryControlWidget::MemoryControlWidget(QWidget* parent) :
    QWidget(parent), _memory(nullptr)
{
    setupUi(this);
}

void MemoryControlWidget::setMemory(Memory* memory)
{
    if(_memory != nullptr)
        disconnectMemoryFromThis();
    _memory = memory;
    if(_memory != nullptr)
        connectMemoryToThis();
}

void MemoryControlWidget::connectMemoryToThis()
{
    connect(loadImagePushButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    connect(_memory, SIGNAL(imageLoadingError(QString)),
            this, SLOT(imageLoadingError(QString)));
}

void MemoryControlWidget::disconnectMemoryFromThis()
{
    disconnect(loadImagePushButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    disconnect(_memory, SIGNAL(imageLoadingError(QString)),
               this, SLOT(imageLoadingError(QString)));
}


void MemoryControlWidget::loadImage()
{
    Q_CHECK_PTR(_memory);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if(dialog.exec())
    {
        QFile file(dialog.selectedFiles().first());
        QMetaObject::invokeMethod(_memory, "loadImage", Qt::QueuedConnection,
                                  Q_ARG(QString, file.fileName()));
    }
}

void MemoryControlWidget::imageLoadingError(const QString& message)
{
    QMessageBox::critical(this, tr("Błąd podczas ładowania obrazu"), message);
}

Register::Type MemoryControlWidget::lengthOfCodeView() const
{
    return viewSizeSpinBox->value();
}
