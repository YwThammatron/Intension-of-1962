#include "GameState.h"

void GameState::initkeybinds()
{
	//Set keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");

}

void GameState::initview()
{
	this->mainview.setSize(1920.f, 1080.f);
	this->mainview.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);

}

void GameState::initframerate() 
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

void GameState::initposition()
{
	this->player.sprite.setPosition(27 * 70, 30 * 70);
}

void GameState::initmagazine()
{
	this->player.bullets = 18;

	if (this->player.bullets > 0) {
		for (int i = 0; i < 6; ++i) {
			this->player.magazine.push_back(new Bullet());
			//std::cout << "Bullet Reloaded" << std::endl;
			this->player.magazine[0]->sprite.setPosition(this->player.sprite.getPosition().x, this->player.sprite.getPosition().y - this->player.sprite.getGlobalBounds().height / 2 - 12);
			this->player.bullets--;
		}
	}
	

	
}

void GameState::initspawn()
{
	for (int i = 0; i < 10; ++i) {
		this->fixenemy.push_back(new Enemy());
		this->fixenemy[i]->isfix = true;
	}

	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			this->fixenemy[i]->sprite.setPosition(this->spawnpos[i].x * 70, this->spawnpos[i].y * 70);
		}
	}

	srand(time(0));

	for (int i = 0; i < 2; ++i) {
		this->walkenemy.push_back(new Enemy());
		this->walkenemy[i]->iswalk = true;
		this->walkenemy[i]->initrandom();
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			
			this->walkenemy[i]->inittrack(this->roompos[this->walkenemy[i]->indexstart].x,this->roompos[this->walkenemy[i]->indexstart].y,this->roompos[this->walkenemy[i]->indexdest].x,this->roompos[this->walkenemy[i]->indexdest].y);
			//std::cout << "Enemy " << i << " Tracking : " << this->walkenemy[i]->indexstart << " to " << this->walkenemy[i]->indexdest << std::endl;
			this->walkenemy[i]->velocity = 3;
		}

	}

}

void GameState::initrooms()
{
	for (int i = 0; i < 9; ++i) {
		this->rooms[i].initposition(this->roominitpos[i].x, this->roominitpos[i].y);
	}
}

void GameState::inititems()
{
	srand(time(0));

	for (int i = 0; i < 16; ++i) {
		this->itemindex = rand() % (3);

		this->tilecode_x = this->items[this->itemindex];
		this->tilecode_y = 0;

		if (this->items[this->itemindex] > 7) {
			this->tilecode_y = this->tilecode_x / 8;
			this->tilecode_x = this->tilecode_x % 8;
		}
		this->MainFloor.sprite[this->itempos[i].y][this->itempos[i].x].setTextureRect(sf::IntRect(70 * this->tilecode_x, 70 * this->tilecode_y, 70, 70));
		this->MainFloor.tilecode[this->itempos[i].y][this->itempos[i].x] = this->items[this->itemindex];
	}
}

void GameState::initroomspawn()
{
	for (int i = 0; i < 10; ++i) {
		this->roomenemy.push_back(new Enemy());
		this->roomenemy[i]->isfix = true;
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			this->roomenemy[i]->sprite.setPosition(this->inroompos[i].x * 70, this->inroompos[i].y * 70);
		}
	}
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states)
	:State(window,supportedkeys,states)
{
	this->initkeybinds();
	this->initview();
	this->initframerate();
	this->inititems();
	this->initrooms();
	this->initmagazine();
	this->initposition();
	this->initspawn();
	this->initroomspawn();

	this->score = 0;

	int index = 0;

	for (int i = 96; i <= 167; ++i) {
		this->furntile[index] = i;
		index++;
	}

	this->totaltime = 0;
	this->endcount = 0;
	this->fadecount = 0;
	this->colorindex = 255;
	this->iswrite = false;
	this->isupdatetex = false;
	this->isfadecolor = false;
}



GameState::~GameState()
{
	std::cout << "GameState Deleted" << std::endl;
	std::cout << "Stacks Size : " << this->states->size() << std::endl;
}

