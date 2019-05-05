#include "database.h"

static sqlite3* db;
static char* zErrMsg;
static int rc;
static const char* sql;
static char * data;
Database::Database()
{

}
//---------------------------------------------------
//---------------------------------------------------
Database::~Database()
{
    sqlite3_close(db);
}

void Database::openDB()
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
void Database::createDB(){

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
void Database::insertIntoDB(double& soln)
{
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
void Database::retrieveFromDB(){
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
