create database game;

use game;

/*-------------------------------------------------PLAYER--------------------------------------------------*/

create table Player(
player_ID int auto_increment primary key,
Username varchar(255) not null,
Password varchar(255) not null,
Nickname varchar(255) not null
);

/*-------------------------------------------------LEVEL--------------------------------------------------*/

create table Levels (
Level_ID int auto_increment primary key,
Description varchar(255) not null
);

create table Level_Rounds(
Level_Round_ID int auto_increment primary key,
Level_ID int,
Player_ID int,
Score int,
foreign key(Level_ID) references Levels(Level_ID),
foreign key(Player_ID) references Player(Player_ID)
);

