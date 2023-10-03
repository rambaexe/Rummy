#ifndef classes
#define classes

#include <iostream>
#include <string.h>
#include <algorithm> 
#include <ctime>   
#include <random>
#include "console_h.h"
using namespace std;

const int stacksno = 15;
const int tilesinstackno = 7;
const int tilesno = 13;
const int nono = 2;
const int tilesingameno = 106;
const int maxtilesonboard = 15;

class Tile
{
public:
	string type;
	int downpoints;
	int finalpoints;
	int no;
	bool atu;
	bool move;

	Tile(string type, int no) : type(type), no(no)
	{
		downpoints = 0;
		finalpoints = 0;
		atu = false;
		move = true;
	}

	void virtual displayInfo() const
	{
		/*cout << "Type: " << type << endl;
		cout << "No: " << no << endl;
		cout << "Down Points: " << downpoints << endl;
		cout << "Final Points: " << finalpoints << endl;*/
	}

	static vector<Tile*> CreateTiles();

	void ResetTile()
	{
		downpoints = 0;
		finalpoints = 0;
		atu = false;
		move = true;
	}

	static void SetMoveFalse(vector <Tile*>& tilesgiven)
	{
		for (const auto& tile : tilesgiven)
		{
			if(tile->type != "joker")
				tile->move = false;
		}
	}

	static void DisplayAtu(vector <Tile*>& alltiles)
	{
		for (const auto& tile : alltiles)
		{
			if (tile->atu == true)
			{
				cout << "ATU: ";
				tile->displayInfo();
				cout << endl;
			}
		}
	}

	static void DisplayMoveFalse(vector <Tile*> tiles)
	{
		cout << "Move False: "<<endl;
		for (const auto& tile : tiles)
		{
			if (tile->move == false)
			{
				tile->displayInfo();
			}
		}
		cout << endl;
	}

	static void DisplayTiles(vector <Tile*>& tiles)
	{
		for (const auto& tile : tiles)
		{
			tile->displayInfo();
		}
		cout << endl;
	}

	static void DisplayStacks(vector <vector<Tile*>> stacks)
	{
		for (auto& stack : stacks)
		{
			Tile::DisplayTiles(stack);
			//cout << endl;
			//cout << "--------------------------------------------------" << endl;
		}
	}

	static vector<Tile*> RandomiseTiles(vector<Tile*> tiles)
	{
		random_device rd;
		mt19937 engine(rd());
		shuffle(tiles.begin(), tiles.end(), engine);
		return tiles;
	}

	static vector<vector<Tile*>> CreateStacks(vector <Tile*> tiles)
	{
		tiles = Tile::RandomiseTiles(tiles);
		vector<vector<Tile*>> stacks;
		for (int j = 1; j <= stacksno; j++)
		{
			vector <Tile*> stack;
			for (int i = 0; i < tilesinstackno; i++)
			{
				stack.push_back(tiles[(j - 1) * tilesinstackno + i]);
			}
			stacks.push_back(stack);
		}
		vector <Tile*> stack;
		stack.push_back(tiles[tiles.size() - 1]);
		tiles[tiles.size() - 1]->atu = true;
		stacks.push_back(stack);
		return stacks;
	}

	int virtual getnumber()
	{
		return 0;
	}
	
	string virtual getcolour() 
	{
		return "";
	}
};

class NormalTile : public Tile
{
public:
	string colour;
	int number;

	NormalTile(string colour, int number, int no) : Tile("normal", no), colour(colour), number(number)
	{
		if (number == 1)
		{
			finalpoints = 25;
		}
		else {
			if (number >= 2 && number <= 9)
			{
				finalpoints = 5;
			}
			else
			{
				if (number >= 10 && number <= 13)
				{
					finalpoints = 10;
				}
			}
		}
	}

	void displayInfo() const override
	{
		Tile::displayInfo();
		/*cout << "Colour: " << colour << endl;
		cout << "Number: " << number << endl;*/


		if (colour == "blue")
			Console::setConsoleColour(blue);
		else
			if (colour == "red")
				Console::setConsoleColour(red);
			else
				if (colour == "yellow")
					Console::setConsoleColour(yellow);
				else
					Console::setConsoleColour(white);

		cout << number;
		Console::setConsoleColour(white);
		cout << " ";
		//cout << endl;
	}

