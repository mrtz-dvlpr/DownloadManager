#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include<QFileDialog>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_2->setText(QFileDialog::getExistingDirectory());
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    manager=new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl(ui->lineEdit->text()));

    reply=manager->get(request);

    QString str=ui->lineEdit->text();
    QStringList list=str.split('/');

    file=new QFile(ui->lineEdit_2->text()+"/"+list[list.size()-1]);
    if(!file->open(QIODevice::WriteOnly))
    {
        return;
    }

    connect(reply, &QNetworkReply::readyRead,this,[   this]{
           QByteArray data = reply->readAll();
           file->write(data);
           connect (reply,&QNetworkReply::downloadProgress, this, [this] (qint64 received, qint64 total)
            {
                int percent = received * 100 / total;
                ui->progressBar->setValue (percent);
            });
    });


    connect(reply, &QNetworkReply::finished,this,[this]{
        delete file;
        delete manager;
        ui->pushButton->setEnabled(true);

    });
}

