CREATE DATABASE FinanceLab;
USE FinanceLab;

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

SELECT transaction_id, amount,
CASE 
    WHEN amount > 20000 THEN 'High'
    ELSE 'Normal'
END AS transaction_level
FROM Transactions;

SELECT transaction_id, amount,
CASE 
    WHEN amount < 5000 THEN 'Small'
    WHEN amount BETWEEN 5000 AND 20000 THEN 'Medium'
    ELSE 'Large'
END AS transaction_category
FROM Transactions;

SELECT transaction_id, transaction_date,
CASE
    WHEN YEAR(transaction_date) = 2025 THEN 'Recent'
    ELSE 'Old'
END AS transaction_period
FROM Transactions;

SELECT 
SUM(CASE WHEN transaction_type = 'Deposit' THEN amount ELSE 0 END) AS total_deposits,
SUM(CASE WHEN transaction_type = 'Withdrawal' THEN amount ELSE 0 END) AS total_withdrawals
FROM Transactions;

SELECT segment, COUNT(*) AS total_customers
FROM Customers
GROUP BY segment;

SELECT account_type,
SUM(opening_balance) AS total_balance,
AVG(interest_rate) AS avg_interest
FROM Accounts
GROUP BY account_type;

SELECT account_type,
SUM(opening_balance) AS total_balance
FROM Accounts
GROUP BY account_type
HAVING SUM(opening_balance) > 300000;

SELECT MONTH(transaction_date) AS month,
SUM(amount) AS total_deposits
FROM Transactions
WHERE transaction_type = 'Deposit'
GROUP BY MONTH(transaction_date)
HAVING SUM(amount) > 50000;

SELECT account_id,
SUM(CASE WHEN transaction_type='Deposit' THEN amount ELSE 0 END) AS total_deposits,
SUM(CASE WHEN transaction_type='Withdrawal' THEN amount ELSE 0 END) AS total_withdrawals,
COUNT(*) AS transaction_count
FROM Transactions
GROUP BY account_id
HAVING COUNT(*) > 1;

SELECT 
CASE 
    WHEN amount < 5000 THEN 'Small'
    WHEN amount BETWEEN 5000 AND 20000 THEN 'Medium'
    ELSE 'Large'
END AS transaction_category,
SUM(amount) AS total_amount
FROM Transactions
GROUP BY 
CASE 
    WHEN amount < 5000 THEN 'Small'
    WHEN amount BETWEEN 5000 AND 20000 THEN 'Medium'
    ELSE 'Large'
END;

SELECT city, COUNT(DISTINCT customer_id) AS total_customers
FROM Customers
GROUP BY city;

SELECT 
    DATE_FORMAT(transaction_date, '%b-%Y') AS month_year,
    SUM(amount) AS total_amount
FROM Transactions
WHERE YEAR(transaction_date) = 2024
GROUP BY DATE_FORMAT(transaction_date, '%b-%Y')
ORDER BY total_amount DESC;

SELECT 
    UPPER(city) AS city,
    COUNT(Customers.customer_id) AS total_customers,
    SUM(opening_balance) AS total_balance,
    CASE 
        WHEN AVG(opening_balance) > 100000 THEN 'High Value'
        ELSE 'Regular'
    END AS customer_segment
FROM Customers
WHERE YEAR(registration_date) >= 2024
GROUP BY UPPER(city)
ORDER BY total_balance DESC;
