#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <vector>
#include <memory>

class Room;
class Quest;
class Action;
class Interaction;
class Activation;

enum GAME_CONDITION
{
    START = -2,
    LOSE = -1,
    NEUTRAL = 0,
    WIN = 1
};

class Action
{
    protected:
    std::string _action_name;
    std::string _action_text;
    int _action_result;
    virtual int make_action(Quest& quest, Room& room);

    public:
    Action(std::string action_name, std::string action_text, int action_result) : 
    _action_name(action_name), _action_text(action_text), _action_result(action_result) {};

    friend Room;
    friend Interaction;
}; 

class Move : public Action
{
    private:
    std::shared_ptr<Room> _room;
    virtual int make_action(Quest& quest, Room& room) override;

    public:
    Move(std::string action_name, std::string action_text, int action_result, std::shared_ptr<Room> room) : 
    Action(action_name, action_text, action_result), _room(room){};
};

class Interaction : public Action
{
    protected:
    virtual int make_action(Quest& quest, Room& room) override;
};

class Deactivation : public Action
{
    protected:
    virtual int make_action(Quest& quest, Room& room) override;
    friend Activation;
};

class Activation : public Action
{
    protected:
    Deactivation _deactivation;
    virtual int make_action(Quest& quest, Room& room) override;
    Activation(std::string action_name, std::string action_text, int action_result, Deactivation deactivation) : 
    Action(action_name, action_text, action_result), _deactivation(deactivation){};
};


class Room
{
    private:
    std::string room_entry_message;
    void print_room_mesage();
    int make_action(std::string action_name, Quest& quest);
    std::vector<std::shared_ptr<Action>> _actions;

    public:
    void add_action(std::shared_ptr<Action> action);

    friend Quest;
    friend Interaction;
};

class Quest
{
    private:
    std::string _start_message;
    std::string _win_message;
    std::string _lose_message;
    void print_message(int condition_code);
    std::shared_ptr<Room> _start_room;
    std::shared_ptr<Room> _current_room;

    public:
    Quest(std::string start_message, std::string win_message, std::string lose_message, std::shared_ptr<Room> start_room) : 
    _start_message(start_message), _win_message(win_message), _lose_message(lose_message), _start_room(start_room) {};
    void start_quest();
    std::vector<std::shared_ptr<Room>> rooms;

    friend Move;
};


#endif