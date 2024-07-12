const mysql = require('mysql2');

const connection = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '2211',
  database: 'schooldb'
});

connection.connect((err) => {
  if (err) throw err;
  console.log('Connected to the database.');
});
 
const results = (query, params) => {
  return new Promise((resolve, reject) => {
    connection.query(query, params, (error, results) => {
      if (error) {
        return reject(error);
      }
      resolve(results);
    });
  });
};
 module.exports = { results };
