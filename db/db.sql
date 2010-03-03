CREATE TABLE IF NOT EXISTS `entry` (
  `name` varchar(255) CHARACTER SET latin1 COLLATE latin1_general_cs NOT NULL,
  `flags` varchar(255) NOT NULL,
  `epoch` varchar(255) NOT NULL,
  `ver` varchar(255) NOT NULL,
  PRIMARY KEY (`name`)
);

CREATE TABLE IF NOT EXISTS `file` (
  `package_id` varchar(255) NOT NULL,
  `name` text NOT NULL
);

CREATE TABLE IF NOT EXISTS `package` (
  `name` varchar(255) NOT NULL,
  `arch` varchar(255) NOT NULL,
  `checksum` varchar(255) NOT NULL,
  `description` text NOT NULL,
  `version` varchar(255) NOT NULL,
  `revision` varchar(255) NOT NULL,
  PRIMARY KEY (`checksum`)
);

CREATE TABLE IF NOT EXISTS `provides` (
  `package_id` varchar(255) NOT NULL,
  `entry_id` varchar(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS `requires` (
  `package_id` varchar(255) NOT NULL,
  `entry_id` varchar(255) NOT NULL
);

