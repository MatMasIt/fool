const express = require('express');
const enableWs = require('express-ws')

const app = express();

var sharedVar = {};

enableWs(app)

app.ws('/gameserver', (ws, req) => {
    ws.on('message', msg => {
        console.log(msg);
        ws.send(msg)
    })

    ws.on('close', () => {
        console.log('WebSocket was closed')
    })
})

app.use('/', express.static('web'));

const server = app.listen(3000);
