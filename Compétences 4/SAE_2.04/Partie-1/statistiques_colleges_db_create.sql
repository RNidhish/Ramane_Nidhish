DROP SCHEMA IF EXISTS colleges CASCADE;
CREATE SCHEMA colleges;
SET SCHEMA 'colleges';


CREATE TABLE _etablissement
(
    uai VARCHAR(8) PRIMARY KEY,
    nom_etablissement VARCHAR(100),
    secteur VARCHAR(100),
    code_postal VARCHAR(5),
    latitude FLOAT,
    longitude FLOAT,
    code_nature VARCHAR(2),
    code_quartier_prioritaire VARCHAR(6),
    code_insee_de_la_commune VARCHAR(5),
    code_du_departement VARCHAR(3),
    code_region VARCHAR(2),
    code_academie VARCHAR(2),

    CONSTRAINT fk_etablissement_code_nature FOREIGN KEY (code_nature) REFERENCES _type(code_nature),
    CONSTRAINT fk_etablissement_code_quartier FOREIGN KEY (code_quartier_prioritaire) REFERENCES _quartier_prioritaire(code_quartier_prioritaire),
    CONSTRAINT fk_etablissement_code_insee FOREIGN KEY (code_insee_de_la_commune) REFERENCES _commune(code_insee_de_la_commune),
    CONSTRAINT fk_etablissement_code_departement FOREIGN KEY (code_du_departement) REFERENCES _departement(code_du_departement),
    CONSTRAINT fk_etablissement_code_region FOREIGN KEY (code_region) REFERENCES _region(code_region),
    CONSTRAINT fk_etablissement_code_academie FOREIGN KEY (code_academie) REFERENCES _academie(code_academie)
);

CREATE TABLE _caracteristiques_college
(
    nbre_eleve_hors_segpa_hors_ulis NUMERIC(5),
    nbre_eleve_segpa NUMERIC(5),
    nbre_eleve_uli NUMERIC(5),
    uai VARCHAR(8),
    annee_scolaire VARCHAR(9),

    CONSTRAINT fk_caracteristiques_college_uai FOREIGN KEY (uai) REFERENCES _etablissement(uai),
    CONSTRAINT fk_caracteristiques_college_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire)
);

CREATE TABLE _caracteristique_tout_etablissement
(
    effectif NUMERIC(5),
    ips FLOAT,
    ecart_type_de_l_ips FLOAT,
    ep VARCHAR(100),
    uai VARCHAR(8),
    annee_scolaire VARCHAR(9),
    
    CONSTRAINT fk_caracteristique_tout_etablissement_uai FOREIGN KEY (uai) REFERENCES _etablissement(uai),
    CONSTRAINT fk_caracteristique_tout_etablissement_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire)
);

CREATE TABLE _annee
(
    annee_scolaire VARCHAR(9) PRIMARY KEY
);

CREATE TABLE _classe
(
    id_classe NUMERIC(5) PRIMARY KEY
);


CREATE TABLE _caracteristiques_selon_classe
(
    nbre_eleve_hors_segpa_hors_ulis_selon_niveau NUMERIC(5),
    nbre_eleve_segpa_selon_niveau NUMERIC(5),
    nbre_eleve_ulis_selon_niveau NUMERIC(5),
    effectif_filles NUMERIC(5),
    effectif_garcons NUMERIC(5),
    id_classe NUMERIC(5),
    annee_scolaire VARCHAR(9),
    uai VARCHAR(8),

    CONSTRAINT fk_caracteristiques_selon_classe_id_classe FOREIGN KEY (id_classe) REFERENCES _classe(id_classe),
    CONSTRAINT fk_caracteristiques_selon_classe_uai FOREIGN KEY (uai) REFERENCES _etablissement(uai),
    CONSTRAINT fk_caracteristiques_selon_classe_annee FOREIGN KEY (annee_scolaire) REFERENCES _annee(annee_scolaire)
);

CREATE TABLE _type
(
    code_nature VARCHAR(2) PRIMARY KEY,
    libelle_nature VARCHAR(100)
);

CREATE TABLE _quartier_prioritaire
(
    code_quartier_prioritaire VARCHAR(6) PRIMARY KEY,
    nom_quartier_prioritaire VARCHAR(100) UNIQUE
);

CREATE TABLE _commune
(
    code_insee_de_la_commune VARCHAR(5) PRIMARY KEY,
    nom_commune VARCHAR(100) UNIQUE
);

CREATE TABLE _departement
(
    code_du_departement VARCHAR(3) PRIMARY KEY,
    nom_departement VARCHAR(100) UNIQUE
);

CREATE TABLE _region
(
    code_region VARCHAR(2) PRIMARY KEY,
    libelle_region VARCHAR(100) UNIQUE
);

CREATE TABLE _academie
(
    code_academie VARCHAR(2) PRIMARY KEY,
    lib_academie VARCHAR(100) UNIQUE
);
