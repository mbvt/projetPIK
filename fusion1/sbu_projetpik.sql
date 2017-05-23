PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE status(id_status integer primary key, label_status varchar(150));
INSERT INTO "status" VALUES(1,'Adult');
INSERT INTO "status" VALUES(2,'Child');
CREATE TABLE category (id_category integer primary key autoincrement, label_category varchar(150));
CREATE TABLE level(id_level integer primary key, label_level varchar(150), length_w integer, nb_w integer, speed_exp_level integer, score_exp_level integer, text_level varchar(500), id_diff integer, id_world integer);
INSERT INTO "level" VALUES(1,'Level 1',4,4,30,20,'qsdfghjklm
',1,1);
INSERT INTO "level" VALUES(2,'Level 2',3,2,30,20,'qsdfghjklmazzertyuiop
',1,1);
INSERT INTO "level" VALUES(3,'Level 3',4,4,30,20,'qsdfghjklmazertyuiopwxcvbn
',1,1);
INSERT INTO "level" VALUES(4,'Level 4',4,4,30,20,'AZERTYUIOPQSDFGHJKLMWXCVBN
',1,2);
INSERT INTO "level" VALUES(5,'Level 5',4,4,30,20,'0123456789
',1,2);
INSERT INTO "level" VALUES(6,'Level 6',4,4,30,20,',;:!&é"''(-è_çà)=$ù*?./§%
',1,2);
INSERT INTO "level" VALUES(7,'Level 7',4,4,30,20,'azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN
',1,3);
INSERT INTO "level" VALUES(8,'Level 8',4,4,30,20,'azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789
',1,3);
INSERT INTO "level" VALUES(9,'Level 9',4,4,30,20,'azertyuiopqsdfghjklmwxcbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789,;:!&é"''(-è_çà)=$ù*?./§%
',1,3);
INSERT INTO "level" VALUES(10,'Level 10',4,4,30,20,'azertyuiopqsdfghjklmwxcbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789,;:!&é"''(-è_çà)=$ù*?./§%
',2,1);
INSERT INTO "level" VALUES(11,'Level 11',4,4,30,20,'~#{[|`\^@]}
',2,1);
INSERT INTO "level" VALUES(12,'Level 12',4,4,30,20,'azertyuiopqsdfghjklmwxcbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789,;:!&é"''(-è_çà)=$ù*?./§%~#{[|`\^@]}
',2,1);
INSERT INTO "level" VALUES(13,'Level 13',4,5,30,20,'abat-amas-arme-baba-bine-broc-coup-came-cent-dada-dol-doux-elfe-ente-esse-faxe-face-fine-gaga-gras-gris-hale-hune-huer-ibis-ives-insu-juin-jure-java-kava-kola-kilo-lace-lune-lame-maki-mimi-musa-nard-nage-nuer-oeuf-omis-orne-pore-pack-page-quoi-quel-quai-rats-ruer-rond-saga-sors-sang-trou-truc-tard-unir-urge-unie-vous-vain-venu-yack-yeux-yoga-zinc-zoom-zone',2,2);
INSERT INTO "level" VALUES(14,'Level 14',8,5,30,20,'abaissai-accalmie-avortera-babioles-bourreau-brunette-cambiste-cherrant-commuter-diraient-division-dupliqua-effacera-engluent-envoilez-facteurs-frelater-fusionne-galopera-gercerez-grillade-hacheras-humerait-horizons-illumine-indemnes-infestai-jaunisse-jugerons-jonglent-kabbales-kamikaze-kouglofs-labourai-laquelle-lifterai-macaques-mariages-missiles-natation-normatif-nourrice-onduleux-observez-officiel-palatins-parieuse-panserai-quarante-quilleur-quittiez-raillons-rouleaux-rebondis-sabliers-semoules-stimuler-traquait-tournois-truquant-utiliser-usurpons-utopique-vacciner-vicomtes-verserez-wagonnet-walkyrie-westerns-xanthine-xylocope-xanthies-yachting-yatagans-yearling-zigoteau-zodiaque-zonerons',2,2);
INSERT INTO "level" VALUES(15,'Level 15',8,5,30,20,'abîmer-ancêtre-âpre-bâcher-bélître-bêche-câbler-câliner-châtain-dégoûter-démâter-écrêter-empêtrer-extrême-fâcher-flûte-frêle-gâcheur-gîte-goûter-hâlé-hâtif-hôte-île-impôt-infâme-jeûne-jeûner-lâche-lâchage-mâcher-mêlée-ôter-pâleur-pâmer-pâte-quête-râble-rôtir-soûl-revêtir-tôlerie-trône-vêlement-verdâtre-voûter',2,2);
INSERT INTO "level" VALUES(16,'Level 16',8,5,30,20,'abîmer-ancêtre-âpre-bâcher-bélître-bêche-câbler-câliner-châtain-dégoûter-démâter-écrêter-empêtrer-extrême-fâcher-flûte-frêle-gâcheur-gîte-goûter-hâlé-hâtif-hôte-île-impôt-infâme-jeûne-jeûner-lâche-age-mâcher-mêlée-ôter-pâleur-pâmer-pâte-quête-râble-rôtir-soûl-revêtir-tôlerie-trône-vêlement-verdâtre-voûter-dupliqua-effacera-engluent-envoilez-facteurs-frelater-fusionne-galopera-gercerez-grillade-hacheras-humerait-9500-2566-25-48-9898-135-10-2-687-9746-369',2,2);
INSERT INTO "level" VALUES(17,'Level 17',8,5,30,20,'abîmer-ancêtre-âpre-bâcher-bélître-bêche-câbler-câliner-châtain-dégoûter-démâter-écrêter-empêtrer-extrême-fâcher-flûte-frêle-gâcheur-gîte-goûter-hâlé-hâtif-hôte-île-impôt-infâme-jeûne-jeûner-lâche-age-mâcher-mêlée-ôter-pâleur-pâmer-pâte-quête-râble-rôtir-soûl-revêtir-tôlerie-trône-vêlement-verdâtre-voûter-dupliqua-effacera-engluent-envoilez-facteurs-frelater-fusionne-galopera-gercerez-grillade-hacheras-humerait-9500-2566-25-48-9898-135-10-2-687-9746-369',2,2);
INSERT INTO "level" VALUES(18,'Level 18',25,5,30,20,'Ried1935@fleckens.hu-mehdiyou@xost.us-john@smith.us-pierre.simon@free.fr-marie@claude.yk-chingchong@yreat.ch-clairedupont@yahoo.com-merwen@dorp.ar-joris-paillandi@lagoon.nc-bob.lalande@epita.fr',2,3);
INSERT INTO "level" VALUES(19,'Level 19',25,5,30,20,'abîmer-ancêtre-âpre-bâcher-bélître-bêche-câbler-câliner-châtain-dégoûter-démâter-écrêter-empêtrer-extrême-fâcher-flûte-frêle-gâcheur-gîte-goûter-hâlé-hâtif-hôte-île-impôt-infâme-jeûne-jeûner-lâche-age-mâcher-mêlée-ôter-pâleur-pâmer-pâte-quête-râble-rôtir-soûl-revêtir-tôlerie-trône-vêlement-verdâtre-voûter-dupliqua-effacera-engluent-envoilez-facteurs-frelater-fusionne-galopera-gercerez-grillade-hacheras-humerait-9500-2566-25-48-9898-135-10-2-687-9746-369-Ried1935@fleckens.hu-mehdiyou@xost.us-john@smith.us-pierre.simon@free.fr-marie@claude.yk-chingchong@yreat.ch-clairedupont@yahoo.com-merwen@dorp.ar-joris-paillandi@lagoon.nc-bob.lalande@epita.fr',2,2);
CREATE TABLE results (id_res integer primary key autoincrement, score integer, speed double, id_pik_user integer, id_level integer, foreign key (id_pik_user) references pik_user(id_pik_user), foreign key (id_level) references level(id_level));
CREATE TABLE pik_user(id_pik_user integer primary key autoincrement, fname_pik_user varchar(150), name_pik_user varchar(150), age_pik_user integer, category_pik_user integer, id_status integer, foreign key(id_status) references status (id_status));
COMMIT;
