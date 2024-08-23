CREATE DEFINER=`root`@`localhost` PROCEDURE `getvar`(
  IN recordType INT, 
  IN userName VARCHAR(255), 
  IN userEmail VARCHAR(255), 
  IN userGender VARCHAR(10), 
  IN userStatus VARCHAR(20)
)
BEGIN
  CASE recordType
    WHEN 1 THEN
      SELECT * FROM student;
    WHEN 2 THEN
      SELECT * FROM teacher;
    WHEN 3 THEN
      INSERT INTO userdb (Name, email, gender, status) VALUES (userName, userEmail, userGender, userStatus);
    WHEN 4 THEN
      DELETE FROM userdb WHERE Name = userName;
    WHEN 5 THEN
      UPDATE userdb SET email = userEmail, gender = userGender, status = userStatus WHERE Name = userName;
    WHEN 6 THEN
      SELECT * FROM userdb WHERE Name = userName;
      WHEN 7 THEN
      SELECT * FROM userdb;
    ELSE
      SELECT 'Invalid record type' AS message;
  END case;
END$$
DELIMITER ;

 
