/// something new that is my first game 
// concept : 
//			*simple 2d open world
//			*really small world size
//          *small battle mechanics
// story   :
//          ---haven't decided yet---
//features :
//			*saving the game feature
//          *attacking mechanics 
//          *hostile mobs

#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>
#include<fstream>

std::vector<sf::RectangleShape> Cells;

class Grid
{
	int size = 8;
	int horizontal = 8;
	int vertical = 12;
public:
	Grid() {};
	Grid(int Size) :size(Size) { horizontal = size; vertical = size; };
	Grid(int Horizontal, int Vertical) :horizontal(Horizontal), vertical(Vertical) {};

	sf::Texture CellTextures[6];
	const std::string FilePaths[6] = { "Cell_Textures/tree.png",
							"Cell_Textures/grass.png",
									  "Cell_Textures/rock.png",
									  "Cell_Textures/wood.png",
									  "Cell_Textures/water.png",
									  "Cell_Textures/marsh.png" };
	void LoadTextures()
	{
		for (int i = 0; i < 6; i++)
		{
			if (!CellTextures[i].loadFromFile(FilePaths[i]))
			{
				std::cout << "error";
			}
		}

	}
	float cellWGlobal = 0;
	void create(float CellWidth = 50, float CellGap = 10, sf::Color CellColor = sf::Color::Blue)
	{
		cellWGlobal = CellWidth;
		sf::RectangleShape initCell;
		initCell.setSize({ CellWidth, CellWidth });
		//initCell.setFillColor(CellColor);
		for (int y = 0; y < vertical; y++)
		{
			for (int x = 0; x < horizontal; x++)
			{
				float positionX = (CellWidth + CellGap/2) * x + CellGap/2;
				float positionY = (CellWidth + CellGap/2) * y + CellGap/2;
				initCell.setPosition({ positionX, positionY });
				Cells.push_back(initCell);
			}
		}
	}
	void Print(sf::RenderWindow &w, float BufferWidth, float BufferHeight, sf::Vector2f BufferCenter)
	{
		int bufferStartX = (BufferCenter.x - (BufferWidth / 2)) / cellWGlobal;
		int bufferStartY = (BufferCenter.y - (BufferWidth / 2)) / cellWGlobal;
		int bufferEndX = (BufferCenter.x + (BufferWidth / 2)) / cellWGlobal;
		int bufferEndY = (BufferCenter.y + (BufferWidth / 2)) / cellWGlobal;
		
		for (int i = bufferStartY+2; i < bufferEndY -1; i++)
		{
			for (int j = bufferStartX; j < bufferEndX+1; j++)
			{

				//std::cout << "jump\n";

				int n = (j) + 70 * (i);
				//std::cout << Cells.size() << " " << n;
				w.draw(Cells[n]);
			}
		}
	}

	std::vector<std::string> FileTokens;
	void Load(std::string filename, int Number_of_rows)
	{
		std::fstream fs;
		fs.open(filename);
		////ENTITIES DEFINED/////////
		/// ASCII art 
		/// tree : 1
		/// grass: -
		/// rock : o
		/// wood : = 
		/// water: .
		/// MARSH (WORLD BORDER): M
		std::string entities[6] = { "|", "-", "o", "=", ".", "M"};
		std::string token;
		while (fs >> token)
		{
			FileTokens.push_back(token);
		}

		int RowNumber = 0;
		int Number_of_colunms = FileTokens.size() / Number_of_rows;
		for (int i = 0; i < FileTokens.size(); i++)
		{
			if (i % Number_of_colunms == 0 && i != 0)
			{
				RowNumber += 1;
			}
			int actualI = i - Number_of_colunms * RowNumber;

			if (FileTokens[i] == entities[0])
			{
				Cells[i].setTexture(&CellTextures[0]);
				//Cells[i].setFillColor(sf::Color(6, 48, 10));
			}
			else if (FileTokens[i] == entities[1])
			{
				Cells[i].setTexture(&CellTextures[1]);
				//Cells[i].setFillColor(sf::Color(23, 135, 48));
			}
			else if (FileTokens[i] == entities[2])
			{
				Cells[i].setTexture(&CellTextures[2]);
				//Cells[i].setFillColor(sf::Color(74, 74, 71));
			}
			else if (FileTokens[i] == entities[3])
			{
				Cells[i].setTexture(&CellTextures[3]);
				//Cells[i].setFillColor(sf::Color(48,6,6));
			}
			else if (FileTokens[i] == entities[4])
			{
				Cells[i].setTexture(&CellTextures[4]);
				//Cells[i].setFillColor(sf::Color::Blue);
			}
			else if (FileTokens[i] == entities[5])
			{
				Cells[i].setTexture(&CellTextures[5]);
				//Cells[i].setFillColor(sf::Color(7, 36, 9));
			}
		}
	}


};

class Player
{
public:
	Player() {};

	sf::RectangleShape Body;
	sf::Texture manright;
	sf::Texture manleft;
	sf::Texture manup;
	sf::Texture mandown;

