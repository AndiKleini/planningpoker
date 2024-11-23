#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

char *ESTIMATION;

int store_estimation(char *itemId, int value) 
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("./database/planningpoker.db", &db);
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stderr, "Opened database successfully\n", 0);
    }

    char sqlins[54+strlen(itemId)+(int)ceil(log10(value))]; 
    sprintf(sqlins, "INSERT INTO ESTIMATION (ITEMID,VALUE) VALUES('%s',%d);", itemId, value);

    int ret = 0;
    rc = sqlite3_exec(db, sqlins, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        ret = 1;
    } else {
        fprintf(stdout, "Records created successfully\n", 0);
    }

    sqlite3_close(db);
    return ret;
}

char* get_estimations(char *itemId) 
{ 
    sqlite3 *db;
    int rc = sqlite3_open("./database/planningpoker.db", &db);
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    int sqlen = 46 + strlen(itemId);
    char sqlsel[sqlen]; 
    sprintf(sqlsel, "SELECT VALUE from ESTIMATION where ITEMID='%s';", itemId);
    printf("%s\n", sqlsel);
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sqlsel, sqlen, &stmt, NULL);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    rc = sqlite3_step(stmt);
    const char *tmpret;
    int retsize;
    if (rc == SQLITE_ROW) {
        tmpret = (char *)sqlite3_column_text(stmt, 0);
        retsize = sqlite3_column_bytes(stmt, 0);
    } else {
        tmpret = "ERR";
    }
        
    char *ret = malloc((retsize+1)*sizeof(char));
    strcpy(ret, tmpret);
    ret[retsize] = '\0';

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return ret;
}