﻿#include "mainwindow.h"
#include "networker.h"
#include "ui_mainwindow.h"
#include "weatherinfo.h"

#include <QComboBox>
#include <QJsonDocument>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
class MainWindow::Private
{
public:
    Private()
    {
        netWorker = NetWorker::instance();
    }

    void fetchWeather(const QString &cityName) const
    {
        netWorker->get(QString("http://api.openweathermap.org/data/2.5/weather?q=%1&mode=json&units=metric&lang=zh_cn").arg(cityName));
    }

    NetWorker *netWorker;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),d(new MainWindow::Private),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QComboBox *cityList = new QComboBox(this);
        cityList->addItem(tr("Beijing"), QLatin1String("Beijing,cn"));
        cityList->addItem(tr("Shanghai"), QLatin1String("Shanghai,cn"));
        cityList->addItem(tr("Nanjing"), QLatin1String("Nanjing,cn"));
        QLabel *cityLabel = new QLabel(tr("City: "), this);
        QPushButton *refreshButton = new QPushButton(tr("Refresh"), this);
        QHBoxLayout *cityListLayout = new QHBoxLayout;
        cityListLayout->setDirection(QBoxLayout::LeftToRight);
        cityListLayout->addWidget(cityLabel);
        cityListLayout->addWidget(cityList);
        cityListLayout->addWidget(refreshButton);

        QVBoxLayout *weatherLayout = new QVBoxLayout;
        weatherLayout->setDirection(QBoxLayout::TopToBottom);
        QLabel *cityNameLabel = new QLabel(this);
        weatherLayout->addWidget(cityNameLabel);
        QLabel *dateTimeLabel = new QLabel(this);
        weatherLayout->addWidget(dateTimeLabel);

        QWidget *mainWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
        mainLayout->addLayout(cityListLayout);
        mainLayout->addLayout(weatherLayout);
        setCentralWidget(mainWidget);
        resize(320, 120);
        setWindowTitle(tr("Weather"));

        connect(d->netWorker, &NetWorker::finished, [=] (QNetworkReply *reply) {
            qDebug() << reply;
            QJsonParseError error;
            QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
            if (error.error == QJsonParseError::NoError) {
                if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
                    QVariantMap data = jsonDocument.toVariant().toMap();
                    WeatherInfo weather;
                    weather.setCityName(data[QLatin1String("name")].toString());
                    QDateTime dateTime;
                    dateTime.setTime_t(data[QLatin1String("dt")].toLongLong());
                    weather.setDateTime(dateTime);
                    QVariantMap main = data[QLatin1String("main")].toMap();
                    weather.setTemperature(main[QLatin1String("temp")].toFloat());
                    weather.setPressure(main[QLatin1String("pressure")].toFloat());
                    weather.setHumidity(main[QLatin1String("humidity")].toFloat());
                    QVariantList detailList = data[QLatin1String("weather")].toList();
                    QList<WeatherDetail *> details;
                    foreach (QVariant w, detailList) {
                        QVariantMap wm = w.toMap();
                        WeatherDetail *detail = new WeatherDetail;
                        detail->setDesc(wm[QLatin1String("description")].toString());
                        detail->setIcon(wm[QLatin1String("icon")].toString());
                        details.append(detail);
                    }
                    weather.setDetails(details);

                    cityNameLabel->setText(weather.cityName());
                    dateTimeLabel->setText(weather.dateTime().toString(Qt::DefaultLocaleLongDate));
                }
            } else {
                QMessageBox::critical(this, tr("Error"), error.errorString());
            }
            reply->deleteLater();
        });
        connect(refreshButton, &QPushButton::clicked, [=] () {
            d->fetchWeather(cityList->itemData(cityList->currentIndex()).toString());
        });
}

MainWindow::~MainWindow()
{
    delete d;
        d = 0;
    delete ui;
}

