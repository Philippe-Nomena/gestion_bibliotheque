#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QIcon"
#include "QSqlError"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ajout des Icons pour les differentes boutons
      ui->erg1->setIcon(QIcon(":/new/icon/pop-shop.ico"));
      ui->pushButton_8->setIcon(QIcon(":/new/icon/pop-shop.ico"));
      ui->pushButton_9->setIcon(QIcon(":/new/icon/Delete.ico"));
      ui->pushButton_6->setIcon(QIcon(":/new/icon/Delete.ico"));
      ui->listPret->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->pushButton_5->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->pushButton_2->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->pushButton_7->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->pushButton_pre->setIcon(QIcon(":/new/icon/pop-shop.ico"));
      ui->pushButton_3->setIcon(QIcon(":/new/icon/Delete.ico"));
      ui->pushButton->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->pushButton_4->setIcon(QIcon(":/new/icon/clipboard_128px.png"));
      ui->actionfichier_lecteur->setToolTip("aller au fichier Lecteur");
      ui->actionfichier_livre->setToolTip("aller au fichier Livre");
      ui->actionfichier_pret->setToolTip("aller au fichier Pret");



    }

MainWindow::~MainWindow()
{
    delete ui;
}


//fonction pour les Icons au dessus de la fenêtre
void MainWindow::on_actionfichier_livre_triggered()
{
      ui->stackedWidget->setCurrentIndex(1);
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
                 ui->tableView_2->setModel(model);


}

void MainWindow::on_actionfichier_pret_triggered()
{

     ui->stackedWidget->setCurrentIndex(2);
     QString num=ui->lineEdit->text();
     ui->lineEdit_7->setText(num);
     connOpen();
     QSqlQuery req;
     int ligne(0);
     req.exec("select count(*) from pret");
     while (req.next()) {
         ligne = req.value(0).toInt();
     }
     model = new QStandardItemModel(ligne,5);
    int row(0);
     req.exec("select * from pret");
     while (req.next()) {
         for(int j=0;j<5;j++){
        QStandardItem *item = new QStandardItem(req.value(j).toString());
        model->setItem(row,j,item);
         }
        row++;
     }
     model->setHeaderData(0,Qt::Horizontal,"num pret");
       model->setHeaderData(1,Qt::Horizontal,"num lecteur");
          model->setHeaderData(2,Qt::Horizontal,"num livre");
              model->setHeaderData(3,Qt::Horizontal,"date pret");
                model->setHeaderData(4,Qt::Horizontal,"date retour");
        ui->tableView_3->setModel(model);

}

void MainWindow::on_actionfichier_lecteur_triggered()
{
     ui->stackedWidget->setCurrentIndex(0);
     connOpen();
     QSqlQuery donne;
     int ligne(0);

     donne.exec("select count(*) from lecteur");
     while (donne.next()) {
         ligne = donne.value(0).toInt();
      }

     model = new QStandardItemModel(ligne,2);
     int row(0);
     donne.exec("select * from lecteur");

     while (donne.next()) {
        for(int j=0;j<2;j++){
            QStandardItem *item = new QStandardItem(donne.value(j).toString());
            model->setItem(row,j,item);
        }
        row++;
     }

     model->setHeaderData(0,Qt::Horizontal,"num_lecteur");
       model->setHeaderData(1,Qt::Horizontal,"nom");
       ui->tableView->setModel(model);
}

void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox::information(this,"Information","Bienvenue dans notre petit application...Gestion des livres");
}


//definition des fonction des boutons dans la fichier lecteur


void MainWindow::on_erg1_clicked()
{
    QString nom=ui->lineEdit_2->text();
    QString num=ui->lineEdit->text();

    QSqlQuery rec;
    rec.prepare("select * from lecteur where nom= '"+nom +"'");
    rec.exec();
    int i(0);
    while (rec.next()) {
        i++;
    }
    if(i==0){
         ajout();
    }
    else {
        QMessageBox::information(this,"information","Lecteur déja saisie ,voir le tableau pour trouver le numero <br>"
                                                    "et passe au pret");
       int ligne(0);
        while (rec.next()) {
            ligne = rec.value(0).toInt();
         }

        model = new QStandardItemModel(ligne,2);
        int row(0);
        rec.exec(" select * from lecteur where nom= '"+nom +"' ");

        while (rec.next()) {
           for(int j=0;j<2;j++){
               QStandardItem *item = new QStandardItem(rec.value(j).toString());
               model->setItem(row,j,item);
           }
           row++;
        }

        model->setHeaderData(0,Qt::Horizontal,"num_lecteur");
          model->setHeaderData(1,Qt::Horizontal,"nom");
          ui->tableView->setModel(model);
    }

  }


