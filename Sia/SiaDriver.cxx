#include <QApplication>
#include "Sia.h"
 
int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
 
  Sia sia;
  sia.show();
 
  return app.exec();
}
