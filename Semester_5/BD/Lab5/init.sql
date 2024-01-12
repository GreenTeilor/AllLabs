SET FOREIGN_KEY_CHECKS=0 ; 

/* Shema creation */
DROP SCHEMA IF EXISTS `bd_lab5` ;
CREATE SCHEMA IF NOT EXISTS `bd_lab5` DEFAULT CHARACTER SET utf8 ;
USE `bd_lab5` ;

/* Drop Tables */

DROP TABLE IF EXISTS `airport` CASCADE
;

DROP TABLE IF EXISTS `black_list` CASCADE
;

DROP TABLE IF EXISTS `citizenship_employee` CASCADE
;

DROP TABLE IF EXISTS `citizenship_passenger` CASCADE
;

DROP TABLE IF EXISTS `city` CASCADE
;

DROP TABLE IF EXISTS `class` CASCADE
;

DROP TABLE IF EXISTS `corporation` CASCADE
;

DROP TABLE IF EXISTS `country` CASCADE
;

DROP TABLE IF EXISTS `delayed_flights` CASCADE
;

DROP TABLE IF EXISTS `employee` CASCADE
;

DROP TABLE IF EXISTS `flight` CASCADE
;

DROP TABLE IF EXISTS `location` CASCADE
;

DROP TABLE IF EXISTS `office` CASCADE
;

DROP TABLE IF EXISTS `office_address` CASCADE
;

DROP TABLE IF EXISTS `office_employee` CASCADE
;

DROP TABLE IF EXISTS `passenger` CASCADE
;

DROP TABLE IF EXISTS `plane` CASCADE
;

DROP TABLE IF EXISTS `position` CASCADE
;

DROP TABLE IF EXISTS `position_employee` CASCADE
;

DROP TABLE IF EXISTS `sale` CASCADE
;

DROP TABLE IF EXISTS `status` CASCADE
;

DROP TABLE IF EXISTS `status_employee` CASCADE
;

DROP TABLE IF EXISTS `status_passenger` CASCADE
;

DROP TABLE IF EXISTS `ticket` CASCADE
;

/* Create Tables */

CREATE TABLE `airport`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	`location_id` INT NOT NULL,
	CONSTRAINT `PK_airport` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `black_list`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`passenger_id` INT NOT NULL,
	`description` VARCHAR(100) NOT NULL,
	CONSTRAINT `PK_black_list` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `citizenship_employee`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`employee_id` INT NOT NULL,
	`citizenship_id` INT NOT NULL,
	CONSTRAINT `PK_citizenship_employee` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `citizenship_passenger`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`passenger_id` INT NOT NULL,
	`citizenship_id` INT NOT NULL,
	CONSTRAINT `PK_citizenship_passenger` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `city`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_city` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `class`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_class` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `corporation`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_corporation` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `country`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_country` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `delayed_flights`
(
	`id` INT NOT NULL,
	`flight_id` INT NOT NULL,
	CONSTRAINT `PK_delayed_flights` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `employee`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(30) NOT NULL,
	`last_name` VARCHAR(30) NOT NULL,
	`patronymic` VARCHAR(30) NULL,
	`birth_date` DATE NOT NULL,
	`passport_number` VARCHAR(50) NOT NULL,
	`phone_number` VARCHAR(20) NOT NULL,
	`email` VARCHAR(50) NOT NULL,
	`nationality` INT NOT NULL,
	`salary` DECIMAL(10,2) NOT NULL,
	CONSTRAINT `PK_employee` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `flight`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`departure_date` TIMESTAMP NOT NULL,
	`departure_airport_id` INT NOT NULL,
	`arrival_date` TIMESTAMP NOT NULL,
	`arrival_airport_id` INT NOT NULL,
	`plane_id` VARCHAR(100) NOT NULL,
	CONSTRAINT `PK_flight` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `location`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`country_id` INT NOT NULL,
	`city_id` INT NOT NULL,
	CONSTRAINT `PK_location` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `office`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(90) NOT NULL,
	`efficiency` DECIMAL(4,2) NOT NULL,
	`location_id` INT NOT NULL,
	CONSTRAINT `PK_office` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `office_address`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`street` VARCHAR(90) NOT NULL,
	`building` VARCHAR(90) NOT NULL,
	`office_id` INT NOT NULL,
	CONSTRAINT `PK_office_address` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `office_employee`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`office_id` INT NOT NULL,
	`employee_id` INT NOT NULL,
	CONSTRAINT `PK_office_employee` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `passenger`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(30) NOT NULL,
	`last_name` VARCHAR(30) NOT NULL,
	`patronymic` VARCHAR(30) NULL,
	`birth_date` DATE NOT NULL,
	`passport_number` VARCHAR(50) NOT NULL,
	`phone_number` VARCHAR(20) NOT NULL,
	`email` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_passenger` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `plane`
(
	`id` VARCHAR(100) NOT NULL,
	`manufaction_corporation_id` INT NULL,
	`serve_from` DATE NOT NULL,
	`expire_at` DATE NOT NULL,
	`next_technical_inspection` TIMESTAMP NOT NULL,
	CONSTRAINT `PK_plane` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `position`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_position` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `position_employee`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`employee_id` INT NOT NULL,
	`position_id` INT NOT NULL,
	CONSTRAINT `PK_position_employee` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `sale`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`date_from` TIMESTAMP NOT NULL,
	`date_to` TIMESTAMP NOT NULL,
	`profit` DECIMAL(21,2) NOT NULL,
	`office_id` INT NOT NULL,
	CONSTRAINT `PK_sale` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `status`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(50) NOT NULL,
	`description` VARCHAR(50) NULL,
	CONSTRAINT `PK_status` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `status_employee`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`employee_id` INT NOT NULL,
	`status_id` INT NOT NULL,
	CONSTRAINT `PK_status_employee` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `status_passenger`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`passenger_id` INT NOT NULL,
	`status_id` INT NOT NULL,
	CONSTRAINT `PK_status_passenger` PRIMARY KEY (`id` ASC)
)

