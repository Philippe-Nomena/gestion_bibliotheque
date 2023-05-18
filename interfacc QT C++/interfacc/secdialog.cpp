#include "secdialog.h"
#include "ui_secdialog.h"
#include "QIcon"
#include "mainwindow.h"
#include "QMessageBox"



SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
      ui->pushButton_4->setIcon(QIcon(":/iconn/icon2/exe.ico"));
       ui->pushButton_5->setIcon(QIcon(":/iconn/icon2/downloads.ico"));
         ui->pushButton->setIcon(QIcon(":/iconn/icon2/search.ico"));
           ui->pushButton_2->setIcon(QIcon(":/new/icon/clipboard_128px.png"));

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_5_clicked()
{}

//fonction pour la boutton acceuille
void SecDialog::on_pushButton_4_clicked()
{
    this->close();
}

//consultation d'un ouvrage à partir de num lect
void SecDialog::on_pushButton_clicked()
{
    connOpen();
    QString numLect= ui->lineEdit->text();
    QSqlQuery rech;
    rech.prepare("select count(*) FROM pret p INNER JOIN lecteur l on l.num_lect = p.num_lectINNER JOIN livre g on g.num_livre = p.num_livre WHERE p.num_lect='"+numLect +"' ");
    rech.exec();

    int ligne(0);
    while (rech.next()) {
        ligne = rech.value(0).toInt();
    }

    model = new QStandardItemModel(ligne,4);
    int row(0);
    rech.exec("select g.designer,g.auteur,g.date_edit, p.datePret FROM pret p INNER JOIN lecteur l on l.num_lect = p.num_lect INNER JOIN livre g on g.num_livre = p.num_livre  WHERE p.num_lect='"+numLect +"' " );
       while (rech.next()) {
          for(int j=0;j<4;j++){
            QStandardItem *item = new QStandardItem(rech.value(j).toString());
            model->setItem(row,j,item);
          }
        row++;
       }

     model->setHeaderData(0,Qt::Horizontal,"designer");
      model->setHeaderData(1,Qt::Horizontal,"auteur");
        model->setHeaderData(2,Qt::Horizontal,"date Edit");
          model->setHeaderData(3,Qt::Horizontal,"date Pret");

          ui->tableView->setModel(model);
          ui->label_2->setText("Nombres des livres preté :" +QString::number(row) );


}

//situation du livre
void SecDialog::on_pushButton_2_clicked()
{
    connOpen();
    QSqlQuery req;
    int ligne(0);
    req.exec("select count(*) from livre");
    while (req.next()) {
        ligne = req.value(0).toInt();
    }

    model = new QStandardItemModel(ligne,5);
    int row(0);
    req.exec("select * from livre");
    while (req.next()) {
        for(int j=0;j<5;j++){
           QStandardItem *item = new QStandardItem(req.value(j).toString());
           model->setItem(row,j,item);
        }
     row++;
    }

    model->setHeaderData(0,Qt::Horizontal,"num livre");
      model->setHeaderData(1,Qt::Horizontal,"designer");
         model->setHeaderData(2,Qt::Horizontal,"auteur");
             model->setHeaderData(3,Qt::Horizontal,"date edition");
               model->setHeaderData(4,Qt::Horizontal,"disponible");
               ui->tableView->setModel(model);
}
