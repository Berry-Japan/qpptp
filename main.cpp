#include <qapplication.h>
#include <qlocale.h>
#include "qpptp.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name());
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    if (!myappTranslator.load("qpptp_" + QLocale::system().name(), "/opt/berry")) {
        myappTranslator.load("qpptp_" + QLocale::system().name(), ".");
    }
    a.installTranslator(&myappTranslator);

    Form1 w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