//pour ajouter des lecteurs
void MainWindow::ajout()
{

    model->setHeaderData(0,Qt::Horizontal,"num_lecteur");
      model->setHeaderData(1,Qt::Horizontal,"nom");
      ui->tableView->setModel(model);

    QString nom=ui->lineEdit_2->text();
    QString num=ui->lineEdit->text();

      connOpen();
      QSqlQuery donne;
      donne.prepare("insert into lecteur(num_lect,nom) values (:numL,:nm)");
      donne.bindValue(":numL",num);
      donne.bindValue(":nm",nom);


      if(donne.exec()){
          ui->lineEdit_2->setText("");
          ui->lineEdit->setText("");
          QMessageBox::information(this,"","enregistrement reussi!!");
           QMessageBox::information(this,"","passer au pret");
      }
      else {
       QMessageBox::information(this,"","Ce numero est déjà énregistré ");
      }

          QSqlQueryModel *modal=new QSqlQueryModel();
          QSqlQuery *qury= new QSqlQuery(mydb);

          qury->prepare("select *from lecteur");

          qury->exec();

          modal->setQuery(*qury);
          ui->tableView->setModel(modal);

 }

//supression des lecteur

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"information","êtes-vous sur de suprimer ",
                        QMessageBox::Cancel | QMessageBox::Ok     );
     QString nom=ui->lineEdit_2->text();
     QString num=ui->lineEdit->text();
   if(QMessageBox::Ok)
   {
       connOpen();
       QSqlQuery qry;
       qry.prepare("delete from lecteur where num_lect='"+num+"'");

       if(qry.exec()){
           QMessageBox::information(this,"Donnees","Suppression reussi avec succees");
           ui->lineEdit_2->setText("");
           ui->lineEdit->setText("");
       }
       else{
           QMessageBox::information(this,"Error",qry.lastError().text());
       }
    }
   QSqlQueryModel *modal=new QSqlQueryModel();
   QSqlQuery *qury= new QSqlQuery(mydb);

   qury->prepare("select *from lecteur");

   qury->exec();

   modal->setQuery(*qury);
   ui->tableView->setModel(modal);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString val1= ui->tableView->model()->data(index).toString();


    connOpen();
    QSqlQuery qry1;
    qry1.prepare("select *from lecteur where num_lect='"+val1+"' or nom='"+val1+"'");
    if(qry1.exec()){
        while(qry1.next()){
            ui->lineEdit->setText(qry1.value(0).toString());
            ui->lineEdit_2->setText(qry1.value(1).toString());
        }
        connClose();
    }
}

//update lecteur
void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"information","êtes-vous sur de modifier ",
                        QMessageBox::Cancel | QMessageBox::Ok     );
     QString nom=ui->lineEdit_2->text();
     QString num=ui->lineEdit->text();
   if(QMessageBox::Ok)
   {
       connOpen();
       QSqlQuery qry;
       qry.prepare("update lecteur set nom='"+nom+"' where num_lect='"+num+"'");

       if(qry.exec()){
           QMessageBox::information(this,"Donnees","Modification reussi avec succees");
           ui->lineEdit_2->setText("");
           ui->lineEdit->setText("");
       }
       else{
           QMessageBox::information(this,"Error",qry.lastError().text());
       }
    }
   QSqlQueryModel *modal=new QSqlQueryModel();
   QSqlQuery *qury= new QSqlQuery(mydb);

   qury->prepare("select *from lecteur");

   qury->exec();

   modal->setQuery(*qury);
   ui->tableView->setModel(modal);
}



//affichage de liste de lecteur
void MainWindow::on_pushButton_4_clicked()
{
    connOpen();
    QSqlQuery donne;
    int ligne(0);

    donne.exec("select count(*) from lecteur");
    while (donne.next()) {
        ligne = donne.value(0).toInt();
     }

    model = new QStandardItemModel(ligne,2);
    int row(0);
    donne.exec("select * from lecteur");

    while (donne.next()) {
       for(int j=0;j<2;j++){
           QStandardItem *item = new QStandardItem(donne.value(j).toString());
           model->setItem(row,j,item);
       }
       row++;
    }

    model->setHeaderData(0,Qt::Horizontal,"num_lecteur");
      model->setHeaderData(1,Qt::Horizontal,"nom");
      ui->tableView->setModel(model);
}


//pour la fichier livre

