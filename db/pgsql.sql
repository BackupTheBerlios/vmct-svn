\connect vmct

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

CREATE TYPE type_t AS ENUM (
    'provides',
    'requires'
);

SET default_tablespace = '';

SET default_with_oids = false;

CREATE TABLE entry (
    name character varying(255) NOT NULL,
    flags character varying(255) NOT NULL,
    epoch character varying(255) NOT NULL,
    ver character varying(255) NOT NULL
);


CREATE TABLE file (
    package character(64) NOT NULL,
    name text NOT NULL
);

CREATE TABLE os (
    name character varying(255) NOT NULL
);


CREATE TABLE package (
    name character varying(255) NOT NULL,
    arch character varying(255) NOT NULL,
    checksum character(64) NOT NULL,
    description text NOT NULL,
    version character varying(255) NOT NULL,
    revision character varying(255) NOT NULL,
    os character varying(255) NOT NULL
);

CREATE TABLE relation (
    type type_t NOT NULL,
    package character(64) NOT NULL,
    entry character varying(255) NOT NULL
);

ALTER TABLE ONLY entry
    ADD CONSTRAINT entry_pkey PRIMARY KEY (name);

ALTER TABLE ONLY os
    ADD CONSTRAINT os_pkey PRIMARY KEY (name);

ALTER TABLE ONLY package
    ADD CONSTRAINT package_pkey PRIMARY KEY (checksum);

CREATE INDEX type_idx ON relation USING btree (type);

ALTER TABLE ONLY file
    ADD CONSTRAINT file_ibfk_1 FOREIGN KEY (package) REFERENCES package(checksum);

ALTER TABLE ONLY package
    ADD CONSTRAINT package_ibfk_1 FOREIGN KEY (os) REFERENCES os(name);

ALTER TABLE ONLY relation
    ADD CONSTRAINT relation_ibfk_1 FOREIGN KEY (entry) REFERENCES entry(name);

ALTER TABLE ONLY relation
    ADD CONSTRAINT relation_ibfk_2 FOREIGN KEY (package) REFERENCES package(checksum);

