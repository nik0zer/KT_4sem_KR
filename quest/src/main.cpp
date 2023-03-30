#include <iostream>
#include "quest.h"

Quest build_quest()
{
    Quest quest("start", "win", "lose", "no such action here");

    std::shared_ptr<Room> room_1(new Room("entry room 1", "room 1:"));
    std::shared_ptr<Room> room_2(new Room("entry room 2", "room 2:"));
    std::shared_ptr<Room> room_3(new Room("entry room 3", "room 3:"));
    std::shared_ptr<Room> room_4(new Room("entry room 4", "room 4:"));

    std::shared_ptr<Action> move_to_1(new Move("move_to_room_1", "you move to room 1", NEUTRAL, room_1));
    std::shared_ptr<Action> move_to_2(new Move("move_to_room_2", "you move to room 2", NEUTRAL, room_2));
    std::shared_ptr<Action> move_to_3(new Move("move_to_room_3", "you move to room 3", NEUTRAL, room_3));
    std::shared_ptr<Action> move_to_4(new Move("move_to_room_4", "you move to room 4", NEUTRAL, room_4));
    std::shared_ptr<Action> drink_water(new Action("drink_water", "you drink the water", NEUTRAL));
    std::shared_ptr<Action> eat_food(new Interaction("eat_food_from_table", "food is over", NEUTRAL));
    std::shared_ptr<Action> raise_coin(new Interaction("raise_a_lucky_coin", "you've passed the maze", WIN));
    std::shared_ptr<Action> jump_to_hole(new Interaction("jump_to_hole", "you dead", LOSE));

    room_2->add_action(move_to_1);
    room_1->add_action(move_to_2);
    room_1->add_action(jump_to_hole);
    room_1->add_action(move_to_4);
    room_4->add_action(move_to_1);
    room_4->add_action(move_to_3);
    room_3->add_action(move_to_3);
    room_2->add_action(drink_water);
    room_2->add_action(move_to_3);
    room_3->add_action(move_to_2);
    room_3->add_action(eat_food);
    room_1->add_action(raise_coin);

    quest.add_room(room_1);
    quest.add_room(room_2);
    quest.set_start_room(room_1);
    return quest;
}

int main()
{
    auto quest = build_quest();
    quest.start_quest();
}