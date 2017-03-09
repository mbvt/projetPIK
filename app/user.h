/* user.h */
#ifndef _PROJETPIK_USER_H
#define _PROJETPIK_USER_H

# include "str_mysql.h"

struct user{
  int             id_user;
  char            *name;
  char            *firstname;
  int             age;
  int             status; // 1 adult - 2 child
  int             handicap; // 0 none - 1 visual - 2 motor
  int             category;
};

/*
 **  Initialize a user with name, firstname, age, status, handicap, profile
 **  Adding it to the database
 **  Get the id from the database and initialize the id_user
 **  return the struct user.
 */
struct user *init_user(char *name, char *firstname, int age, int status,
    int handicap, int category);


int exist_user(char *name, char *firstname);

int insert_user(struct user *newuser, struct S_MYSQL *query);

struct user *get_user(char *string, struct user **user);


/*
 **  Finding the user into the database with name and firstname
 **  store it in the struct user given in args,
 **  return 1 if success or 0.
 */
int find_user(char *name, char *firstname, struct user **user);

/*
 **  Modify the user's data with name, firstname, age, status, handicap, profile
 **  in the database and modifie the user given in args,
 **  return 1 if success or 0.
 */
int modify_user(char *name, char *firstname, int age, int status,
    int handicap, int category, struct user **user);

/*
 **  Delete the user in the database and return 1 on success or 0.
 */
int delete_user(struct user *user);

/*
 **  This function determine the category with the status of the user and if he
 **  is handicap.
 **  Return the id_category or -1 if it fails.
 */
int determine_category(int status, int handicap);

/*
 **  MCQ to create the user. It will ask the name, firstname, age, if the user
 **  gets used with a keyboard and if he has an handicap.
 **  For the status and the handicap:
 **    - get a list of handicap and status from database
 **    - in the question for both of them loop on the posibilities (for each
 **  status and handicap print the id and the libelle
 **    - get the answer and check if it exist in the database.
 **
 **  Then the function will initialize a profile with a category determined
 **  by the function determine_cat in the file profile.c.
 **  After using the function init_user and updating the data, the function will
 **  store the user created in the user given in arg and
 **  return 1 on success or 0.
 */
int mcq_user(struct user **user);
#endif
