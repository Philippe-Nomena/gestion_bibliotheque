#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "QSqlQuery"
#include <QStandardItemModel>
#include <QDebug>


namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();
    void connOpen(){
        QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE");
        conn.setDatabaseName("C:/Users/TSOU/Desktop/bd.sqlite");
        if(conn.open()){
            qDebug()<<"Base de donnée connecté";
        }
    }


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::SecDialog *ui;
     QStandardItemModel *model = new QStandardItemModel;
};

#endif // SECDIALOG_H
