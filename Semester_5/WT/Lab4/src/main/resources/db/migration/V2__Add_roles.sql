CREATE TABLE IF NOT EXISTS `roles`
(
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `name` VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS `users_roles`
(
    `id` INT PRIMARY KEY AUTO_INCREMENT,
    `userId` INT NOT NULL,
    `roleId` INT NOT NULL,
    CONSTRAINT `fk_uId` FOREIGN KEY (`userId`) REFERENCES `users` (`id`),
    CONSTRAINT `fk_roleId` FOREIGN KEY (`roleId`) REFERENCES `roles` (`id`)
);