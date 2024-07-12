const express = require('express');
const router = express.Router();
const { executeProcedure } = require('../model/mschool.js');

router.get('/', async (req, res) => {
  try {
    const users = await executeProcedure(7, null, null, null, null);
    res.render('index1', { results: users });
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

router.get('/form', (req, res) => {
  res.render('form', { user: null });
});

router.get('/edit/:name', async (req, res) => {
  const userName = req.params.name;
  try {
    const users = await executeProcedure(6, userName, null, null, null);
    console.log('Users:', users);
    if (users.length > 0) {
      res.render('form', { user: users[0] });
    } else {
      res.status(404).send('User not found');
    }
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

router.post('/add-user', async (req, res) => {
  const { name, email, gender, status } = req.body;
  try {
    await executeProcedure(3, name, email, gender, status);
    console.log(`User added with ID: ${name}`);
    res.redirect('/');
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

router.post('/update-user/:name', async (req, res) => {
  const oldName = req.params.name;
  const { name, email, gender, status } = req.body;
  try {
    await executeProcedure(5, oldName, email, gender, status);
    res.redirect('/');
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

router.delete('/delete-user/:name', async (req, res) => {
  const userName = req.params.name;
  try {
    await executeProcedure(4, userName, null, null, null);
    res.send('User deleted successfully');
  } catch (error) {
    console.error(error);
    res.status(500).send('Error deleting user');
  }
});

module.exports = router;
