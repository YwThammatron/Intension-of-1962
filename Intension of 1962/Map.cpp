              #include "Map.h"

void Map::inittexture()
{
	if (!this->tilesheettex.loadFromFile("Tilesheet/TileSheet.png")) {
		std::cout << "Tilesheet Loading Error" << std::endl;
	}
}

void Map::initsprite()
{
           
    for (int y = 0; y < this->tilerow; ++y) {
        for (int x = 0; x < this->tilecolumn; ++x) {

            this->sprite[y][x].setTexture(this->tilesheettex);

            this->tilecodex = this->tilecode[y][x];
            this->tilecodey = 0;

            if (this->tilecode[y][x] > 7) {
                this->tilecodey = this->tilecodex / 8;
                this->tilecodex = this->tilecodex % 8;
            }

            this->sprite[y][x].setTextureRect(sf::IntRect(this->gridsizeu * this->tilecodex, this->gridsizeu * this->tilecodey, this->gridsizeu, this->gridsizeu));
            this->sprite[y][x].setPosition(this->gridsizef * x, this->gridsizef * y);
        }
    }
}

Map::Map()
{
	this->inittexture();

	this->gridsizef = 70.f;
	this->gridsizeu = static_cast<unsigned>(this->gridsizef);

    this->initsprite();
}

Map::~Map()
{
    
}

void Map::update()
{
}

void Map::render(sf::RenderTarget* target,sf::Vector2i playerposgrid)
{
    /*this->fromx = playerposgrid.x - 8;
    this->tox = playerposgrid.x + 8;

    this->fromy = playerposgrid.y - 5;
    this->toy = playerposgrid.y + 5;*/

    this->fromx = 0;
    this->fromy = 0;
    
    this->tox = this->tilecolumn;
    this->toy = this->tilerow;

    if (this->fromx < 0) {
        this->fromx = 0;
    }
    else if (this->fromx > this->tilecolumn) {
        this->fromx = this->tilecolumn;
    }

    if (this->tox < 0) {
        this->tox = 0;
    }
    else if (this->tox > this->tilecolumn) {
        this->tox = this->tilecolumn;
    }

    if (this->fromy < 0) {
        this->fromy = 0;
    }
    else if (this->fromy > this->tilerow) {
        this->fromy = this->tilerow;
    }

    if (this->toy < 0) {
        this->toy = 0;
    }
    else if (this->toy > this->tilerow) {
        this->toy = this->tilerow;
    }

    for (int y = this->fromy; y < this->toy; ++y) {
        for (int x = this->fromx; x < this->tox; ++x) {
            target->draw(this->sprite[y][x]);
        }
    }

    
}