//ajout livre
void MainWindow::on_pushButton_8_clicked()
{
    QString numlivre,auteur,design,date,dispo;

    numlivre=ui->lineEdit_numLivre->text();
    auteur=ui->lineEdit_auteur->text();
    design=ui->lineEdit_design->text();
    date=ui->lineEdit_date->text();
   // dispo=ui->lineEdit_num_6->text();

    connOpen();
    QSqlQuery qryh;

    qryh.prepare("insert into livre(num_livre,designer,auteur,date_edit,disponible) VALUES ('"+numlivre+"','"+design+"','"+auteur+"','"+date+"','oui')");

    if(qryh.exec()){
        QMessageBox::information(this,"Donnees","Ajouter avec succees");
    }
    else{
        QMessageBox::critical(this,"Error",qryh.lastError().text());
    }

    QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery *qury= new QSqlQuery(mydb);

    qury->prepare("select *from livre");

    qury->exec();

    modal->setQuery(*qury);
    ui->tableView_2->setModel(modal);
    //ui->listView->setModel(modal);

    qDebug()<<(modal->rowCount());
    ui->lineEdit_numLivre->setText("");
    ui->lineEdit_auteur->setText("");
    ui->lineEdit_design->setText("");
}

//tableau livre
void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QString val1= ui->tableView_2->model()->data(index).toString();


    connOpen();
    QSqlQuery qry1;
    qry1.prepare("select *from livre where num_livre='"+val1+"' or designer='"+val1+"' or auteur='"+val1+"'or date_edit='"+val1+"'");
    if(qry1.exec()){
        while(qry1.next()){
            ui->lineEdit_numLivre->setText(qry1.value(0).toString());
            ui->lineEdit_design->setText(qry1.value(1).toString());
            ui->lineEdit_auteur->setText(qry1.value(2).toString());
            ui->lineEdit_date->setText(qry1.value(3).toString());

        }
        connClose();
    }
}

//liste livre
void MainWindow::on_pushButton_clicked()
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
               ui->tableView_2->setModel(model);

}

//delete livre
void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::information(this,"information","êtes-vous sur de suprimer ",
                        QMessageBox::Cancel | QMessageBox::Ok     );
    QString numlivre,auteur,design,date,dispo;

    numlivre=ui->lineEdit_numLivre->text();
    auteur=ui->lineEdit_auteur->text();
    design=ui->lineEdit_design->text();
    date=ui->lineEdit_date->text();

   if(QMessageBox::Ok)
   {
       connOpen();
       QSqlQuery qry;
       qry.prepare("delete from livre where num_livre='"+numlivre+"'");

       if(qry.exec()){
           QMessageBox::information(this,"Donnees","Suppression reussi avec succees");
            ui->lineEdit_numLivre->setText("");
            ui->lineEdit_auteur->setText("");
            ui->lineEdit_design->setText("");
            ui->lineEdit_date->setText("");
       }
       else{
           QMessageBox::information(this,"Error",qry.lastError().text());
       }
    }
   QSqlQueryModel *modal=new QSqlQueryModel();
   QSqlQuery *qury= new QSqlQuery(mydb);

   qury->prepare("select *from livre");
   qury->exec();
   modal->setQuery(*qury);
   ui->tableView_2->setModel(modal);
}

//update livre
void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox::information(this,"information","êtes-vous sur de modifier ",
                        QMessageBox::Cancel | QMessageBox::Ok     );

   if(QMessageBox::Ok)
   {
       QString numlivre,auteur,design,date,dispo;

       numlivre=ui->lineEdit_numLivre->text();
       auteur=ui->lineEdit_auteur->text();
       design=ui->lineEdit_design->text();
       date=ui->lineEdit_date->text();

       connOpen();
       QSqlQuery qry;
       qry.prepare("update livre set designer='"+design+"',auteur='"+auteur+"',date_edit='"+date+"' where num_livre='"+numlivre+"'");

       if(qry.exec()){
           QMessageBox::information(this,"Donnees","Modification reussi avec succees");
         ui->lineEdit_numLivre->setText("");
          ui->lineEdit_auteur->setText("");
          ui->lineEdit_design->setText("");
          ui->lineEdit_date->setText("");
       }
       else{
           QMessageBox::information(this,"Error",qry.lastError().text());
       }
    }
   QSqlQueryModel *modal=new QSqlQueryModel();
   QSqlQuery *qury= new QSqlQuery(mydb);

   qury->prepare("select *from livre");
   qury->exec();
   modal->setQuery(*qury);
   ui->tableView_2->setModel(modal);
}




