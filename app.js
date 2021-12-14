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



enableWs(app)

app.ws('/gameserver', (ws, req) => {
    socketsList.push(ws);
    var bat = spawn('./gameC/game', ["aaa"]);
    ws.on('message', msg => {
        console.log(msg);
        bat.stdin.write(msg + "\n");
    })
    bat.stdout.on('data', (data) => {
        console.log(data.toString('utf-8'));
        ws.send(data.toString('utf-8'));
    });


    bat.on('exit', (code) => {
        console.log('WebSocket was closed')
        ws.send("CLOSE");
        ws.close();
    });

    ws.on('close', () => {
        console.log('WebSocket was closed')
        bat.kill('SIGINT');
        socketsList = removeItemOnce(socketsList, ws);
    })
})

app.get('/gamedata', (req, res) => {
    let proc = spawn('./gameC/jsonGameObj');
    res.set('Content-Type', 'application/json');
    proc.stdout.on('data', (data) => {
        res.send(data.toString('utf-8'));
    });
})

app.get('/playerdata', (req, res) => {
    let proc = spawn('./gameC/jsonPlayersObj');
    res.set('Content-Type', 'application/json');
    proc.stdout.on('data', (data) => {
        res.send(data.toString('utf-8'));
    });
})
app.use('/', express.static('web'));


const server = app.listen(3000);
