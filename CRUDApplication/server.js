const express = require('express');
const app = express();
const routes = require('./routes/routes'); // Import routes from routes.js

app.set('view engine', 'ejs');
app.set('views', __dirname + '/views');
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(express.static('public'));
app.use('/path/to/fontawesome', express.static(__dirname + '/node_modules/@fortawesome/fontawesome-free'));

// Use the routes defined in routes.js
app.use('/', routes);

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
