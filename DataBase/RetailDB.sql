CREATE DATABASE RetailDB;
USE RetailDB;

CREATE TABLE Customers(
customer_id INT PRIMARY KEY UNIQUE NOT NULL,
customer_name VARCHAR(100) NOT NULL,
email VARCHAR(100) UNIQUE NOT NULL CHECK (email LIKE '%@%.%'),
city VARCHAR(100),
gender CHAR(1) CHECK(gender IN ('M','F')),
registration_date DATE NOT NULL DEFAULT (CURRENT_DATE)   
);

CREATE TABLE Suppliers (
supplier_id INT PRIMARY KEY UNIQUE NOT NULL,
supplier_name VARCHAR(100) NOT NULL,
contact_email VARCHAR(100) UNIQUE,
city VARCHAR(100),
phone_number VARCHAR(100),
registration_date DATE NOT NULL DEFAULT (CURRENT_DATE)  
); 

CREATE TABLE Products(
product_id INT PRIMARY KEY UNIQUE NOT NULL,
product_name VARCHAR(100) NOT NULL,
category VARCHAR(100) NOT NULL, -- Electronics,Clothing,Grocery,Beauty,Stationery
price DECIMAL(12,2) NOT NULL CHECK(price >= 0),
stock_quantity INT NOT NULL DEFAULT 0 CHECK (stock_quantity >= 0),
is_active BOOLEAN DEFAULT TRUE,
supplier_id INT,
FOREIGN KEY (supplier_id) REFERENCES Suppliers(supplier_id)
);

CREATE TABLE Sales(
sale_id INT PRIMARY KEY UNIQUE NOT NULL,
customer_id INT NOT NULL,
product_id INT NOT NULL,
quantity INT NOT NULL CHECK( quantity > 0),
sale_date DATE NOT NULL DEFAULT (CURRENT_DATE),
FOREIGN KEY(customer_id) REFERENCES Customers(customer_id),
FOREIGN KEY(product_id) REFERENCES Products(product_id)
);

INSERT INTO Customers VALUES
(1,'Ali Adil','Ali@gmail.com','Multan','M','2023-04-10'),
(2,'Sara Khan','Sara@gmail.com','Karachi','F','2023-02-18'),
(3,'Bilal Sheikh','Bilal@gmail.com','Rawalpindi','M','2023-01-01'),
(4,'Ayesha Sarfaraz','Ayesha@gmail.com','Lahore','F','2023-04-19'),
(5,'Raza Mehdi','Raza@gmail.com','Sialkot','M','2023-09-18'),
(6,'Maheen Zahra','Maheen@gmail.com','Islamabad','F','2023-06-20'),
(7,'Jazim Abbas','Jazim@gmail.com','Sargodha','M','2024-09-05'),
(8,'Zainab Ali','Zainab@gmail.com','Faisalabad','F','2023-08-11'),
(9,'Raees Abbas','Raees@gmail.com','Islamabad','M','2023-05-22'),
(10,'Tooba Zafar','Tooba@gmail.com','Lahore','F','2023-02-23'),
(11,'Ahmad Abbas','Ahmad@gmail.com','Karachi','M','2023-11-12'),
(12,'Wajeeha Ali','Wajeeha@gmail.com','Sheikupura','F','2023-12-01'),
(13,'Murtaza Ali','Murtaza@gmail.com','Lahore','M','2024-01-15'),
(14,'Zoya Khan','Zoya@gmail.com','Peshawar','F','2024-02-20'),
(15,'Ghayoor Abbas','Ghayoor@gmail.com','Islamabad','M','2024-03-10'),
(16,'Nadia Mehmood','Nadia@gmail.com','Lahore','F','2024-04-05'),
(17,'Maryam Akmal','Maryam@gmail.com','Karachi','F','2024-05-12'),
(18,'Tehreem Kashan','Tehreem@gmail.com','Sawat','F','2024-06-18'),
(19,'Daniel Astridge','Daniel@gmail.com','Sargodha','M','2024-07-09'),
(20,'Mehak Imran','Mehak@gmail.com','Gujranwala','F','2024-08-25');

