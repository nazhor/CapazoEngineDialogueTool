#include "MainWindow.h"

#include <QApplication>
#include <QLockFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);    
    QApplication a(argc, argv);

    QString tmpDir = QDir::tempPath();
    QString lockId = "capazo_engine_dt_lock_file";
    QLockFile lockFile(tmpDir + "/" + lockId);
    if (!lockFile.tryLock(100))
    {
        return 1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
