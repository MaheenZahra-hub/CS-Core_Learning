CREATE DATABASE SQLLab_09;
USE SQLLab_09;

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

-- Simple transaction - Fund Transfer
-- Problem: Transfer money from one account to another
-- Business Use: Safe money transfer between accounts
-- Check balances before transfer
SELECT account_id, opening_balance 
FROM Accounts 
WHERE account_id IN (101, 102);
-- Start transaction
START TRANSACTION;
-- Deduct from account 101
UPDATE Accounts 
SET opening_balance = opening_balance - 20000 
WHERE account_id = 102;
-- Add to account 102
UPDATE Accounts 
SET opening_balance = opening_balance + 20000 
WHERE account_id = 101;
-- Check if everything looks correct
SELECT account_id, opening_balance 
FROM Accounts 
WHERE account_id IN (101, 102);
-- If all good, commit the transaction
COMMIT;
-- Finalize the transaction 
-- Changes are now: Permanent, Saved in database, Cannot be undone with ROLLBACK

-- Transaction with ROLLBACK (Error Handling)
-- Problem: Attempt a transfer that would cause negative balance
-- Business Use: Prevent invalid transactions
-- Check current balance
SELECT account_id, opening_balance 
FROM Accounts 
WHERE account_id = 101;
-- Start transaction
START TRANSACTION;
-- Try to withdraw more than available
UPDATE Accounts 
SET opening_balance = opening_balance - 100000 
WHERE account_id = 101;
-- Check balance (might be negative)
SELECT account_id, opening_balance 
FROM Accounts 
WHERE account_id = 101;
-- If balance becomes negative, undo the transaction
ROLLBACK;
-- Verify balance is restored
SELECT account_id, opening_balance 
FROM Accounts 
WHERE account_id = 101;

-- Transaction with Multiple Steps
-- Problem: Record a deposit and update account balance
-- Business Use: Complete deposit operation with logging
ALTER TABLE Transactions  -- adding new column
ADD COLUMN description VARCHAR(255);
-- Insert deposit transaction and update balance
START TRANSACTION;
-- Insert transaction record
INSERT INTO Transactions (transaction_id, account_id, transaction_type, amount, transaction_date, description)
VALUES (1051, 101, 'Deposit', 5000, CURDATE(), 'Cash Deposit');
-- Update account balance
UPDATE Accounts 
SET opening_balance = opening_balance + 5000 
WHERE account_id = 101;
-- Check if both operations were successful
SELECT 
    'Transaction Inserted' AS Status,
    (SELECT COUNT(*) FROM Transactions WHERE transaction_id = 1051) AS Transaction_Count,
    (SELECT opening_balance FROM Accounts WHERE account_id = 101) AS New_Balance;
-- Commit if everything is correct
COMMIT;

-- TRANSACTION WITHIN A PROCEDURE- TRANSFERING MONEY FROM ONE ACCOUNT TO THE OTHER
DELIMITER //
CREATE PROCEDURE TransferMoney()
-- Defines a stored procedure named TransferMoney
-- BEGIN ... END contains all the logic
BEGIN
    DECLARE sender_balance DECIMAL(10,2);
-- Creates a variable to store the sender’s balance
    -- Start transaction
    START TRANSACTION;
-- Changes are temporary 
-- Can be saved (COMMIT) or undone (ROLLBACK)
-- COMMIT → save changes permanently,  ROLLBACK → undo changes
    -- Get sender balance
    SELECT opening_balance 
    INTO sender_balance
    FROM Accounts
    WHERE account_id = 101;
    -- Condition check
    IF sender_balance < 10000 THEN
        -- Not enough balance → cancel transaction
        ROLLBACK;
-- Cancels the transaction. No money is deducted or added.  Database remains unchanged.
    ELSE
        -- Deduct from sender
        UPDATE Accounts 
        SET opening_balance = opening_balance - 10000
        WHERE account_id = 101;
        -- Add to receiver
        UPDATE Accounts 
        SET opening_balance = opening_balance + 10000
        WHERE account_id = 102;
        -- Save changes
        COMMIT;
-- Makes all updates permanent
    END IF;
END //
DELIMITER ;

-- VIEW
-- simple view example
-- Problem: Create a view showing only customer name and city (hide other details)
-- Business Use: For customer service representatives who don't need sensitive data
CREATE VIEW customer_basic_info AS
SELECT 
    customer_id,
    customer_name,
    city,
    segment
FROM Customers;
-- Now query the view like a table
SELECT * FROM customer_basic_info
ORDER BY city, customer_name
LIMIT 10;

-- View with Calculated Columns
-- Problem: Create a view showing account summary with calculated fields
-- Business Use: Quick access to account performance metrics
CREATE VIEW account_summary AS
SELECT 
    a.account_id,
    a.account_type,
    a.opening_balance,
    a.interest_rate,
    ROUND(a.opening_balance * a.interest_rate / 100, 2) AS yearly_interest,
    ROUND(a.opening_balance * a.interest_rate / 1200, 2) AS monthly_interest,
    c.customer_name,
    c.city
FROM Accounts a
JOIN Customers c ON a.customer_id = c.customer_id;
-- Query the view
SELECT * FROM account_summary
WHERE account_type = 'Savings'
ORDER BY yearly_interest DESC
LIMIT 5;

-- View with Joins (Simplifying Complex Queries)
-- Problem: Create a view that shows complete transaction details
-- Business Use: Easy access to transaction history with customer info
CREATE VIEW transaction_details AS
SELECT 
    t.transaction_id,
    t.transaction_date,
    t.transaction_type,
    t.amount,
    t.description,
    a.account_id,
    a.account_type,
    c.customer_name,
    c.city,
    c.segment
FROM Transactions t
JOIN Accounts a ON t.account_id = a.account_id
JOIN Customers c ON a.customer_id = c.customer_id;
-- Now simple query gives complete transaction history
SELECT * FROM transaction_details
WHERE transaction_date >= '2021-11-01'
ORDER BY transaction_date DESC
LIMIT 5;

