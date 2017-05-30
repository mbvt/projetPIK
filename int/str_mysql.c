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

/****** CONVERT INT TO STRING ******/
char* int_to_str(int nb)
{
  char* str_int = calloc(300, sizeof(char));
  sprintf(str_int, "%d", nb);

  return str_int;
}

/******* BUILD QUERY FOR smysql->query *******/
char* build_req_values(char* str1, char* str2, char* str3, char* str4, char* str5)
{
  char *req = calloc(1024,sizeof(char));

  strcat(req, str1);
  strcat(req, ",");
  strcat(req, str2);
  strcat(req, ",");
  strcat(req, str3);
  strcat(req, ",");
  strcat(req, str4);
  strcat(req, ",");
  strcat(req, str5);

  return req;
}


int callback2(void *, int, char **, char **);

char* select_level(char* id_lvl, struct S_MYSQL *smysql)
{
  char *err_msg = 0;

  char* req = calloc(516, sizeof(char));
  strcat(req, "select length_w, nb_w, speed_exp_level, score_exp_level, text_level, id_diff, id_world from level ");
  strcat(req, "where id_level = ");
  strcat(req, id_lvl);
  strcat(req, ";");

  char *res = calloc(1024, sizeof (char));
  int rc = sqlite3_exec(smysql->handle, req, callback2, res, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("Failed to select data\n");
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
    return 0;
  }

  return res;
}

int callback2(void *ret, int nb_col, char **val_col, char **name_col)
{
  for(int i = 0; i < nb_col; ++i)
  {
    size_t len = strlen(val_col[i]);
    char *tmp = val_col[i];
    if (tmp[len-1] == '\n')
      tmp[len-1] ='\0';
    strcat(ret, val_col[i]);
    strcat(ret," ");
  }
  (void)name_col;
  return 0;
}


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
    strcat(ret, val_col[i]);
    if(i < nb_col-1)
      strcat(ret, ",");
  }
  (void)name_col;

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

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, query, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }

  int id_insert = sqlite3_last_insert_rowid(smysql->handle);

  return id_insert;
}

int insert_lvl(struct S_MYSQL *smysql)
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

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, query, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }

  int id_insert = sqlite3_last_insert_rowid(smysql->handle);

  return id_insert;
}

char *double_to_str(double item)
{
  char* str = calloc(100, sizeof(char));
  sprintf(str, "%f", item);

  return str;
}


int insert_res(struct S_MYSQL *smysql , int score, int level, double speed, int id_user)
{
  char *s_score = int_to_str(score);
  char *s_lvl = int_to_str(level);
  char *s_id = int_to_str(id_user);
  char *s_speed = double_to_str(speed);

  for(size_t i = 0; s_speed[i] != '\0'; ++i)
  {
    if(s_speed[i] == ',')
      s_speed[i] = '.';
  }

  char *ins_val = calloc(50, sizeof(char));
  strcat(ins_val, s_score);
  strcat(ins_val, ",");
  strcat(ins_val, s_speed);
  strcat(ins_val, ",");
  strcat(ins_val, s_id);
  strcat(ins_val, ",");
  strcat(ins_val, s_lvl);

  char *values = ins_val;
  char *table = smysql->table_name;

  char *str1 = "insert into ";
  char *str3 = " values (NULL,";
  char *end = ");";

  size_t len = strlen(str1) + strlen(table) + strlen(str3) + strlen(values) + strlen(end);

  char *query = calloc(len, sizeof(char));
  strcat(query, str1);
  strcat(query, table);
  strcat(query, str3);
  strcat(query, values);
  strcat(query, end);

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, query, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }
  free(query);

  int id_insert = sqlite3_last_insert_rowid(smysql->handle);

  return id_insert;
}


struct S_MYSQL *connect_db(struct S_MYSQL *smysql)
{
  smysql = calloc(1, sizeof(struct S_MYSQL));

  int retval;
  char *db = "projetpik.db";
  sqlite3 *handle;

  retval = sqlite3_open(db, &handle);

  if(retval != SQLITE_OK)
  {
    printf("Error while connecting db : %s\n", db);
  }
  
  smysql->handle = handle;

  return smysql;
}


int callback3(void *, int nb_col, char **, char **);

char *do_query(struct S_MYSQL *smysql, char* req)
{
  char *res = calloc(1024, sizeof(char));
  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, req, callback3, res, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("Failed to select data\n");
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
    return 0;
  }

  return res;
}


int get_top_score(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);

  char *req = calloc(100, sizeof(char));
  strcat(req,"select max(score) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char *res = do_query(smysql, req);
  free(req);

  int score = atoi(res);
  free(res);

  return score;
}

double get_top_time(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);

  char *req = calloc(100, sizeof(char));
  strcat(req,"select min(speed) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char* res = do_query(smysql, req);
  free(req);

  double time = atof(res);
  free(res);

  return time;

}

int get_top_level(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);

  char *req = calloc(100, sizeof(char));
  strcat(req,"select max(id_level) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char* res = do_query(smysql, req);

  int lvl = atoi(res);
  free(res);

  return lvl;
}

