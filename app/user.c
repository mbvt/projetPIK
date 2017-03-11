/* user.c */
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "user.h"
//# include "str_mysql.h"

struct user *init_user(char *name, char *firstname, int age, int status, int
    handicap, int category){

  struct user *newuser =  malloc(sizeof (struct user));
  newuser->name =            name;
  newuser->firstname =       firstname;
  newuser->age =             age;
  newuser->status =          status;
  newuser->handicap =        handicap;
  newuser->category =        category;

  /*
   **  TODO  query to add the user in the database
   **  get the id from the user and add it to newuser->id_user
   **  - convert int to string for query values
   */

   return  newuser;
}

int exist_user(char *name, char *firstname, struct S_MYSQL *smysql)
{

  char *data = select_user(name, firstname, smysql);

  return strlen(data) != 0;
}

int insert_user(struct user *newuser, struct S_MYSQL *query)
{
    char *firstname = newuser->firstname;
    char *name = newuser->name;
  
    firstname = insert_string(newuser->firstname);
    name = insert_string(newuser->name);

    char* str_age = int_to_str(newuser->age);
    char* str_cat = int_to_str(newuser->category);
    char* str_status = int_to_str(newuser->status);

    char* reqst = build_req_values(firstname, name, str_age, str_cat, str_status);

    char* q = calloc(100, sizeof(char));
    strcat(q, "NULL,");
    strcat(q, reqst);

    query->table_name = "pik_user";
    query->insert_values = q;

    int id_user = insert_table(query);
    printf("id_user ! %d\n", id_user);
    newuser->id_user = id_user;

    return id_user;
}

struct user *get_user(char *name, char *firstname, struct S_MYSQL *smysql)
{  
  struct user *user = calloc(1, sizeof(struct user));
  
  char *data = select_user(name, firstname, smysql);

  char *s = ",";
  char *token;
  int cpt = 0;
  int tmp = 0; 
  token = strtok(data, s);

  while(token != NULL)
  {
    if (cpt == 0)
    {
     tmp = atoi(token);
     user->id_user = tmp;
    }
    else if (cpt == 1)
      user->firstname = token;

    else if (cpt == 2)
      user->name = token;

    else if (cpt == 3)
    {
      tmp = atoi(token);
      user->age = tmp;
    }
    else if (cpt == 4)
    {
      tmp = atoi(token);
      user->category = tmp;
    }
    else if (cpt == 5)
    {
      tmp = atoi(token);
      user->status = tmp;
    }
    cpt += 1;
    token = strtok(NULL, s);
  }

  // *user->handicap left (in another table)

  return user;
}

//int modify_user(char *name, char *firstname, int age, int status, int handicap,
  //  int category, struct user **user)
//{
  /*  TODO Querry to modify user
   **  Check if everything is ok return 1 or 0
   */
 // return 1;
//}

int delete_user(struct user *user, struct S_MYSQL *smysql)
{
  /*  TODO Querry to delete user
   **  Check if everything is ok return 1 or 0
   */
  int check = 0;
  
  del_user(user->id_user, smysql);
  check = exist_user(user->name, user->firstname, smysql);
  
  return check;
}

int determine_category(int status, int handicap)
{
  /* enfant
   ** handicap
   ** black_white
   ** motor
   TODO determiner
   ** les dicos
   ** les speed
   ** les clavier couleur etc // Pour l'instant juste clavier noir et blanc
   ** est il possible d'avoir plussieur handicap + etre enfant
   */

  int category;

  if (status > 0)
    category = status;
  else
    return -1;

  if (handicap > 0)
    category = handicap +2;
  //verify that category exist in database

  return category;
}
/*
int mcq_user(struct user **user, struct S_MYSQL *smysql)
{
  char name[50];
  char firstname[50];
  int age;
  int handicap = 0;
  int category;
  int status;

  printf("Entrez votre nom:\n");
  scanf("%s",name);
  printf("Entrez votre prenom:\n");
  scanf("%s",firstname);
  printf("Entrez votre age:\n");
  scanf("%d",&age);

  //TODO Query select to get all the handicap possible
  // then loop printf ( handicapname, i)
  printf("Avez vous un handicap ? 0/1\n");
  scanf("%d",&handicap);
  if (handicap == 1)
  {
    printf("Lequel : Daltonien(1) Moteur(2)\n");
    scanf("%d",&handicap);
  }
  status = (age > 16)?  1 :  2; // if age > 16 ? adulte : child
  if ((category = determine_category(status, handicap)) == -1)
    err(1, "error while determine category");

  // initialize the user
  if( exist_user(name, firstname, smysql) == 0)
  {
    if ((*user = insert_user(*name,firstname,age,status,handicap,category)) == NULL)
      err(1, "error while initialize user");
  }

  return 1;
}
*/
/*
int main()
{
  struct S_MYSQL *smysql = conn_init_sql();

  struct user *newuser = calloc(1, sizeof(struct user));
  newuser->firstname = "Brandon";
  newuser->name = "QUINNE";


  int check = 0;

  if(!exist_user(newuser->name, newuser->firstname, smysql))
  {
    check = insert_user(newuser, smysql);
  }
  else
  {
    get_user(newuser->name, newuser->firstname, smysql);
  }

  if(check)
    printf("Insert réussi magl (ptet' fill en fait) !\n ID : %d\n", newuser->id_user);

  return 0;
}
*/
