USE CECSProject; 

INSERT INTO HOTEL VALUES (02, 'address_test', 'manager_test', 2, 'amenities_test');
INSERT INTO ROOM VALUES (55, 'regular', 1, 2, 'queen', 1, 02);
INSERT INTO CUSTOMER VALUES (02, 'customer_name_test', 'customer_street_test', 'customer_city_test', '20000', 'status_test');
INSERT INTO RESERVATION VALUES (02, 02, 55, '2018-12-19 09:26:03', '2024-12-19 09:26:03', '23232', '0624');

INSERT INTO HOTEL VALUES (01, 'address_test', 'manager_test', 2, 'amenities_test');
INSERT INTO ROOM VALUES (55, 'regular', 1, 2, 'queen', 1, 01);
INSERT INTO CUSTOMER VALUES (01, 'customer_name_test', 'customer_street_test', 'customer_city_test', '20000', 'status_test');
INSERT INTO RESERVATION VALUES (01, 01, 55, '2018-12-19 09:26:03', '2026-12-19 09:26:03', '23232', '0624');


INSERT INTO REVENUE (hotelid, total)
WITH base_hotel AS
  (SELECT TIMESTAMPDIFF(DAY, `begin-date`, `end-date`) AS count_days ,
          hotelid ,
          `room-number` AS room_number
   FROM RESERVATION),
     hotel_price AS
  (SELECT AVG(price) AS room_rate ,
          `hotel-id` AS hotel_id ,
          `number` AS room_number
   FROM ROOM
   GROUP BY hotel_id ,
            room_number)
SELECT hotelid ,
       SUM(room_revenue) AS total
FROM
  (SELECT base_hotel.hotelid ,
          base_hotel.room_number ,
          room_rate * count_days AS room_revenue
   FROM base_hotel
   INNER JOIN hotel_price ON base_hotel.room_number = hotel_price.room_number
   AND base_hotel.hotelid = hotel_price.hotel_id) AS calculated_room_rate
GROUP BY hotelid;




INSERT INTO ROOM VALUES (51, 'regular', 1, 2, 'queen', 2000, 02);
INSERT INTO CUSTOMER VALUES (03, 'customer_name_test', 'customer_street_test', 'customer_city_test', '20000', 'status_test');
INSERT INTO RESERVATION VALUES (02, 03, 51, '2018-12-19 09:26:03', '3000-12-19 09:26:03', '23232', '0624');




INSERT INTO ROOM VALUES (1, 'room_type_test', 1, 2,  'type_of_beds_test', -3, 02);


CALL Occupancy(02, '2019-12-19 09:26:03');


INSERT INTO ROOM VALUES (55, 'regular', 1, 2, 'queen', 1, 02);
