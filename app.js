const express = require('express');
const enableWs = require('express-ws')

const app = express();

var sharedVar = {};
var socketsList = [];

function removeItemOnce(arr, value) {
    var index = arr.indexOf(value);
    if (index > -1) {
        arr.splice(index, 1);
    }
    return arr;
}

function braoadcastAll(text) {
    socketsList.forEach(function iterate(socket) {
        socket.send(text);
    })
}

enableWs(app)

app.ws('/gameserver', (ws, req) => {
    socketsList.push(ws);
    ws.on('message', msg => {
        console.log(msg);
        braoadcastAll(msg)
    })

    ws.on('close', () => {
        console.log('WebSocket was closed')
        socketsList = removeItemOnce(socketsList, ws);
    })
})

app.use('/', express.static('web'));

const server = app.listen(3000);
