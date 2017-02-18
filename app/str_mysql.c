/* str_mysql.c */

#include "str_mysql.h"

void finish_with_error(MYSQL *mysql){
  printf("Error: %s\n", mysql_error(mysql));
  mysql_close(mysql);
}

void finish_success(MYSQL *mysql){
  printf("Success !\n");
  mysql_close(mysql);
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
    printf("Failed to connect database %s.\nError : %s\n", db, mysql_error(mysql));
    mysql_close(mysql);
    return 0;
  }

  return 1;
}

char *find_fields(S_MYSQL *smysql)
{
  char *str1 = "select COLUMN_NAME from INFORMATION_SCHEMA.COLUMNS";
  char *str2 = " where table_name = \'";
  char *end = "\';";

  unsigned int len = strlen(str1) + strlen(str2) + strlen(smysql->table_name) + strlen(end);

  char *query = malloc(len * sizeof(char));
  strcat(query, str1);
  strcat(query, str2);
  strcat(query, smysql->table_name);
  strcat(query, end);

  if(mysql_query(smysql->con, query))
    finish_success(smysql->con);

  if(mysql_store_result(smysql->con))   //TODO mysql_use_result
   {
    finish_success(smysql->con);
    printf("OK stored\n");
   }
  else
  {
    printf("NOPE\n");
  }

  MYSQL_RES *result = mysql_store_result(smysql->con);
  unsigned int num_fields = mysql_num_rows(result);

  MYSQL_FIELD *fields;
  fields = mysql_fetch_fields(result);

  char *res = "";
  for(unsigned int i = 0; i < num_fields; ++i)
  {
    printf("Le champ %u est %s\n", i, fields[i].name);
    strcat(res, fields[i].name);
    strcat(res, ", ");
  }



 /* char *res_tab[num_rows];
  char *res;

  for(int i = 0; i < num_rows; ++i)
  {
    res_tab[i] = (char*)result[i];
    printf("%s\n", res_tab[i]);
    res = strcat(res, res_tab[i]);
  }
  */

  return res;
}

int insert_table(S_MYSQL *smysql)
{
  /*char *flds = "";
  char *vals = "";
  if(mysql_query(smysql->con, "Insert into "+ smysql->table_name +"("+ flds +
        ") values (" + vals + ");"))
    finish_success(smysql->con);
*/
  return 0;
}


int main()//int argc, char* argv[])
{
  int check = 1;
  S_MYSQL *req = malloc(sizeof(struct S_MYSQL));
  MYSQL var;

  req->con = &var;
  check = init_sql(req->con);
  if(check == 0)
    printf("Error while init in main");

  req->server = "localhost";
  req->user = "adminPIK";
  req->password = "projetpik";
  req->db = "projetpik";
  req->table_name = "pik_user";

    check = connect_sql(req->con, req->server, req->user, req->password);
  if(check == 0)                                                                
    printf("Error while connecting db in main");

  char *res = find_fields(req);
  printf("RES MAIN : %s\n", res);

  return 0;
}
