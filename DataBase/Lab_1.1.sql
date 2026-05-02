CREATE DATABASE LAB_1;

USE LAB_1;
CREATE TABLE Students (
student_id INT,
first_name VARCHAR(50),
last_name VARCHAR(50),
email VARCHAR(100),
age INT,
gender char(1),
registration_date DATE 
);
CREATE TABLE Departments (
dept_id INT,
dept_name VARCHAR(50) 
);
DROP TABLE Students;
CREATE TABLE Students (
student_id INT PRIMARY KEY AUTO_INCREMENT,
first_name VARCHAR(50) NOT NULL,
last_name VARCHAR(50) NOT NULL,
email VARCHAR(100) UNIQUE,
age INT CHECK (age >= 18),
gender CHAR(1),
registration_date DATETIME DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE Courses (
course_id INT PRIMARY KEY AUTO_INCREMENT,
course_name VARCHAR(50) NOT NULL,
Credits INT CHECK(credits>1 and credits<5),
start_date DATE,
end_date DATE,
is_active BOOLEAN DEFAULT TRUE
);
DROP TABLE Courses;
DROP TABLE Departments;
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
INSERT INTO Departments (dept_id, dept_name)
VALUES (1, 'Computer Science');
INSERT INTO Students (student_name, email, age, dept_id)
VALUES ('Ali Khan', 'ali@example.com', 20, 1);
INSERT INTO Students (student_name, email, age, dept_id)
VALUES ('Ahmed', 'ahmed@example.com', 22, 5);
CREATE TABLE Enrollments (
enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
student_id INT NOT NULL,
dept_id INT NOT NULL,
enroll_date DATETIME DEFAULT CURRENT_TIMESTAMP,
FOREIGN KEY (student_id) REFERENCES Students(student_id),
FOREIGN KEY (dept_id) REFERENCES Departments(dept_id)
);
UPDATE Students SET email = 'ali.khan@university.edu' WHERE student_id = 1;
 UPDATE Students SET age = age + 1 WHERE dept_id = 1;
 UPDATE Students
SET dept_id = 2
WHERE student_id = 2;
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
DROP TABLE Students;