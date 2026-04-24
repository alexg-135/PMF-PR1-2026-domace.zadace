#include<string>
#include<map>
#include<set>
#include<vector>
#include<utility>

#include "social_network.h"

// struct SocialNetwork{
//     std::set<std::string> users;
//     std::map<std::string, std::set<std::string>> following; 

//     SocialNetwork();
//     SocialNetwork(std::set<std::string> _users);

//     bool addUser(std::string user);
//     void follow(std::string user1, std::string user2);
//     void unfollow(std::string user1, std::string user2);
//     bool removeUser(std::string user);
//     std::set<std::string> getFollowers(std::string user);
//     std::set<std::string> recommend(std::string user);
//     std::vector<std::string> getInfluencers();
//     std::set<std::pair<std::string, std::string>> getMutualPairs();
// };

SocialNetwork::SocialNetwork(){
    return; // TODO: implement this constructor
}

SocialNetwork::SocialNetwork(std::set<std::string> _users){
    return; // TODO: implement this constructor
}

bool SocialNetwork::addUser(std::string user){
    return false; // TODO: implement this function
}

void SocialNetwork::follow(std::string user1, std::string user2){
    return; // TODO: implement this function
}

void SocialNetwork::unfollow(std::string user1, std::string user2){
    return; // TODO: implement this function
}

bool SocialNetwork::removeUser(std::string user){
    return false; // TODO: implement this function
}

std::set<std::string> SocialNetwork::getFollowers(std::string user){
    return std::set<std::string>(); // TODO: implement this function
}

std::set<std::string> SocialNetwork::recommend(std::string user){
    return std::set<std::string>(); // TODO: implement this function
}

std::vector<std::string> SocialNetwork::getInfluencers(){
    return std::vector<std::string>(); // TODO: implement this function
}

std::set<std::pair<std::string, std::string>> SocialNetwork::getMutualPairs(){
    return std::set<std::pair<std::string, std::string>>(); // TODO: implement this function
}
