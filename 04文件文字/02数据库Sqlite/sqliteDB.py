# -*- coding: UTF-8 -*-
import sqlite3


class SqliteDB:
    def __init__(self):
        self.conn = None

    def openDB(self, dbname):
        self.conn = sqlite3.connect(dbname)

    def runSQL(self, sql):
        self.conn.execute(sql)
        self.conn.commit()

    def select(self, sql):
        return self.conn.execute(sql)

    def closeDB(self):
        self.conn.close()


def printCursor(cursor):
    for row in cursor:
        print("ID = ", row[0])
        print("NAME = ", row[1])
        print("ADDRESS = ", row[2])
        print("SALARY = ", row[3], "\n")


mydb = SqliteDB()
mydb.openDB("test.db")
mydb.runSQL(
    """CREATE TABLE COMPANY
       (ID INT PRIMARY KEY     NOT NULL,
       NAME           TEXT    NOT NULL,
       AGE            INT     NOT NULL,
       ADDRESS        CHAR(50),
       SALARY         REAL);"""
)

mydb.runSQL(
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
      VALUES (1, 'Paul', 32, 'California', 20000.00 )"
)
mydb.runSQL(
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
      VALUES (2, 'Allen', 25, 'Texas', 15000.00 )"
)
cursor = mydb.select("SELECT id, name, address, salary  from COMPANY")
printCursor(cursor)

mydb.runSQL("UPDATE COMPANY set SALARY = 25000.00 where ID=1")
cursor = mydb.select("SELECT id, name, address, salary  from COMPANY")
printCursor(cursor)

mydb.runSQL("DELETE from COMPANY where ID=1;")
cursor = mydb.select("SELECT id, name, address, salary  from COMPANY")
printCursor(cursor)
