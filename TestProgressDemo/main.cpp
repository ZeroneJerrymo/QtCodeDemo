﻿#include <QCoreApplication>
#include <QProcess>
#include <QTextCodec>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString program = "C:/Windows/System32/cmd.exe";
    QStringList arguments;
    arguments << "/c" << "dir" << "C:\\";
    QProcess *cmdProcess = new QProcess;
    QObject::connect(cmdProcess, &QProcess::readyRead, [=] () {
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QString dir = codec->toUnicode(cmdProcess->readAll());
        qDebug() << dir;
    });
    cmdProcess->start(program, arguments);

    return a.exec();
}
