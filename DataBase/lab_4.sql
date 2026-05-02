CREATE DATABASE LAB_4;
USE LAB_4;

CREATE TABLE Departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(50) NOT NULL UNIQUE
);
CREATE TABLE Students (
    student_id INT PRIMARY KEY AUTO_INCREMENT,
    student_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE,
    age INT CHECK (age >= 18),
    gender CHAR(1),
    dept_id INT,
    registration_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES Departments(dept_id)
);
CREATE TABLE Courses (
    course_id INT PRIMARY KEY AUTO_INCREMENT,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL CHECK (credits > 0),
    start_date DATE NOT NULL,
    end_date DATE NOT NULL,
    is_active BOOLEAN DEFAULT TRUE
);
CREATE TABLE Enrollments (
    enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
    student_id INT,
    course_id INT,
    enroll_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (student_id) REFERENCES Students(student_id),
    FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);

INSERT INTO Departments (dept_id, dept_name)
VALUES
(1, 'Computer Science'),
(2, 'Electrical Engineering'),
(3, 'Mechanical Engineering'),
(4, 'Civil Engineering'),
(5, 'Business Administration');
INSERT INTO Students
(student_id, student_name, email, age, gender, dept_id, registration_date)
VALUES
(1, 'Ali Khan', 'ali.khan@example.com', 20, 'M', 1, '2025-01-10'),
(2, 'Sara Ahmed', 'sara.ahmed@example.com', 22, 'F', 2, '2025-02-15'),
(3, 'Ayesha Malik', 'ayesha.m@example.com', 21, 'F', 2, '2025-03-01'),
(4, 'Bilal Shah', 'bilal.shah@example.com', 23, 'M', 1, '2025-04-10'),
(5, 'Nadia Khan', 'nadia.k@example.com', 19, 'F', 3, '2025-05-05'),
(6, 'Hamza Ali', 'hamza.ali@example.com', 24, 'M', 4, '2025-06-20'),
(7, 'Fatima Noor', 'fatima.n@example.com', 20, 'F', 1, '2025-07-11'),
(8, 'Omar Qureshi', 'omar.q@example.com', 21, 'M', 5, '2025-08-01'),
(9, 'Hina Iqbal', 'hina.iqbal@example.com', 22, 'F', 3, '2025-09-15'),
(10, 'Usman Riaz', 'usman.r@example.com', 23, 'M', 2, '2025-10-05');
INSERT INTO Courses
(course_id, course_name, credits, start_date, end_date, is_active)
VALUES
(1, 'Programming Fundamentals', 3, '2025-09-01', '2025-12-15', TRUE),
(2, 'Data Structures', 4, '2025-09-01', '2025-12-15', TRUE),
(3, 'Digital Electronics', 3, '2025-09-01', '2025-12-15', TRUE),
(4, 'Thermodynamics', 3, '2025-09-01', '2025-12-15', TRUE),
(5, 'Marketing Basics', 2, '2025-09-01', '2025-12-15', TRUE),
(6, 'Civil Engineering Drawing', 3, '2025-09-01', '2025-12-15', TRUE),
(7, 'Advanced Algorithms', 4, '2025-09-01', '2025-12-15', TRUE);

INSERT INTO Enrollments
(enrollment_id, student_id, course_id, enroll_date)
VALUES
(4, 3, 3, '2025-09-04'),
(5, 4, 2, '2025-09-05'),
(6, 5, 4, '2025-09-06'),
(7, 6, 6, '2025-09-07'),
(8, 7, 1, '2025-09-08'),
(9, 8, 5, '2025-09-09'),
(10, 9, 4, '2025-09-10'),
(11, 10, 3, '2025-09-11'),
(12, 2, 2, '2025-09-12'),
(13, 3, 1, '2025-09-13'),
(14, 4, 1, '2025-09-14'),
(15, 5, 2, '2025-09-15');

SELECT * FROM Students WHERE age > 21;
SELECT student_name, email
FROM Students
WHERE dept_id = 1;

SELECT * FROM Students
WHERE age >= 20 AND age <= 22;

SELECT * FROM Students
WHERE dept_id = 1 OR dept_id = 3;

SELECT * FROM Students
WHERE age BETWEEN 20 AND 22;

SELECT * FROM Students
ORDER BY age ASC;

SELECT student_name, age
FROM Students
ORDER BY student_name DESC;