	int getnumber() override
	{
		return number;
	}

	string getcolour() override
	{
		return colour;
	}
};

class JokerTile : public Tile
{
public:

	JokerTile(int no) : Tile("joker", no)
	{
		finalpoints = 50;
	}

	void displayInfo() const override
	{
		cout << type;
		Tile::displayInfo();
		cout << " ";
		//cout << endl;
	}
};


vector<Tile*> Tile::CreateTiles()
{
	vector<Tile*> tiles;
	tiles.push_back(new JokerTile(1));
	tiles.push_back(new JokerTile(2));

	for (int i = 1; i <= nono; i++)
	{
		for (int j = 1; j <= tilesno; j++)
		{
			tiles.push_back(new NormalTile("blue", j, i));
			tiles.push_back(new NormalTile("red", j, i));
			tiles.push_back(new NormalTile("yellow", j, i));
			tiles.push_back(new NormalTile("black", j, i));
		}
	}
	return tiles;
}


class Board
{
public:
	vector <Tile*> board_tiles;
	int tilesnoboard;

	Board()
	{
		tilesnoboard = 0;
	}

	void addtoBoard(vector <Tile*> tstack)
	{
		tilesnoboard += int(tstack.size());
		for (int i = 0; i < tstack.size(); i++)
		{
			board_tiles.push_back(tstack[i]);
		}
	}

	/*void Reset_Board()
	{
		board_tiles.clear();
		tilesnoboard = 0;
	}*/

	void displayBoardinfo()
	{
		cout << tilesnoboard << endl;
		for (const auto& tile : board_tiles)
		{
			tile->displayInfo();
		}
	}
};

class Player
{
public:
	static int number_of_players;
	Board* playerboard;
	int match_points;
	int total_points;
	int playerno;

	Player()
	{
		playerboard = new Board();
		number_of_players++;
		playerno = number_of_players;
		match_points = 0;
		total_points = 0;
	}

	void displayPlayerinfo() const
	{
		cout << "PLAYER " << playerno << endl;
		// cout << "Points: " << points << endl;
		playerboard->displayBoardinfo();
		cout << endl;
	}

	void displayPlayername() const
	{
		cout << "PLAYER " << playerno << endl;
	}

	void ResetPlayer()
	{
		playerboard = new Board();
		match_points = 0;
	}

	static void DisplayPlayers(vector <Player*>& players)
	{
		for (int i = 0; i < Player::number_of_players; i++)
		{
			players[i]->displayPlayerinfo();
		}
	}

	static vector <Player*> InitialisePlayers()
	{
		int n;
		while (true)
		{
			cout << "Enter number of players: ";
			cin >> n;
			if (n >= 1 && n <= 4)
			{
				break;
			}
			cout << "Invalid input, please try again" << endl;
		}
		vector <Player*> players = InitialiseNPlayers(n);
		return players;
	}

	static vector <Player*> InitialiseNPlayers(int n)
	{
		vector <Player*> players;
		for (int i = 1; i <= n; i++)
		{
			players.push_back(new Player());
		}
		return players;
	}

	static Player* get_Player(int no, vector<Player*> players)
	{
		for (const auto& player : players)
		{
			if (no == player->playerno)
			{
				return player;
			}
		}

	}

	int getPlayerNumber()
	{
		int pnumber = 0;
		string numberstring;
		cout << "Number: ";
		
		cin >> numberstring;

		try
		{
			pnumber = stoi(numberstring);
		}
		catch (exception& err)
		{
			cout << "Error occured. You must insert a number."<<endl;
		}
		
		return pnumber;
	}

	string getPlayerColour()
	{
		string pcolour;
		cout << "Colour: ";
		cin >> pcolour;
		return pcolour;
	}

