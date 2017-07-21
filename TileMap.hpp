#ifndef TILEMAP_HPP
#define TILEMAP_HPP


#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

		TileMap::tiles = tiles;
		TileMap::width = width;


        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
				//Scales tile to be tileLength long and wide
				double tileLength = 40.0;
				TileMap::tileLength = tileLength;
				double scaleTileX = tileLength / tileSize.x;
				double scaleTileY = tileLength / tileSize.y;

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize.x * scaleTileX, j * tileSize.y * scaleTileY);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x * scaleTileX, j * tileSize.y * scaleTileY);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x * scaleTileX, (j + 1) * tileSize.y * scaleTileY);
				quad[3].position = sf::Vector2f(i * tileSize.x * scaleTileX, (j + 1) * tileSize.y * scaleTileY);

				// get the current tile number
				int tileNumber = tiles[i + j * width];
				
				if (tileNumber != -1)
				{
					/*
					// find its position in the tileset texture
					int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
					int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
					*/

					int tu = tileNumber % 10;
					int tv = tileNumber / 10;



					/*
					// define its 4 texture coordinates
					quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
					quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
					quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
					quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
					*/

					// define its 4 texture coordinates for tiles.png
					int space = 2;
					int spaceRegion = 3 * (tv / 3); //Space between every region, such as between ice and grass regions
					int startX = 9;
					int startY = 5;
					quad[0].texCoords = sf::Vector2f(startX + tu * (tileSize.x + space), startY + spaceRegion + tv * (tileSize.y + space));
					quad[1].texCoords = sf::Vector2f(startX + tu * (tileSize.x + space) + tileSize.x, startY + spaceRegion + tv * (tileSize.y + space));
					quad[2].texCoords = sf::Vector2f(startX + tu * (tileSize.x + space) + tileSize.x, startY + spaceRegion + tv * (tileSize.y + space) + tileSize.y);
					quad[3].texCoords = sf::Vector2f(startX + tu * (tileSize.x + space), startY + spaceRegion + tv * (tileSize.y + space) + tileSize.y);
				}
            }

        return true;
    }

	int getTileType(int x, int y)
	{
		int xTileLoc = x / tileLength;
		int yTileLoc = y / tileLength;

		int arrayPos = yTileLoc * width + xTileLoc;

		return tiles[arrayPos];
	}

	int getTileLength()
	{
		return tileLength;
	}


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
	int width;
	int tileLength;
	const int* tiles;
};

#endif