USE vmct;

CREATE TABLE IF NOT EXISTS `entry` (
  `name` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `flags` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `epoch` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `ver` varchar(255) COLLATE latin1_general_cs NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_cs;

CREATE TABLE IF NOT EXISTS `file` (
  `package` char(64) COLLATE latin1_general_cs NOT NULL,
  `name` text COLLATE latin1_general_cs NOT NULL,
  KEY `fk1` (`package`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_cs;

CREATE TABLE IF NOT EXISTS `os` (
  `name` varchar(255) COLLATE latin1_general_cs NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_cs;

CREATE TABLE IF NOT EXISTS `package` (
  `name` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `arch` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `checksum` char(64) COLLATE latin1_general_cs NOT NULL,
  `description` text COLLATE latin1_general_cs NOT NULL,
  `version` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `revision` varchar(255) COLLATE latin1_general_cs NOT NULL,
  `os` varchar(255) COLLATE latin1_general_cs NOT NULL,
  PRIMARY KEY (`checksum`),
  KEY `fk1` (`os`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_cs;

CREATE TABLE IF NOT EXISTS `relation` (
  `type` enum('provides','requires') COLLATE latin1_general_cs NOT NULL,
  `package` char(64) COLLATE latin1_general_cs NOT NULL,
  `entry` varchar(255) COLLATE latin1_general_cs NOT NULL,
  KEY `type` (`type`),
  KEY `relation_ibfk_2` (`package`),
  KEY `relation_ibfk_1` (`entry`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_cs;

ALTER TABLE `file`
  ADD CONSTRAINT `file_ibfk_1` FOREIGN KEY (`package`) REFERENCES `package` (`checksum`);

ALTER TABLE `package`
  ADD CONSTRAINT `package_ibfk_1` FOREIGN KEY (`os`) REFERENCES `os` (`name`);

ALTER TABLE `relation`
  ADD CONSTRAINT `relation_ibfk_1` FOREIGN KEY (`entry`) REFERENCES `entry` (`name`),
  ADD CONSTRAINT `relation_ibfk_2` FOREIGN KEY (`package`) REFERENCES `package` (`checksum`);
