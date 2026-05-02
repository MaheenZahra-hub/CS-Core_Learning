CREATE DATABASE lab_09;
USE lab_09;

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

-- Basic CTE - High Value Cusomers
-- Finds high-value customers (balance > 200,000) and classifies them into tiers (Silver, Gold, Platinum).
WITH high_value_customers AS (
-- Creates a temporary result set (like a virtual table)
    SELECT 
        c.customer_id,
        c.customer_name,
        SUM(a.opening_balance) AS total_balance
    FROM Customers c
    JOIN Accounts a ON c.customer_id = a.customer_id
    GROUP BY c.customer_id, c.customer_name
    HAVING SUM(a.opening_balance) > 200000
)
SELECT 
    customer_name,
    total_balance,
-- Takes data from the CTE
    CASE 
        WHEN total_balance > 400000 THEN 'Platinum'
        WHEN total_balance > 300000 THEN 'Gold'
        WHEN total_balance > 200000 THEN 'Silver'
    END AS tier
FROM high_value_customers
ORDER BY total_balance DESC;


-- Multiple CTEs - Transaction Analysis
-- Calculate net flow for each account type
WITH deposits AS (
    SELECT 
        a.account_type,
        SUM(t.amount) AS total_deposits
    FROM Transactions t
    JOIN Accounts a ON t.account_id = a.account_id
    WHERE t.transaction_type = 'Deposit'
    GROUP BY a.account_type
-- Calculates total deposits per account type
),
withdrawals AS (
    SELECT 
        a.account_type,
        SUM(t.amount) AS total_withdrawals
    FROM Transactions t
    JOIN Accounts a ON t.account_id = a.account_id
    WHERE t.transaction_type = 'Withdrawal'
    GROUP BY a.account_type
-- Calculate total withdrawals per account type
)
SELECT 
    d.account_type,
    d.total_deposits,
    COALESCE(w.total_withdrawals, 0) AS total_withdrawals,
-- If no withdrawals exist for an account type → result = NULL,  NULL would break calculations, it Replaces NULL with 0
    d.total_deposits - COALESCE(w.total_withdrawals, 0) AS net_flow
-- Net Flow = Deposits − Withdrawals
FROM deposits d
LEFT JOIN withdrawals w ON d.account_type = w.account_type
-- LEFT JOIN, Ensures all deposit types are shown, Even if no withdrawals exist
ORDER BY net_flow DESC;

-- CTE Aggregation - Monthly Trends
-- Calculate month-over-month growth
WITH monthly_data AS (
    SELECT 
        DATE_FORMAT(transaction_date, '%Y-%m') AS month,
        SUM(CASE WHEN transaction_type = 'Deposit' THEN amount ELSE 0 END) AS deposits,
        SUM(CASE WHEN transaction_type = 'Withdrawal' THEN amount ELSE 0 END) AS withdrawals,
        COUNT(*) AS transaction_count
    FROM Transactions
    WHERE transaction_date >= '2024-01-01'
    GROUP BY DATE_FORMAT(transaction_date, '%Y-%m')
)
SELECT 
    month,
    deposits,
    withdrawals,
    deposits - withdrawals AS net_flow,
    transaction_count,
    LAG(deposits) OVER (ORDER BY month) AS previous_month_deposits,
-- LAG(deposits), looks at the previous row’s deposits 
-- OVER (ORDER BY month), defines the order (month-wise) 
-- AS previous_month_deposits , gives alias (column name)
    ROUND((deposits - LAG(deposits) OVER (ORDER BY month)) / 
          LAG(deposits) OVER (ORDER BY month) * 100, 2) AS growth_percentage
-- Growth % = ((Current - Previous) / Previous) × 100
-- First Month , no previous month data, its Null
FROM monthly_data
ORDER BY month;


-- CTE with CASE - Customer Segmentation
-- Segment customers based on balance and activity
WITH customer_metrics AS (
    SELECT 
        c.customer_id,
        c.customer_name,
        SUM(a.opening_balance) AS total_balance,
        COUNT(DISTINCT a.account_id) AS account_count,
        COUNT(t.transaction_id) AS transaction_count
    FROM Customers c
    LEFT JOIN Accounts a ON c.customer_id = a.customer_id
    LEFT JOIN Transactions t ON a.account_id = t.account_id
    GROUP BY c.customer_id, c.customer_name
    HAVING total_balance > 0
)
SELECT 
    customer_name,
    total_balance,
    account_count,
    transaction_count,
    CASE 
        WHEN total_balance >= 300000 THEN 'Premium'
        WHEN total_balance >= 100000 THEN 'Standard'
        ELSE 'Basic'
    END AS balance_tier,
    CASE 
        WHEN transaction_count >= 10 THEN 'Very Active'
        WHEN transaction_count >= 5 THEN 'Active'
        WHEN transaction_count >= 1 THEN 'Occasional'
        ELSE 'Inactive'
    END AS activity_level,
    CASE 
        WHEN total_balance >= 300000 AND transaction_count >= 5 THEN 'VIP'
        WHEN total_balance >= 100000 AND transaction_count >= 1 THEN 'Regular'
        ELSE 'Normal'
    END AS customer_segment
