#include "Player.h"

Player::Player(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet) :
	direc(direcSet),
	topHitBox(0, 0, 50, 50),
	bottomHitBox(0, 50, 50, 50),
	state(STANDING)
{
	std::copy(&animationSet[0], &animationSet[TOTAL_PLAYER_ANIMATIONS], &animations[0]);
	currentImage = &animations[STAND];
	
	if(direc == RIGHT)
		for(int i = 0; i < TOTAL_PLAYER_ANIMATIONS; i++)
		{
			animations[i].bitmap->RotateFlip(RotateNoneFlipX);
			animations[i].shiftX = animationSet[STAND].width-animationSet[i].width-animationSet[i].shiftX;
		}
}

void Player::Draw(ImageHandler * img)
{
	img->DrawSprite(*currentImage, (direc == RIGHT));
	
	/*img->DrawSquare(topHitBox);
	img->DrawSquare(bottomHitBox);
	if(Attacking())
		img->DrawSquare(AttackBox());*/
}

void Player::Update()
{
	UpdateHitBoxes();
	NextFrame();
}

void Player::ReleaseControl()
{
	if(!Attacking() && !GettingHit())
	{
		ChangeImage(&animations[STAND]);
		state = STANDING;
	}
}

void Player::Input(InputHandler input)
{
	if(!Attacking() && !GettingHit())
	{
		if(input.IsPressed(0x5A))
			Punch();
		if(input.IsPressed(0x58))
			Kick();
		if(input.IsDown(VK_LEFT) && currentImage->x > -50)
			WalkLeft(input.IsDown(VK_RIGHT));
		if(input.IsDown(VK_RIGHT) && currentImage->x < SCREEN_WIDTH - animations[STAND].width)
			WalkRight(input.IsDown(VK_LEFT));
		if((!input.IsDown(VK_RIGHT) && state == WALKING_RIGHT) || (!input.IsDown(VK_LEFT) && state == WALKING_LEFT))
			Stand();
	}
}

bool Player::CheckCollision(Rect attackBox)
{
	if(!GettingHit())
	{
		Rect checkBox = attackBox;
		if(checkBox.Intersect(topHitBox))
		{
			ChangeImage(&animations[HIT_HIGH]);
			state = BEING_HIT_HIGH;
			return true;
		}
		checkBox = attackBox;
		if(checkBox.Intersect(bottomHitBox))
		{
			ChangeImage(&animations[HIT_HIGH]);
			state = BEING_HIT_HIGH;
			return true;
		}
	}
	return false;
}

Rect Player::AttackBox()
{
	if(Attacking())
	{
		Rect newBox = attackBoxes[state][currentImage->currentFrame];
		if(direc == RIGHT)
			newBox.X += -animations[STAND].width + currentImage->shiftX;
		newBox.Offset(GetOriginPoint());
		return newBox;
	}
	else
		return Rect(0, 0, 0, 0);
}

Point Player::AttackEndPoint()
{
	Rect aBox = AttackBox();

	return Point((direc == LEFT ? aBox.X + aBox.Width : aBox.X), aBox.Y + (aBox.Width/2));
}

void Player::Win()
{
	if(state != VICTORYING)
	{
		ChangeImage(&animations[VICTORY]);
		state = VICTORYING;
	}
}

void Player::Die()
{
	if(state != DIEING)
	{
		ChangeImage(&animations[DEATH]);
		state = DIEING;
	}
}

void Player::Punch()
{
	ChangeImage(&animations[PUNCH]);
	state = PUNCHING;
}

void Player::Kick()
{
	ChangeImage(&animations[KICK]);
	state = KICKING;
}

void Player::Stand()
{
	ChangeImage(&animations[STAND]);
	state = STANDING;
}

void Player::WalkRight(bool leftKeyDown)
{
	if(state == STANDING || (state == WALKING_LEFT && !leftKeyDown))
	{
		ChangeImage(&animations[WALK_RIGHT]);
		state = WALKING_RIGHT;
	}
	animations[WALK_RIGHT].x += 5;
}

void Player::WalkLeft(bool rightKeyDown)
{
	if(state == STANDING || (state == WALKING_RIGHT && !rightKeyDown))
	{
		ChangeImage(&animations[WALK_LEFT]);
		state = WALKING_LEFT;
	}
	animations[WALK_LEFT].x -= 5;
}

bool Player::Attacking()
{
	return state == PUNCHING || state == KICKING;
}

bool Player::GettingHit()
{
	return state == BEING_HIT_HIGH;
}

Point Player::GetOriginPoint()
{
	int x = currentImage->x - currentImage->shiftX;
	int y = currentImage->y - currentImage->shiftY;

	return Point(x, y);
}

void Player::UpdateHitBoxes()
{
	Point origin = GetOriginPoint();

	topHitBox = Rect(origin.X + 10, origin.Y, (&animations)[STAND]->width - 20, (&animations)[STAND]->height/2);
	bottomHitBox = Rect(origin.X + 5, origin.Y + (&animations)[STAND]->height/2, (&animations)[STAND]->width - 10, (&animations)[STAND]->height/2);
}

void Player::RecenterImages()
{
	Point origin = GetOriginPoint();

	for(int i = 0; i < TOTAL_PLAYER_ANIMATIONS; i++)
		CenterImage(&animations[i], origin.X, origin.Y);
}

void Player::CenterImage(Sprite *image, int x, int y)
{
	image->x = x + image->shiftX;
	image->y = y + image->shiftY;
}

void Player::ChangeImage(Sprite *nextImage)
{
	RecenterImages();
	currentImage = nextImage;
	currentImage->currentFrame = 0;
}

void Player::NextFrame()
{
	currentImage->currentFrame++;

	if(currentImage->currentFrame > currentImage->frames)
	{
		if(state == VICTORYING || state == DIEING)
			currentImage->currentFrame--;
		else
		{
			currentImage->currentFrame = 0;
			if(Attacking() || GettingHit())
			{
				ChangeImage(&animations[STAND]);
				state = STANDING;
			}
		}
	}
}