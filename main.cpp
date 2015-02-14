#include <QCoreApplication>
#include "DataTreatment.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    DataTreatment test("result_give_me_my _data.txt",
                       "Marcel Augusto", 3);
    test.readData();

    //return a.exec();
}