void GameState::updateinput(const float& dt)
{
	this->checkforquit();
	this->checkforpause();

	if (this->player.walkmode) {
		//Move Player entity if Press A,D,W,S
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
			this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * this->player.animationframe, this->player.spriteheight * 1, this->player.spritewidth, this->player.spriteheight));
			this->player.move(dt, -(this->player.velocity), 0.f);
			this->player.framecount++;

			this->player.direction = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
			this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * this->player.animationframe, this->player.spriteheight * 0, this->player.spritewidth, this->player.spriteheight));
			this->player.move(dt, this->player.velocity, 0.f);
			this->player.framecount++;

			this->player.direction = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
			this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * this->player.animationframe, this->player.spriteheight * 2, this->player.spritewidth, this->player.spriteheight));
			this->player.move(dt, 0.f, -(this->player.velocity));
			this->player.framecount++;

			this->player.direction = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
			this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * this->player.animationframe, this->player.spriteheight * 3, this->player.spritewidth, this->player.spriteheight));
			this->player.move(dt, 0.f, this->player.velocity);
			this->player.framecount++;

			this->player.direction = 3;
		}
		else {

			if (this->player.shootmode) {
				if (this->player.direction == 4) {
					this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * 5, this->player.spriteheight * 0, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 3) {
					this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * 5, this->player.spriteheight * 3, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 2) {
					this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * 5, this->player.spriteheight * 1, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 1) {
					this->player.sprite.setTextureRect(sf::IntRect(this->player.spritewidth * 5, this->player.spriteheight * 2, this->player.spritewidth, this->player.spriteheight));
				}
			}
			else {

				if (this->player.direction == 4) {
					this->player.sprite.setTextureRect(sf::IntRect(0, this->player.spriteheight * 0, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 3) {
					this->player.sprite.setTextureRect(sf::IntRect(0, this->player.spriteheight * 3, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 2) {
					this->player.sprite.setTextureRect(sf::IntRect(0, this->player.spriteheight * 1, this->player.spritewidth, this->player.spriteheight));
				}
				if (this->player.direction == 1) {
					this->player.sprite.setTextureRect(sf::IntRect(0, this->player.spriteheight * 2, this->player.spritewidth, this->player.spriteheight));
				}
			}

		}

		if (this->player.framecount >= this->framerate / 3) {
			this->player.animationframe++;
			this->player.framecount = 0;
		}

		if (this->player.animationframe > 4) {
			this->player.animationframe = 1;
		}

	}
	
}


void GameState::checkforpause()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE")))) {
		this->states->push(new PauseState(this->window, this->supportedkeys, this->states));
	}
}



void GameState::updateposition()
{
	
}




void GameState::updateview()
{
	this->window->setView(this->mainview);
	this->mainview.setCenter(this->player.position.x,this->player.position.y);
	this->window->setView(this->window->getDefaultView());
}

void GameState::updaterooms()
{
	for (int i = 0; i < 9; ++i) {
		if (this->player.shape.getGlobalBounds().intersects(this->rooms[i].room.getGlobalBounds())) {
			this->rooms[i].inroom();

			for (int j = 0; j < this->roomenemy.size(); ++j) {
				if (this->roomenemy[j]->sprite.getGlobalBounds().intersects(this->rooms[i].room.getGlobalBounds())) {
					this->roomenemy[j]->isalert = true;
				}
			}
		}
		else {
			this->rooms[i].outroom();
		}
	}

	if (this->totaltime % 120 == 0 && this->totaltime != 0) {

		while (this->roomenemy.size() < 10) {
			this->roomenemy.push_back(new Enemy());
		}

		if (!this->roomenemy.empty()) {
			for (int i = 0; i < this->roomenemy.size(); ++i) {
				this->roomenemy[i]->isfix = true;
				this->roomenemy[i]->sprite.setPosition(this->inroompos[i].x * 70, this->inroompos[i].y * 70);

			}
		}
		
	}
}


void GameState::updatetime()
{
	this->totaltime = this->clock.getElapsedTime().asSeconds();
	//std::cout << "Time : " << this->totaltime << std::endl;
}

void GameState::updateitems()
{
	if (this->totaltime == 60) {

		this->sounditem.sound.play();

		srand(time(0));

		this->micindex = (int)(rand() % (7));
		std::cout << "Microfilm spawned at room : " << this->micindex << std::endl;
		this->MainFloor.sprite[this->micpos[this->micindex].y][this->micpos[this->micindex].x].setTextureRect(sf::IntRect(70 * 1, 70 * 20, 70, 70));
		this->MainFloor.tilecode[this->micpos[this->micindex].y][this->micpos[this->micindex].x] = 161;
	}

	if (this->totaltime % 60 == 0 && this->totaltime != 0) {
		this->sounditem.sound.play();
		this->inititems();
	}
}



