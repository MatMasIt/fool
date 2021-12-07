var bi = new BootIntent();
document.querySelector("#signupForm").addEventListener("submit", function signin(event) {
    event.preventDefault();
    bi.signUp(
        document.querySelectorAll(".signupInput[name=email]")[0].value,
        document.querySelectorAll(".signupInput[name=username]")[0].value,
        document.querySelectorAll(".signupInput[name=password]")[0].value
    );
    bi.commitGame();
});
document.querySelector("#signinForm").addEventListener("submit", function signin(event) {
    event.preventDefault();
    bi.signIn(
        document.querySelectorAll(".signinInput[name=email]")[0].value,
        document.querySelectorAll(".signinInput[name=password]")[0].value
    );
    bi.commitGame();
});