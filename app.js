const express = require('express');
const enableWs = require('express-ws')
const { spawn } = require('child_process');
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
    var bat = spawn('./gameC/game');
    ws.on('message', msg => {
        console.log(msg);
        bat.stdin.write(msg+"\n");
        //braoadcastAll(msg)    
    })
    bat.stdout.on('data', (data) => {
        console.log(data.toString('utf-8'));
        ws.send(data.toString('utf-8'));
    });

    ws.on('close', () => {
        console.log('WebSocket was closed')
        bat.kill('SIGINT');
        socketsList = removeItemOnce(socketsList, ws);
    })
})

app.use('/', express.static('web'));

const server = app.listen(3000);
