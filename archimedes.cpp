#include "archimedes.h"
#include "ui_archimedes.h"

double Archimedes::DBcalVal = 0.0;

Archimedes::Archimedes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Archimedes)
{
    ui->setupUi(this);
    openDB();
     QFile mFile;
     mFile.setFileName("latestAnswer.db");

     if(!mFile.exists())
     {
         createDB();
     }

     retrieveFromDB();



    ui->Display->setText(QString::number(DBcalVal));

    QPushButton* numButtons[10];

    for (int i = 0; i < 10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Archimedes::findChild<QPushButton*> (butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemAddPressed()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemGetPressed()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemClearPressed()));

}
//---------------------------------------------------
//---------------------------------------------------
Archimedes::~Archimedes()
{
    sqlite3_close(db);
    delete ui;
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::NumPressed()
{
    //after database sets test to display pressing key should clear display
    if(!first_key_press){
         ui->Display->setText("");
         first_key_press = true;
    }

    if(equalTrigger)
    {
        ui->Display->setText("");
        calVal = 0.0;
    }
    QPushButton* button = /*(QPushButton*)sender();*/qobject_cast<QPushButton*>(sender());
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0)||(displayVal.toDouble() == 0.0))
    {
         ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
        equalTrigger = false;
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::MathButtonPressed()
{
    if(!equalTrigger)
    {
        EqualButtonPressed();
    }


    QString statusMessage = "Current Operator";
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    equalTrigger = false;

    QString displayVal = ui->Display->text();
    calVal = displayVal.toDouble();

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString butVal = button->text();

    if(QString::compare(butVal,"/",Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if (QString::compare(butVal,"+",Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }
    ui->statusBar->showMessage(statusMessage + "  " + butVal);
    ui->Display->setText("");

}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::EqualButtonPressed()
{
    equalTrigger = true;
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger||subTrigger||divTrigger||mulTrigger)
    {
        if(addTrigger)
        {
            solution = calVal + dblDisplayVal;
        }
        else if(subTrigger)
        {
            solution = calVal - dblDisplayVal;
        }
        else if (mulTrigger)
        {
            solution = calVal * dblDisplayVal;
        }
        else
        {
            solution = calVal / dblDisplayVal;
        }
        ui->statusBar->clearMessage();
        ui->Display->setText(QString::number(solution));
        insertIntoDB(solution);
    }
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]");
    if(reg.exactMatch((displayVal)))
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1*dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}
//---------------------------------------------------
//---------------------------------------------------
 void Archimedes::ClearPressed()
 {
     ui->Display->setText("0");
     calVal = 0.0;
 }
 //---------------------------------------------------
 //---------------------------------------------------
void Archimedes::on_actionclose_triggered()
{
    close();
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::MemAddPressed()
{
    memory = ui->Display->text().toDouble();
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::MemGetPressed()
{
    ui->Display->setText(QString::number(memory));
}
//---------------------------------------------------
//---------------------------------------------------

void Archimedes::MemClearPressed()
{
    memory = 0.0;
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::openDB()
{
    rc = sqlite3_open("latestAnswer.db", &db);

    if (rc) {
            qDebug() << "can't open database: " << sqlite3_errmsg(db)<<endl;
            return;
    }
    else {
            qDebug() << "Opened database successfully" << endl;
    }
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::createDB(){

  sql =  "CREATE TABLE LATEST(" \
         "ID INT PRIMARY KEY NOT NULL," \
         "ANSWER REAL NOT NULL );";

  rc = sqlite3_exec(db, sql, callbacks, nullptr, &zErrMsg);
   if (rc != SQLITE_OK) {
     qDebug() << "SQL Error: " << zErrMsg<<endl;
   }
   else {
     qDebug() << "DB created successfully" << endl;
   }


  std::string val_to_store_STDstring = "INSERT INTO LATEST(ID, ANSWER) VALUES (1, 0)";

  sql = val_to_store_STDstring.c_str();
  rc = sqlite3_exec(db, sql, callbacks, (void*)data, &zErrMsg);

   if (rc != SQLITE_OK) {
     qDebug() << "SQL Error: " << zErrMsg<<endl;
   }
   else {
     qDebug() << "inserted successfully" << endl;
   }
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::insertIntoDB(double& soln){

  auto val_to_store = QString::number(soln);

  std::string val_to_store_STDstring = "UPDATE LATEST set ANSWER = " + val_to_store.toStdString() + " where ID = 1;";
  sql = val_to_store_STDstring.c_str();

  rc = sqlite3_exec(db, sql, callbacks, nullptr, &zErrMsg);

  if (rc != SQLITE_OK) {
       qDebug() << "SQL Error: " << zErrMsg<<endl;
                  }
  else {
       qDebug() << "inserted successfully" << endl;
   }
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::retrieveFromDB(){
    sql = "SELECT * from LATEST";

    rc = sqlite3_exec(db, sql, callbacks, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
     qDebug() << "SQL Error: " << zErrMsg<<endl;
     }
    else {
     qDebug() << "Operation done successfully" << endl;
     }

}
//---------------------------------------------------
//---------------------------------------------------












