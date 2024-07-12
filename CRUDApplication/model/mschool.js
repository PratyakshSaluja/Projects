const { results } = require('../utils/db.js');

const executeProcedure = (recordType, name, email, gender, status) => {
  const procedure = 'CALL getvar(?, ?, ?, ?, ?)';
  const params = [recordType, name, email, gender, status];
  return results(procedure, params).then(data => data[0]); 
};


module.exports = {executeProcedure};
