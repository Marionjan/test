/**
 * @file server.cpp
 * @brief Implementation of the TCP server that handles multimedia objects and groups.
 * 
 * This file contains the server logic for handling requests from clients to manage multimedia objects
 * such as photos, videos, and films, as well as groups of multimedia objects. The server listens on
 * a TCP socket and processes various commands sent by the client, including object creation, search, 
 * and display.
 * 
 * @author Eric Lecolinet
 * @contributors Marion Jan 
 * @date 2016
 * @note Telecom ParisTech
 * 
 */

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "Administrator.h"
#include "Film.h"
#include "Video.h"
#include "Photo.h"
#include "Group.h"

const int PORT = 3331; ///< Port on which the server listens for incoming client connections.

/**
 * @brief Main function that initializes and runs the TCP server.
 * 
 * The main function creates a `TCPServer` instance and enters a loop where it waits for requests
 * from clients. Upon receiving a request, the server parses the request and performs the corresponding
 * action, such as creating multimedia objects (photo, video, film), searching for objects, displaying
 * their details, or playing media.
 * 
 * The server responds to each request with a corresponding response message, and the connection remains
 * open until the client terminates it or an error occurs.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if the server runs successfully, 1 if an error occurs.
 */
int main(int argc, char* argv[])
{
  // Create the TCPServer
  Administrator admin; ///< The administrator that handles multimedia objects.

  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {
    
    // The request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    // Handle 'create photo' command
    if (request.rfind("create photo ", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name, pathname;
      int xdim, ydim;
      iss >> name >> pathname >> xdim >> ydim;
      response = "Creating photo: " + name;
      admin.createPhoto(name, pathname, xdim, ydim);

      std::ostringstream oss;
      admin.display(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
      
    }
    // Handle 'create video' command
    else if (request.rfind("create video", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name, pathname;
      int duration;
      iss >> name >> pathname >> duration;
      response = "Creating video: " + name;
      admin.createVideo(name, pathname, duration);
      
      std::ostringstream oss;
      admin.display(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle 'create film' command
    else if (request.rfind("create film", 0) == 0){
      std::string query = request.substr(12);
      std::istringstream iss(query);
      std::string name, pathname;
      int duration, nbChapters;
      iss >> name >> pathname >> duration >> nbChapters;
      int* chapters = new int[nbChapters];
      for (int i = 0; i < nbChapters; i++){
        iss >> chapters[i];
      }
      response = "Creating film: " + name;
      admin.createFilm(name, pathname, duration, chapters, nbChapters);
      
      std::ostringstream oss;
      admin.display(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle 'create group' command
    else if (request.rfind("create group", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Creating group: " + name;
      admin.createGroup(name);
      response = "Group " + name + " created";
    }
    // Handle 'search object' command
    else if (request.rfind("search object", 0) == 0){
      std::string query = request.substr(14);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      
      std::ostringstream oss;
      admin.searchObject(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle 'search group' command
    else if (request.rfind("search group", 0) == 0){
      std::string query = request.substr(13);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      
      std::ostringstream oss;
      admin.searchGroup(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle 'display' command
    else if (request.rfind("display", 0) == 0){
      std::string query = request.substr(8);
      std::istringstream iss(query);
      std::string name;
      iss >> name;
      response = "Displaying: " + name;
      
      std::ostringstream oss;
      admin.display(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle 'play' command
    else if (request.rfind("play ", 0) == 0) {
      std::string query = request.substr(5);
      std::istringstream iss(query);
      std::string name;
      iss >> name;

      std::ostringstream oss;
      admin.play(name, oss);
      std::string ossStr = oss.str();
      std::replace(ossStr.begin(), ossStr.end(), '\n', ';');
      response = ossStr;
    }
    // Handle unknown command
    else{
      response = "Unknown command ... "
        "Available commands: ; "
           "1. create photo <name> <pathname> <xdim> <ydim> ; "
           "2. create video <name> <pathname> <duration> ; "
           "3. create film <name> <pathname> <duration> <nbChapters> <chapters...> ; "
           "4. create group <name> ; "
           "5. search object <name> ; "
           "6. search group <name> ; "
           "7. display <name> ; "
           "8. play <name> ; "
           "9. quit"; 
    }

    // Return true to keep the connection open with the client
    return true;
  });

  // Start the infinite loop of the server
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // If there is an error starting the server
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}
