#include "Enemy.h"

void Enemy::inittexture()
{
	if (!this->texture.loadFromFile("Sprite/SpriteSheet_Officer.png")) {
		std::cout << "Enemy Spritesheet loading error" << std::endl;
	}
}

void Enemy::initsprite()
{
	this->sprite.setTexture(this->texture);

	this->spritewidth = this->texture.getSize().x / 6;
	this->spriteheight = this->texture.getSize().y / 4;

	this->sprite.setTextureRect(sf::IntRect(0, 0, this->spritewidth, this->spriteheight));
	this->sprite.setOrigin(this->spritewidth / 2, this->spriteheight);
	this->sprite.setPosition(0, 0);
}

void Enemy::initbools()
{
	this->ishavepistol = true;
	this->ishaverifle = false;
	this->isinroom = false;

	this->isfinish = false;
	this->isvanish = false;

	this->isalert = false;
	this->startalert = false;
	this->startmin = true;
	this->ismovegap = false;
	this->startcap = false;
	this->turnpoint = false;
	this->startdistance = false;
	this->isstop = false;

	this->isshot = false;
	this->isstart = false;

	this->isplayershot = false;
	this->blockshot = false;

	this->isfix = false;
	this->iswalk = false;
}

void Enemy::initmagazine()
{
	for (int i = 0; i < 7; ++i) {
		this->magazine.push_back(new Bullet());
		this->magazine[0]->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);
	}
}

void Enemy::initframerate()
{
	std::ifstream ifs("Config/window.ini");

	//window variables
	std::string title = "None";
	sf::VideoMode window_bounds(1920, 1080);
	unsigned framerate_limit = 60;
	bool Vertical_Sync_Enabled = false;

	//Set files to variables
	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> Vertical_Sync_Enabled;
	}

	ifs.close();

	this->framerate = framerate_limit;
}

void Enemy::initrandom()
{
	this->indexstart = rand() % (7);
	this->indexdest = rand() % (7);
}

Enemy::Enemy()
{
	this->inittexture();
	this->initsprite();

	this->shape.setSize(sf::Vector2f(this->spritewidth, this->spriteheight));
	this->shape.setFillColor(sf::Color::Transparent);

	this->healthpoint = 100;
	this->movementspeed = 60;
	this->velocity = 5;
	this->direction = 0;
	this->min = 1000;

	this->initbools();
	this->initframerate();

	this->start = sf::Vector2i(0, 0);
	this->dest = sf::Vector2i(0, 0);

	this->indexstart = 0;
	this->indexdest = 0;

	this->gapx = 0;
	this->gapy = 0;

	this->lastdirection = 0;
	this->functioncount = 0;

	this->shoottimer = 0;
	this->reloadtimer = 0;
	this->gaptimer = 0;

	this->initmagazine();
	
}

Enemy::~Enemy()
{
	this->isalert = false;
	this->startalert = false;
}

void Enemy::checkinroom(float positiongrid_x, float positiongrid_y)
{

}

void Enemy::checkshot()
{
}

void Enemy::checkhealth()
{
}