	int getPlayerOption1()
	{
		int pnumber = 0;
		string numberstring;
		cout << "Choose from taking a tile from the stacks (1) or taking a tile from the queue (2): ";

		cin >> numberstring;

		try
		{
			pnumber = stoi(numberstring);
		}
		catch (exception& err)
		{
			cout << "Error occured. You must insert a number." << endl;
		}

		return pnumber;
	}

	tuple<string, int, string> getPlayerInputTile()			// type, number, colour
	{
		// get Type:
		string stringp;
		cout << "Type [n - normal; j - joker]: ";
		cin >> stringp;

		if (stringp == "j")
		{
			return make_tuple("joker", 0, "");
		}
		else if (stringp == "n")
		{
			int pnumber = getPlayerNumber();
			string pcolour = getPlayerColour();

			return make_tuple("normal", pnumber, pcolour);
		}
		return make_tuple("notvalid", 0, "notvalid");
	}

	static void removeTilefromBoard(string currenttype, int currentnumber, string currentcolour, Player*& player)
	{
		int i = 0;
		for (int i = 0; i < player->playerboard->board_tiles.size(); i++)
		{
			if ((currenttype == "joker" && currenttype == player->playerboard->board_tiles[i]->type) ||
				(player->playerboard->board_tiles[i]->getnumber() == currentnumber
				&& player->playerboard->board_tiles[i]->getcolour() == currentcolour))
			{
				player->playerboard->board_tiles.erase(player->playerboard->board_tiles.begin() + i);
				player->playerboard->tilesnoboard--;
				break;
			}
		}
		// cout << endl;  player->playerboard->displayBoardinfo();
	}

};

int Player::number_of_players = 0;

class Game
{
public:
	int multiplier;
	int roundpointer;
	int matchpointer;

	Game()
	{
		roundpointer = 0;
		matchpointer = 0;
		multiplier = 1;
	}

