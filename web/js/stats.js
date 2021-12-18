function cloneO(a) {
    return JSON.parse(JSON.stringify(a));
}

function htmlEntities(str) {
    return String(str).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}
var gamedatafetcher = new XMLHttpRequest();
var url = "gamedata";

gamedatafetcher.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        var gamefile = JSON.parse(this.responseText);
        handleData(gamefile);
    }
};
gamedatafetcher.open("GET", url, true);
gamedatafetcher.send();

var userdatafetcher = new XMLHttpRequest();
var urlp = "playerdata";

userdatafetcher.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        var gamefile = JSON.parse(this.responseText);
        handlePlayers(gamefile);
    }
};
userdatafetcher.open("GET", urlp, true);


var itemsMap = {};
var roomsMap = {};
function handleData(data) {
    var finalData = ``;
    data["worlds"].forEach(function world(w) {
        finalData += `
        <div class="world">
        <h3>`+ htmlEntities(w["name"]) + `</h3>
        <i>`+ htmlEntities(w["desc"]) + `</i>
        <div class="rooms">`;
        roomsMap[w["ID"]] = cloneO(w);
        roomsMap[w["ID"]]["rooms"] = {};
        w["rooms"].forEach(function room(r) {
            roomsMap[w["ID"]]["rooms"][r["ID"]] = r;
            finalData += `
            <div class="room box">
                <h3>`+ htmlEntities(r["name"]) + `</h3>
                <div class="box-body">
                    <i>`+ htmlEntities(r["desc"]) + `</i>
                    <h4>Items</h4>
                    <p class="items">`;
            r["items"].forEach(function item(i, index) {
                itemsMap[i["ID"]] = i;
                finalData += `<b>Name</b> ` + htmlEntities(i["name"]) + `<br />
                        <b>Description</b> `+ htmlEntities(i["desc"]) + `<br />`;
                if (index != (r["items"].length - 1)) finalData += `<hr />`;

            });
            finalData += `</p>

                    <h4>Paths</h4>
                    <p class="paths">`;
            r["paths"].forEach(function path(p, index) {
                let direction = "", roomName = "";
                switch (p["dir"]) {
                    case "N":
                        direction = "North";
                        break;
                    case "S":
                        direction = "South";
                        break;
                    case "E":
                        direction = "East";
                        break;
                    case "W":
                        direction = "West";
                        break;

                }
                let it = 0;
                while (!roomName.length || it > w["rooms"].length - 1) {
                    if (!w["rooms"][it]) break;
                    if (w["rooms"][it]["ID"] == p["toRoomId"]) roomName = w["rooms"][it]["name"];
                    it++;
                }
                if (!roomName.length) roomName = "????";
                finalData += `<b>` + direction + `</b>, to <b>` + htmlEntities(roomName) + `</b>`;
                if (index != (r["paths"].length - 1)) finalData += `<br />`;

            });
            finalData += `</p>
                     </div>
                 </div>`;
        });
        finalData += `</div></div>`;
        userdatafetcher.send();
    });
    document.getElementById("gamesdisplay").innerHTML = finalData;
}
//creazione player
function handlePlayers(data) {
    var finalData = ``;
    data["users"].forEach(function user(u) {
        finalData += `
        <div class="user">
        <h3>`+ htmlEntities(u["username"]) + `</h3>
        <i>`+ htmlEntities(u["email"]) + `</i>
        <hr />
        <div class="SaveSlots">`;

        u["saveSlots"].forEach(function SaveSlot(s, i) {
            console.log(s);
            finalData += `
            <div class="SaveSlot box">
                <i>Slot <b>`+ (i + 1) + `</b></i>
                <h3>`+ htmlEntities(s["slotName"]) + `</h3>
                <div class="box-body">
                Last Seen in <i>`+ htmlEntities(roomsMap[s["worldId"]]["rooms"][s["roomId"]]["name"]) + `</i>
                    <h4>Items</h4>
                    <p class="items">`;
            s["items"].forEach(function item(i, index) {
                if (itemsMap[i["id"]]["name"]) {
                    finalData += htmlEntities(itemsMap[i["id"]]["name"]);
                }
                else {
                    finalData += `????`;
                }
                finalData += " (x <b>" + i["quantity"] + "</b>)";
                if (index != (s["items"].length - 1)) finalData += `<hr />`;
            });
            finalData += `</p>
                    </div>
                 </div>`;
        });
        finalData += `</div></div>`;
    });
    document.getElementById("playersdisplay").innerHTML = finalData;
}

