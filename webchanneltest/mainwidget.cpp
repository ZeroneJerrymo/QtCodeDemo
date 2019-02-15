#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "previewpage.h"
#include "document.h"

#include <QFile>
#include <QWebChannel>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    PreviewPage *page = new PreviewPage(this);
    ui->preview->setPage(page);
    m_content.setUi(ui);

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);

    ui->preview->setUrl(QUrl("qrc:/index.html"));

    ui->editor->setPlainText("hello...\n");
}

MainWidget::~MainWidget()
{
    delete ui;
}

bool MainWidget::isModified() const
{
    return ui->editor->document()->isModified();
}

void MainWidget::on_pushButton_clicked()
{

    m_content.setSendTextText(ui->lineEdit->text());

}
