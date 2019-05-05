#ifndef ARCHIMEDES_H
#define ARCHIMEDES_H

#include <QMainWindow>
#include <sqlite3.h>
#include <QDebug>
#include <string>
#include <QFile>



namespace Ui {
class Archimedes;

}

class Archimedes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Archimedes(QWidget *parent = nullptr);
    ~Archimedes();
    static int callbacks(void* data, int num_of_cols, char** fields_in_rows, char** col_names)
    {
        data = nullptr;
        const char* val = fields_in_rows[1];
        if(val != nullptr)
        {
         QString str{val};
         DBcalVal = str.toDouble();
        }
        else {
            DBcalVal = 0.0;
        }

        return 0;
    }

    void createDB();
    void insertIntoDB(double& soln);
    void retrieveFromDB();
    void openDB();
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
    static double DBcalVal;
    bool divTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool mulTrigger = false;
    bool equalTrigger = false;
    double memory = 0.0;
    bool first_key_press = false;

    sqlite3* db;
    char* zErrMsg = nullptr ;
    int rc;
    const char* sql;
    const char* data = "callback called";


};

#endif // ARCHIMEDES_H
