//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "Administrator.h"
#include "Film.h"
#include "Video.h"
#include "Photo.h"
#include "Group.h"

const int PORT = 3331;


int main(int argc, char* argv[])
{
  // cree le TCPServer
  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {
    Administrator admin;
    std::cout << "Administrator created" << std::endl;
    // the request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    
    if (request.rfind("create photo ", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name, filepath;
      int xdim, ydim;
      iss >> name >> filepath >> xdim >> ydim;
      response = "Creating photo: " + name;
      admin.createPhoto(name, filepath, xdim, ydim);
      admin.display(name);
      
    }
    else if (request.rfind("create video", 0) == 0){
      /* code */
    }
    else if (request.rfind("create film", 0) == 0){
      /* code */
    }
    else if (request.rfind("create group", 0) == 0){
      /* code */
    }
    else if (request.rfind("add", 0) == 0) {
      std::string query = request.substr(4);
      // Process the add query
      response = "Adding: " + query;
    }
    else if (request.rfind("play ", 0) == 0) {
      std::string query = request.substr(5);
      // Process the add query
      response = "Playing: " + query;
    }
    else if (request.rfind("search ", 0) == 0) {
      std::string query = request.substr(7);
      // Process the search query
      response = "Searching for: " + query;
    }
    else{
      response = "Unknown command" + request;
    }
    // return false would close the connecytion with the client
    return true;
  });


  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}

