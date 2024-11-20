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
  Administrator admin;
  
  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {
    
    

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
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name, filepath;
      int duration;
      iss >> name >> filepath >> duration;
      response = "Creating video: " + name;
      admin.createVideo(name, filepath, duration);
      admin.display(name);
    }
    else if (request.rfind("create film", 0) == 0){
      std::string query = request.substr(12);
      std::istringstream iss(query);
      std::string name, filepath;
      int duration, nbChapters;
      iss >> name >> filepath >> duration >> nbChapters;
      int* chapters = new int[nbChapters];
      for (int i = 0; i < nbChapters; i++){
        iss >> chapters[i];
      }
      response = "Creating film: " + name;
      admin.createFilm(name, filepath, duration, chapters, nbChapters);
      admin.display(name);
    }
    else if (request.rfind("create group", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Creating group: " + name;
      admin.createGroup(name);
      admin.display(name);
    }
    else if (request.rfind("search object", 0) == 0){
      std::string query = request.substr(14);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Searching object: " + name;
      admin.searchObject(name);
    }
    else if (request.rfind("search group", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Searching group: " + name;
      admin.searchGroup(name);
    }
    else if (request.rfind("display", 0) == 0){
      std::string query = request.substr(8);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Displaying: " + name;
      admin.display(name);
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
      response = "Unknown command\n\n"
        "Available commands:\n"
           "1. create photo <name> <filepath> <xdim> <ydim>\n"
           "2. create video <name> <filepath> <duration>\n"
           "3. create film <name> <filepath> <duration> <nbChapters> <chapters...>\n"
           "4. create group <name>\n"
           "5. search object <name>\n"
           "6. search group <name>\n"
           "7. display <name>\n"
           "8. play <name>\n"
           "9. search <query>\n";
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

