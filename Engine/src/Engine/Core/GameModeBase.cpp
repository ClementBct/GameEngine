#include "Engine/Core/GameModeBase.h"

#include <typeinfo>

GameModeBase::GameModeBase(){

}

GameModeBase::~GameModeBase(){

}

const std::string GameModeBase::getName() {
	return typeid(*this).name();
}