#ifndef ARCHIMEDES_H
#define ARCHIMEDES_H

#include <QMainWindow>

namespace Ui {
class Archimedes;
}

class Archimedes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Archimedes(QWidget *parent = nullptr);
    ~Archimedes();


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

private:
    Ui::Archimedes *ui;
    double calVal = 0.0;
    bool divTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool mulTrigger = false;
    bool equalTrigger = false;
    double memory = 0.0;

};

#endif // ARCHIMEDES_H
