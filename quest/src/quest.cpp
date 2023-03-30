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
    
}


int Room::make_action(std::string action_name, Quest& quest)
{
    for(auto i = _actions.begin(); i != _actions.end(); i++)
    {
        if((*i)->_action_name == action_name)
        {

        }
    }
}