SELECT CURDATE();
SELECT CURTIME();
SELECT student_name, CURDATE() AS Today FROM Students;
SELECT student_name, DATE_ADD(registration_date, INTERVAL 30 DAY) AS Next_Month FROM Students;
SELECT student_name, DATE_SUB(registration_date, INTERVAL 1 YEAR) AS Last_Year FROM Students;
SELECT student_name, DATEDIFF(CURDATE(), registration_date) AS Days_Since_Registration FROM Students;
SELECT student_name, YEAR(registration_date) AS Reg_Year FROM Students;
SELECT student_name, MONTH(registration_date) AS Reg_Month, DAY(registration_date) AS Reg_Day FROM Students;
SELECT DAYNAME('2025-02-10') AS Curr_Day;
SELECT DATE_FORMAT('2025-02-10', '%d-%m-%Y') as Curr_Date;
SELECT DATE_FORMAT('2025-02-10', '%m/%d/%Y') as Curr_Date;
SELECT DATE_FORMAT('2025-02-10', '%W, %d %M %Y')as Curr_Date;
SELECT DATE_FORMAT('2025-02-10', '%M %d, %Y') as Curr_Date;

SELECT student_name, registration_date
FROM Students
WHERE registration_date > '2025-03-01'
ORDER BY registration_date ASC;

SELECT *
FROM Students
WHERE (dept_id = 1 OR dept_id = 2)
AND age BETWEEN 20 AND 23;

SELECT student_name
FROM Students
WHERE YEAR(registration_date) = YEAR(CURDATE());

SELECT student_name,
DATE_ADD(registration_date, INTERVAL 6 MONTH) AS anniversary_date
FROM Students;

SELECT student_name, registration_date
FROM Students
WHERE DAYNAME(registration_date) = 'Monday';

SELECT student_name, DATEDIFF(CURDATE(), registration_date) AS days_passed
FROM Students
WHERE DATEDIFF(CURDATE(), registration_date) > 60;

SELECT student_name, age, registration_date
FROM Students
ORDER BY age ASC, registration_date DESC;

SELECT student_name, DATE_SUB(registration_date, INTERVAL 15 DAY) AS date_before_registration
FROM Students;

SELECT student_name, 25 - age AS years_to_25
FROM Students;

SELECT student_name, age, dept_id
FROM Students
WHERE dept_id = 1 AND age > 20;

SELECT student_name, dept_id
FROM Students
WHERE dept_id = 2 OR dept_id = 3;

SELECT student_name, dept_id
FROM Students
WHERE NOT dept_id = 3;

SELECT student_name, dept_id
FROM Students
ORDER BY student_name ASC;

SELECT CONCAT(student_name, ' ', email) AS Full_Nameid FROM Students;
SELECT student_name, LENGTH(student_name) AS Name_Length FROM Students;
SELECT TRIM(student_name) AS Trimmed_Name FROM Students;
SELECT student_name FROM Students WHERE student_name LIKE 'A%';
SELECT student_name FROM Students WHERE student_name LIKE '%K';
SELECT student_name FROM Students WHERE student_name LIKE '%ah%';
SELECT student_name, age + 1 AS Next_Year_Age FROM Students;
SELECT student_name, dept_id FROM Students WHERE dept_id IN (1, 3);
SELECT DISTINCT age FROM Students;
SELECT student_name, age + 1 AS Next_Age FROM Students;
SELECT course_name, credits * 2 AS Double_Credits FROM Courses;
SELECT student_name, dept_id FROM Students WHERE dept_id != 2;
SELECT DISTINCT dept_id FROM Students;
SELECT course_name, credits / 2 AS Half_Credits FROM Courses;
SELECT student_name, age, gender FROM Students WHERE age > 21 AND gender = 'F';
SELECT student_name, age + 2 AS Age_In_Two_Years FROM Students;
SELECT student_name, age * 2 AS Double_Age FROM Students;
SELECT student_name, dept_id, age FROM Students ORDER BY dept_id ASC, age DESC;
SELECT DISTINCT gender FROM Students;
SELECT student_name, age / 2 AS Half_Age FROM Students; 

SELECT student_name, UPPER(student_name) AS Upper_Name, LOWER(student_name) AS Lower_Name
FROM Students;

SELECT student_name, SUBSTRING(student_name, 1, 3) AS Short_Name
FROM Students;

SELECT student_name
FROM Students
WHERE student_name LIKE '%ah%';

SELECT age / 2 AS Half_Age FROM Students;

SELECT 
	student_name,
    UPPER(student_name) AS Full_name_upper,
    DATEDIFF(CURDATE(), registration_date) AS Days_Since_Registrations,
    MONTHNAME(registration_date) AS Registration_Month
FROM
	students
WHERE
	student_name LIKE 'A%';
    
SELECT 
	student_name,
    UPPER(CONCAT(student_name, ' ', email)) AS Full_name_upper,
    DATEDIFF(CURDATE(), registration_date) AS Days_Since_Registrations,
    MONTH(registration_date) AS Registration_Month
FROM
	students
WHERE
	student_name LIKE 'A%';