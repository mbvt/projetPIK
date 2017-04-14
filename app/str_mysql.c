/* str_mysql.c */
/* to compile : gcc str_mysql.c -o str_mysql -l sqlite3 -std=c99 */

#include "str_mysql.h"
#define MAXSIZE 1000

/***** ADD QUOTES BEFORE AND AFTER THE WORD FOR INSERTION IN QUERY ********/
char* insert_string(char *word)
{
  size_t len = strlen(word);
  char* f_str = calloc(len + 3, sizeof(char));

  strcat(f_str, "\'");
  strcat(f_str, word);
  strcat(f_str, "\'");

  return f_str;
}

/******* BUILD QUERY CONCAT(STR1, ',', STR2, ',', ...) ********/
/*char* concat_query(char* str1, char* str2, char* str3, char* str4, char* str5)
  {
  char* conc = "concat(";
  strcat(conc, str1);
  strcat(conc, ",");
  strcat(conc, "\',\',");
  strcat(conc, str2);
  strcat(conc, ",");
  strcat(conc, "\',\',");
  strcat(conc, str3);
  strcat(conc, ",");
  strcat(conc, str4);
  strcat(conc, "\',\',");
  strcat(conc, ",");
  strcat(conc, str5);
  strcat(conc, ") ");

  return conc;
  }
  */
/****** CONVERT INT TO STRING ******/
char* int_to_str(int nb)
{
  char* str_int = calloc(3, sizeof(char));
  sprintf(str_int, "%d", nb);

  return str_int;
}

/******* BUILD QUERY FOR smysql->query *******/
char* build_req_values(char* str1, char* str2, char* str3, char* str4, char* str5)
{
  strcat(str1, ",");
  strcat(str1, str2);
  strcat(str1, ",");
  strcat(str1, str3);
  strcat(str1, ",");
  strcat(str1, str4);
  strcat(str1, ",");
  strcat(str1, str5);

  //printf("builded req_val : %s\n", str1);

  return str1;
}

/****** INIT CONNECTION STRUCT MYSQL *******/
/*struct S_MYSQL *conn_init_sql()
{
  //int check = 1;
  struct S_MYSQL *smysql = malloc(sizeof(struct S_MYSQL));
  //struct S_MYSQL *smysql;
  MYSQL *var = mysql_init(NULL);

  //smysql->con = &var;
  smysql->con = var;
  //if(check == 0)
  // printf("Error while init in connect_sql");

  smysql->server = "localhost";
  smysql->user = "adminPIK";
  smysql->password = "projetpik";
  smysql->db = "projetpik";

  if(mysql_real_connect(smysql->con, smysql->server, smysql->user, smysql->password, smysql->db, 0, NULL, 0) == NULL)
  {
    printf("Failed to connect database %s\n", smysql->db);
    //mysql_close(smysql->con);
  }

  return smysql;
}
*/
/******** SELECT BY NAME AND FIRSTNAME ***********/

int callback(void *, int, char **, char **);

char* select_user(char* name, char *firstname, struct S_MYSQL *smysql)
{
  char *err_msg = 0;
  name = insert_string(name);
  firstname = insert_string(firstname);

  char* req = calloc(300, sizeof(char));
  strcat(req, "select * from pik_user ");
  strcat(req, "where name_pik_user = ");
  strcat(req, name);
  strcat(req, " and fname_pik_user = ");
  strcat(req, firstname);
  strcat(req, ";");

  printf("Getting user :\n %s\n", req);

  char *res = calloc(100, sizeof (char));
  int rc = sqlite3_exec(smysql->handle, req, callback, res, &err_msg);

 if(rc != SQLITE_OK)
 {
  printf("Failed to select data\n");
  printf("SQL error : %s\n", err_msg);
  sqlite3_free(err_msg);
  return 0;
 }

  printf("%s\n", res);
 return res;
  

}

int callback(void *ret, int nb_col, char **val_col, char **name_col)
{
  for(int i = 0; i < nb_col; ++i)
  {
    //printf("%s = %s\n", name_col[i], val_col[i] ? val_col[i] : "NULL");
    strcat(ret, val_col[i]);
    printf("%s\n", name_col[i]);
    if(i < nb_col-1)
      strcat(ret, ",");

  }
  //printf("%s\n", (char *)ret);

  return 0;
}

/******* REMOVE PARENTHESES FROM RESULTING STRING ******/
char *remove_parths(char* data)
{
  char *dst = "";
  char *tmp = "";

  for(size_t i = 1; i < strlen(data)-1; ++i)
  {
    *tmp = data[i];
    strcat(dst, tmp);
  }

  return dst;
}

/****** DELETE QUERY USER ******/
void del_user(int id, struct S_MYSQL *smysql)
{
  char *id_str = int_to_str(id);

  char* req = calloc(300, sizeof(char));                                        
  strcat(req, "delete from pik_user ");                                       
  strcat(req, "where id_pik_user = ");                                        
  strcat(req, id_str);                                                            
  strcat(req, ";");

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, req, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }
}

/****** INSERT QUERY IN TABLE GIVEN BY smysql->table_name ******/
int insert_table(struct S_MYSQL *smysql)
{
  char *values = smysql->insert_values;
  char *table = smysql->table_name;

  char *str1 = "insert into ";
  char *str3 = " values (";
  char *end = ");";

  size_t len = strlen(str1) + strlen(table) + strlen(str3) + strlen(values) + strlen(end);

  char *query = calloc(len, sizeof(char));
  strcat(query, str1);
  strcat(query, table);
  strcat(query, str3);
  strcat(query, values);
  strcat(query, end);

  printf("Inserting user :\n %s\n", query);

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, query, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }
  
  int id_insert = sqlite3_last_insert_rowid(smysql->handle);

  printf("Inserted with id %d\n", id_insert); 

  return id_insert;
}

<<<<<<< HEAD
struct S_MYSQL *connect_db(struct S_MYSQL *smysql)
{
  smysql = calloc(1, sizeof(struct S_MYSQL));

  int retval;
  char *db = "projetpik.db";
  //sqlite3_stmt *stmt;
  sqlite3 *handle;
=======
//====> void insert_level_dico(char *text, 

>>>>>>> 3d9160254bafab3633e968e4ea608a34343aa9a0

  retval = sqlite3_open(db, &handle);

  if(retval != SQLITE_OK)
  {
    printf("Error while connecting db : %s\n", db);
  }
  printf("Connection success\n");

  //smysql->stmt = stmt;
  smysql->handle = handle;

  return smysql;
}

/*
int main()
{
  struct S_MYSQL *smysql = NULL;
  smysql = connect_db(smysql);
  smysql->insert_values = "NULL, \"test34\", \"test34n\", 11, 1, 2";
  smysql->table_name = "pik_user";

  char *name = "Quinne";
  char *firstname = "Brandon";

  int ret = 0;
  int id_user = 0;
  char *data = "";
  
  id_user = insert_table(smysql);
  if(id_user == 0)
    printf("Error inserting in table\n");

  data = select_user(name, firstname, smysql);
  printf("Select complete:\n%s\n", data);

  del_user(id_user, smysql);

  data = select_user(name, firstname, smysql);
  if(ret == 24)
    printf("Select complete\n");


  sqlite3_close(smysql->handle);

  return 0;
}
*/
