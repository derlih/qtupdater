#if defined(QT_GUI_LIB)
    #include <QApplication>
#else
    #include <QCoreApplication>
#endif

#include <memory>

int main(int argc, char **argv)
{
    std::auto_ptr<QCoreApplication> app(
            #if defined(QT_GUI_LIB)
                new QApplication(argc, argv)
            #else
                new QCoreApplication(argc, argv)
            #endif
                );




    return app->exec();
}
