CREATE DATABASE lab_08;
USE lab_08;

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

-- Check data counts
SELECT 'Customers' AS Table_Name, COUNT(*) AS Total_Rows FROM Customers
UNION ALL
SELECT 'Accounts', COUNT(*) FROM Accounts
UNION ALL
SELECT 'Transactions', COUNT(*) FROM Transactions;

 -- Problem: Find all accounts that have balance more than the average balance
 -- Business Use: Identify high-value accounts
-- First, let's see the average balance
SELECT AVG(opening_balance) AS Average_Balance FROM Accounts;
-- Now find accounts above average
SELECT 
    account_id,
    account_type,
    opening_balance
FROM Accounts
WHERE opening_balance > (SELECT AVG(opening_balance) FROM Accounts)
ORDER BY opening_balance DESC;

-- Problem: Find the customer who has the highest total balance
-- Business Use: Identify the bank's top customer
SELECT 
    c.customer_id,
    c.customer_name,
    SUM(a.opening_balance) AS total_balance
-- Adds up all balances of a customer’s accounts, Gives total_balance per customer
FROM Customers c
JOIN Accounts a ON c.customer_id = a.customer_id
-- Joins the Customers table with Accounts, Each row in the result represents an account linked to a customer
GROUP BY c.customer_id, c.customer_name
--  Groups all accounts per customer
-- Aggregation functions like SUM() now operate per customer
HAVING SUM(a.opening_balance) = (
-- Filter groups (customers) whose total balance equals the maximum.
    SELECT MAX(total_balance)
-- Finds the highest total balance from all customers.
    FROM (
        SELECT SUM(opening_balance) AS total_balance
        FROM Accounts
        GROUP BY customer_id
-- Groups accounts per customer again (inside the subquery).
-- Calculates total balance for each customer.
    ) AS customer_totals
);

-- Problem: Find customers who joined after the average registration date
-- Business Use: Identify recent customers for welcome campaigns
SELECT 
    customer_id,
    customer_name,
    registration_date
FROM Customers
WHERE registration_date > (SELECT AVG(registration_date) FROM Customers)
ORDER BY registration_date DESC;

-- MULTI-ROW Subqueries

-- Problem: Find customers who have investment accounts
-- Business Use: Target investment customers for wealth management services
SELECT 
    customer_id,
    customer_name,
    city
FROM Customers
WHERE customer_id IN (
-- IN operator is used to check if a value matches any value in a list or subquery.
    SELECT DISTINCT customer_id
    FROM Accounts
    WHERE account_type = 'Investment'
)
ORDER BY customer_name;

-- Problem: Find customers who have made transactions over 20,000
-- Business Use: Identify high-value transaction customers
SELECT DISTINCT
    c.customer_name,
    c.city,
    c.segment
FROM Customers c
WHERE c.customer_id IN (
-- IN operator is used to check if a value matches any value in a list or subquery.
-- Filters only those customers whose IDs are returned in below mention middle query
    SELECT a.customer_id
    FROM Accounts a
    WHERE a.account_id IN (
-- Takes account IDs from Below mentioned query, Finds customer IDs who own those accounts
        SELECT t.account_id
        FROM Transactions t
        WHERE t.amount > 20000
    )
-- Finds all account IDs where a transaction amount is greater than 20,000
);

-- Problem: Find customers who have never made any transaction
-- Business Use: Identify inactive customers for engagement campaigns
SELECT 
    c.customer_id,
    c.customer_name,
    c.city,
    c.registration_date
FROM Customers c
WHERE c.customer_id NOT IN (
    SELECT DISTINCT a.customer_id
    FROM Accounts a
    JOIN Transactions t ON a.account_id = t.account_id
)
ORDER BY c.customer_name;

-- Problem: Format customer names for official letters
-- Business Use: Create standardized name formats
SELECT 
    customer_id,
    customer_name,
    UPPER(customer_name) AS uppercase_name,
    LOWER(customer_name) AS lowercase_name,
    CONCAT('Dear ', customer_name, ',') AS salutation
FROM Customers
LIMIT 5;

-- Problem: Extract first name from full name
-- Business Use: Personalized communication
SELECT 
    customer_name,
    SUBSTRING_INDEX(customer_name, ' ', 1) AS first_name,
    SUBSTRING_INDEX(customer_name, ' ', -1) AS last_name