INSERT INTO Suppliers (supplier_id, supplier_name, contact_email, city, phone_number) VALUES
(1, 'Haier Home Appliances', 'supply@haier.com.pk', 'Lahore', '+92 42 3530111'),
(2, 'Gul Ahmed Textiles', 'vendors@gulahmed.com', 'Karachi', '+92 21 1114854'),
(3, 'Nestlé Pakistan Ltd', 'logistics@nestle.pk', 'Sheikhupura', '+92 56 3406600'),
(4, 'Unilever Beauty Care', 'orders@unilever.pk', 'Lahore', '+92 42 1118642'),
(5, 'Dollar Stationery Ltd', 'sales@dollar.com.pk', 'Sawat', '+92 21 3256110'),
(6, 'Samsung Mobile PK', 'partner@samsung.pk', 'Islamabad', '+92 51 2821100'),
(7, 'Junaid Jamshed J.', 'wholesale@jdot.com', 'Karachi', '+92 21 3438120'),
(8, 'National Foods Ltd', 'distrib@nfoods.com', 'Faisalabad', '+92 41 1116351'),
(9, 'Loreal Paris PK', 'pro@loreal.pk', 'Lahore', '+92 42 3517101'),
(10, 'Sayyed Stationery', 'contact@sayyed.com', 'Gujranwala', '+92 55 3254511'),
(11, 'Dawlance Home', 'support@dawlance.com', 'Peshawar', '+92 22 3881234'),
(12, 'Khaadi Retail', 'retail@khaadi.com', 'Karachi', '+92 21 1115421'),
(13, 'Shan Foods Global', 'export@shanfoods.com', 'Karachi', '+92 21 3505301'),
(14, 'Ponds Skincare', 'care@ponds.pk', 'Lahore', '+92 42 3575121'),
(15, 'Oxford University Press', 'edu@oup.pk', 'Rawalpindi', '+92 51 4425211'),
(16, 'Orient Electronics', 'info@orient.com.pk', 'Lahore', '+92 42 1111161'),
(17, 'Sana Safinaz', 'business@sanasafinaz.com', 'Karachi', '+92 21 1110033'),
(18, 'Olpers Dairy', 'fresh@olpers.com', 'Sargodha', '+92 40 4501231'),
(19, 'Rivaj Cosmetics', 'beauty@rivaj.pk', 'Lahore', '+92 42 3735012'),
(20, 'Pel Appliances', 'distribution@pel.com', 'Multan', '+92 61 4500121');

INSERT INTO Products VALUES
(101, 'Mechanical Keyboard', 'Electronics', 7500.00, 25, 1, 1),
(102, 'Wireless Mouse', 'Electronics', 1500.00, 40, 1, 6),
(103, 'HD Webcam 1080p', 'Electronics', 5500.00, 15, 1, 11),
(104, 'Bluetooth Headphones', 'Electronics', 12000.00, 10, 1, 16),
(105, 'Cotton Polo Shirt', 'Clothing', 1800.00, 60, 1, 2),
(106, 'Denim Jacket', 'Clothing', 4500.00, 20, 1, 7),
(107, 'Formal Trousers', 'Clothing', 3200.00, 35, 1, 12),
(108, 'Summer Lawn Suit', 'Clothing', 5500.00, 15, 1, 17),
(109, 'Basmati Rice 5kg', 'Grocery', 1450.00, 100, 1, 3),
(110, 'Cooking Oil 5L', 'Grocery', 2200.00, 80, 1, 8),
(111, 'Organic Honey 500g', 'Grocery', 950.00, 50, 1, 13),
(112, 'Green Tea Box', 'Grocery', 450.00, 120, 1, 18),
(113, 'Matte Lipstick', 'Beauty', 1100.00, 45, 1, 4),
(114, 'Hydrating Face Wash', 'Beauty', 850.00, 70, 1, 9),
(115, 'Sunscreen SPF 50', 'Beauty', 1250.00, 30, 1, 14),
(116, 'Moisturizing Lotion', 'Beauty', 1600.00, 25, 1, 19),
(117, 'A4 Paper Reem', 'Stationery', 1150.00, 200, 1, 5),
(118, 'Scientific Calculator', 'Stationery', 2800.00, 15, 1, 10),
(119, 'Gel Pen Set (12pcs)', 'Stationery', 600.00, 150, 1, 15),
(120, 'Hardcover Notebook', 'Stationery', 450.00, 90, 1, 20);

