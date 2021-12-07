var xmlhttp = new XMLHttpRequest();
var url = "gamedata";

xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        var gamefile = JSON.parse(this.responseText);
        handleData(gamefile);
    }
};
xmlhttp.open("GET", url, true);
xmlhttp.send();

function htmlEntities(str) {
    return String(str).replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/"/g, '&quot;');
}

function handleData(data) {
    var finalData = ``;
    data["worlds"].forEach(function world(w) {
        finalData += `
        <div class="world">
        <h3>`+ htmlEntities(w["name"]) + `</h3>
        <i>`+ htmlEntities(w["desc"]) + `</i>
        <div class="rooms">`;

        w["rooms"].forEach(function room(r) {
            finalData += `
            <div class="room box">
                <h3>`+htmlEntities(r["name"])+`</h3>
                <div class="box-body">
                    <i>`+htmlEntities(r["desc"])+`</i>
                    <h4>Items</h4>
                    <p class="items">`;
                    r["items"].forEach(function item(i,index){
                        finalData+=`<b>Name</b> `+htmlEntities(i["name"])+`<br />
                        <b>Description</b> `+htmlEntities(r["desc"])+`<br />`;
                        if(index!=(r["items"].length-1)) finalData+=`<hr />`;

                    });
                    finalData+=`</p>

                    <h4>Paths</h4>
                    <p class="paths">`;
                    r["paths"].forEach(function path(p,index){
                        let direction="", roomName="";
                        switch(p["dir"]){
                            case "N":
                                direction="North";
                                break;
                            case "S":
                                direction="South";
                                break;
                            case "E":
                                direction="East";
                                break;
                            case "W":
                                direction="West";
                                break;
                            
                        }
                        let it=0;
                        while(!roomName.length || it > w["rooms"].length-1){
                            if(!w["rooms"][it]) break;
                            if(w["rooms"][it]["ID"]==p["toRoomId"]) roomName= w["rooms"][it]["name"];
                            it++;
                        }
                        if(!roomName.length) roomName="????";
                        finalData+=`<b>`+direction+`</b>, to <b>`+htmlEntities(roomName)+`</b>`;
                        if(index!=(r["paths"].length-1)) finalData+=`<br />`;

                    });
                    finalData+=`</p>
                     </div>
                 </div>`;
        });
        finalData += `</div></div>`;
    });
    document.getElementById("gamesdisplay").innerHTML = finalData;
}

