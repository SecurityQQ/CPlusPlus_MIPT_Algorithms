//
//  main.c
//  SQlite
//
//  Created by Александр Малышев on 12.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
    }

int myExec(const char *dataBasePath, sqlite3 *dataBase,const char *sqlRequest ) {
    
    int rc = sqlite3_open(dataBasePath, &dataBase);
    
    if( !rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dataBase));
        exit(1);
    }
    
    sqlite3_stmt *statement;
    const char * tailStatements;
    
    sqlite3_prepare(dataBase, sqlRequest, (int)strlen(sqlRequest), &statement, &tailStatements);
    while ( (rc = sqlite3_step(statement) )  == SQLITE_ROW ) {
        int data = sqlite3_column_int( statement, 0);
    }
    
    
    
//    sqlite3_reset(statement); //Needs for unused statements
    sqlite3_finalize(statement);
    sqlite3_close(dataBase);
    return 1;
}






    int main(int argc, char **argv){
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        if( argc != 3 ){
            fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
            return(1);
        }
        rc = sqlite3_open(argv[1], &db);
        if( rc ){
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return(1);
        }
        rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        sqlite3_close(db);
        return 0;
    }


