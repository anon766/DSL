#include "dictionary.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dictionary w;
    QFile fin("L4_P1_input.csv");
    if(!fin.open(QIODevice::ReadOnly | QIODevice::Text))
        return -7;
    QString input,word,definition;
    while(!fin.atEnd())
    {
        input=fin.readLine();
        QStringList fields=input.split(";");
        word=fields.at(0);
        definition=fields.at(1);
        w.insert(word, definition);
    }
    fin.close();

    w.show();

    return a.exec();
}
