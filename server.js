// Express
const express = require('express');
const app = express();

// Serve static files from /public
app.use(express.static('public'));

// Start server on port 2222
app.listen(2222, () => {
    console.log('Server is running on port 2222!');
});
