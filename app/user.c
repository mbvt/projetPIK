/* user.c */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "user.h"

struct user *init_user(char *name, char *firstname, int age,
            struct profile *profile){
    
    struct user *newuser =  malloc(sizeof (struct user));
    newuser->name =            name;  
    newuser->firstname =       firstname;  
    newuser->age =             age;  
    newuser->profile =         profile;

    char profname[] = *(profile->name);
    
    char append[2];
    FILE *file = fopen("~/data/user","w");
    char *line = malloc(256*sizeof(char));
    strcat(line,name);
    strcat(line,"/");
    strcat(line,firstname);
    strcat(line,"/");
    sprintf(append,"%d",age);
    strcat(line,append);
    strcat(line,"/");
    strcat(line,profname);
    fwrite(line,1,sizeof(line),file);
    fclose(file);

    return  newuser;
}

struct user *find_user(char *name, char *firstname){
    FILE *file = fopen("~/data/user","r");
    struct user *user = malloc(sizeof (struct user));
    char line[128];
    int i = 0;
    int find = 0;
    while(fgets(line, sizeof (line), file) != NULL && find == 0 )
    {
        //for each elmt seperate by delimiter
        // stocker dans liste tout la ligne
        // si l.name = name && l.firstname = firstname
        // init_user avec les elmt de la liste retourné le user.
        printf("line %d : %s",i,line);
        i++;
    }

    fclose(file);
    return user; 
}

struct user *mcq_user(void)
{
    struct user *user;
    struct profile *profile;
    char name[50];
    char firstname[50];
    char age[3];
    int keyboard;
    int handicap;
    
    printf("Entrez votre nom:\n");
    scanf("%s",name);
    printf("Entrez votre prenom:\n");
    scanf("%s",firstname);
    printf("Entrez votre age:\n");
    scanf("%s",age);
    printf("Avez vous déjà utilisé un clavier ? 0/1\n");
    scanf("%d",&keyboard);
    printf("Avez vous un handicap ? 0/1\n"); 
    printf("Lequel : Daltonien(1) Malvoyant(2) Moteur(3)\n");
    scanf("%d",&handicap);
   
    profile = determine_profile(age,keyboard,handicap);
    
    // créer le profile
    user = find_user(name,firstname);
    if(user == NULL)
        user = init_user(name,firstname,age,profile);
   
    return user; 
}