//pour la fichier pret

//affichage du pret
void MainWindow::on_listPret_clicked()
{
    connOpen();
    QSqlQuery req;
    int ligne(0);
    req.exec("select count(*) from pret");
    while (req.next()) {
        ligne = req.value(0).toInt();
    }
    model = new QStandardItemModel(ligne,5);
   int row(0);
    req.exec("select * from pret");
    while (req.next()) {
        for(int j=0;j<5;j++){
       QStandardItem *item = new QStandardItem(req.value(j).toString());
       model->setItem(row,j,item);
        }
       row++;
    }
    model->setHeaderData(0,Qt::Horizontal,"num pret");
      model->setHeaderData(1,Qt::Horizontal,"num lecteur");
         model->setHeaderData(2,Qt::Horizontal,"num livre");
             model->setHeaderData(3,Qt::Horizontal,"date pret");
               model->setHeaderData(4,Qt::Horizontal,"date retour");
       ui->tableView_3->setModel(model);
}


//suprimer pret
void MainWindow::on_pushButton_9_clicked()
{

     QString numLivre=ui->lineEdit_8->text();
     QString npret=ui->lineEdit_numpret->text();

     QMessageBox::information(this,"information","etes-vous sur de suprimer ",
                         QMessageBox::Cancel | QMessageBox::Ok     );

     if(QMessageBox::Ok){
         connOpen();
         QSqlQuery data;
           data.prepare("delete from pret where nPret = '"+npret+"' or num_lect = '"+numLivre+"' ");
           if( data.exec())
           {
                 QMessageBox::information(this,"","supression terminer");
                 ui->lineEdit_numpret->setText("");
                 ui->lineEdit_7->setText("");
                 ui->lineEdit_8->setText("");
                 ui->lineEdit_pret->setText("");
                 ui->lineEdit_retour->setText("");
                 connOpen();
                 QSqlQuery dis;
                            dis.prepare("update livre set disponible = 'oui' where num_livre= '"+numLivre +"' ");

                            if(dis.exec()){
                                QMessageBox::information(this,"information","Il y a un livre disponible");
                            }
                            else {
                                 QMessageBox::information(this,"information","erreur B!!");
                            }
           }
           else{
                 QMessageBox::information(this,"","erreur");
           }
     }
     QSqlQueryModel *modal=new QSqlQueryModel();
     QSqlQuery *qury= new QSqlQuery(mydb);

     qury->prepare("select *from pret");
     qury->exec();
     modal->setQuery(*qury);
     ui->tableView_3->setModel(modal);
}


