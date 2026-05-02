CREATE DATABASE FinanceOperator;
USE FinanceOperator;

CREATE TABLE Customers (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(100) NOT NULL,
    city VARCHAR(50),
    segment VARCHAR(20), -- Retail, Corporate, SME
    registration_date DATE NOT NULL
);

INSERT INTO Customers VALUES
(1,'Ali Khan','Lahore','Retail','2023-01-10'),
(2,'Sara Ahmed','Karachi','Corporate','2023-02-15'),
(3,'Bilal Sheikh','Islamabad','Retail','2023-03-01'),
(4,'Ayesha Malik','Lahore','SME','2023-04-12'),
(5,'Hassan Raza','Karachi','Retail','2023-05-18'),
(6,'Fatima Noor','Islamabad','Corporate','2023-06-20'),
(7,'Usman Tariq','Lahore','SME','2023-07-05'),
(8,'Zainab Ali','Karachi','Retail','2023-08-11'),
(9,'Omar Farooq','Islamabad','Corporate','2023-09-22'),
(10,'Mariam Saeed','Lahore','Retail','2023-10-30'),
(11,'Ahmad Javed','Karachi','SME','2023-11-12'),
(12,'Hira Shah','Islamabad','Retail','2023-12-01'),
(13,'Imran Iqbal','Lahore','Corporate','2024-01-15'),
(14,'Sana Tariq','Karachi','Retail','2024-02-20'),
(15,'Tariq Mehmood','Islamabad','SME','2024-03-10'),
(16,'Nadia Khan','Lahore','Retail','2024-04-05'),
(17,'Hamza Ali','Karachi','Corporate','2024-05-12'),
(18,'Kiran Malik','Islamabad','Retail','2024-06-18'),
(19,'Adnan Shah','Lahore','SME','2024-07-09'),
(20,'Mehak Raza','Karachi','Retail','2024-08-25');

CREATE TABLE Accounts (
    account_id INT PRIMARY KEY,
    customer_id INT,
    account_type VARCHAR(20), -- Savings, Current, Investment
    opening_balance DECIMAL(12,2),
    interest_rate DECIMAL(5,2),
    open_date DATE,
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id)
);

INSERT INTO Accounts VALUES
(101,1,'Savings',50000,5.5,'2023-01-15'),
(102,2,'Current',120000,0,'2023-02-20'),
(103,3,'Investment',200000,8.5,'2023-03-05'),
(104,4,'Savings',75000,5.5,'2023-04-18'),
(105,5,'Savings',60000,5.5,'2023-05-25'),
(106,6,'Investment',300000,9.0,'2023-06-25'),
(107,7,'Current',90000,0,'2023-07-12'),
(108,8,'Savings',45000,5.5,'2023-08-15'),
(109,9,'Investment',400000,8.0,'2023-09-30'),
(110,10,'Savings',55000,5.5,'2023-10-31'),
(111,11,'Current',110000,0,'2023-11-20'),
(112,12,'Savings',65000,5.5,'2023-12-10'),
(113,13,'Investment',250000,8.5,'2024-01-20'),
(114,14,'Savings',70000,5.5,'2024-02-25'),
(115,15,'Current',130000,0,'2024-03-15'),
(116,16,'Savings',48000,5.5,'2024-04-12'),
(117,17,'Investment',350000,9.2,'2024-05-20'),
(118,18,'Savings',52000,5.5,'2024-06-22'),
(119,19,'Current',80000,0,'2024-07-15'),
(120,20,'Savings',62000,5.5,'2024-08-28');

CREATE TABLE Transactions (
    transaction_id INT PRIMARY KEY,
    account_id INT,
    transaction_type VARCHAR(10), -- Deposit, Withdrawal
    amount DECIMAL(12,2),
    transaction_date DATE,
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
);

INSERT INTO Transactions VALUES
(1001,101,'Deposit',10000,'2024-01-05'),
(1002,101,'Withdrawal',5000,'2024-02-10'),
(1003,103,'Deposit',25000,'2024-03-15'),
(1004,104,'Deposit',12000,'2024-04-01'),
(1005,105,'Withdrawal',8000,'2024-04-10'),
(1006,106,'Deposit',50000,'2024-05-05'),
(1007,108,'Deposit',7000,'2024-05-12'),
(1008,109,'Withdrawal',20000,'2024-06-02'),
(1009,110,'Deposit',9000,'2024-06-20'),
(1010,112,'Deposit',15000,'2024-07-01'),
(1011,113,'Withdrawal',30000,'2024-07-10'),
(1012,114,'Deposit',11000,'2024-07-18'),
(1013,115,'Withdrawal',10000,'2024-08-05'),
(1014,116,'Deposit',6000,'2024-08-15'),
(1015,117,'Deposit',40000,'2024-08-22'),
(1016,118,'Withdrawal',7000,'2024-09-01'),
(1017,119,'Deposit',8000,'2024-09-10'),
(1018,120,'Deposit',10000,'2024-09-15'),
(1019,103,'Withdrawal',12000,'2024-09-20'),
(1020,106,'Withdrawal',15000,'2024-09-25');

