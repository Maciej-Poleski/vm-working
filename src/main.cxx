#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

#include "MachineWidget.hxx"
#include "Machine.hxx"

int main(int argc,char**argv)
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MachineWidget *widget=new MachineWidget;
    Machine *machine=new Machine;
    widget->setMachine(machine);
    widget->show();

    app.exec();
}
