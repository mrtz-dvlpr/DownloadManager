#pragma once

#include <QMainWindow>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QFile *file;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;

};
