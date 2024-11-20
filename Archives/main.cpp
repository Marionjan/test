//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include "MultimediaObject.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Group.h"
#include "Administrator.h"
#include <sstream>


using namespace std;

const int PORT = 3331;

/// @brief main function
/// @param argc  
/// @param argv  
/// @return  0
int main(int argc, const char* argv[])
{
    Administrator admin;





    std::cout << "Hello brave new world" << std::endl;

    shared_ptr<Video> mObject1 = make_shared<Video>("video_test.mp4", "C:/Users/Marion/Documents/TELECOM/2A/INF224/video_test.mp4", 10);
    shared_ptr<Photo> mObject2 = make_shared<Photo>("image_test.jpg", "C:/Users/Marion/Documents/TELECOM/2A/INF224/image_test.jpg", 100, 150);
    shared_ptr<Video> mObject3 = make_shared<Video>("video_test2.mp4", "C:/Users/Marion/Documents/TELECOM/2A/INF224/video_test2.mp4", 8);
    shared_ptr<Photo> mObject4 = make_shared<Photo>("image_test2.mp4", "C:/Users/Marion/Documents/TELECOM/2A/INF224/image_test2.mp4", 200, 250);

    // mObject1->display(std::cout);
    // mObject2->display(std::cout);

    // mObject1->play();
    // mObject2->play();

    // //Tableau d'objets multimédia
    // MultimediaObject *mObjects[4];
    // mObjects[0] = mObject1.get();
    // mObjects[1] = mObject2.get();
    // mObjects[2] = mObject3.get();
    // mObjects[3] = mObject4.get();

    // //Affichage des objets multimédia
    // for(int i = 0; i < 4; i++){
    //     mObjects[i]->display(std::cout);
    // }


    // Create a Film object
    int chapters[] = {10, 20, 30, 60};
    // Film *myMovie = new Film("film_test.mp4", "C:/Users/Marion/Documents/TELECOM/2A/INF224/film_test.mp4", 120, chapters, 4);


    // // Display the Film object
    // myMovie->display(std::cout);

    // // Modify the Film object
    // int chapters2[] = {15, 25, 35};
    // myMovie->setChapters(chapters2, 3);

    // // Display the modified Film object
    // myMovie->display(std::cout);

    // // Clean up
    // for(int i = 0; i < 4; i++){
    //     delete mObjects[i];
    // }
    // delete myMovie;


    std::cout << "Hello brave new world" << std::endl;

    // Create groups
    std::shared_ptr<Group> group1 = std::make_shared<Group>("Groupe 1");
    std::shared_ptr<Group> group2 = std::make_shared<Group>("Groupe 2");


    // Add multimedia objects to groups
    group1->push_back(mObject1);
    group1->push_back(mObject2);

    group2->push_back(mObject2); // mObject2 belongs to both group1 and group2
    group2->push_back(mObject3);
    group2->push_back(mObject4);

    // Display groups

    std::cout << " ______________ AFFICHAGE DU GROUPE 1 _____________" << std::endl;
    group1->displayGroup(std::cout);

    std::cout << " ______________ AFFICHAGE DU GROUPE 2 _____________" << std::endl;
    group2->displayGroup(std::cout);



    


    // Clean up groups
    group1.reset();
    std::cout << " ______________ GROUPE 1 SUPPRIME _________________" << std::endl;
    std::cout << " ______________ AFFICHAGE DU GROUPE 2 _____________" << std::endl;
    group2->displayGroup(std::cout);

    
    group2.reset();
    std::cout << " ______________ GROUPE 2 SUPPRIME _________________" << std::endl;




    // Use Administrator
    
    admin.createPhoto("photoAdmin1", "C:/Users/Marion/Documents/TELECOM/2A/INF224/image_test.jpg", 100, 200);
    admin.createPhoto("photoAdmin2", "C:/Users/Marion/Documents/TELECOM/2A/INF224/image_test2.jpg", 150, 250);
    admin.createVideo("videoAdmin1", "C:/Users/Marion/Documents/TELECOM/2A/INF224/video_test.mp4", 10);
    admin.createVideo("videoAdmin2", "C:/Users/Marion/Documents/TELECOM/2A/INF224/video_test2.mp4", 15);
    admin.createFilm("film_testAdmin", "C:/Users/Marion/Documents/TELECOM/2A/INF224/film_test.mp4", 120, chapters, 4);

    admin.createGroup("group1Admin");
    admin.createGroup("group2Admin");

    admin.searchObject("photoAdmin1");
    admin.searchObject("videoAdmin1");
    admin.searchObject("film_testAdmin");

    admin.searchGroup("group1Admin");


    admin.play("videoAdmin1");
    admin.display("Film_testAdmin");   


    return 0;
}