FROM customer_metrics
ORDER BY total_balance DESC
LIMIT 10;


-- Combining CTE, subquery, truncate
-- Monthly reporting process with data reset

-- Step 1: Create monthly report table
CREATE TABLE monthly_report (
    report_id INT PRIMARY KEY AUTO_INCREMENT,
    report_month VARCHAR(7),
    total_customers INT,
    total_accounts INT,
    total_balance DECIMAL(12,2),
	-- DECIMAL(12,2) means: 12 digits total, 2 digits after decimal
    active_customers INT,
    generated_date DATE
);
-- Step 2: CTE to calculate metrics
INSERT INTO monthly_report (report_month, total_customers, total_accounts, total_balance, active_customers, generated_date)
WITH current_metrics AS (
    SELECT 
        DATE_FORMAT(CURDATE(), '%Y-%m') AS report_month,
        COUNT(DISTINCT c.customer_id) AS total_customers,
        COUNT(a.account_id) AS total_accounts,
        SUM(a.opening_balance) AS total_balance,
        COUNT(DISTINCT CASE WHEN t.transaction_id IS NOT NULL THEN c.customer_id END) AS active_customers
-- Logic: If a transaction exists ,return customer_id 
-- If no transaction , return NULL
-- COUNT(DISTINCT ...)
-- Counts unique non-NULL values only
    FROM Customers c
    LEFT JOIN Accounts a ON c.customer_id = a.customer_id
    LEFT JOIN Transactions t ON a.account_id = t.account_id
        AND t.transaction_date >= DATE_FORMAT(CURDATE(), '%Y-%m-01')
)
-- Step 3: Insert into report
SELECT 
    report_month,
    total_customers,
    total_accounts,
    total_balance,
    active_customers,
    CURDATE()
FROM current_metrics;
-- Step 4: Check report
SELECT * FROM monthly_report;

-- Step 5: At month end, archive and reset
-- Create archive table
CREATE TABLE monthly_report_archive LIKE monthly_report;
-- is used to create a new table with the exact same structure as an existing table
-- Backup current month
INSERT INTO monthly_report_archive 
SELECT * FROM monthly_report 
WHERE report_month = DATE_FORMAT(CURDATE(), '%Y-%m');

-- Clear current month for next month
TRUNCATE TABLE monthly_report;


-- CTE with subquery
-- Write a query using CTE to find customers whose balance is above their city's average
WITH city_avg AS (
    SELECT 
        c.city,
        ROUND(AVG(a.opening_balance),2) AS avg_balance
    FROM Accounts a
    JOIN Customers c ON a.customer_id = c.customer_id
    GROUP BY c.city
),
-- 2nd CTE
customer_balances AS (
    SELECT 
        c.customer_name,
        c.city,
        SUM(a.opening_balance) AS total_balance
    FROM Customers c
    JOIN Accounts a ON c.customer_id = a.customer_id
    GROUP BY c.customer_id, c.customer_name, c.city
)
SELECT 
    cb.customer_name,
    cb.city,
    cb.total_balance,
    ca.avg_balance,
    CASE 
        WHEN cb.total_balance > ca.avg_balance THEN 'Above Average'
        ELSE 'Below Average'
    END AS status
FROM customer_balances cb
JOIN city_avg ca ON cb.city = ca.city
ORDER BY cb.city, cb.total_balance DESC;

-- nested query with truncate
-- Create a process to identify and archive inactive customers, then truncate temporary table
-- Create inactive customers table
CREATE TABLE inactive_customers (
    customer_id INT,
    customer_name VARCHAR(100),
    last_transaction_date DATE,
    days_inactive INT,
    archived_date DATE
);

-- Identify inactive customers (no transactions in last 90 days)
INSERT INTO inactive_customers (customer_id, customer_name, last_transaction_date, days_inactive, archived_date)
SELECT 
    c.customer_id,
    c.customer_name,
    MAX(t.transaction_date) AS last_transaction,
    DATEDIFF(CURDATE(), MAX(t.transaction_date)) AS days_inactive,
    CURDATE()
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
LEFT JOIN Transactions t ON a.account_id = t.account_id
GROUP BY c.customer_id, c.customer_name
HAVING days_inactive > 90 OR MAX(t.transaction_date) IS NULL;
-- Inactive for more than 90 days OR Never made any transaction
-- Check results
SELECT * FROM inactive_customers;

-- Clear temporary data (for next run)
TRUNCATE TABLE inactive_customers;