TRUNCATE TABLE Transactions;

SET FOREIGN_KEY_CHECKS = 0;
TRUNCATE TABLE Accounts;
SET FOREIGN_KEY_CHECKS = 1;

SET FOREIGN_KEY_CHECKS = 0;
TRUNCATE TABLE Customers;
SET FOREIGN_KEY_CHECKS = 1;

SELECT 'Customers' AS Table_Name, COUNT(*) AS Row_Count FROM Customers
UNION ALL
SELECT 'Accounts', COUNT(*) FROM Accounts
UNION ALL
SELECT 'Transactions', COUNT(*) FROM Transactions;

INSERT INTO Customers (customer_id, customer_name, city, segment, registration_date) VALUES
(1, 'Ali Khan', 'Lahore', 'Retail', '2023-01-15'),
(2, 'Sara Ahmed', 'Karachi', 'Corporate', '2023-02-20'),
(3, 'Bilal Sheikh', 'Islamabad', 'Retail', '2023-03-10'),
(4, 'Ayesha Malik', 'Lahore', 'SME', '2023-04-05'),
(5, 'Hassan Raza', 'Karachi', 'Retail', '2023-05-12'),
(6, 'Fatima Noor', 'Islamabad', 'Corporate', '2023-06-18'),
(7, 'Usman Tariq', 'Lahore', 'SME', '2023-07-22'),
(8, 'Zainab Ali', 'Karachi', 'Retail', '2023-08-30'),
(9, 'Omar Farooq', 'Islamabad', 'Corporate', '2023-09-14'),
(10, 'Mariam Saeed', 'Lahore', 'Retail', '2023-10-25'),
(11, 'Ahmad Javed', 'Karachi', 'SME', '2023-11-08'),
(12, 'Hira Shah', 'Islamabad', 'Retail', '2024-01-05'),
(13, 'Imran Iqbal', 'Lahore', 'Corporate', '2024-02-18'),
(14, 'Sana Tariq', 'Karachi', 'Retail', '2024-03-22'),
(15, 'Tariq Mehmood', 'Islamabad', 'SME', '2024-04-10'),
(16, 'Bob Khan', 'Karachi', 'Retail', '2023-01-15'),
(17, 'George Bush', 'London', 'SME', '2023-01-15');
-- Verify insertion (by default: asc)
SELECT * FROM Customers ORDER BY customer_id;

-- Insert 17 accounts (some customers have multiple accounts)
INSERT INTO Accounts (account_id, customer_id, account_type, opening_balance, interest_rate, open_date) VALUES
-- Customer 1 has 2 accounts (for SELF JOIN examples)
(101, 1, 'Savings', 50000.00, 5.5, '2023-01-20'),
(102, 1, 'Investment', 150000.00, 8.5, '2024-06-15'),
-- Customer 2
(103, 2, 'Current', 120000.00, 0, '2023-02-25'),
-- Customer 3 has 2 accounts
(104, 3, 'Investment', 200000.00, 8.5, '2023-03-15'),
(105, 3, 'Savings', 25000.00, 5.5, '2024-07-20'),
-- Customer 4
(106, 4, 'Savings', 75000.00, 5.5, '2023-04-10'),
-- Customer 5
(107, 5, 'Savings', 60000.00, 5.5, '2023-05-20'),
-- Customer 6
(108, 6, 'Investment', 300000.00, 9.0, '2023-06-25'),
-- Customer 7
(109, 7, 'Current', 90000.00, 0, '2023-07-15'),
-- Customer 8
(110, 8, 'Savings', 45000.00, 5.5, '2023-08-20'),
-- Customer 9
(111, 9, 'Investment', 400000.00, 8.0, '2023-09-25'),
-- Customer 10
(112, 10, 'Savings', 55000.00, 5.5, '2023-10-28'),
-- Customer 11
(113, 11, 'Current', 110000.00, 0, '2023-11-15'),
-- Customer 12
(114, 12, 'Savings', 65000.00, 5.5, '2024-01-10'),
-- Customer 13
(115, 13, 'Investment', 250000.00, 8.5, '2024-02-20'),
-- Customer 14 (new account, no transactions yet)
(116, 14, 'Savings', 70000.00, 5.5, '2024-03-25'),
-- Customer 15 (new account, no transactions yet)
(117, 15, 'Current', 130000.00, 0, '2024-04-15');
-- Verify insertion
SELECT COUNT(*) AS Account_Count FROM Accounts;
SELECT * FROM Accounts ORDER BY account_id;

