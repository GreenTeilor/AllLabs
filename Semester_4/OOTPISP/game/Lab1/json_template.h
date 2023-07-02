#pragma once
#include <nlohmann/json.hpp>
#include "Ball.h"
#include "Stand.h"
#include "Brick.h"

//Ball serialization
void to_json(nlohmann::json& j, const Ball& ball)
{
	j = nlohmann::json{ {"coordinateX", ball.getCoordinateX()}, {"coordinateY", ball.getCoordinateY()}, {"velocityX", ball.getVelocityX()}, {"velocityY", ball.getVelocityY()}};
}

void from_json(const nlohmann::json& j, Ball& ball) 
{
	ball.setCoordinateX(j.at("coordinateX").get<int>()); 
	ball.setCoordinateY(j.at("coordinateY").get<int>());
	ball.setVelocityX(j.at("velocityX").get<int>());
	ball.setVelocityY(j.at("velocityY").get<int>());
}

//Stand serialization
void to_json(nlohmann::json& j, const Stand& stand)
{
	j = nlohmann::json{ {"coordinateX", stand.getCoordinateX()}, {"coordinateY", stand.getCoordinateY()} };
}

void from_json(const nlohmann::json& j, Stand& stand)
{
	stand.setCoordinateX(j.at("coordinateX").get<int>());
	stand.setCoordinateY(j.at("coordinateY").get<int>());
}

//Brick serialization
void to_json(nlohmann::json& j, const Brick& brick)
{
	j = nlohmann::json{ {"coordinateX", brick.getCoordinateX()}, {"coordinateY", brick.getCoordinateY()}, {"bonus", brick.getBonusType()}};
}

void from_json(const nlohmann::json& j, Brick& brick)
{
	brick.setCoordinateX(j.at("coordinateX").get<int>());
	brick.setCoordinateY(j.at("coordinateY").get<int>());
	brick.m_bonuses[0].setCoordinateX(j.at("coordinateX").get<int>());
	brick.m_bonuses[0].setCoordinateY(j.at("coordinateY").get<int>());
	brick.m_bonuses[0].setType((Bonus::Type)j.at("bonus").get<int>());
}

//Ball serialization
void to_json(nlohmann::json& j, const Bonus& bonus)
{
	j = nlohmann::json{ {"coordinateX", bonus.getCoordinateX()}, {"coordinateY", bonus.getCoordinateY()}, {"type", bonus.getType()} };
}

void from_json(const nlohmann::json& j, Bonus& bonus)
{
	bonus.setCoordinateX(j.at("coordinateX").get<int>());
	bonus.setCoordinateY(j.at("coordinateY").get<int>());
	bonus.setType((Bonus::Type)j.at("type").get<int>());
	bonus.canCast = true;
}

//Active bonuses serialization
void to_json(nlohmann::json& j, const ActiveBonuses::State& state)
{
	j = nlohmann::json{ {"isActive", state.isActive}, {"activeTime", state.m_activeTime} };
}

void from_json(const nlohmann::json& j, ActiveBonuses::State& state)
{
	state.isActive = j.at("isActive").get<bool>();
	state.m_activeTime = j.at("activeTime").get<double>();
}