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
    NO_SUCH_ACTION = -3,
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

    public:
    Interaction(std::string action_name, std::string action_text, int action_result) : 
    Action(action_name, action_text, action_result){};
};

class Deactivation : public Action
{
    protected:
    virtual int make_action(Quest& quest, Room& room) override;
    friend Activation;

    public:
    Deactivation(std::string action_name, std::string action_text, int action_result) : 
    Action(action_name, action_text, action_result){};
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
    std::string _room_entry_message;
    std::string _room_message;
    int make_action(std::string action_name, Quest& quest);
    std::vector<std::shared_ptr<Action>> _actions;

    public:
    Room(std::string room_entry_message, std::string room_message) :
    _room_entry_message(room_entry_message), _room_message(room_message) {};

    void add_action(std::shared_ptr<Action> action);
    void print_room_entry_mesage();
    void print_room_mesage();
    void print_actions();

    friend Quest;
    friend Interaction;
};

class Quest
{
    private:
    std::string _start_message;
    std::string _no_such_action_message;
    std::string _win_message;
    std::string _lose_message;
    void print_message(int condition_code);
    std::shared_ptr<Room> _start_room;
    std::shared_ptr<Room> _current_room;
    std::vector<std::shared_ptr<Room>> _rooms;

    public:
    Quest(std::string start_message, std::string win_message, std::string lose_message,
    std::string no_such_action_message) : 
    _start_message(start_message), _win_message(win_message),
    _lose_message(lose_message), _no_such_action_message(no_such_action_message) {};

    void start_quest();
    void add_room(std::shared_ptr<Room> room);
    void set_start_room(std::shared_ptr<Room> room);
    std::vector<std::shared_ptr<Room>> rooms;

    friend Move;
};


#endif