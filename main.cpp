#include <QApplication>
#include "game.h"
#include "littleMermaidGame.h"

Game * game; //game object pointer declared as global

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    // game = new Game();
    littleMermaidGame playGame;
    playGame.show();

    // game = new Game();
    //    game->show();

    return a.exec();
}