;

CREATE TABLE `ticket`
(
	`id` INT NOT NULL AUTO_INCREMENT,
	`purchase_time` TIMESTAMP(6) NOT NULL,
	`passenger_id` INT NOT NULL,
	`price` DECIMAL(8,2) NOT NULL,
	`flight_id` INT NOT NULL,
	`class_id` INT NOT NULL,
	CONSTRAINT `PK_ticket` PRIMARY KEY (`id` ASC)
)

;

/* Create Primary Keys, Indexes, Uniques, Checks */

ALTER TABLE `black_list` 
 ADD CONSTRAINT `unique_passenger_id` UNIQUE (`passenger_id` ASC)
;

ALTER TABLE `delayed_flights` 
 ADD CONSTRAINT `unique_flight_id` UNIQUE (`flight_id` ASC)
;

ALTER TABLE `employee` 
 ADD CONSTRAINT `unique_passport_number` UNIQUE (`passport_number` ASC)
;

ALTER TABLE `employee` 
 ADD INDEX `ind_name_last_name_patronymic` (`name` ASC, `last_name` ASC, `patronymic` ASC)
;

ALTER TABLE `employee` 
 ADD CONSTRAINT `CHK_employee_name_first_upper` CHECK (CAST(UPPER(LEFT(`name`, 1)) AS BINARY) = LEFT(`name`, 1));
;

ALTER TABLE `employee` 
 ADD CONSTRAINT `CHK_employee_last_name_first_upper` CHECK (CAST(UPPER(LEFT(`last_name`, 1)) AS BINARY) = LEFT(`last_name`, 1));
;

ALTER TABLE `employee` 
 ADD CONSTRAINT `CHK_employee_patronymic_first_upper` CHECK (CAST(UPPER(LEFT(`patronymic`, 1)) AS BINARY) = LEFT(`patronymic`, 1));
;

ALTER TABLE `flight` 
 ADD INDEX `ind_departure` (`departure_date` ASC, `departure_airport_id` ASC)
;

ALTER TABLE `flight` 
 ADD INDEX `ind_arrival` (`arrival_date` ASC, `arrival_airport_id` ASC)
;

ALTER TABLE `office` 
 ADD INDEX `unique_name` (`name` ASC)
;

ALTER TABLE `office_address` 
 ADD CONSTRAINT `unique_office_id` UNIQUE (`office_id` ASC)
;

ALTER TABLE `passenger` 
 ADD CONSTRAINT `unique_passport_number` UNIQUE (`passport_number` ASC)
;

ALTER TABLE `passenger` 
 ADD CONSTRAINT `CHK_passenger_name_first_upper` CHECK (CAST(UPPER(LEFT(`name`, 1)) AS BINARY) = LEFT(`name`, 1));
;

ALTER TABLE `passenger` 
 ADD CONSTRAINT `CHK_passenger_last_name_first_upper` CHECK (CAST(UPPER(LEFT(`last_name`, 1)) AS BINARY) = LEFT(`last_name`, 1));
;

ALTER TABLE `passenger` 
 ADD CONSTRAINT `CHK_passenger_patronymic_first_upper` CHECK (CAST(UPPER(LEFT(`patronymic`, 1)) AS BINARY) = LEFT(`patronymic`, 1));
;

ALTER TABLE `country` 
 ADD CONSTRAINT `unique_name` UNIQUE (`name` ASC)
;

ALTER TABLE `city` 
 ADD CONSTRAINT `unique_name` UNIQUE (`name` ASC)
;

ALTER TABLE `passenger` 
 ADD INDEX `ind_name_last_name_patronymic` (`name` ASC, `last_name` ASC, `patronymic` ASC)
;

ALTER TABLE `plane` 
 ADD INDEX `ind_next_technical_inspection` (`next_technical_inspection` ASC)
;

ALTER TABLE `plane` 
 ADD INDEX `ind_expire_at` (`expire_at` ASC)
;

ALTER TABLE `sale` 
 ADD INDEX `ind_period` (`date_from` ASC, `date_to` ASC)
;

ALTER TABLE `ticket` 
 ADD INDEX `ind_passenger_id_flight_id` (`passenger_id` ASC, `flight_id` ASC)
