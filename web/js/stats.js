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

function handleData(data) {
    
}
