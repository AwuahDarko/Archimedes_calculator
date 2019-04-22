#include "archimedes.h"
#include "ui_archimedes.h"



Archimedes::Archimedes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Archimedes)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calVal));

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
    delete ui;
}
//---------------------------------------------------
//---------------------------------------------------
void Archimedes::NumPressed()
{
    if(equalTrigger)
    {
        ui->Display->setText("");
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
    ui->statusBar->showMessage(statusMessage + " " + " " + butVal);
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
