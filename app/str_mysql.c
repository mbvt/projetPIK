/* str_mysql.c */

#include "str_mysql.h"

void finish_with_error(MYSQL *con){
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
}

int init_sql(MYSQL *mysql)
{
  if(mysql_init(mysql)==NULL) //&mysql
  {
    printf("\nFailed to initate MySQL connection");
    return 0;
  }

  return 1;
}

int connect_sql(MYSQL *mysql, char *host, char *user, char *pwd)
{
  char *db = "projetpik";

  if(mysql_real_connect(mysql, host, user, pwd, db, 0, NULL, 0) == NULL)
  {
    printf("Failed to connect database.\nError : %s\n", mysql_error(mysql);
    mysql_close(mysql);
    return 0;
  }

  return 1;
}



