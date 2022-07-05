CREATE DATABASE IF NOT EXISTS CECSProject;

CREATE USER IF NOT EXISTS 'cecs535'@'%' IDENTIFIED BY 'taforever';

GRANT ALL PRIVILEGES ON *.* TO 'cecs535'@'%' WITH GRANT OPTION;

USE CECSProject;


CREATE TABLE IF NOT EXISTS HOTEL(hotelid INT NOT NULL AUTO_INCREMENT, address VARCHAR(255), `manager-name` VARCHAR(30), `number-rooms` INT, amenities VARCHAR(400), PRIMARY KEY(hotelid) );


CREATE TABLE IF NOT EXISTS ROOM( `number` INT NOT NULL, type VARCHAR(30), occupancy INT, `number-beds` INT, `type-beds` VARCHAR(30), price INT, `hotel-id` INT NOT NULL, PRIMARY KEY(`number`,`hotel-id`), FOREIGN KEY(`hotel-id`) REFERENCES HOTEL(hotelid) );


CREATE TABLE IF NOT EXISTS CUSTOMER( `cust-id` INT NOT NULL AUTO_INCREMENT, name VARCHAR(30), street VARCHAR(255), city VARCHAR(30), zip VARCHAR(9), status VARCHAR(30), PRIMARY KEY(`cust-id`));


CREATE TABLE IF NOT EXISTS RESERVATION( hotelid INT NOT NULL, `cust-id` INT NOT NULL, `room-number` INT NOT NULL, `begin-date` DATETIME NOT NULL, `end-date` DATETIME NOT NULL, `credit-card-number` VARCHAR(20) NOT NULL, `exp-date` VARCHAR(10) NOT NULL, PRIMARY KEY(hotelid, `cust-id`, `room-number`),
                         FOREIGN KEY(hotelid) REFERENCES HOTEL(hotelid),
                         FOREIGN KEY(`cust-id`) REFERENCES CUSTOMER(`cust-id`),
                         FOREIGN KEY(`room-number`, hotelid) REFERENCES ROOM(`number`, `hotel-id`));

DELIMITER $$
CREATE TRIGGER RoomExpectations
BEFORE INSERT ON ROOM
FOR EACH ROW BEGIN IF NEW.price < 0 THEN SIGNAL SQLSTATE '45000'; END IF; IF NEW.type NOT IN ( 'regular', 'extra', 'suite', 'business', 'luxury', 'family') THEN SIGNAL SQLSTATE '45000'; END IF; IF NEW.occupancy NOT BETWEEN 1 AND 5 THEN SIGNAL SQLSTATE '45000'; END IF; IF NEW.`number-beds` NOT IN (1, 2, 3) THEN SIGNAL SQLSTATE '45000'; END IF; IF NEW.`type-beds` NOT IN ( 'queen', 'king', 'full') THEN SIGNAL SQLSTATE '45000'; END IF; END;$$ 

DELIMITER ;


DELIMITER $$
CREATE PROCEDURE Occupancy(IN numberid_hotel INT, IN query_date DATETIME) 
BEGIN
SELECT COUNT(`room-number`) AS occupancy_count
FROM RESERVATION
WHERE query_date BETWEEN `begin-date` AND `end-date` AND numberid_hotel = hotelid; 
END $$ 

DELIMITER ;

CREATE TABLE IF NOT EXISTS REVENUE(hotelid INT NOT NULL, total INT NOT NULL, PRIMARY KEY(hotelid), FOREIGN KEY(hotelid) REFERENCES RESERVATION(hotelid) );

DELIMITER $$
CREATE TRIGGER RevenueUpdateTrigger 
AFTER INSERT ON RESERVATION
FOR EACH ROW BEGIN
UPDATE REVENUE AS r
SET r.total =
  (SELECT SUM(room_revenue) AS total
   FROM
     (SELECT base_hotel.hotelid ,
             base_hotel.`room-number` ,
             room_rate * count_days AS room_revenue
      FROM
        (SELECT TIMESTAMPDIFF(DAY,`begin-date`, `end-date`) AS count_days ,
                hotelid ,
                `room-number`
         FROM RESERVATION
         WHERE r.hotelid = RESERVATION.hotelid) AS base_hotel
      INNER JOIN
        (SELECT AVG(price) AS room_rate ,
               `hotel-id`,
               `number`
         FROM ROOM
         WHERE r.hotelid = `hotel-id`
         GROUP BY `hotel-id` ,
                  `number`) AS hotel_price ON base_hotel.`room-number` = hotel_price.`number`
      AND base_hotel.hotelid = hotel_price.`hotel-id`) AS revenue_calculation)
WHERE r.hotelid = NEW.hotelid; END $$ 
DELIMITER ;