void GameState::equipments()
{
	if (this->playercode == 161) {
		//Microfilm
		this->textmiccollect.initcolor(sf::Color::White);

		this->MainFloor.tilecode[this->player.positiongrid.y][this->player.positiongrid.x] = 2;
		this->MainFloor.sprite[this->player.positiongrid.y][this->player.positiongrid.x].setTextureRect(sf::IntRect(70 * 2, 70 * 0, 70, 70));
		
		this->player.ishavemic = true;
		this->score += 5000;
	}
	if (this->playercode == 170) {
		//Mini First-Aid
		this->soundfirstaid.sound.play();

		this->player.healthpoint = this->player.healthpoint + 10;

		this->MainFloor.tilecode[this->player.positiongrid.y][this->player.positiongrid.x] = 2;
		this->MainFloor.sprite[this->player.positiongrid.y][this->player.positiongrid.x].setTextureRect(sf::IntRect(70 * 2, 70 * 0, 70, 70));
		this->score += 500;
	}

	if (this->playercode == 171) {
		//Big First-Aid
		this->soundfirstaid.sound.play();

		this->player.healthpoint = this->player.healthpoint + 30;

		this->MainFloor.tilecode[this->player.positiongrid.y][this->player.positiongrid.x] = 2;
		this->MainFloor.sprite[this->player.positiongrid.y][this->player.positiongrid.x].setTextureRect(sf::IntRect(70 * 2, 70 * 0, 70, 70));
		this->score += 1000;
	}

	if (this->playercode == 172) {
		//Mini Bullets
		this->sounditem.sound.play();

		this->player.bullets = this->player.bullets + 6;

		this->MainFloor.tilecode[this->player.positiongrid.y][this->player.positiongrid.x] = 2;
		this->MainFloor.sprite[this->player.positiongrid.y][this->player.positiongrid.x].setTextureRect(sf::IntRect(70 * 2, 70 * 0, 70, 70));
		this->score += 500;
	}

}

void GameState::collision()
{
	this->playercode = this->MainFloor.tilecode[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x];

	//Player furniture Collision
	for (int i = 0; i < 72; ++i) {
		if (this->playercode == this->furntile[i]) {
			if (this->player.direction == 1) {
				//W and S
				this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height));

			}
			if (this->player.direction == 3) {
				this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y - 1));

			}
			if (this->player.direction == 2) {
				//A and D
				this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width, this->player.sprite.getPosition().y));

			}
			if (this->player.direction == 4) {
				this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x - 1, this->player.sprite.getPosition().y));

			}
		}
	}

	//Player Edge wall collision
	if (this->playercode == 80) {
		this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y - 1));
	}

	if (this->playercode == 81) {
		this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width, this->player.sprite.getPosition().y));
	}

	if (this->playercode == 82) {
		this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height));
	}

	if (this->playercode == 83) {
		this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x - 1, this->player.sprite.getPosition().y));
	}

	//Player Path collision
	for (int i = 0; i < 4; ++i) {
		if (this->playercode == this->pathtile1[i]) {
			if ((int)this->player.sprite.getPosition().y < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8) {
				this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8));
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (this->playercode == this->pathtile2[i]) {
			if ((int)this->player.sprite.getPosition().x < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15) {
				this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15, this->player.sprite.getPosition().y));
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (this->playercode == this->pathtile3[i]) {
			if ((int)this->player.sprite.getPosition().y > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8) {
				this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8));
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (this->playercode == this->pathtile4[i]) {
			if ((int)this->player.sprite.getPosition().x > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15) {
				this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15, this->player.sprite.getPosition().y));
			}
		}
	}

	//Player 2-Edge Path Collision
	if (this->playercode == 88 || this->playercode == 94) {
		//Player direction 1 and 4
		if ((int)this->player.sprite.getPosition().y < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8));
		}

		if ((int)this->player.sprite.getPosition().x > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15, this->player.sprite.getPosition().y));
		}
	}

	if (this->playercode == 89 || this->playercode == 92) {
		//Player direction 3 and 4
		if ((int)this->player.sprite.getPosition().y > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8));
		}

		if ((int)this->player.sprite.getPosition().x > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15, this->player.sprite.getPosition().y));
		}
	}

	if (this->playercode == 90 || this->playercode == 95) {
		//Player direction 2 and 3
		if ((int)this->player.sprite.getPosition().x < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15, this->player.sprite.getPosition().y));
		}

		if ((int)this->player.sprite.getPosition().y > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8));
		}
	}

	if (this->playercode == 92 || this->playercode == 93) {
		//Player direction 1 and 2
		if ((int)this->player.sprite.getPosition().y < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8));
		}

		if ((int)this->player.sprite.getPosition().x < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15, this->player.sprite.getPosition().y));
		}
	}

	//Player Room Edge collision
	if (this->playercode == 84) {
		//Player Direction 1
		if ((int)this->player.sprite.getPosition().y < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + 8));
		}
	}

	if (this->playercode == 85) {
		//Player Direction 2
		if ((int)this->player.sprite.getPosition().x < this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + 15 , this->player.sprite.getPosition().y));
		}
	}

	if (this->playercode == 86) {
		//Player Direction 3
		if ((int)this->player.sprite.getPosition().y > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8) {
			this->player.sprite.setPosition(sf::Vector2f(this->player.sprite.getPosition().x, this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().y + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().height - 8));
		}
	}

	if (this->playercode == 87) {
		//Player Direction 4
		if ((int)this->player.sprite.getPosition().x > this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15) {
			this->player.sprite.setPosition(sf::Vector2f(this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getPosition().x + this->MainFloor.sprite[(int)this->player.positiongrid.y][(int)this->player.positiongrid.x].getGlobalBounds().width - 15 , this->player.sprite.getPosition().y));
		}
	}
}


