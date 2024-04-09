-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 07, 2024 at 10:07 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pond_management`
--
CREATE DATABASE IF NOT EXISTS pond_management;


--
-- Database: `pond_management`
--
use pond_management;
-- --------------------------------------------------------

--
-- Table structure for table `parameters`
--

CREATE TABLE IF NOT EXISTS `parameters` (
  `parameter_id` varchar(10) NOT NULL,
  `name` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `ponds`
--

CREATE TABLE IF NOT EXISTS  `ponds` (
  `pond_id` varchar(20) NOT NULL,
  `name` varchar(60) NOT NULL,
  `location` varchar(30) NOT NULL,
  `created` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `reading`
--

CREATE TABLE IF NOT EXISTS  `reading` (
  `user_id` varchar(20) NOT NULL,
  `pond_id` varchar(20) NOT NULL,
  `parameter_id` varchar(10) NOT NULL,
  `readtime` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS  `users` (
  `user_id` varchar(20) NOT NULL,
  `name` varchar(60) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(255) NOT NULL,
  `last_pwd_change` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `parameters`
--
ALTER TABLE `parameters`
  ADD PRIMARY KEY (`parameter_id`);

--
-- Indexes for table `ponds`
--
ALTER TABLE `ponds`
  ADD PRIMARY KEY (`pond_id`);

--
-- Indexes for table `reading`
--
ALTER TABLE `reading`
  ADD KEY `user_id` (`user_id`),
  ADD KEY `pond_id` (`pond_id`),
  ADD KEY `parameter_id` (`parameter_id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`user_id`,`email`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `reading`
--
ALTER TABLE `reading`
  ADD CONSTRAINT `reading_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`),
  ADD CONSTRAINT `reading_ibfk_2` FOREIGN KEY (`pond_id`) REFERENCES `ponds` (`pond_id`),
  ADD CONSTRAINT `reading_ibfk_3` FOREIGN KEY (`parameter_id`) REFERENCES `parameters` (`parameter_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