INSERT INTO Transactions (transaction_id, account_id, transaction_type, amount, transaction_date) VALUES
-- Account 101 (Savings - Ali Khan) - Multiple transactions
(2001, 101, 'Deposit', 15000.00, '2024-01-10'),
(2002, 101, 'Withdrawal', 5000.00, '2024-02-15'),
(2003, 101, 'Deposit', 10000.00, '2024-03-20'),
-- Account 102 (Investment - Ali Khan)
(2004, 102, 'Deposit', 25000.00, '2024-07-01'),
(2005, 102, 'Withdrawal', 10000.00, '2024-08-15'),
-- Account 103 (Current - Sara Ahmed)
(2006, 103, 'Withdrawal', 15000.00, '2024-01-25'),
(2007, 103, 'Deposit', 20000.00, '2024-02-28'),
-- Account 104 (Investment - Bilal Sheikh)
(2008, 104, 'Deposit', 50000.00, '2024-03-10'),
-- Account 106 (Savings - Ayesha Malik)
(2009, 106, 'Deposit', 12000.00, '2024-04-05'),
-- Account 108 (Investment - Fatima Noor)
(2010, 108, 'Deposit', 60000.00, '2024-05-15'),
(2011, 108, 'Withdrawal', 20000.00, '2024-06-20'),
-- Account 111 (Investment - Omar Farooq)
(2012, 111, 'Withdrawal', 30000.00, '2024-07-10'),
-- Account 113 (Current - Ahmad Javed)
(2013, 113, 'Deposit', 25000.00, '2024-08-05'),
-- Account 114 (Savings - Hira Shah)
(2014, 114, 'Deposit', 8000.00, '2024-09-01'),
(2015, 114, 'Withdrawal', 3000.00, '2024-10-15'),
-- Account 115 (Investment - Imran Iqbal)
(2016, 115, 'Deposit', 40000.00, '2024-11-01'),
(2017, 115, 'Withdrawal', 15000.00, '2024-11-20');
-- Note: Accounts 105, 107, 109, 110, 112, 116, 117 have no transactions (for LEFT JOIN examples)
-- Verify insertion
SELECT COUNT(*) AS Transaction_Count FROM Transactions;
SELECT * FROM Transactions ORDER BY transaction_id;

-- cross join
SELECT * 
FROM Customers, Accounts, Transactions
WHERE Customers.customer_id = Accounts.customer_id 
  AND Accounts.account_id = Transactions.account_id AND Customers.customer_id=1 AND 
Transactions.transaction_date>'2024-01-01';

-- inner join
-- use case: Find customers who have active accounts and their account details
-- Query: List all customers and their account information
SELECT 
    c.customer_id,
    c.customer_name,
    c.city,
    a.account_id,
    a.account_type,
    a.opening_balance,
    a.open_date
FROM Customers c
INNER JOIN Accounts a ON c.customer_id = a.customer_id
ORDER BY c.customer_name;

-- inner join with aggregation - account summary
-- Query: Show each customer with their number of accounts and total balance
SELECT 
    c.customer_id,
    c.customer_name,
    COUNT(a.account_id) AS total_accounts,
    SUM(a.opening_balance) AS total_balance,
    AVG(a.opening_balance) AS avg_balance_per_account
FROM Customers c
INNER JOIN Accounts a ON c.customer_id = a.customer_id
GROUP BY c.customer_id, c.customer_name
ORDER BY total_balance DESC;

-- inner join with multiple conditions - city-wise analysis
-- Query: Find customers from Lahore with Savings accounts
SELECT 
    c.customer_name,
    c.city,
    a.account_id,
    a.account_type,
    a.opening_balance
FROM Customers c
INNER JOIN Accounts a ON c.customer_id = a.customer_id
WHERE c.city = 'Lahore' 
  AND a.account_type = 'Savings'
ORDER BY a.opening_balance DESC;

-- inner join with three tables - complete transactions history
-- Query: Show transaction details with customer and account information
SELECT 
    t.transaction_id,
    t.transaction_date,
    t.transaction_type,
    t.amount,
    a.account_type,
    c.customer_name,
    c.city
