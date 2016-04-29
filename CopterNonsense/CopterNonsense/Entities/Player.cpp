#include "Player.h"



Player::Player()
	: p_object_(nullptr), mass_(3200), invMass_(1.f / mass_), verticalAllowed_(true)
{
	setGravity(sf::Vector2f(0, 981));


}

Player::~Player()
{

}

//Public Functions 
bool Player::initialise()
{
	p_object_->setScale(64.f, 64.f);
	p_object_->setFillColor(sf::Color::Blue);

	velocity_.x = MAX_HORIZONTAL_SPEED;
	return(true);
}

void Player::update(float delta)
{
	stepForces();
	stepVelocity(delta);

	p_object_->move(velocity_ * delta);

	force_ = sf::Vector2f(0.f, 0.f);
}

void Player::events(const sf::Event& evnt)
{
	if (evnt.type == sf::Event::KeyPressed)
	{
		if (verticalAllowed_ && evnt.key.code == sf::Keyboard::Space)
		{
			applyForce(sf::Vector2f(0.f, ((-gravity_.y * 85) * mass_))); //* 71.5f));
			verticalAllowed_ = false;
		}
	}

	if (evnt.type == sf::Event::KeyReleased)
	{
		if (!verticalAllowed_ && evnt.key.code == sf::Keyboard::Space)
		{
			verticalAllowed_ = true;
		}
	}
}

void Player::setPosition(sf::Vector2f position)
{
	p_object_->setPosition(position);
}

//Private Functions 
void Player::stepForces()
{
	force_ += (gravity_ * mass_);
}

void Player::stepVelocity(float delta)
{

	velocity_ += (invMass_ * force_) * delta; //Increment the velocity by the overall acceleration acting upon the player 
	//printf("\nVel Before: %f", velocity_.y);
	velocity_.y = clamp(velocity_.y, gravity_.y / 4, -gravity_.y / 4);
	//printf("\nVel After: %f", velocity_.y);

}