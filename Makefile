devrun:
	make tg
	node app.js
run:
	make game
	node app.js
all:
	make game
game:
	make main
	make jsonPlayers
	make jsonGame
testdata:
	make ulistTest
	make gameBuildTest
	./gameC/genUlistTest
	./gameC/gameBuild
tg:
	make game
	make testdata
main:
	gcc gameC/game.c -o gameC/game -g
jsonPlayers:
	gcc gameC/jsonPlayersObj.c -o gameC/jsonPlayersObj -g
jsonGame:
	gcc gameC/jsonGameObj.c -o gameC/jsonGameObj -g
ulistTest:
	gcc gameC/genUlistTest.c -o gameC/genUlistTest -g
gameBuildTest:
	gcc gameC/gameBuild.c -o gameC/gameBuild -g