FROM Transactions t
INNER JOIN Accounts a ON t.account_id = a.account_id
INNER JOIN Customers c ON a.customer_id = c.customer_id
WHERE t.transaction_date >= '2024-10-01'
ORDER BY t.transaction_date DESC;

-- LEFT JOIN
-- Use Case: Identify customers without accounts for marketing campaigns.

-- left join - all customers with account information
-- Query: List all customers, show account details if they have accounts
SELECT 
    c.customer_id,
    c.customer_name,
    c.city,
    c.registration_date,
    a.account_id,
    a.account_type,
    a.opening_balance
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
ORDER BY c.customer_id;

-- left join with WHERE - customers without accounts
-- Query: Find customers who have NO accounts (for cross-selling)
SELECT 
    c.customer_id,
    c.customer_name,
    c.city,
    c.segment,
    c.registration_date
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
WHERE a.account_id IS NULL;

-- left join with aggregation - customer account summary
-- Query: Show all customers with their account statistics (including those without accounts)
SELECT 
    c.customer_id,
    c.customer_name,
    c.city,
    c.segment,
    COUNT(a.account_id) AS num_accounts,
    IFNULL(SUM(a.opening_balance), 0) AS total_balance,
    IFNULL(MAX(a.opening_balance), 0) AS max_balance,
    IFNULL(MIN(a.opening_balance), 0) AS min_balance
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
GROUP BY c.customer_id, c.customer_name, c.city, c.segment
ORDER BY total_balance DESC;

-- left join with date filter - recent customer activity
-- Query: Show customers registered in 2024 with their transaction activity
SELECT 
    c.customer_name,
    c.registration_date,
    a.account_id,
    COUNT(t.transaction_id) AS transaction_count,
    IFNULL(SUM(t.amount), 0) AS total_transaction_amount
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
LEFT JOIN Transactions t ON a.account_id = t.account_id
WHERE YEAR(c.registration_date) = 2024
GROUP BY c.customer_name, c.registration_date, a.account_id
ORDER BY c.registration_date;

-- RIGHT JOIN
-- Use Case: When you want all records from the table on the right side of the join.

-- right join - all account with customer information
-- Query: Show all accounts and their customer details
SELECT 
    a.account_id,
    a.account_type,
    a.opening_balance,
    c.customer_name,
    c.city,
    c.segment
FROM Customers c
RIGHT JOIN Accounts a ON c.customer_id = a.customer_id
ORDER BY a.opening_balance DESC;

-- right join with aggregation - account type summary
-- Query: Show all account types with customer count and average balance
SELECT 
    a.account_type,
    COUNT(DISTINCT a.account_id) AS total_accounts,
    COUNT(DISTINCT c.customer_id) AS unique_customers,
    AVG(a.opening_balance) AS avg_balance,
    SUM(a.opening_balance) AS total_balance
FROM Customers c
RIGHT JOIN Accounts a ON c.customer_id = a.customer_id
GROUP BY a.account_type;

-- SELF JOIN
-- Use Case: Find customers who registered in the same month or have similar patterns

-- self join -customers in same city
-- Query: Find pairs of customers from the same city
SELECT 
    c1.customer_name AS Customer1,
    c2.customer_name AS Customer2,
    c1.city AS City,
    c1.segment AS Segment1,
    c2.segment AS Segment2
FROM Customers c1
INNER JOIN Customers c2 ON c1.city = c2.city AND c1.customer_id < c2.customer_id
ORDER BY c1.city, Customer1;

-- self join - customers registered in same month
-- Query: Find customers who registered in the same month and year
SELECT 
    c1.customer_name AS Customer1,
    c2.customer_name AS Customer2,
    c1.registration_date AS Date1,
    c2.registration_date AS Date2,
    MONTHNAME(c1.registration_date) AS Month,
    YEAR(c1.registration_date) AS Year
FROM Customers c1
INNER JOIN Customers c2 
    ON MONTH(c1.registration_date) = MONTH(c2.registration_date)
    AND YEAR(c1.registration_date) = YEAR(c2.registration_date)
    AND c1.customer_id < c2.customer_id
ORDER BY Year DESC, Month, Customer1;

-- self join with different segments
-- Query: Find customers from same city but different segments (for cross-selling)
SELECT 
    c1.customer_name AS Retail_Customer,
    c2.customer_name AS Corporate_Customer,
    c1.city AS City
FROM Customers c1
INNER JOIN Customers c2 
    ON c1.city = c2.city 
    AND c1.segment = 'Retail' 
    AND c2.segment = 'Corporate'
    AND c1.customer_id != c2.customer_id
ORDER BY c1.city;