;

ALTER TABLE `ticket` 
 ADD INDEX `ind_flight_id` (`flight_id` ASC)
;

/* Create Foreign Key Constraints */

ALTER TABLE `employee` 
 ADD CONSTRAINT `FK_EMPL_nationality`
	FOREIGN KEY (`nationality`) REFERENCES `country` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `airport` 
 ADD CONSTRAINT `FK_APORT_location_id`
	FOREIGN KEY (`location_id`) REFERENCES `location` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `black_list` 
 ADD CONSTRAINT `FK_BL_passenger_id`
	FOREIGN KEY (`passenger_id`) REFERENCES `passenger` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `citizenship_employee` 
 ADD CONSTRAINT `FK_CE_citizenship_id`
	FOREIGN KEY (`citizenship_id`) REFERENCES `country` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `citizenship_employee` 
 ADD CONSTRAINT `FK_CE_employee_id`
	FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `citizenship_passenger` 
 ADD CONSTRAINT `FK_CP_citizenship_id`
	FOREIGN KEY (`citizenship_id`) REFERENCES `country` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `citizenship_passenger` 
 ADD CONSTRAINT `FK_CP_passenger_id`
	FOREIGN KEY (`passenger_id`) REFERENCES `passenger` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `delayed_flights` 
 ADD CONSTRAINT `FK_DF_flight_id`
	FOREIGN KEY (`flight_id`) REFERENCES `flight` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `flight` 
 ADD CONSTRAINT `FK_FLT_arrival_airport_id`
	FOREIGN KEY (`arrival_airport_id`) REFERENCES `airport` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `flight` 
 ADD CONSTRAINT `FK_FLT_departure_airport_id`
	FOREIGN KEY (`departure_airport_id`) REFERENCES `airport` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `flight` 
 ADD CONSTRAINT `FK_FLT_plane_id`
	FOREIGN KEY (`plane_id`) REFERENCES `plane` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `location` 
 ADD CONSTRAINT `FK_LCTN_city_id`
	FOREIGN KEY (`city_id`) REFERENCES `city` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `location` 
 ADD CONSTRAINT `FK_LCTN_country_id`
	FOREIGN KEY (`country_id`) REFERENCES `country` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `office` 
 ADD CONSTRAINT `FK_OFC_location_id`
	FOREIGN KEY (`location_id`) REFERENCES `location` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `office_address` 
 ADD CONSTRAINT `FK_OA_office_id`
	FOREIGN KEY (`office_id`) REFERENCES `office` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `office_employee` 
 ADD CONSTRAINT `FK_OE_employee_id`
	FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `office_employee` 
 ADD CONSTRAINT `FK_OE_office_id`
	FOREIGN KEY (`office_id`) REFERENCES `office` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `plane` 
 ADD CONSTRAINT `FK_PLANE_manufaction_corporation_id`
	FOREIGN KEY (`manufaction_corporation_id`) REFERENCES `corporation` (`id`) ON DELETE Set Null ON UPDATE Cascade
;

ALTER TABLE `position_employee` 
 ADD CONSTRAINT `FK_PE_employee_id`
	FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `position_employee` 
 ADD CONSTRAINT `FK_PE_position_id`
	FOREIGN KEY (`position_id`) REFERENCES `position` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `sale` 
 ADD CONSTRAINT `FK_SALE_office_id`
	FOREIGN KEY (`office_id`) REFERENCES `office` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `status_employee` 
 ADD CONSTRAINT `FK_SE_employee_id`
	FOREIGN KEY (`employee_id`) REFERENCES `employee` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `status_employee` 
 ADD CONSTRAINT `FK_SE_status_id`
	FOREIGN KEY (`status_id`) REFERENCES `status` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `status_passenger` 
 ADD CONSTRAINT `FK_SP_passenger_id`
	FOREIGN KEY (`passenger_id`) REFERENCES `passenger` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `status_passenger` 
 ADD CONSTRAINT `FK_SP_status_id`
	FOREIGN KEY (`status_id`) REFERENCES `status` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `ticket` 
 ADD CONSTRAINT `FK_TCKT_class_id`
	FOREIGN KEY (`class_id`) REFERENCES `class` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `ticket` 
 ADD CONSTRAINT `FK_TCKT_flight_id`
	FOREIGN KEY (`flight_id`) REFERENCES `flight` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

ALTER TABLE `ticket` 
 ADD CONSTRAINT `FK_TCKT_passenger_id`
	FOREIGN KEY (`passenger_id`) REFERENCES `passenger` (`id`) ON DELETE Cascade ON UPDATE Cascade
;

/* Triggers */
DELIMITER $$
CREATE DEFINER=`root`@`localhost` TRIGGER `employee_BEFORE_INSERT_age_must_be_greater_than_or_equal_to_18` BEFORE INSERT ON `employee` FOR EACH ROW BEGIN
	IF datediff(CURRENT_DATE(), NEW.birth_date) / 365.2425 < 18 THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Employee age must be greater than or equal to 18';
	END IF;
END$$
DELIMITER ;

SET FOREIGN_KEY_CHECKS=1
; 
