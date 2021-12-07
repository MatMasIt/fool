class BootIntent {
    constructor() {

    }
    signUp(email, username, password) {
        this.destroy();
        localStorage.setItem("BootIntent", JSON.stringify({
            "action": "signup",
            "email": email,
            "username": username,
            "password": password
        }));
    }
    signIn(email, password) {
        this.destroy();
        localStorage.setItem("BootIntent", JSON.stringify({
            "action": "signin",
            "email": email,
            "password": password
        }));
    }
    commitGame() {
        location.href = "game.html";
    }
    load() {
        return JSON.parse(localStorage.getItem("BootIntent"));
    }
    destroy() {
        localStorage.removeItem("BootIntent");
    }
}