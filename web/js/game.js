var bi = new BootIntent();
if (!bi.load()) location.href = ".";
var writebuffer = "";
var delay = 10;
var audio = new Audio('old.mp3');
audio.loop = true;
function okPrint(k) {
    return "ABCDEFGHIJLKMNOPQRESTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890'ì!\"£$%&/()=?èéà°°#*€@.".split("").indexOf(k) != -1;
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
var bi = new BootIntent();
function startSocket() {
    gamefield.innerHTML = "";
    ws = new WebSocket("ws://localhost:3000/gameserver");

    ws.onopen = function () {
        let o = bi.load();
        switch (o["action"]) {
            case "signup":
                ws.send(o["action"] + "|" + o["email"].replace("|", "-") + "|" + o["username"].replace("|", "-") + "|" + o["password"].replace("|", "-"));
                break;
            case "signin":
                ws.send(o["action"] + "|" + o["email"].replace("|", "-") + "|N|" + o["password"].replace("|", "-"));
                break;
        }
    };

    ws.onmessage = function (event) {
        let splitMu = event.data.trim().split("mu|");
        var reconstructedText = "";
        if (splitMu.length > 1) {
            if (!event.data.trim().startsWith("mu|")) reconstructedText += splitMu[0];
            let lastD = "";
            splitMu.forEach(pCommand => {
                let dcomm = pCommand.split("|um")[0];
                if (dcomm.length) lastD = dcomm;
                if (pCommand.split("|um")[1]) reconstructedText += pCommand.split("|um")[1];
            });
            type(reconstructedText + "\n");
            audio.pause();
            audio.src = lastD + ".mp3";
            audio.currentTime = 0;
            audio.looping = 0;
            audio.play();
        }else if (event.data.trim() == "LOGOUT") {
            bi.destroy();
        }
        else if (event.data.trim() == "CLOSE") {
            ws.close();
            gamefield.innerHTML += "<br /><p style=\"color:red\">The server hanged up</p><br /><a href=\".\">Back</a>";
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