void GameState::shootmode()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->player.shootmode = true;
		this->player.velocity = 6;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		this->player.shootmode = false;
		this->player.velocity = 5;
	}
}

void GameState::updatedt(const float& dt)
{
	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			this->fixenemy[i]->dt = dt;
		}
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			this->walkenemy[i]->dt = dt;
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			this->roomenemy[i]->dt = dt;
		}
	}
}


void GameState::shooting(const float& dt)
{
	this->shootmode();

	//std::cout << "Bullets left : " << this->player.magazine.size() << std::endl;

	//Reload
	if (this->player.shoottimer == 6 && this->player.ishavepistol && this->player.bullets > 0) {

		//std::cout << "Isshot : " << this->player.isshot << std::endl;

		if (this->player.reloadtimer == this->framerate) {
			this->soundpistolreload.sound.play();
		}

		if (this->player.reloadtimer < this->framerate*3) {
			this->player.reloadtimer++;
		}
		else if (this->player.reloadtimer == this->framerate*3) {

			for (int i = 0; i < 6; ++i) {
				this->player.magazine.push_back(new Bullet());
				this->player.magazine[0]->sprite.setPosition(this->player.sprite.getPosition().x + 20, this->player.sprite.getPosition().y - this->player.sprite.getGlobalBounds().height / 2 - 12);
				
			}

			this->player.bullets = this->player.bullets - 6;
			this->player.reloadtimer = 0;
			this->player.shoottimer = 0;

			
		}
	}

	//Click and Shooting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player.ishavepistol && this->player.shootmode && (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
		if (this->player.shoottimer < 6) {
			this->player.isshot = true;
			if(this->player.direction == 4){
				this->player.shootgap = 26;
			}
			else if (this->player.direction == 2) {
				this->player.shootgap = -26;
			}
			else {
				this->player.shootgap = 0;
			}

			this->player.magazine[0]->sprite.setPosition(this->player.sprite.getPosition().x + this->player.shootgap, this->player.sprite.getPosition().y - this->player.sprite.getGlobalBounds().height / 2 - 12);
		}
	}

	if (this->player.isshot) {

		//Start Position
		if (this->player.ishavepistol && !this->player.isstart) {
			this->player.startpos = sf::Vector2i(this->player.sprite.getPosition().x + this->player.shootgap, this->player.sprite.getPosition().y - this->player.sprite.getGlobalBounds().height/2 - 12);
			this->player.magazine[0]->direction = this->player.direction;

			if (this->player.magazine[0]->direction == 4) {
				this->player.magazine[0]->sprite.setTextureRect(sf::IntRect(this->player.magazine[0]->spritewidth * 0, 0, this->player.magazine[0]->spritewidth, this->player.magazine[0]->spriteheight));
			}
			if (this->player.magazine[0]->direction == 3) {
				this->player.magazine[0]->sprite.setTextureRect(sf::IntRect(this->player.magazine[0]->spritewidth * 3, 0, this->player.magazine[0]->spritewidth, this->player.magazine[0]->spriteheight));
			}
			if (this->player.magazine[0]->direction == 2) {
				this->player.magazine[0]->sprite.setTextureRect(sf::IntRect(this->player.magazine[0]->spritewidth * 1, 0, this->player.magazine[0]->spritewidth, this->player.magazine[0]->spriteheight));
			}
			if (this->player.magazine[0]->direction == 1) {
				this->player.magazine[0]->sprite.setTextureRect(sf::IntRect(this->player.magazine[0]->spritewidth * 2, 0, this->player.magazine[0]->spritewidth, this->player.magazine[0]->spriteheight));
			}

			this->player.isstart = true;
			this->soundpistolshot.sound.play();
			this->player.shoottimer++;
		}

		//Bullet move
		if (this->player.magazine[0]->direction == 4) {
			this->player.magazine[0]->move(dt, (this->player.magazine[0]->velocity), 0);
		}
		if (this->player.magazine[0]->direction == 3) {
			this->player.magazine[0]->move(dt, 0, (this->player.magazine[0]->velocity));
		}
		if (this->player.magazine[0]->direction == 2) {
			this->player.magazine[0]->move(dt, -(this->player.magazine[0]->velocity), 0);
		}
		if (this->player.magazine[0]->direction == 1) {
			this->player.magazine[0]->move(dt, 0, -(this->player.magazine[0]->velocity));
		}

		//Distance between Bullet and Start Position
		this->player.distance = std::sqrt(std::pow(this->player.startpos.x - this->player.magazine[0]->sprite.getPosition().x, 2) + std::pow(this->player.startpos.y - this->player.magazine[0]->sprite.getPosition().y, 2));

		if (this->player.distance > 350) {
			this->player.isvanish = true;
		}

		if (!this->fixenemy.empty()) {
			for (int i = 0; i < this->fixenemy.size(); ++i) {
				if (this->player.magazine[0]->sprite.getGlobalBounds().intersects(this->fixenemy[i]->sprite.getGlobalBounds())) {
					this->fixenemy[i]->healthpoint -= 25;
					this->player.isvanish = true;
					this->fixenemy[i]->isalert = true;
				}
			}
		}

		if (!this->walkenemy.empty()) {
			for (int i = 0; i < this->walkenemy.size(); ++i) {
				if (this->player.magazine[0]->sprite.getGlobalBounds().intersects(this->walkenemy[i]->sprite.getGlobalBounds())) {
					this->walkenemy[i]->healthpoint -= 25;
					this->player.isvanish = true;
					this->walkenemy[i]->isalert = true;
				}
			}
		}

		if (!this->roomenemy.empty()) {
			for (int i = 0; i < this->roomenemy.size(); ++i) {
				if (this->player.magazine[0]->sprite.getGlobalBounds().intersects(this->roomenemy[i]->sprite.getGlobalBounds())) {
					this->roomenemy[i]->healthpoint -= 25;
					this->player.isvanish = true;
					this->roomenemy[i]->isalert = true;
				}
			}
		}
		

		if (this->player.isvanish) {
			this->player.magazine.erase(this->player.magazine.begin() + 0);

			this->player.isshot = false;
			this->player.isstart = false;
			this->player.isvanish = false;
		}
	}
	else if(!this->player.isshot && this->player.ishavepistol && !this->player.magazine.empty()){
		this->player.magazine[0]->sprite.setPosition(this->player.sprite.getPosition().x, this->player.sprite.getPosition().y - this->player.sprite.getGlobalBounds().height/2 - 12);
	}
}

