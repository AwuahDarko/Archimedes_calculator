#ifndef ARCHIMEDES_H
#define ARCHIMEDES_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <QFile>
#include <thread>
#include "thread_guard.h"
#include "database.h"
#include <memory>
#include <future>


namespace Ui {
class Archimedes;

}

class Archimedes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Archimedes(QWidget *parent = nullptr);
    ~Archimedes();
    void setScreen();


private slots:
     void NumPressed();
     void MathButtonPressed();
     void EqualButtonPressed();
     void ChangeNumberSign();
     void ClearPressed();
     void on_actionclose_triggered();
     void MemAddPressed();
     void MemGetPressed();
     void MemClearPressed();
     void PointPressed();

private:
    Ui::Archimedes *ui;
    double calVal = 0.0;
    bool divTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool mulTrigger = false;
    bool equalTrigger = false;
    double memory = 0.0;
    bool first_key_press = false;

    std::shared_ptr<Database> mDatabase;
};

#endif // ARCHIMEDES_H
