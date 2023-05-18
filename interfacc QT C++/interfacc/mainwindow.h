#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QStandardItemModel>
#include "secdialog.h"
#include "QDebug"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase mydb;
    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    void connOpen(){
        QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE");
        conn.setDatabaseName("C:/Users/TSOU/Desktop/bd.sqlite");
        if(conn.open()){
            qDebug()<<"Base de donnée connecté";
        }
    }


private slots:


    void on_erg1_clicked();

    void on_actionfichier_livre_triggered();

    void on_actionfichier_pret_triggered();

    void on_actionfichier_lecteur_triggered();

    void on_actionA_propos_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void ajout();


    void on_pushButton_clicked();

    //void on_erg1_2_clicked();

    void on_listPret_clicked();

    void on_pushButton_9_clicked();
    
    void on_pushButton_pre_clicked();
    
    void on_actionconsultation_d_un_ouvrage_2_triggered();

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase conn;
    QStandardItemModel *model = new QStandardItemModel;
    SecDialog *secdialog;
};

#endif // MAINWINDOW_H
