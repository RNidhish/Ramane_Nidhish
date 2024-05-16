drop schema if exists programme_but;
create schema programme_but;
set schema 'programme_but';

CREATE TABLE _niveau(
    numero_n NUMERIC(10),
    CONSTRAINT _niveau_pk_1 PRIMARY KEY (numero_n)
);

CREATE TABLE _competences(
    lib_competence VARCHAR(20),
    CONSTRAINT _competences_pk_1 PRIMARY KEY (lib_competence)
);

CREATE TABLE _activites(
    lib_activite VARCHAR(20),
    CONSTRAINT _activites_pk_1 PRIMARY KEY (lib_activite),
    CONSTRAINT _activites_fk_1 FOREIGN KEY (lib_activite) REFERENCES _competences(lib_competence)
);

CREATE TABLE _semestre(
    numero_sem VARCHAR(20),
    CONSTRAINT _semestre_fk_1 PRIMARY KEY (numero_sem)
);

CREATE TABLE _ue(
    code_ue VARCHAR(20),
    lib_activite VARCHAR(20),
    numero_sem VARCHAR(20),
    CONSTRAINT _ue_pk_1 PRIMARY KEY (code_ue),
    CONSTRAINT _ue_fk_1 FOREIGN KEY (code_ue) REFERENCES _activites(lib_activite),
    CONSTRAINT _ue_fk_2 FOREIGN KEY (code_ue) REFERENCES _semestre(numero_sem)
);

CREATE TABLE _ressources(
    code_r VARCHAR(20),
    lib_r VARCHAR(20) NOT NULL,
    nb_h_cm_pn NUMERIC(10)NOT NULL,
    nb_h_td_pn NUMERIC(10)NOT NULL,
    nb_h_tp_pn NUMERIC(10)NOT NULL,
    CONSTRAINT _ressources_pk_1 PRIMARY KEY (code_r),
    CONSTRAINT _ressources_fk_1 FOREIGN KEY (code_r) REFERENCES _semestre(numero_sem)
);

CREATE TABLE _sae(
    code_sae VARCHAR(20) ,
    lib_sae VARCHAR(20) NOT NULL,
    nb_h_td_enc NUMERIC(10)NOT NULL,
    nb_h_tp_projet_autonomie NUMERIC(10),
    CONSTRAINT _sae_pk_1 PRIMARY KEY (code_sae)
);

CREATE TABLE _parcours(
    code_p VARCHAR(1) ,
    libelle_parcours VARCHAR(20) NOT NULL,
    nbre_gpe_td_p NUMERIC(10) NOT NULL,
    nbre_gpe_tp_p NUMERIC(10) NOT NULL,
    code_r VARCHAR(20) NOT NULL,
    CONSTRAINT _parcours_pk_1 PRIMARY KEY (code_p),
    CONSTRAINT _parcours_fk_1 FOREIGN KEY (code_r) REFERENCES _ressources(code_r),
    CONSTRAINT _parcours_fk_2 UNIQUE (code_p, code_r)

);

CREATE TABLE correspond(
    code_P VARCHAR(1),
    numero_N NUMERIC(10),
    lib_activite VARCHAR(20),
    CONSTRAINT correspond_pk_1 PRIMARY KEY (code_p, numero_n, lib_activite),
    CONSTRAINT correspond_fk_1 FOREIGN KEY (code_p) REFERENCES _parcours(code_p),
    CONSTRAINT correspond_fk_2 FOREIGN KEY (numero_n) REFERENCES _niveau(numero_n),
    CONSTRAINT correspond_fk_3 FOREIGN KEY (lib_activite) REFERENCES _activites(lib_activite)
);

CREATE TABLE fait_parti(
    numero_n NUMERIC(10),
    numero_sem VARCHAR(20) ,
    CONSTRAINT fait_parti_pk_1 UNIQUE (numero_n, numero_sem),
    CONSTRAINT fait_parti_fk_1 FOREIGN KEY (numero_n) REFERENCES _niveau(numero_n),
    CONSTRAINT fait_parti_fk_2 FOREIGN KEY (numero_sem) REFERENCES _semestre(numero_sem)
    
);

CREATE TABLE comprend_r(
    code_sae VARCHAR(20),
    code_r VARCHAR(20),
    nb_h_td_c NUMERIC(10)NOT NULL,
    nb_h_tp_c NUMERIC(10)NOT NULL,
    CONSTRAINT comprend_r_pk_1 PRIMARY KEY (code_sae,code_r),
    CONSTRAINT comprend_r_fk_1 FOREIGN KEY (code_sae) REFERENCES _sae(code_sae),
    CONSTRAINT comprend_r_fk_2 FOREIGN KEY (code_r) REFERENCES _ressources(code_r)
);