	vector <Tile*> DivideStacks(vector <vector<Tile*>> stacks, vector <Tile*>& alltiles, vector <Player*>& players)
	{
		//stacks[stacks.size()-1][0] -> Atu

		cout << "ATU: ";
		stacks[stacks.size() - 1][0]->displayInfo(); cout << endl;
		stacks[stacks.size() - 1][0]->move = false;							//do not allow atu to be moved

		int pos = 1;
		if (stacks[stacks.size() - 1][0]->type == "normal")
		{
			pos = stacks[stacks.size() - 1][0]->getnumber();
		}

		stacks[pos].push_back(stacks[pos - 1][stacks[pos - 1].size() - 1]);      // last tile moved to the next stack
		stacks[pos - 1][stacks[0].size() - 1] = stacks[stacks.size() - 1][0];  // atu to the new stack
		stacks.pop_back();

		Tile::DisplayStacks(stacks);

		// divide stacks
		if (matchpointer == Player::number_of_players)
		{
			matchpointer = 1;
		}
		else 
		{
			matchpointer++;
		}
		int auxmatchpointer = matchpointer-1;
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < Player::number_of_players; i++)
			{
				if (pos == stacks.size())
				{
					pos = 0;
				}
				Tile::SetMoveFalse(stacks[pos]);
				players[auxmatchpointer]->playerboard->addtoBoard(stacks[pos]);
				stacks.erase(stacks.begin() + pos);

				if (auxmatchpointer == Player::number_of_players - 1)
				{
					auxmatchpointer = 0;
				}
				else
				{
					auxmatchpointer++;
				}
			}
		}
		Player::DisplayPlayers(players);

		// Creating queue:
		vector <Tile*> queue;

		while (stacks.size() != 0)
		{
			if (pos == stacks.size())
			{
				pos = 0;
			}
			if (stacks.size() == 1)        // last stack with atu
			{
				for (int j = stacks[pos].size() - 2; j >= 0; j--)
				{
					queue.push_back(stacks[pos][j]);
				}
				queue.push_back(stacks[pos][stacks[pos].size() - 1]);
			}
			else
			{
				for (int j = stacks[pos].size() - 1; j >= 0; j--)
				{
					queue.push_back(stacks[pos][j]);
				}
			}
			stacks.erase(stacks.begin() + pos);
		}

		// Set move

		return queue;
	}

	static void Reset_Match(vector <Tile*>& alltiles, vector <Player*>& players)
	{
		for (const auto& tile : alltiles)
		{
			tile->ResetTile();
		}
		for (const auto& player : players)
		{
			player->ResetPlayer();
		}
	}
	
	static Tile* CheckTile(string ptype, int pnumber, string pcolour, vector<Tile*> playertiles)
	{
		for (const auto& tile : playertiles)
		{
			if (ptype == "joker")
			{
				if (tile->type == ptype)
				{
					return tile;
				}
			}
			else
			{
				if (tile->type == ptype && tile->getnumber() == pnumber && tile->getcolour() == pcolour)
				{
					return tile;
				}
			}
		}
		Tile* notonboardtile = new Tile("notvalid", 0);
		return notonboardtile;
	}

	void Match(vector <Player*>& players, vector <Tile*>& stackqueue, vector <Tile*>& alltiles, vector <Tile*>& queue)
	{
		// choose player to start (with 15 tiles):
		for (const auto& player : players)
		{
			if (player->playerboard->tilesnoboard == maxtilesonboard)
			{
				Game::roundpointer = player->playerno;
			}
		}
	
		Player* currentPlayer = Player::get_Player(roundpointer, players);
		string currenttype, currentcolour;
		int currentnumber;
		Tile* currentTile = new Tile("", 0);

		// get player input for tile
		currentPlayer->displayPlayerinfo();
		cout << "Choose card to put in queue." << endl;
		while (true)
		{
			tie(currenttype, currentnumber, currentcolour) = currentPlayer->getPlayerInputTile();
			currentTile = CheckTile(currenttype, currentnumber, currentcolour, currentPlayer->playerboard->board_tiles);
			currentTile->displayInfo();
			if (currentTile->no == 0  && currentTile->type == "notvalid")
			{
				cout << "Not a valid tile. Try again." << endl;
			}
			else
			{
				break;
			}
		}
		currentTile->displayInfo(); cout << endl;

		Player::removeTilefromBoard(currenttype, currentnumber, currentcolour, currentPlayer);
		currentPlayer->displayPlayerinfo();
		
		queue.push_back(currentTile);
		cout << "Queue: ";  Tile::DisplayTiles(queue);
		queue[0]->move = false;			// cannot pick the first card
		
		int ct = 1;
		for (int i = 0; i <= 9; i++)
		{
			players[roundpointer]->displayPlayerinfo();

			if (roundpointer == Player::number_of_players - 1)
			{
				roundpointer = 0;
			}
			else
			{
				roundpointer++;
			}
			ct++;
			
			players[roundpointer]->displayPlayerinfo();
			Player* currentPlayer = Player::get_Player(roundpointer, players);
			

			//if (ct == 2) // second player not allowed to break
			//{

			//}
			//else
			//{

			//}

			Tile* currentTile = new Tile("", 0);

			// get player input for tile
			players[roundpointer]->displayPlayerinfo();
			cout << "Choose card to put in queue." << endl;
			while (true)
			{
				tie(currenttype, currentnumber, currentcolour) = players[roundpointer]->getPlayerInputTile();
				currentTile = CheckTile(currenttype, currentnumber, currentcolour, players[roundpointer]->playerboard->board_tiles);
				currentTile->displayInfo();
				if (currentTile->no == 0 && currentTile->type == "notvalid")
				{
					cout << "Not a valid tile. Try again." << endl;
				}
				else
				{
					break;
				}
			}
			currentTile->displayInfo(); cout << endl;

			Player::removeTilefromBoard(currenttype, currentnumber, currentcolour, players[roundpointer]);
			// currentPlayer->displayPlayerinfo();
			players[roundpointer]->displayPlayerinfo();

			queue.push_back(currentTile);
			cout << "Queue: ";  Tile::DisplayTiles(queue);
			queue[0]->move = false;			// cannot pick the first card
		}
	}
};

#endif