void Enemy::checkmove(const float& dt)
{
	if (this->direction == 4) {

		this->sprite.setTextureRect(sf::IntRect(this->spritewidth * this->animationframe, this->spriteheight * 0, this->spritewidth, this->spriteheight));
		this->sprite.move(this->velocity * dt * this->movementspeed , 0);

		this->framecount++;
	}
	else if (this->direction == 3) {

		this->sprite.setTextureRect(sf::IntRect(this->spritewidth * this->animationframe, this->spriteheight * 3, this->spritewidth, this->spriteheight));
		this->sprite.move(0.f, this->velocity * dt * this->movementspeed );

		this->framecount++;
	}
	else if (this->direction == 2) {

		this->sprite.setTextureRect(sf::IntRect(this->spritewidth * this->animationframe, this->spriteheight * 1, this->spritewidth, this->spriteheight));
		this->sprite.move(-(this->velocity * dt * this->movementspeed), 0);

		this->framecount++;
	}
	else if (this->direction == 1) {

		this->sprite.setTextureRect(sf::IntRect(this->spritewidth * this->animationframe, this->spriteheight * 2, this->spritewidth, this->spriteheight));
		this->sprite.move(0.f, -(this->velocity * dt * this->movementspeed));

		this->framecount++;
	}
	else {
		if (this->isalert) {
			if (this->lastdirection == 4) {
				this->sprite.setTextureRect(sf::IntRect(this->spritewidth * 5, this->spriteheight * 0, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 3) {
				this->sprite.setTextureRect(sf::IntRect(this->spritewidth * 5, this->spriteheight * 3, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 2) {
				this->sprite.setTextureRect(sf::IntRect(this->spritewidth * 5, this->spriteheight * 1, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 1) {
				this->sprite.setTextureRect(sf::IntRect(this->spritewidth * 5, this->spriteheight * 2, this->spritewidth, this->spriteheight));
			}
		}
		else {

			if (this->lastdirection == 4) {
				this->sprite.setTextureRect(sf::IntRect(0, this->spriteheight * 0, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 3) {
				this->sprite.setTextureRect(sf::IntRect(0, this->spriteheight * 3, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 2) {
				this->sprite.setTextureRect(sf::IntRect(0, this->spriteheight * 1, this->spritewidth, this->spriteheight));
			}
			if (this->lastdirection == 1) {
				this->sprite.setTextureRect(sf::IntRect(0, this->spriteheight * 2, this->spritewidth, this->spriteheight));
			}
		}
	}

	if (this->framecount >= 20) {
		this->animationframe++;
		this->framecount = 0;
	}

	if (this->animationframe > 4) {
		this->animationframe = 1;
	}
}

void Enemy::inittrack(float start_x, float start_y, float dest_x, float dest_y)
{
	this->start.x = start_x;
	this->start.y = start_y;

	this->dest.x = dest_x;
	this->dest.y = dest_y;

	this->sprite.setPosition(this->start.x * 70, this->start.y * 70);
}

void Enemy::tracking()
{
	if (this->isfix) {
		this->startmin = true;
	}

	if(this->iswalk){
		this->startmin = false;
	}

	
	if (this->start.x > 0 && this->start.y > 0 && this->dest.x > 0 && this->dest.y > 0) {

		//std::cout << "Startmin : " << this->startmin << std::endl;

		if (functioncount == 1 && !this->turnpoint && !this->isstop) {

			//std::cout << "StartMin function called" << std::endl;

			if (!this->startdistance) {
				this->start.x = this->positiongrid.x;
				this->start.y = this->positiongrid.y;
				this->startdistance = true;
			}

			this->startmin = false;
		}

		this->turnpoint = false;
		this->functioncount = 0;
		this->startdistance = false;

		//find Shortest Distance

		if (!this->startmin) {
			for (int i = 0; i < 8; ++i) {
				if (this->Checkpoint[i].x == this->start.x || this->Checkpoint[i].y == this->start.y) {

					//std::cout << "Shortest Distance function called" << std::endl;
					this->distance = std::sqrt(std::pow(this->Checkpoint[i].x - this->dest.x, 2) + std::pow(this->Checkpoint[i].y - this->dest.y, 2));
					if(this->distance < this->min) {
						this->min = this->distance;
						this->index = i;
						this->isfinish = true;
					
						//std::cout << "Minimum Distance function called" << std::endl;

						//std::cout << "Min : " << this->min << std::endl;
						//std::cout << "Checkpoint : " << this->Checkpoint[this->index].x << " " << this->Checkpoint[this->index].y << std::endl;

					
					}
				}
			}

			this->startmin = true;
		}

		if (this->start.x == this->Checkpoint[this->index].x && this->start.y == this->Checkpoint[this->index].y) {
			this->isfinish = false;
		}
		

		//std::cout << "Winner Checkpoint : " << this->Checkpoint[this->index].x << " " << this->Checkpoint[this->index].y << std::endl;
		//std::cout << "isfinish : " << this->isfinish << std::endl;
		//std::cout << "Winner min : " << this->min << std::endl;


		if (this->isfinish) {
			
			//find Direction
			if (this->start.y == this->positiongrid.y && this->start.y == this->Checkpoint[this->index].y) {

				//Find Direction
				if (this->Checkpoint[this->index].x - this->start.x > 0) {
					//std::cout << "Find Direction (Direction : 4) function called" << std::endl;
					this->direction = 4;
				}
				else if (this->Checkpoint[this->index].x - this->start.x < 0) {
					//std::cout << "Find Direction (Direction : 2) function called" << std::endl;
					this->direction = 2;
				}

			}
			else if(this->start.y != this->positiongrid.y && this->start.y == this->Checkpoint[this->index].y){

				//Reroute to find Direction
				if (this->start.y - this->positiongrid.y > 0) {
					//std::cout << "Find Direction : Reroute Direction (Direction : 3) function called" << std::endl;
					this->direction = 3;
				}
				else if (this->start.y - this->positiongrid.y < 0) {
					//std::cout << "Find Direction : Reroute Direction (Direction : 1) function called" << std::endl;
					this->direction = 1;
				}
			}
			
			if (this->start.x == this->positiongrid.x && this->start.x == this->Checkpoint[this->index].x) {

				//find direction
				if (this->Checkpoint[this->index].y - this->start.y > 0) {
					//std::cout << "Find Direction (Direction : 3) function called" << std::endl;
					this->direction = 3;
				}
				else if (this->Checkpoint[this->index].y - this->start.y < 0) {
					//std::cout << "Find Direction ((Direction : 1) function called" << std::endl;
					this->direction = 1;
				}
			}
			else if(this->start.x != this->positiongrid.x && this->start.x == this->Checkpoint[this->index].x){

				//Reroute to find direction
				if (this->start.x - this->positiongrid.x > 0) {
					//std::cout << "Find Direction : Reroute Direction (Direction : 4) function called" << std::endl;
					this->direction = 4;
				}
				else if (this->start.x - this->positiongrid.x < 0) {
					//std::cout << "Find Direction : Reroute Direction (Direction : 2) function called" << std::endl;
					this->direction = 2;
				}
			}

		}

		if (!this->isstop) {
			this->magazine[0]->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);
		}

		this->isstop = false;

		//Last Checkpoint to Destination
		if ((this->positiongrid.x == this->dest.x || this->positiongrid.y == this->dest.y) && !this->isfinish) {
			
			this->functioncount++;
			this->startcap = false;

			//std::cout << "Last Checkpoint to Destination function called" << std::endl;

			if (this->dest.x - this->positiongrid.x > 0) {
				this->gapx = -2;
				this->gapy = 0;
				this->direction = 4;

			}
			else if (this->dest.x - this->positiongrid.x < 0) {
				this->gapx = 2;
				this->gapy = 0;
				this->direction = 2;
			}

			if (this->dest.y - this->positiongrid.y > 0) {
				this->gapx = 0;
				this->gapy = -2;
				this->direction = 3;
			}
			else if (this->dest.y - this->positiongrid.y < 0) {
				this->gapx = 0;
				this->gapy = 2;
				this->direction = 1;
			}
		}

		//To Destination then stop

		//If Enemy is not alerted
		if (!this->isalert) {
			if (this->positiongrid.x == this->dest.x && this->positiongrid.y == this->dest.y) {

				this->lastdirection = this->direction;
				this->direction = 0;
				this->isdisappear = true;
				this->min = 100;
			}
		}

		//If Enemy is alerted
		else if(this->isalert){

			if (this->positiongrid.x == this->dest.x + this->gapx && this->positiongrid.y == this->dest.y + this->gapy) {

				//std::cout << "STOP! function called" << std::endl;

				if (!this->isfinish) {
					this->lastdirection = this->direction;
					this->direction = 0;

					this->shooting(this->dt);

					if (!this->startcap) {
						this->start.x = this->positiongrid.x;
						this->start.y = this->positiongrid.y;
						this->startcap = true;
					}

					this->isfinish = false;
					this->isstop = true;
				}

			}

			else {
				
				if (!this->isfinish) {

					//std::cout << "Reroute To Destination with Gap function called" << std::endl;

					this->functioncount++;

					if (this->dest.x + this->gapx - this->positiongrid.x > 0) {
						this->direction = 4;

					}
					else if (this->dest.x + this->gapx - this->positiongrid.x < 0) {
						this->direction = 2;
					}

					if (this->dest.y + this->gapy - this->positiongrid.y > 0) {
						this->direction = 3;
					}
					else if (this->dest.y + this->gapy - this->positiongrid.y < 0) {
						this->direction = 1;
					}

				}
			}
			
		}

		//Check turning point
		for (int i = 0; i < 8; ++i) {
			if (this->positiongrid.x == this->Checkpoint[i].x && this->positiongrid.y == this->Checkpoint[i].y) {
				this->start.x = this->Checkpoint[i].x;
				this->start.y = this->Checkpoint[i].y;
				this->isfinish = false;
				this->startmin = false;
				this->turnpoint = true;
				this->min = 100;
				//std::cout << "Turning point" << std::endl;
			}
		}

		

		//std::cout << "Enemy Position: " << this->positiongrid.x << " " << this->positiongrid.y << std::endl;
		//std::cout << "Enemy Direction: " << this->direction << std::endl;
		//std::cout << "Function Count : " << this->functioncount << std::endl;
		//std::cout << "Turning Point : " << this->turnpoint << std::endl;
		//std::cout << "Start: " << this->start.x << " " << this->start.y<< std::endl;
		//std::cout << "Dest: " << this->dest.x << " " << this->dest.y << std::endl << std::endl;
		
	}
}

void Enemy::shooting(const float& dt)
{
	//Reload
	if (this->shoottimer == 6 && this->ishavepistol) {

		//std::cout << "Heyyyyyyyyyyyyyyyyyyyy" << std::endl;

		if (this->reloadtimer == this->framerate) {
			this->soundpistolreload.sound.play();
		}

		if (this->reloadtimer < this->framerate * 3) {
			this->reloadtimer++;
		}
		else if (this->reloadtimer == this->framerate * 3) {

			if (this->magazine.size() > 7) {
				for (int i = 0; i < this->magazine.size() - 7; ++i) {
					this->magazine.erase(this->magazine.begin() + 0);
				}
			}
			
			for (int i = 0; i < 6; ++i) {
				this->magazine.push_back(new Bullet());
				this->magazine[0]->sprite.setPosition(this->sprite.getPosition().x + 20, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);

			}

			this->reloadtimer = 0;
			this->shoottimer = 0;
		}
	}

	if (this->blockshot == true) {
		if (this->gaptimer < this->framerate - 10) {
			this->gaptimer++;
		}
		if (this->gaptimer == this->framerate - 10) {
			this->blockshot = false;
			this->gaptimer = 0;
		}
	}

	//std::cout << "Blockshot : " << this->blockshot << std::endl;

	//Click and Shooting
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->ishavepistol && (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
		if (this->shoottimer < 6 && this->ishavepistol && !this->blockshot) {

			//std::cout << "Shooting function called" << std::endl;

			this->isshot = true;
			if (this->direction == 4) {
				this->shootgap = 26;
			}
			else if (this->direction == 2) {
				this->shootgap = -26;
			}
			else {
				this->shootgap = 0;
			}
			

			this->magazine[0]->sprite.setPosition(this->sprite.getPosition().x + this->shootgap, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);
			this->blockshot = true;
		}
	//}


	if (this->isshot && !this->magazine.empty()) {

		//std::cout << "Shoottimer Added function called" << std::endl;

		//Start Position
		if (this->ishavepistol && !this->isstart) {
			this->startpos = sf::Vector2i(this->sprite.getPosition().x + this->shootgap, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);
			this->magazine[0]->direction = this->lastdirection;

			if (this->magazine[0]->direction == 4) {
				this->magazine[0]->sprite.setTextureRect(sf::IntRect(this->magazine[0]->spritewidth * 0, 0, this->magazine[0]->spritewidth, this->magazine[0]->spriteheight));
			}
			if (this->magazine[0]->direction == 3) {
				this->magazine[0]->sprite.setTextureRect(sf::IntRect(this->magazine[0]->spritewidth * 3, 0, this->magazine[0]->spritewidth, this->magazine[0]->spriteheight));
			}
			if (this->magazine[0]->direction == 2) {
				this->magazine[0]->sprite.setTextureRect(sf::IntRect(this->magazine[0]->spritewidth * 1, 0, this->magazine[0]->spritewidth, this->magazine[0]->spriteheight));
			}
			if (this->magazine[0]->direction == 1) {
				this->magazine[0]->sprite.setTextureRect(sf::IntRect(this->magazine[0]->spritewidth * 2, 0, this->magazine[0]->spritewidth, this->magazine[0]->spriteheight));
			}

			this->isstart = true;
			this->soundpistolshot.sound.play();
			this->shoottimer++;
			//std::cout << "Bullet left : " << this->shoottimer << std::endl;
		}

		//Bullet move
		if (this->magazine[0]->direction == 4) {
			this->magazine[0]->move(dt, (this->magazine[0]->velocity), 0);
		}
		if (this->magazine[0]->direction == 3) {
			this->magazine[0]->move(dt, 0, (this->magazine[0]->velocity));
		}
		if (this->magazine[0]->direction == 2) {
			this->magazine[0]->move(dt, -(this->magazine[0]->velocity), 0);
		}
		if (this->magazine[0]->direction == 1) {
			this->magazine[0]->move(dt, 0, -(this->magazine[0]->velocity));
		}

		//std::cout << "Start Position : " << this->startpos.x << " " << this->startpos.y << std::endl;

		//Distance between Bullet and Start Position
		this->distance = std::sqrt(std::pow(this->startpos.x - this->magazine[0]->sprite.getPosition().x, 2) + std::pow(this->startpos.y - this->magazine[0]->sprite.getPosition().y, 2));

		//std::cout << "Distance : " << this->distance << std::endl;
		
		if (this->distance > 350) {
			this->isvanish = true;
		}

		if (this->isvanish) {
			this->magazine.erase(this->magazine.begin() + 0);

			this->isshot = false;
			this->isstart = false;
			this->isvanish = false;
			
		}
	}
	else if (!this->isshot && this->ishavepistol && !this->magazine.empty()) {
		this->magazine[0]->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2 - 12);
	}
}

void Enemy::update(const float& dt)
{
	this->updatespritepos();
	this->updateentitypos();
	
	
	this->checkmove(dt);
	this->tracking();
}

void Enemy::updateentitypos()
{
	this->position = sf::Vector2i(this->sprite.getPosition());
	this->positiongrid = sf::Vector2i(this->position.x / 70, this->position.y / 70);
}

void Enemy::updatespritepos()
{
	this->shape.setPosition(this->sprite.getPosition());
}

void Enemy::render(sf::RenderTarget* target)
{
	if (!this->magazine.empty()) {
		this->magazine[0]->render(target);
	}

	target->draw(this->sprite);
	target->draw(this->shape);

	
}


