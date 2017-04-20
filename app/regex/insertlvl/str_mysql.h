/* str_mysql.h */

#ifndef STR_MYSQL_H_
#define STR_MYSQL_H_

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



struct S_MYSQL{
//  MYSQL *con;
//  char *password;
//  char *root_password;
//  char *user;
//  char *server;
  char *db;
  char *table_name;
  char *query_create_table;
  char *insert_values;
  char *query_data;
  sqlite3_stmt *stmt;
  sqlite3 *handle;
};

/* Indicates wherever there is an error or success in MYSQL query */
//void finish_with_error(MYSQL *mysql);
//void finish_success(struct S_MYSQL *smysql);

/* Init a new connection to MYSQL */
//int init_sql(MYSQL *mysql);
struct S_MYSQL *conn_init_sql();

/* Add quotes to string for insert in query for database */
char* insert_string(char *word);

/* Convert int to string */
char* int_to_str(int nb);

/* Build query to fit this : CONCAT(STR1, ',', STR2, ',', ...) */
char* concat_query(char* str1, char* str2, char* str3, char* str4, char* str5);

/* Build query adding commas between values */
char* build_req_values(char* str1, char* str2, char* str3, char* str4, char* str5);

/* select all data user by name and firstname, returns string of concated data*/
char *select_user(char* name, char* firstname, struct S_MYSQL *smysql);

/* Store result from query in string */
//char *result_query(MYSQL *smysql);

void del_user(int id, struct S_MYSQL *smysql);

int insert_table(struct S_MYSQL *smysql);
int insert_lvl(struct S_MYSQL *smysql);
int insert_res(struct S_MYSQL *smysql, int score, int level, int id_user);

/* INIT CONNECTION TO DB */
struct S_MYSQL *connect_db(struct S_MYSQL *smysql);
/* returns concated string of fields from table of smysql->table_name */
//char *find_fields(struct S_MYSQL *smysql);


#endif /* STR_MYSQL_H_ */
