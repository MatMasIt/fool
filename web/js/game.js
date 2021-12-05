var writebuffer = "";
var delay = 10;
var audio = new Audio('old.mp3');
audio.loop = true;
function okPrint(k) {
    return "ABCDEFGHIJLKMNOPQESTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890'ì!\"£$%&/()=?èéà°°#*€@".split("").indexOf(k) != -1;
}

if (!String.prototype.replaceAll) {
    String.prototype.replaceAll = function (str, newStr) {

        // If a regex pattern
        if (Object.prototype.toString.call(str).toLowerCase() === '[object regexp]') {
            return this.replace(str, newStr);
        }

        // If a string
        return this.replace(new RegExp(str, 'g'), newStr);

    };
}
var gamefield = document.getElementById("field"), busy = true, first = true;
setInterval(function type() {
    if (first) {
        busy = true;
        return false;
    }
    else if (writebuffer[0] == undefined) {
        busy = false;
        return false;
    }
    busy = true;
    if (writebuffer[0] == "\n") gamefield.innerHTML += "<br>";
    else if (writebuffer[0] == " ") gamefield.innerHTML += "&nbsp;";
    else gamefield.innerHTML += writebuffer[0];
    writebuffer = writebuffer.substring(1);
}, delay);
function type(text) {
    if (gamefield.innerHTML.slice(gamefield.innerHTML.length - 4) != "<br>") writebuffer += "\n" + text;
    else writebuffer += text;
}
var ws;
function startSocket() {
    gamefield.innerHTML = "";
    ws = new WebSocket("ws://localhost:3000/gameserver");

    ws.onopen = function () {
        ws.send("Hi, from the client."); // this works

    };

    ws.onmessage = function (event) {
        if (event.data.trim().split("|")[0] == "mu"){
            audio.pause();
            audio.src=event.data.trim().split("|")[1]+".mp3";
            audio.currentTime=0;
            audio.play();
        }
        else if (event.data.trim() == "CLOSE") {
            ws.close();
            gamefield.innerHTML+="<br /><p style=\"color:red\">The server hanged up</p>";
        }
        else {
            type(event.data + "\n");
        }
    };


}
document.addEventListener('keydown', function pressed(key) {
    if (first) {
        audio.play();
        startSocket();
        first = false;
    }
    if (busy) return false;
    let rows = gamefield.innerHTML.split("<br>");
    rows[rows.length - 1] = rows[rows.length - 1].replace('<span class="userinput">', "").replace('</span>', "");
    if (key.key.toLocaleLowerCase() == "backspace" && gamefield.innerHTML.slice(gamefield.innerHTML.length - 4) != "<br>") rows[rows.length - 1] = rows[rows.length - 1].slice(0, -1);
    else if (key.key.toLocaleLowerCase() == "enter") {
        let t = rows[rows.length - 1];
        rows[rows.length - 1] += "<br>";
        ws.send(t.replaceAll("&nbsp;", " ").replace("</span>", ""));
    }
    else if (key.key.toLocaleLowerCase() == " ") rows[rows.length - 1] += "&nbsp;";
    else if (okPrint(key.key)) rows[rows.length - 1] += key.key;
    rows[rows.length - 1] = '<span class="userinput">' + rows[rows.length - 1] + '</span>';
    gamefield.innerHTML = rows.join("<br/>");
});