int get_nb_game(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);
  
  char *req = calloc(100, sizeof(char));
  strcat(req,"select count(id_pik_user) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char* res = do_query(smysql, req);
  int nb = atoi(res);
  free(res);

  return nb;

}

int get_sum_score(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);

  char *req = calloc(100, sizeof(char));
  strcat(req,"select sum(score) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char* res = do_query(smysql, req);

  int nb = atoi(res);
  free(res);

  return nb;

}


double get_nb_time(struct S_MYSQL *smysql, int id_user)
{
  char *id = int_to_str(id_user);

  char *req = calloc(100, sizeof(char));
  strcat(req,"select sum(speed) from results where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char* res = do_query(smysql, req);

  double nb = atof(res);
  free(res);

  return nb;

}

char **get_f_name(struct S_MYSQL *smysql, int id)
{
  char** f_name = calloc(2, sizeof(char*));
  char* s_id = int_to_str(id);
  
  char *req = calloc(100, sizeof(char));
  strcat(req,"select fname_pik_user from pik_user where id_pik_user = ");
  strcat(req, s_id);
  strcat(req, ";");

  f_name[0] = do_query(smysql, req);

  char *req2 = calloc(100, sizeof(char));
  strcat(req2,"select name_pik_user from pik_user where id_pik_user = ");
  strcat(req2, s_id);
  strcat(req2, ";");

  f_name[1] = do_query(smysql, req2);

  free(req);
  free(req2);

  return f_name;
}

int get_best_player(struct S_MYSQL *smysql)
{
  char *req = calloc(100, sizeof(char));
  strcat(req,"select id_pik_user from best_res where total_score = ");
  strcat(req, "(select max(total_score) from best_res);");

  char* res = do_query(smysql, req);

  int id = atoi(res);
  free(res);

  return id;
}

int get_id_user(struct S_MYSQL *smysql, char *name, char *fname)
{
  char *s_fname = insert_string(fname);
  char *s_name = insert_string(name);
  (void)s_name;

  char *req = calloc(100, sizeof(char));
  strcat(req,"select id_pik_user from pik_user where fname_pik_user = ");
  strcat(req, s_name);
  //strcat(req, "and fname_pik_user = ");
  //strcat(req, s_fname);
  strcat(req, ";");

  char* res = do_query(smysql, req);
  int id = atoi(res);
  free(res);

  return id;
} 


int insert_best_res(struct S_MYSQL *smysql, int id_user)
{
  int score = get_sum_score(smysql, id_user);
  int nb_game = get_nb_game(smysql, id_user);
  double avg = (score / nb_game);

  char* id = int_to_str(id_user);
  char* s_score = int_to_str(score);

  char *s_avg = calloc(1024, sizeof(char));
  sprintf(s_avg, "%f", avg);
  
  for(size_t i = 0; s_avg[i] != '\0'; ++i)
  {
    if(s_avg[i] == ',')
      s_avg[i] = '.';
  }

  char* req = calloc(1024, sizeof(char));
  strcat(req, "select total_score from best_res where id_pik_user = ");
  strcat(req, id);
  strcat(req, ";");

  char *res = do_query(smysql, req);
  free(req);
  
  char* req2 = calloc(1024, sizeof(char));
  char* req2_1 = calloc(1024, sizeof(char));
  
  if(strlen(res) != 0)
  {
    printf("User %s in best_res yet\n", id);
    strcat(req2, "update best_res set total_score = ");
    strcat(req2, s_score);
    strcat(req2, " where id_pik_user = ");
    strcat(req2, id);
    strcat(req2, ";");

    char* res2 = do_query(smysql, req2);
    free(req2);
    free(res2);
   
    strcat(req2_1, "update best_res set avg = ");
    strcat(req2_1, s_avg);
    strcat(req2_1, " where id_pik_user = ");
    strcat(req2_1, id);
    strcat(req2_1, ";");

    char *res3 = do_query(smysql, req2_1);
    free(req2_1);
    free(res3);

    return score;
  }

  char* req3 = calloc(1024, sizeof(char));
  strcat(req3, "insert into best_res values (NULL,");
  strcat(req3, s_score);
  strcat(req3, ",");
  strcat(req3, s_avg);
  strcat(req3, ",");
  strcat(req3, id);
  strcat(req3, ");");

  char *err_msg = 0;
  int rc = sqlite3_exec(smysql->handle, req3, 0, 0, &err_msg);

  if(rc != SQLITE_OK)
  {
    printf("SQL error : %s\n", err_msg);
    sqlite3_free(err_msg);
  }
  free(req3);

  int id_insert = sqlite3_last_insert_rowid(smysql->handle);

  return id_insert;

}


int callback3(void *ret, int nb_col, char **val_col, char **name_col)
{
  for(int i = 0; i < nb_col; ++i)
  {
    strcat(ret, val_col[i]);
    if(i < nb_col-1)
      strcat(ret, ",");
  }
  (void)name_col;
  return 0;
}