void GameState::response()
{
	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			if (this->fixenemy[i]->isalert) {

				if (!this->fixenemy[i]->startalert) {
					this->fixenemy[i]->start.x = this->spawnpos[i].x;
					this->fixenemy[i]->start.y = this->spawnpos[i].y;
					this->fixenemy[i]->startalert = true;
				}

				this->fixenemy[i]->dest.x = this->player.positiongrid.x;
				this->fixenemy[i]->dest.y = this->player.positiongrid.y;

			}
		}
	}

	
	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			if (this->walkenemy[i]->isalert) {
				
				if (!this->walkenemy[i]->startalert) {
					this->walkenemy[i]->start.x = this->spawnpos[i].x;
					this->walkenemy[i]->start.y = this->spawnpos[i].y;
					this->walkenemy[i]->startalert = true;
				}

				this->walkenemy[i]->dest.x = this->player.positiongrid.x;
				this->walkenemy[i]->dest.y = this->player.positiongrid.y;
			}
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			if (this->roomenemy[i]->isalert) {

				if (!this->roomenemy[i]->startalert) {
					this->roomenemy[i]->start.x = this->inroompos[i].x;
					this->roomenemy[i]->start.y = this->inroompos[i].y;
					this->roomenemy[i]->startalert = true;
				}

				this->roomenemy[i]->dest.x = this->player.positiongrid.x;
				this->roomenemy[i]->dest.y = this->player.positiongrid.y;

			}
		}
	}

}


