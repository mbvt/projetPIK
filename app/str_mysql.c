/* str_mysql.c */
/*to compile :gcc str_mysql.c -o str_mysql -std=c99  `mysql_config --cflags
 * --libs` */
#include "str_mysql.h"

void finish_with_error(MYSQL *mysql){
  printf("Error: %s\n", mysql_error(mysql));
  mysql_close(mysql);
}

void finish_success(MYSQL *mysql){
  printf("Success !\n");
  //mysql_close(mysql);
}

int init_sql(MYSQL *mysql)
{
  if(mysql_init(mysql)==NULL) 
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
  char *str1 = "select group_concat(COLUMN_NAME) from INFORMATION_SCHEMA.COLUMNS";
  char *str2 = " where table_name = \'";
  char *end = "\';";

  size_t len = strlen(str1) + strlen(str2) + strlen(smysql->table_name) + strlen(end);

  char *query = calloc(len, sizeof(char));
  strcat(query, str1);
  strcat(query, str2);
  strcat(query, smysql->table_name);
  strcat(query, end);

  printf("Query: %s\n", query);

  if(mysql_query(smysql->con, query))
  {
    finish_success(smysql->con);
    free(query);
  }

  MYSQL_RES *res_store = malloc(sizeof(MYSQL_RES));
    
  if(res_store = mysql_store_result(smysql->con))
   {
    finish_success(smysql->con);
    printf("Result stored\n");
   }
  else
  {
    printf("Did not manage to store result\n");
  }

  int num_fields = mysql_num_fields(res_store);
  MYSQL_ROW row;
  char *res = calloc(num_fields, sizeof(char));
  int i = 0;
  
  while((row = mysql_fetch_row(res_store)))
  {
    for(; i < num_fields; ++i)
    {
      printf("%s", row[i] ? row[i] : "NULL");
      strcat(res, row[i]);
    } 
    printf("\n");
  }
 
  mysql_free_result(res_store);

  return res;
}

int insert_table(S_MYSQL *smysql)
{
  char *flds = find_fields(smysql);
  char *values = smysql->insert_values;
  char *table = smysql->table_name;

  char *str1 = "insert into ";
  char *str2 = " (";
  char *str3 = ") values (";
  char *end = ");";
 
  size_t len = strlen(str1) + strlen(table) + strlen(str2) + strlen(flds)
                + strlen(str3) + strlen(values) + strlen(end);
  
  char *query = calloc(len, sizeof(char));
  strcat(query, str1);
  strcat(query, table);
  strcat(query, str2);
  strcat(query, flds);
  strcat(query, str3);
  strcat(query, values);
  strcat(query, end);
 
  printf("Query Ins: %s\n", query);

  mysql_query(smysql->con, "use projetpik;");

  if(mysql_query(smysql->con, query))
      finish_success(smysql->con);

  int id_u;
  
  if(id_u = mysql_insert_id(smysql->con))
   finish_success(smysql->con);

  printf("id user: %d\n", id_u);

  
  
  
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
  req->insert_values = "1,\'Amine\',\'Ahmed Ali\',23,1,1";

    check = connect_sql(req->con, req->server, req->user, req->password);
  if(check == 0)                                                                
    printf("Error while connecting db in main");

  //char *res = find_fields(req);
  //printf("RES MAIN : %s\n", res);
  
  check = insert_table(req);
  if(check != 0)
    printf("Error while inserting");

  return 0;
}
