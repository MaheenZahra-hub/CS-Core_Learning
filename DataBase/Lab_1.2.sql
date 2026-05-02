CREATE DATABASE LAB_2;
USE LAB_2;

DROP TABLE Students;
CREATE TABLE Departments (
dept_id INT PRIMARY KEY AUTO_INCREMENT,
dept_name VARCHAR(50) NOT NULL UNIQUE
);
CREATE TABLE Students (
student_id INT PRIMARY KEY AUTO_INCREMENT,
student_name VARCHAR(50) NOT NULL,
email VARCHAR(100) UNIQUE,
age INT CHECK (age >= 18),
dept_id INT NOT NULL,
FOREIGN KEY (dept_id) REFERENCES Departments(dept_id)
);
CREATE TABLE Enrollments (
enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
student_id INT NOT NULL,
dept_id INT NOT NULL,
enroll_date DATETIME DEFAULT CURRENT_TIMESTAMP,
FOREIGN KEY (student_id) REFERENCES Students(student_id),
FOREIGN KEY (dept_id) REFERENCES Departments(dept_id)
);
INSERT INTO DEPARTMENTS (dept_id, dept_name)
VALUES
(101, 'Software Engineering'),
(102, 'Data Science'),
(103, 'Artificial Intelligence');
INSERT INTO STUDENTS (student_id, student_name, age, dept_id)
VALUES
(1, 'Ali Khan', 20, 101),
(2, 'Sara Ahmed', 21, 102),
(3, 'Hassan Raza', 22, 101),
(4, 'Ayesha Noor', 19, 103),
(5, 'Bilal Malik', 23, 102);
INSERT INTO ENROLLMENTS (enrollment_id, student_id, dept_id)
VALUES
(1, 1, 101),
(2, 2, 102),
(3, 3, 101),
(4, 4, 103);
UPDATE STUDENTS
SET dept_id = 103
WHERE student_id = 2;
UPDATE STUDENTS
SET age = 22
WHERE student_id = 1;
SET SQL_SAFE_UPDATES = 0;
UPDATE STUDENTS
SET age = age + 1;
DELETE FROM Students
WHERE student_id=5;