void GameState::update(const float& dt)
{
	this->updatetime();
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatedt(dt);

	this->textbullet.update(std::to_string(6 - this->player.shoottimer) + "/" + std::to_string(this->player.bullets));
	this->texthealth.update(std::to_string(this->player.healthpoint));
	

	if (!this->isupdatetex) {
		this->imageheart.updatetexture("GameUI/Heart.png",0.05, 640 - 60, 880 + 30);
		this->isupdatetex = true;

		std::stringstream location;
		location << "KGB Headquarters" << std::endl << std::endl

			<< "Albert \"Baron\" Johnson, CIA Agent" << std::endl
			<< "Lubyanka Buliding, Moscow" << std::endl
			<< "24 October 1962";

		this->textlocation.updatestring(location.str());
	}

	//Make text fading
	if (!this->isfadecolor && this->totaltime > 3) {
		if (this->colorindex != 0) {

			if (this->fadecount < 3) {
				this->fadecount++;
			}

			if (this->fadecount == 3) {
				this->textlocation.text.setFillColor(sf::Color(this->colorindex, this->colorindex, this->colorindex));
				this->colorindex = this->colorindex - 15;
				this->fadecount = 0;
			}
		}
		else if (this->colorindex == 0) {
			this->textlocation.text.setFillColor(sf::Color::Transparent);
			this->player.walkmode = true;
			this->isfadecolor = true;
		}
	}
	
	

	this->updateview();
	
	this->updateitems();
	this->MainFloor.update();
	this->player.update(dt);
	this->updaterooms();

	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			this->fixenemy[i]->update(dt);
		}
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			this->walkenemy[i]->update(dt);
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			this->roomenemy[i]->update(dt);
		}
	}

	
	this->collision();
	this->shooting(dt);

	
	this->healthpoint();
	this->equipments();
	this->response();
	this->endgame();
}

void GameState::healthpoint()
{
	if (this->player.healthpoint > 100) {
		this->player.healthpoint = 100;
	}

	if (this->player.healthpoint < 0) {
		this->player.healthpoint = 0;
	}

	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			if (this->player.sprite.getGlobalBounds().intersects(this->fixenemy[i]->magazine[0]->sprite.getGlobalBounds()) && this->fixenemy[i]->isshot) {
				this->player.healthpoint = this->player.healthpoint - 10;
				this->fixenemy[i]->isvanish = true;

				//std::cout << "Bullet Isvanish function called" << std::endl;
			}
		}
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			if (this->player.sprite.getGlobalBounds().intersects(this->walkenemy[i]->magazine[0]->sprite.getGlobalBounds()) && this->walkenemy[i]->isshot) {
				this->player.healthpoint = this->player.healthpoint - 10;
				this->walkenemy[i]->isvanish = true;

				//std::cout << "Bullet Isvanish function called" << std::endl;
			}
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			if (this->player.sprite.getGlobalBounds().intersects(this->roomenemy[i]->magazine[0]->sprite.getGlobalBounds()) && this->roomenemy[i]->isshot) {
				this->player.healthpoint = this->player.healthpoint - 10;
				this->roomenemy[i]->isvanish = true;

				//std::cout << "Bullet Isvanish function called" << std::endl;
			}
		}
	}

	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			if (this->fixenemy[i]->healthpoint <= 0) {
				this->fixenemy.erase(this->fixenemy.begin() + i);
				this->player.enemykilled++;
			}
		}
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			if (this->walkenemy[i]->isdisappear) {
				this->walkenemy.erase(this->walkenemy.begin() + i);
				//std::cout << "Check3" << std::endl;
			}
			else if (this->walkenemy[i]->healthpoint <= 0) {
				this->walkenemy.erase(this->walkenemy.begin() + i);
				this->player.enemykilled++;
				//std::cout << "Check3" << std::endl;
			}
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			if (this->roomenemy[i]->healthpoint <= 0) {
				this->roomenemy.erase(this->roomenemy.begin() + i);
				this->player.enemykilled++;
			}
		}
	}

}

