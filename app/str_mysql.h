/* str_mysql.h */

#ifndef STR_MYSQL_H_
#define STR_MYSQL_H_

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH   128
#define MAX_QUERY_LENGTH  1024

typedef struct S_MYSQL{
  MYSQL *con;
  char *password;//[MAX_NAME_LENGTH];
  char *root_password;//[MAX_NAME_LENGTH];
  char *user;//[MAX_NAME_LENGTH];
  char *server;//[MAX_NAME_LENGTH];
  char *db;//[MAX_NAME_LENGTH];
  char *table_name;//[MAX_NAME_LENGTH];
  char *query_create_table;//[MAX_QUERY_LENGTH];
  char *insert_values;//[MAX_QUERY_LENGTH];
  char *query_data;//[MAX_QUERY_LENGTH];
}S_MYSQL;


void finish_with_error(MYSQL *mysql);
void finish_success(MYSQL *mysql);
int init_sql(MYSQL *mysql);
int connect_sql(MYSQL *mysql, char *host, char *user, char *pwd);
char* insert_string(char *word);
char* int_to_str(int nb);
char* concat_query(char* str1, char* str2, char* str3, char* str4, char* str5);
char* build_req_values(char* str1, char* str2, char* str3, char* str4, char* str5);
char* select_user(char* name, char* firstname, S_MYSQL *smysql);
char *result_query(MYSQL *smysql);
struct S_MYSQL *conn_init_sql();
char *find_fields(S_MYSQL *smysql);


/*int s_mysql_init(S_MYSQL *mysql);
int s_mysql_connect(S_MYSQL *mysql);
int s_mysql_disconnect(S_MYSQL *mysql);
//int s_mysql_createdb(S_MYSQL *mysql);
int s_mysql_createtable(S_MYSQL *mysql);
int s_mysql_setdb(S_MYSQL *mysql);
int s_mysql_insertdata(S_MYSQL *mysql);
int s_mysql_quickinsert(S_MYSQL *mysql);
*/
#endif /* STR_MYSQL_H_ */
