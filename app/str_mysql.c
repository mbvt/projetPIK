/* str_mysql.c */
/*to compile :gcc str_mysql.c -o str_mysql -std=c99  `mysql_config --cflags
  --libs` */
#include "str_mysql.h"
#define MAXSIZE 1000

/*struct user{                                                                   
  int             id_user;                                                     
  char            *name;                                                       
  char            *firstname;                                                  
  int             age;                                                         
  int             status; // 1 adult - 2 child                                 
  int             handicap; // 0 none - 1 visual - 2 motor                     
  int             category;
  };
  */

void finish_with_error(MYSQL *mysql){
  printf("Error: %s\n", mysql_error(mysql));
  mysql_close(mysql);
}

void finish_success(struct S_MYSQL *smysql){
  printf("Success query :\n %s\n", smysql->query_data);
}

int init_sql(MYSQL *mysql)
{
  mysql=mysql_init(NULL);
  if(mysql==NULL) 
  {
    printf("\nFailed to initate MySQL connection");
    return 0;
  }

  return 1;
}


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

/*
   char *find_fields(struct S_MYSQL *smysql)
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
   */
/****** INIT CONNECTION STRUCT MYSQL *******/
struct S_MYSQL *conn_init_sql()
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

/******** STORE RESULT IN STRING ***********/
// TODO char* array[] 
char *result_query(MYSQL *mysql_con)
{
  MYSQL_RES *res_store = malloc(sizeof(MYSQL_RES));

  if((res_store = mysql_store_result(mysql_con))!=NULL)
  {
    //finish_success(mysql_con);
   // printf("Result stored\n");
  }
  else
  {
    finish_with_error(mysql_con);
  }

  int num_fields = mysql_num_fields(res_store);
  MYSQL_ROW row;
  char *res = calloc(100, sizeof(char));
  int i = 0;

  while((row = mysql_fetch_row(res_store)))
  {
    for(; i < num_fields; ++i)
    {
      //printf("%s", row[i] ? row[i] : "NULL");
      strcat(res, row[i]);
      if( i < num_fields)
        strcat(res, ",");
    } 
    printf("\n");
  }

  char *query_res = res;
  //size_t len = strlen(query_res);
  //printf("len res : %s\n", query_res);
  mysql_free_result(res_store);

  return query_res;

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


/****** SELECT QUERY BY NAME AND FIRSTNAME & CHECK IF EXISTS USER ******/
char* select_user(char* name, char* firstname, struct S_MYSQL *smysql)
{
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

  //S_MYSQL *smysql = conn_init_sql();

  mysql_query(smysql->con, "use projetpik;");

  //printf("use proj\n");

  if(mysql_query(smysql->con, req))
  {
    smysql->query_data = req;
    finish_success(smysql);
  }

  char *res_query = result_query(smysql->con);

  return res_query;
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

  mysql_query(smysql->con, "use projetpik;");

  if(mysql_query(smysql->con, req))
  {
    smysql->query_data = req;
    finish_success(smysql);
  }
}

/****** INSERT QUERY IN TABLE GIVEN BY smysql->table_name ******/
int insert_table(struct S_MYSQL *smysql)
{
  //char *flds = find_fields(smysql);
  char *values = smysql->insert_values;
  char *table = smysql->table_name;

  char *str1 = "insert into ";
  //char *str2 = " (";
  char *str3 = " values (";
  char *end = ");";

  size_t len = strlen(str1) + strlen(table) + strlen(str3) + strlen(values) + strlen(end);

  char *query = calloc(len, sizeof(char));
  strcat(query, str1);
  strcat(query, table);
  //  strcat(query, str2);
  //  strcat(query, flds);
  strcat(query, str3);
  strcat(query, values);
  strcat(query, end);

  printf("Inserting user :\n %s\n", query);

  mysql_query(smysql->con, "use projetpik;");

  if(mysql_query(smysql->con, query))
  {
    smysql->query_data = query;
    finish_success(smysql);
  }
  int id_u;

  if(!(id_u = mysql_insert_id(smysql->con)))
    printf("Error with last inserted ID");
    //finish_success(smysql->con);

  //printf("id user: %d\n", id_u);

  return id_u;
}



/*int main()//int argc, char* argv[])
  {
  int check = 1;
  S_MYSQL *req = malloc(sizeof(struct S_MYSQL));
  MYSQL var;

  req->con = &var;
  check = init_sql(req->con);
  if(check == 0)
  printf("Error while init in main");

//  struct S_MYSQL *query = malloc(sizeof(struct S_MYSQL));                       
char *firstname = "Brandon";
char *name = "QUINNE";
*/ /*  int age = 23;
       int category = 1;
       int status = 1;

       firstname = insert_string(firstname);
       name = insert_string(name);

       char* ch_age = int_to_str(age);
       char* ch_cat = int_to_str(category);
       char* ch_status = int_to_str(status);

       char *reqst = build_req_values(firstname, name, ch_age, ch_cat, ch_status);
       */



/*printf("début -d\n");
  char *str = calloc(50, sizeof(char));
  char *str1 = calloc(8,sizeof(char));
 *str1 = *firstname;                                                        
 char *str2 = calloc(6, sizeof(char));
 *str2 = *name;
// char *gui = "\'";
// strcat(gui, str);  
strcat(str, firstname);
strcat(str, ",");                                                             
printf("début -dd\n");
strcat(str, name);                                                            
strcat(str, ",");
//char *buf = calloc(3,sizeof(char));
//sprintf(buf, ",%d,%d,%d", age, category, status);
printf("début\n");
*/
/*  char *ch_age = malloc(2*sizeof(char)); 
    sprintf(ch_age,"%d", age);
    printf("début s\n");
    strcat(ch_age, ",");
    printf("%s\n", ch_age);
    char *ch_cat = malloc(sizeof(char));
    sprintf(ch_cat, "%d", category);
    strcat(ch_cat, ",");
    char *ch_status = malloc(sizeof(char));
    sprintf(ch_status, "%d", status);
    */

/*
   char *q = calloc(100,sizeof(char));                                               

//strcat(q, "(");
strcat(q, "NULL,");
// strcat(q, "\'");
strcat(q, reqst);                                                      
strcat(q, ch_age);
strcat(q, ch_cat);
strcat(q, ch_status);  
// strcat(q, ")");                                                     

//query->table_name = "pik_user";                                               
req->insert_values = q;

printf("Requete : %s\n", q);  
*/

/* req->server = "localhost";
   req->user = "adminPIK";
   req->password = "projetpik";
   req->db = "projetpik";
   req->table_name = "pik_user";
//req->insert_values = "NULL,\'Amine\',\'Ahmed Ali\',23,1,1";


check = connect_sql(req->con, req->server, req->user, req->password);
if(check == 0)                                                                
printf("Error while connecting db in main\n");

//char *res = find_fields(req);
//printf("RES MAIN : %s\n", res);

*/ /*  check = insert_table(req);
       if(check == 0)
       printf("Error while inserting\n");
       */

/* char *string = select_user(name, firstname, req);
   printf("Returned string : %s\n", string);

*/
/*  struct user *user = calloc(1,sizeof(struct user));

    user = get_user(string, user);
    printf("\nuser : %d  %s  %s  %d  %d  %d\n", user->id_user, user->name, user->firstname,
    user->age, user->category, user->status);
    */
/*
   return 0;
   }*/
