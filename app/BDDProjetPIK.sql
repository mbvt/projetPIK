        use projetpik;


create table status (
        id_status int not null,
        label_status varchar(150),
        primary key (id_status));


create table pik_user (
        id_pik_user int not null auto_increment,
        fname_pik_user varchar(150),
        name_pik_user varchar(150),
        age_pik_user int,
        category_pik_user int,
        id_status int not null,
        primary key (id_pik_user),
        foreign key (id_status) references status (id_status));
  



create table handicap (
        id_handicap int not null,
        label_handicap varchar(150),
        primary key (id_handicap));        




create table statistics (
        id_statistics int not null,
        id_user int not null auto_increment,
        label_status varchar(150),
        primary key (id_status));




create table world (
        id_world int not null,
        label_world varchar(150),
        primary key (id_world));


create table difficulty (
        id_difficulty int not null,
        label_difficulty varchar(150),
        primary key (id_difficulty));


create table level (
        id_level int not null auto_increment,
        label_level varchar(150),
        speed_exp_level double not null,
        score_exp_level int not null,
        text_level varchar(500),
        id_world int not null,
        id_difficulty int not null,
        primary key (id_level),
        foreign key (id_world) references world,
        foreign key (id_difficulty) references difficulty);


create table dictionnary (
        id_dictionnary int not null auto_increment,
        label_dictionnary varchar(150),
        primary key (id_dictionnary));


create table category (
        id_category int not null auto_increment,
        label_category varchar(150),
        primary key (id_category));