FROM Customers
LIMIT 5;

-- Problem: Calculate length of customer names
-- Business Use: Check data quality and formatting
SELECT 
    customer_name,
    LENGTH(customer_name) AS name_length,
    CHAR_LENGTH(customer_name) AS character_count
FROM Customers
WHERE LENGTH(customer_name) > 10
ORDER BY name_length DESC;

-- Problem: Round balances for summary reports
-- Business Use: Create cleaner financial reports
SELECT 
    account_id,
    account_type,
    opening_balance,
    ROUND(opening_balance) AS rounded_balance,
    ROUND(opening_balance, -3) AS rounded_to_thousands,
    ROUND(opening_balance * 1.05, 2) AS balance_after_5_percent
FROM Accounts
WHERE account_type = 'Savings'
LIMIT 5;

-- Problem: Calculate summary statistics for each account type
-- Business Use: Understand portfolio distribution
SELECT 
    account_type,
    COUNT(*) AS number_of_accounts,
-- Counts how many rows (accounts) exist for each account type
    ROUND(AVG(opening_balance), 2) AS average_balance,
    ROUND(MIN(opening_balance), 2) AS minimum_balance,
    ROUND(MAX(opening_balance), 2) AS maximum_balance,
    ROUND(SUM(opening_balance), 2) AS total_balance
FROM Accounts
GROUP BY account_type;

-- Problem: Calculate what percentage each account type contributes
-- Business Use: Portfolio composition analysis
SELECT 
    account_type,
    ROUND(SUM(opening_balance), 2) AS total_balance,
    ROUND(SUM(opening_balance) / (SELECT SUM(opening_balance) FROM Accounts) * 100, 2) AS percentage
-- SUM(opening_balance), Total balance for current account type
-- (SELECT SUM(opening_balance) FROM Accounts), Total balance of all accounts in the table
FROM Accounts
GROUP BY account_type
ORDER BY percentage DESC;

-- Problem: Break down transaction dates into components
-- Business Use: Analyze patterns by month, day, year
SELECT 
    transaction_id,
    transaction_date,
    YEAR(transaction_date) AS year,
    MONTH(transaction_date) AS month,
    MONTHNAME(transaction_date) AS month_name,
    DAY(transaction_date) AS day,
    DAYNAME(transaction_date) AS day_name
FROM Transactions
WHERE transaction_date >= '2023-11-01'
ORDER BY transaction_date DESC
LIMIT 5;

-- Problem: Calculate how many days accounts have been open
-- Business Use: Track account maturity
SELECT 
    a.account_id,
    c.customer_name,
    a.account_type,
    a.open_date,
    DATEDIFF(CURDATE(), a.open_date) AS days_old,
-- days_old=today−open_date
    FLOOR(DATEDIFF(CURDATE(), a.open_date) / 30) AS months_old,
-- Converts days into months by dividing by 30 i.e 2190 days ÷ 30 = 73 months
    FLOOR(DATEDIFF(CURDATE(), a.open_date) / 365) AS years_old
-- Converts days into years by dividing by 365 i.e 2190 ÷ 365 = 6 years
-- Rounds down to nearest whole number
FROM Accounts a
JOIN Customers c ON a.customer_id = c.customer_id
WHERE a.account_type = 'Savings'
ORDER BY days_old DESC
LIMIT 5;

-- Problem: Calculate important future dates for accounts
-- Business Use: Plan follow-ups and reviews
SELECT 
    account_id,
    account_type,
    open_date,
    DATE_ADD(open_date, INTERVAL 1 YEAR) AS first_anniversary,
-- Adds 1 year to the open_date
    DATE_ADD(open_date, INTERVAL 6 MONTH) AS six_month_review,
-- Adds 6 months to the open_date
	DATE_ADD(open_date, INTERVAL 6 DAY) AS six_day_review,
-- Adds 6 days to the open_date
    LAST_DAY(open_date) AS month_end
-- Returns the last day of the month for the given date
FROM Accounts
WHERE account_type = 'Investment'
LIMIT 5;

-- Problem: Create a summary report for each customer showing their activity
-- Business Use: Customer dashboard
SELECT 
    c.customer_id,
    c.customer_name,
    COUNT(DISTINCT a.account_id) AS num_accounts,