//ajout pret
void MainWindow::on_pushButton_pre_clicked()
{

        QString numLect=ui->lineEdit_7->text();
        QString numLivre=ui->lineEdit_8->text();
        QString dateP=ui->lineEdit_pret->text();
        QString dateR=ui->lineEdit_retour->text();

        connOpen();
        QSqlQuery rec,rec1;
        rec.prepare("select * from pret where num_lect= '"+numLect +"'");
        rec.exec();
        rec1.prepare("select * from pret where num_livre= '"+numLivre +"'");
        rec1.exec();
        int i(0);int j(0);
        while (rec.next()) {
            i++;
        }
        while (rec1.next()) {
            j++;
        }

      if(j<=0)

      {
          if(i<3) {

              QSqlQuery data;
              data.prepare("insert into pret(num_lect,num_livre,datePret,dateRetour) values('"+numLect +"','"+numLivre +"',:dateP,:dateR)");
              data.bindValue(":dateP",dateP);
              data.bindValue(":dateR",dateR);
              if( data.exec()){
                  QMessageBox::information(this,"information","enregitrement reussi!!");
                  ui->lineEdit_numpret->setText("");
                  ui->lineEdit_7->setText("");
                  ui->lineEdit_8->setText("");
                  ui->lineEdit_pret->setText("");
                  ui->lineEdit_retour->setText("");
               }
              else {
                   QMessageBox::information(this,"information","erreur!!");
              }
              QSqlQuery dis;
                        dis.prepare("update livre set disponible = 'non' where num_livre= '"+numLivre +"' ");

                         if(dis.exec()){
                             QMessageBox::information(this,"information","modification terminer!!");
                         }
                         else {
                              QMessageBox::information(this,"information","erreur B!!");

                  }
          }
          else {
              QMessageBox::warning(this,"iformation","Imposible de Preté... votre  pret est déja 3 ");

              int ligne(0);

              while (rec.next()) {
                  ligne = rec.value(0).toInt();
              }
              model = new QStandardItemModel(ligne,5);
             int row(0);
              rec.exec("select * from pret where num_lect= '"+numLect +"'");
              while (rec.next()) {
                  for(int j=0;j<5;j++){
                 QStandardItem *item = new QStandardItem(rec.value(j).toString());
                 model->setItem(row,j,item);
                  }
              }
              row++;
              model->setHeaderData(0,Qt::Horizontal,"num pret");
                model->setHeaderData(1,Qt::Horizontal,"num lecteur");
                   model->setHeaderData(2,Qt::Horizontal,"num livre");
                       model->setHeaderData(3,Qt::Horizontal,"date pret");
                         model->setHeaderData(4,Qt::Horizontal,"date retour");
                 ui->tableView_3->setModel(model);
          }
      }
      else {
             QMessageBox::warning(this,"ifomation","Imposible de Preté... livre non disponible <br>"
                                                   " voir le tableau  ");
             int ligne(0);

             while (rec1.next()) {
                 ligne = rec1.value(0).toInt();
             }
             model = new QStandardItemModel(ligne,5);
            int row(0);
             rec1.exec("select * from pret where num_livre= '"+numLivre +"'");
             while (rec1.next()) {
                 for(int j=0;j<5;j++){
                QStandardItem *item = new QStandardItem(rec1.value(j).toString());
                model->setItem(row,j,item);
                 }
                row++;
             }
             model->setHeaderData(0,Qt::Horizontal,"num pret");
               model->setHeaderData(1,Qt::Horizontal,"num lecteur");
                  model->setHeaderData(2,Qt::Horizontal,"num livre");
                      model->setHeaderData(3,Qt::Horizontal,"date pret");
                        model->setHeaderData(4,Qt::Horizontal,"date retour");
                        ui->tableView_3->setModel(model);
      }
      QSqlQueryModel *modal=new QSqlQueryModel();
      QSqlQuery *qury= new QSqlQuery(mydb);

      qury->prepare("select *from pret");
      qury->exec();
      modal->setQuery(*qury);
      ui->tableView_3->setModel(modal);

}

//update pret
void MainWindow::on_pushButton_5_clicked()
{

    QMessageBox::information(this,"information","êtes-vous sur de modifier ",
                        QMessageBox::Cancel | QMessageBox::Ok     );

           QString numLect=ui->lineEdit_7->text();
           QString numLivre=ui->lineEdit_8->text();
           QString dateP=ui->lineEdit_pret->text();
           QString dateR=ui->lineEdit_retour->text();
           QString npret=ui->lineEdit_numpret->text();
   if(QMessageBox::Ok)
   {
       connOpen();
       QSqlQuery qry;
       qry.prepare("update pret set num_lect='"+numLect+"',num_livre='"+numLivre+"',datePret='"+dateP+"', dateRetour='"+dateR+"' where nPret='"+npret+"'");

       if(qry.exec()){
           QMessageBox::information(this,"Donnees","Modification reussi avec succees");
           ui->lineEdit_7->setText("");
           ui->lineEdit_8->setText("");
           ui->lineEdit_retour->setText("");
           ui->lineEdit_pret->setText("");
       }
       else{
           QMessageBox::information(this,"Error",qry.lastError().text());
       }
    }
   QSqlQueryModel *modal=new QSqlQueryModel();
   QSqlQuery *qury= new QSqlQuery(mydb);

   qury->prepare("select *from pret");

   qury->exec();

   modal->setQuery(*qury);
   ui->tableView_3->setModel(modal);
}


//Tableau de pret
void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    QString val1= ui->tableView_3->model()->data(index).toString();


    connOpen();
    QSqlQuery qry1;
    qry1.prepare("select *from pret where nPret='"+val1+"' or num_lect='"+val1+"' or num_livre='"+val1+"' or dateRetour='"+val1+"'or datePret='"+val1+"'");
    if(qry1.exec()){
        while(qry1.next()){
            ui->lineEdit_numpret->setText(qry1.value(0).toString());
            ui->lineEdit_7->setText(qry1.value(1).toString());
            ui->lineEdit_8->setText(qry1.value(2).toString());
            ui->lineEdit_pret->setText(qry1.value(3).toString());
            ui->lineEdit_retour->setText(qry1.value(4).toString());

        }
        connClose();
    }
}



//affichage de la consultation d'un ouvrage
void MainWindow::on_actionconsultation_d_un_ouvrage_2_triggered()
{
    secdialog =new SecDialog;
    secdialog->show();
}







