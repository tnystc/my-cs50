-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE  month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street';
--Gain general information from crime scene

SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021;
--Read the interviews with witnesses

SELECT license_plate, activity, hour, minute
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND year = 2021;
--Searching for possible suspect's plates using the information coming from wintesses

SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE license_plate = '5P2BI95' OR license_plate = '94KL13X'
OR license_plate = '6P58WS2' OR license_plate = '4328GD8'
OR license_plate = 'G412CB7' OR license_plate = 'L93JTIZ'
OR license_plate = '322W7JE' OR license_plate = '0NTHK55';
--people who exit the bakery after the crime within 10 minutes

SELECT person_id
FROM bank_accounts
WHERE account_number IN(
SELECT account_number
FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street');
--Thief withdraw some money according to Eugene's interview

SELECT id, caller, receiver, duration
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number
FROM people
WHERE license_plate = '5P2BI95' OR license_plate = '94KL13X'
OR license_plate = '6P58WS2' OR license_plate = '4328GD8'
OR license_plate = 'G412CB7' OR license_plate = 'L93JTIZ'
OR license_plate = '322W7JE' OR license_plate = '0NTHK55');
--find a match between license plates and calls, eliminate other suspects

--Diana and Bruce are suspects now

SELECT id, destination_airport_id, hour, minute
FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
AND origin_airport_id IN (SELECT id FROM airports WHERE city = 'Fiftyville');
--find the earliest tomorrow flight

SELECT *
FROM airports
WHERE id = 4;
--the city the thief escaped to ->new york city

SELECT name
FROM people
WHERE passport_number IN (
SELECT passport_number
FROM passengers
WHERE flight_id = 36);
--list of people in the plane
--Bruce is the only suspect in the plane -> Bruce is the thief

SELECT *
FROM people
WHERE name = 'Bruce';
--checking if there is one Bruce

SELECT name
FROM people
WHERE phone_number IN (
SELECT receiver
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (
SELECT phone_number
FROM people
WHERE name = 'Bruce'));
--finding the accomplice by looking phone calls with Bruce -> Robin is the accomplice
