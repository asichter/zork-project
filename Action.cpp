#include "Action.h"

Action::Action(std::string _type) {
    type = _type;
    item = "none";
    container = "none";
    status = "none";
    target = "none";
}

void Action::setItem(std::string _item) {
    item = _item;
}

void Action::setContainter(std::string _container) {
    item = _container;
}

void Action::setStatus(std::string _status) {
    status = _status;
}

void Action::setTarget(std::string _target) {
    target = _target;
}

std::string Action::getType() {
    return type;
}

std::string Action::getItem() {
    return item;
}

std::string Action::getContainer() {
    return container;
}

std::string Action::getStatus() {
    return status;
}

std::string Action::getTarget() {
    return target;
}