INSERT INTO Sales VALUES
(1, 1, 101, 2, '2025-01-06'), 
(2, 2, 105, 1, '2025-01-07'),  
(3, 4, 110, 3, '2025-01-08'), 
(4, 5, 120, 1, '2025-01-13'),   
(5, 1, 115, 2, '2025-01-14'),
(6, 8, 101, 1, '2025-01-15'),  
(7, 3, 108, 1, '2025-01-20'),   
(8, 10, 104, 1, '2025-01-21'),  
(9, 12, 112, 10, '2025-01-22'), 
(10, 15, 103, 2, '2025-02-03'), 
(11, 2, 101, 1, '2025-02-04'),  
(12, 17, 117, 5, '2025-02-05'),
(13, 19, 119, 1, '2025-02-10'), 
(14, 20, 106, 2, '2025-02-11'), 
(15, 1, 109, 1, '2025-02-12'), 
(16, 6, 113, 2, '2025-02-17'),  
(17, 9, 118, 1, '2025-02-18'),  
(18, 14, 104, 3, '2025-02-19'), 
(19, 11, 111, 4, '2025-02-24'), 
(20, 13, 116, 1, '2025-02-25');

-- Question no 01
SELECT DISTINCT city, gender
FROM Customers
ORDER BY city ASC, gender ASC;

-- Question no 02
SELECT 
    product_name, 
    price AS original_price, 
    (price * 0.90) AS discounted_price
FROM Products
WHERE is_active = 1 AND price > 1000
ORDER BY discounted_price DESC;

-- Question no 03
SELECT *
FROM Sales
WHERE quantity > 1 
  AND WEEKDAY(sale_date) <= 2  -- 0=Mon, 1=Tue, 2=Wed
ORDER BY sale_date DESC, quantity ASC;

-- Question no 04
SELECT 
    category, 
    COUNT(product_id) AS total_products, 
    SUM(stock_quantity) AS total_stocks
FROM Products
GROUP BY category
HAVING COUNT(product_id) > 2
ORDER BY total_products DESC;

-- Question no 05
SELECT 
    category, 
    AVG(price) AS average_price, 
    MAX(price) AS maximum_price
FROM Products
GROUP BY category
HAVING AVG(price) > 1000
ORDER BY average_price DESC;

-- Question no 06
SELECT 
    customer_id, 
    SUM(quantity) AS total_quantity_purchased, 
    COUNT(sale_id) AS number_of_orders
FROM Sales
WHERE quantity > 0
GROUP BY customer_id
ORDER BY total_quantity_purchased DESC;

-- Question no 07
SELECT 
    category, 
    MIN(price) AS minimum_price, 
    MAX(price) AS maximum_price, 
    AVG(price) AS average_price
FROM Products
GROUP BY category
HAVING MIN(price) < 5000
ORDER BY average_price DESC;

-- Question no 08
SELECT 
    product_id, 
    SUM(quantity) AS total_quantity_sold, 
    COUNT(DISTINCT customer_id) AS unique_customers
FROM Sales
GROUP BY product_id
HAVING SUM(quantity) > 2
ORDER BY total_quantity_sold DESC;

-- Question no 09
SELECT 
    product_id, 
    SUM(quantity) AS total_units_sold, 
    AVG(quantity) AS average_order_quantity
FROM Sales
GROUP BY product_id
HAVING SUM(quantity) > 1
ORDER BY total_units_sold DESC, average_order_quantity ASC;

-- Question no 10
SELECT *
FROM Sales
WHERE quantity > 1 
  AND sale_date BETWEEN '2025-01-01' AND '2025-03-01'
  AND sale_id % 2 = 0
ORDER BY sale_date DESC, quantity ASC;

-- Question no 11
SELECT 
    category, 
    SUM(stock_quantity) AS total_stock_quantity, 
    COUNT(product_id) AS total_products
FROM Products
GROUP BY category
HAVING SUM(stock_quantity) > 20
ORDER BY total_stock_quantity DESC;

-- Question no 12
SELECT 
    CONCAT(UPPER(SUBSTRING(customer_name, 1, 1)), LOWER(SUBSTRING(customer_name, 2))) AS formatted_customer_name,
    DATE_FORMAT(registration_date, '%b-%Y') AS registration_month_year
FROM Customers
WHERE registration_date < CURDATE()
ORDER BY registration_date DESC;
