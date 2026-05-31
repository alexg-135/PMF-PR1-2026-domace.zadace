#include<string>
#include<map>
#include<set>
#include<vector>
#include<utility>

struct SocialNetwork{
    std::set<std::string> users;
    std::map<std::string, std::set<std::string>> following; 

    SocialNetwork();
    SocialNetwork(std::set<std::string> _users);

    bool addUser(std::string user);
    void follow(std::string user1, std::string user2);
    void unfollow(std::string user1, std::string user2);
    bool removeUser(std::string user);
    std::set<std::string> getFollowers(std::string user);
    std::set<std::string> recommend(std::string user);
    std::vector<std::string> getInfluencers();
    std::set<std::pair<std::string, std::string>> getMutualPairs();
};