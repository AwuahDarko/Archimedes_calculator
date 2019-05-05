#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <QString>
#include <QDebug>


class Database
{
public:
    Database();
    ~Database();
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
    static void insertIntoDB(double& soln);
    void retrieveFromDB();
    void openDB();

    static double DBcalVal;
private:



};

#endif // DATABASE_H
