#ifndef CPROFESSIONALWORDDBWGT_H
#define CPROFESSIONALWORDDBWGT_H
#include "CProfessionalWordDbWgt.h"
#include <QWidget>
#include <QTextEdit>
#include <QDialog>
#pragma execution_character_set("utf-8")

class CProfessionalWordDbWgt : public QDialog
{
    Q_OBJECT

public:
    CProfessionalWordDbWgt(QWidget *parent = Q_NULLPTR);
    ~CProfessionalWordDbWgt();
    void setSpeedWord(QString speechWord);
protected:
    void initUI();
    void addWordDb(QMap<QString, QString> wordDbmap);
    void initLayout();
    void tryUpdataStyle(QList<QString> speechWordList);
private:
    QTextEdit* te_wordDb;
    QMap<QString, QString> m_wordDbMap;
};

#endif // CPROFESSIONALWORDDBWGT_H