-- Counts how many unique accounts each customer has.
-- DISTINCT avoids duplicate counting due to joins.
    ROUND(SUM(a.opening_balance), 2) AS total_balance,
-- sum of  balances from the  accounts.
-- Rounded to 2 decimal places
    COUNT(t.transaction_id) AS transaction_count,
-- Counts total number of transactions for the customer from transaction table
    ROUND(SUM(CASE WHEN t.transaction_type = 'Deposit' THEN t.amount ELSE 0 END), 2) AS total_deposits,
-- logic: If transaction is Deposit include amount , Otherwise  add 0
    ROUND(SUM(CASE WHEN t.transaction_type = 'Withdrawal' THEN t.amount ELSE 0 END), 2) AS total_withdrawals,
-- logic: If transaction is Withdrawal include amount , Otherwise  add 0
    MAX(t.transaction_date) AS last_transaction_date,
-- Finds the most recent transaction date for each customer.
    DATEDIFF(CURDATE(), MAX(t.transaction_date)) AS days_inactive
-- to see how long the customer has been inactive.
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
-- left join Keeps customers even if they don’t have accounts.
LEFT JOIN Transactions t ON a.account_id = t.account_id
-- Connects accounts to transactions.
-- Keeps accounts even if they have no transactions.
GROUP BY c.customer_id, c.customer_name
-- Groups all rows per customer
-- After grouping: SUM, COUNT, MAX work per customer
HAVING total_balance > 0
-- Filters after aggregation i.e in above query ROUND(SUM(a.opening_balance), 2) AS total_balance,
-- Keeps only customers whose total balance is greater than 0.
ORDER BY total_balance DESC
LIMIT 10;

-- Problem: Create a monthly summary of all transactions
-- Business Use: Monthly performance reporting
SELECT 
    DATE_FORMAT(transaction_date, '%Y-%m') AS month,
-- DATE_FORMAT() converts a date into a specific format '%Y-%m' → Year and month
    COUNT(*) AS transaction_count,
-- Counts total number of transactions in each month.Includes both deposits and withdrawals.
    ROUND(SUM(amount), 2) AS total_amount,
    ROUND(AVG(amount), 2) AS average_amount,
    SUM(CASE WHEN transaction_type = 'Deposit' THEN amount ELSE 0 END) AS deposits,
-- If transaction is Deposit include amount Otherwise add 0
    SUM(CASE WHEN transaction_type = 'Withdrawal' THEN amount ELSE 0 END) AS withdrawals
FROM Transactions
WHERE transaction_date >= '2024-01-01'
GROUP BY DATE_FORMAT(transaction_date, '%Y-%m')
-- Groups transactions by month.
-- All calculations (COUNT, SUM, AVG) are done per month.
ORDER BY month DESC;

-- Problem: Segment customers based on their total balance
-- Business Use: Targeted marketing
SELECT 
    c.customer_id,
    c.customer_name,
    ROUND(SUM(a.opening_balance), 2) AS total_balance,
    CASE 
        WHEN SUM(a.opening_balance) >= 300000 THEN 'Platinum'
        WHEN SUM(a.opening_balance) >= 150000 THEN 'Gold'
        WHEN SUM(a.opening_balance) >= 50000 THEN 'Silver'
        WHEN SUM(a.opening_balance) > 0 THEN 'Bronze'
        ELSE 'No Balance'
    END AS customer_tier,
    CASE 
        WHEN COUNT(t.transaction_id) >= 10 THEN 'Very Active'
        WHEN COUNT(t.transaction_id) >= 5 THEN 'Active'
        WHEN COUNT(t.transaction_id) >= 1 THEN 'Occasional'
        ELSE 'Inactive'
    END AS activity_level
FROM Customers c
LEFT JOIN Accounts a ON c.customer_id = a.customer_id
LEFT JOIN Transactions t ON a.account_id = t.account_id
-- Keeps all customers even if:No accounts, No transactions
GROUP BY c.customer_id, c.customer_name
-- Groups data per customer
-- Aggregates like SUM() and COUNT() work per customer
HAVING total_balance > 0
-- Removes customers with zero or NULL balance
-- HAVING clause is used to filter grouped data
ORDER BY total_balance DESC
LIMIT 10;
