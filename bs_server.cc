//******************************************************************************
// File:        bs_client.cc
// Author:      Wesley Ryder
// Description:
//******************************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

//using namespace std;

using namespace std;
using boost::asio::ip::tcp;

string endgameMsg(int game_state)
{
  string msg;
  switch(game_state)
  {
    case 1:
      msg = "Player 1 Won!";
      break;
    case 2:
      msg = "Player 2 won!";
      break;
    case 3:
      msg = " --- Tie --- ";
      break;
  }
  return msg;
}

bool game_status(int state)
{
    if(state == 1 || state == 2 || state == 3)
    {
      return true;
    }
    else{return false;}
}


int determine_winner(int p1, int p2)
{
  if(p1 == 3 && p2 == 3) {
    return 3;
  }
  else if(p1 == 3 && p2 < p1) {
    return 1;
  }
  else if(p2 == 3 && p1 < p2) {
    return 2;
  }
  else{return 0;}
}

void update_player_points(int &player_points, int p1_response)
{
  if(p1_response == 2)
  {
    player_points++;
  }
}

int place_shot(vector<vector<int> > &enemy_board, string data)
{
  int x = 0;
  int y = 0;

  int hit  = 2;
  int miss = 3;

  string tmp;
  int pos = 0;

  string delimiter = "-";

  tmp = data.substr(pos, data.find(delimiter));
  y = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  x = stoi(tmp);
  pos += data.find(delimiter) + 1;

  if(enemy_board[y][x] == 1)
  {
    return 2;
  }
  else{return 3;}


}

void place_ship(vector<vector<int> > &board, string data)
{
  int x1 = 0;
  int x2 = 0;
  int x3 = 0;
  int y1 = 0;
  int y2 = 0;
  int y3 = 0;

  string tmp;
  int pos = 0;

  string delimiter = "-";

  for (int i=0;i<4;i++) {
    vector<int> t;
    for (int j=0;j<4;j++) {
      t.push_back(0);
    }
    board.push_back(t);
  }

  tmp = data.substr(pos, data.find(delimiter));
  y1 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  x1 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  y2 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  x2 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  y3 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  tmp = data.substr(pos, data.find(delimiter));
  x3 = stoi(tmp);
  pos += data.find(delimiter) + 1;

  board[y1][x1] = 1;
  board[y2][x2] = 1;
  board[y3][x3] = 1;


  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      cout << board[i][j];
    }
    cout << endl;
  }


}

void RSP() {

    bool game_over = false;
    int game_state = 0;
    string winner = "";

    int p1_pts = 0;
    int p2_pts = 0;

    vector<vector<int> > player_one_board;
    vector<vector<int> > player_two_board;
    vector<vector<int> > player_one_fire;
    vector<vector<int> > player_two_fire;


    boost::asio::io_service my_service;

    // Accept connections on
    // Advertise a service on port 4700
    tcp::acceptor acceptor(my_service, tcp::endpoint(tcp::v4(), 4700));

    //Wait for a connection on Socket #1
    tcp::socket socket1(my_service);
    acceptor.accept(socket1);
    // Connection Established!!!

    //Wait for a connection on Socket #2
    tcp::socket socket2(my_service);
    acceptor.accept(socket2);
    // Connection Established!!!!

    // Read from Socket 1 until newline
    boost::asio::streambuf buf;
    boost::asio::read_until( socket1, buf, "\n" );
    string data = boost::asio::buffer_cast<const char*>(buf.data());

    // Read from Socket 2 until newline
    boost::asio::streambuf buf2;
    boost::asio::read_until( socket2, buf2, "\n" );
    string data2 = boost::asio::buffer_cast<const char*>(buf2.data());


    place_ship(player_one_board, data);
    place_ship(player_two_board, data2);

    // This is just a block for placing a target hit location for enemy board
    // after ship placement. Everything proceeding the '_|' is meaningless
    // and is there as a joke
    string gatez = "1| We about to play a mean game of batlle ship my guy";
    string gatez2 = "2| What lies behind this gate kappa ripppp";

    boost::asio::write( socket1, boost::asio::buffer(gatez) );
    boost::asio::write( socket2, boost::asio::buffer(gatez2) );

    while (!game_over)
    {
      int p1_response;
      int p2_response;
      string buf1_;
      string buf2_;

      // Player 1
      boost::asio::streambuf buf;
      boost::asio::read_until( socket1, buf, "\n" );
      string data = boost::asio::buffer_cast<const char*>(buf.data());

      // Player 2
      boost::asio::streambuf buf2;
      boost::asio::read_until( socket2, buf2, "\n" );
      string data2 = boost::asio::buffer_cast<const char*>(buf2.data());

      // Player 1
      p1_response = place_shot(player_two_board, data);
      update_player_points(p1_pts, p1_response);
      cout << "p1 response "<<p1_response << endl;
      buf1_ = to_string(p1_response);
      buf1_.append("\n");

      // Player 2
      p2_response = place_shot(player_one_board, data2);
      update_player_points(p2_pts, p2_response);
      cout << "p2 response "<< p2_response << endl;
      buf2_ = to_string(p2_response);
      buf2_.append("\n");

      cout << "p1 pts, p2 pts " << p1_pts << " " << p2_pts << endl;
      game_state = determine_winner(p1_pts, p2_pts);
      cout << "game status " << game_state << endl;
      game_over = game_status(game_state);
      cout << "game over? " << game_over << endl;

      if(game_over == true)
      {
        cout << "Got here " << endl;
        buf1_ = "-1";
        buf1_.append("\n").append(endgameMsg(game_state)).append("*");
        buf2_ = "-1";
        buf2_.append("\n").append(endgameMsg(game_state)).append("*");
        cout << buf1_.substr(3, buf1_.find("*") - 3) << endl;
      }

      boost::asio::write( socket1, boost::asio::buffer(buf1_) );
      boost::asio::write( socket2, boost::asio::buffer(buf2_) );

    }
}

int main()
{
  RSP();

  return 0;
}