	std::string filepaths[4] = { "Cell_Textures/manleft.png", "Cell_Textures/manright.png",
								"Cell_Textures/manup.png", "Cell_Textures/mandown.png"};
                                
	void Spwan(std::vector<float> PlayerCoords, float radius, sf::Color PlayerColor = sf::Color::White)
	{
		Body.setSize({2*radius, 2*radius});
		if (!manleft.loadFromFile(filepaths[0]) ||
			!manright.loadFromFile(filepaths[1]) ||
			!manup.loadFromFile(filepaths[2]) ||
			!mandown.loadFromFile(filepaths[3]))
		{
			std::cout << "player error";
		}
		//Body.setFillColor(PlayerColor);
		Body.setTexture(&manleft);
		Body.setPosition({ PlayerCoords[0], PlayerCoords[1] });
	}
	void Draw(sf::RenderWindow &r)
	{
		r.draw(Body);
	}
	void Move(float Speed, std::string Direction, float limit)
	{
		float CurrentCoordsX = Body.getPosition().x;
		float CurrentCoordsY = Body.getPosition().y;

		if (Direction == "UP" && CurrentCoordsY - Speed > limit)
		{
			Body.setPosition({ CurrentCoordsX, CurrentCoordsY - Speed });
			Body.setTexture(&manup);

		}
		else if (Direction == "RIGHT" && CurrentCoordsX + Speed < limit)
		{
			Body.setPosition({ CurrentCoordsX + Speed, CurrentCoordsY });
			Body.setTexture(&manright);

		}
		else if (Direction == "DOWN" && CurrentCoordsY + Speed < limit)
		{
			Body.setPosition({ CurrentCoordsX, CurrentCoordsY + Speed });
			Body.setTexture(&mandown);

		}
		else if (Direction == "LEFT" && CurrentCoordsX - Speed > limit)
		{
			Body.setPosition({ CurrentCoordsX - Speed, CurrentCoordsY });
			Body.setTexture(&manleft);

		}
	}
	sf::Vector2f HasCoord()
	{
		return Body.getPosition();
	}
	void SetCoord(sf::Vector2f pos)
	{
		Body.setPosition(pos);
	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "My Game");
	window.setFramerateLimit(60);

	sf::View PlayerView;
	PlayerView.setSize({ 1280, 720 });

	int mapGridWidth = 42, mapGridHeight = 20;
	int SingleSideBorderX = 14, SingleSideBorderY = 10;
	int BorderX = 2* SingleSideBorderX, BorderY = 2* SingleSideBorderY;
	int totalAreaX = mapGridWidth + BorderX, totalAreaY = mapGridHeight + BorderY;

	Grid MapGrid(totalAreaX, totalAreaY);
	float CellWidth = 50, CellSpacing = 0;
	MapGrid.create(CellWidth, CellSpacing);
	MapGrid.LoadTextures();          ////// this is the prefect place for texture do not change
    relativePath = "try.txt";
    
	MapGrid.Load(AbsloutePath, totalAreaY);


	Player Player1;
	float SpwanCoordX = (CellWidth*totalAreaX)/2,SpwanCoordY =  (CellWidth*totalAreaY)/2;
	float PlayerWidthR = 30;
	Player1.Spwan({ SpwanCoordX, SpwanCoordY }, PlayerWidthR);
	PlayerView.setCenter({ SpwanCoordX, SpwanCoordY });
	float Speed = 10;

	while (window.isOpen())
	{

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keypressed = event->getIf<sf::Event::KeyPressed>())
			{
				bool hold = false;
				if (keypressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window.close();
				}
			}
		}
		///////KEYBOARD INPUT////////
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
					Player1.Move(Speed, "UP", SingleSideBorderY*CellWidth);
					PlayerView.setCenter(Player1.HasCoord());
					//std::cout << Speed << "\n";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
					Player1.Move(Speed, "RIGHT", CellWidth * (totalAreaX - SingleSideBorderX) - 2 * PlayerWidthR);
					PlayerView.setCenter(Player1.HasCoord());
					//std::cout << Speed << "\n";

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
					Player1.Move(Speed, "DOWN", CellWidth * (totalAreaY - SingleSideBorderY) - 2* PlayerWidthR);
					PlayerView.setCenter(Player1.HasCoord());
					//std::cout << Speed << "\n";

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
					Player1.Move(Speed, "LEFT", CellWidth * SingleSideBorderX);
					PlayerView.setCenter(Player1.HasCoord());
					//std::cout << Speed << "\n";

			}
			// to fix the speed issue need polar coordinates, don't have time for that
		////////////////////////////

		window.setView(PlayerView);
		window.clear(sf::Color::White);
		//std::cout << " check1\n";

		MapGrid.Print(window, 1280, 720, Player1.HasCoord());
		//std::cout << " check2\n";
		Player1.Draw(window);
		//window.draw(rect);
		window.display();
	}


	return 0;
}