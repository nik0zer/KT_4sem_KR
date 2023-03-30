#include "quest.h"

int Action::make_action(Quest& quest, Room& room)
{
    std::cout<<_action_text<<std::endl;
    return _action_result;
}

int Move::make_action(Quest& quest, Room& room)
{
    std::cout<<_action_text<<std::endl;
    quest._current_room = _room;
    std::cout<<std::endl<<std::endl;
    quest._current_room->print_room_entry_mesage();
    return _action_result;
}

int Interaction::make_action(Quest& quest, Room& room)
{
    std::cout<<_action_text<<std::endl;
    for(auto i = room._actions.begin(); i != room._actions.end(); i++)
    {
        if((*i)->_action_name == _action_name)
        {
            room._actions.erase(i);
            return _action_result;
        }
    }
    return _action_result;
}

int Activation::make_action(Quest& quest, Room& room)
{
    std::cout<<_action_text<<std::endl;
    _deactivation.make_action(quest, room);
    return _action_result;
}


int Deactivation::make_action(Quest& quest, Room& room)
{
    std::cout<<_action_text<<std::endl;
    return _action_result;
}


int Room::make_action(std::string action_name, Quest& quest)
{
    if(_actions.size() == 0)
    {
        return LOSE;
    }
    for(auto i = _actions.begin(); i != _actions.end(); i++)
    {
        if((*i)->_action_name == action_name)
        {
            return (*i)->make_action(quest, *this);
        }
    }
    return NO_SUCH_ACTION;
}

void Room::print_room_entry_mesage()
{
    std::cout<<_room_entry_message<<std::endl;
}

void Room::print_room_mesage()
{
    std::cout<<_room_message<<std::endl;
}

void Room::add_action(std::shared_ptr<Action> action)
{
    _actions.push_back(action);
}

void Room::print_actions()
{
    int num = 1;
    for(auto i = _actions.begin(); i != _actions.end(); i++)
    {
        std::cout<<num<<") "<<(*i)->_action_name<<std::endl;
        num++;
    }
}


void Quest::print_message(int condition_code)
{
    switch (condition_code)
    {
    case LOSE:
        std::cout<<_lose_message<<std::endl;
        break;
    case WIN:
        std::cout<<_win_message<<std::endl;
        break;
    case START:
        std::cout<<_start_message<<std::endl;
        break;
    case NO_SUCH_ACTION:
        std::cout<<_no_such_action_message<<std::endl;
        break;
    default:
        break;
    }
}

void Quest::start_quest()
{
    int condition_code = START;
    print_message(condition_code);
    _current_room = _start_room;
    while(condition_code != LOSE && condition_code != WIN)
    {
        _current_room->print_room_mesage();
        std::cout<<"available actions:"<<std::endl;
        _current_room->print_actions();
        std::string action_name;
        std::cin>>action_name;
        condition_code = _current_room->make_action(action_name, *this);
        print_message(condition_code);
        std::cout<<std::endl;
    }
    std::cout<<"You're out of the game"<<std::endl;
}

void Quest::add_room(std::shared_ptr<Room> room)
{
    _rooms.push_back(room);
}

void Quest::set_start_room(std::shared_ptr<Room> room)
{
    _start_room = room;
}