void GameState::writescore(int score)
{
	std::ofstream file("Config/scoreboard.txt", std::ios::out | std::ios::app);
	if (file.is_open() && !this->iswrite) {
		file << score << "\n";
		this->iswrite = true;
	}
}

void GameState::endgame()
{
	if (this->player.healthpoint <= 0) {

		this->isgameover = true;

		if (this->endcount < framerate * 1) {
			this->endcount++;
		}
		else if (this->endcount == framerate * 1) {

			this->endstate();

			this->score =  this->score + (this->totaltime * 69);
			this->score = this->score + (this->player.healthpoint * 50);
			this->score = this->score + (this->player.enemykilled * 1000);

			this->writescore(this->score);

			this->states->pop();
			this->states->push(new EndState(this->window, this->supportedkeys, this->states,this->isgoodending,this->isbadending,this->isgameover,this->score));
			this->endcount = 0;
		}
	}

	if (this->player.positiongrid.y > 31) {

		if (this->player.ishavemic) {
			this->isgoodending = true;
		}
		else {
			this->isbadending = true;
		}

		if (this->endcount < framerate * 1) {
			this->endcount++;
		}
		else if (this->endcount == framerate * 1) {
			
			this->endstate();

			this->score = this->score + (this->totaltime * 69);
			this->score = this->score + (this->player.healthpoint * 50);
			this->score = this->score + (this->player.enemykilled * 1000);

			if (this->isgoodending) {
				this->score += 5000;
			}
			if (this->isbadending && this->score > 2500) {
				this->score -= 2500;
			}

			this->writescore(this->score);

			this->states->pop();
			this->states->push(new EndState(this->window, this->supportedkeys, this->states, this->isgoodending, this->isbadending, this->isgameover,this->score));
			this->endcount = 0;
		}
	}


}



void GameState::endstate()
{
	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			this->fixenemy.erase(this->fixenemy.begin() + i);
		}

		//std::cout << "All fix enemies is deleted" << std::endl;
	}

	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			this->walkenemy.erase(this->walkenemy.begin() + i);
		}

		//std::cout << "All walk enemies is deleted" << std::endl;
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			this->roomenemy.erase(this->roomenemy.begin() + i);
		}

		//std::cout << "All room enemies is deleted" << std::endl;
	}
}


void GameState::render(sf::RenderTarget* target)
{
	//If target binding to nothing then it will bind to window
	if (!target) {
		target = this->window;
	}

	this->window->setView(this->mainview);
	
	this->MainFloor.render(target, sf::Vector2i(this->player.positiongrid));

	if (!this->fixenemy.empty()) {
		for (int i = 0; i < this->fixenemy.size(); ++i) {
			this->fixenemy[i]->render(target);
		}
	}

	
	if (!this->walkenemy.empty()) {
		for (int i = 0; i < this->walkenemy.size(); ++i) {
			this->walkenemy[i]->render(target);
		}
	}

	if (!this->roomenemy.empty()) {
		for (int i = 0; i < this->roomenemy.size(); ++i) {
			this->roomenemy[i]->render(target);
		}
	}

	for (int i = 0; i < 9; ++i) {
		this->rooms[i].render(target);
	}

	if (!this->player.magazine.empty()) {
		this->player.magazine[0]->render(target);
	}

	this->player.render(target);

	

	this->window->setView(this->window->getDefaultView());
	this->textbullet.render(target);
	this->imageheart.render(target);
	this->texthealth.render(target);
	this->textlocation.render(target);
	this->textmiccollect.render(target);
}









