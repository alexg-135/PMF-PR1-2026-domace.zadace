/**
 * @file social_network.cpp
 * @brief Implementacija strukture SocialNetwork
 * 
 * @author Alexander Gustovarac
 * @date 24-04-2026
 */

#include<string>
#include<map>
#include<set>
#include<vector>
#include<utility>

#include "social_network.h"

/**
 * @brief Defultni konstruktor za SocialNetwork. 
 * Inicijalizuje prazan set od stringova i map
 * 
 * @param
 * 
 * @return void
 */
SocialNetwork::SocialNetwork(){
    users = std::set<std::string>();
    following = std::map<std::string, std::set<std::string>>();
}

/**
 * @brief Konstruktor za SocialNetwork. 
 * Inicijalizuje prazan set od stringova i map
 *
 * @param _users set od stringov
 * 
 * @return void
 */
SocialNetwork::SocialNetwork(std::set<std::string> _users){
    users = std::set<std::string>();
    following = std::map<std::string, std::set<std::string>>();

    for (std::string _user : _users)
    {
        users.insert(_user);
        following[_user] = std::set<std::string>();
    }
}

/**
 * @brief unkcija koja dodaje novog korisnika u društvenu mrežu.
 * Novi korisnik ne prati nikog. Ako se korisnik user već nalazi u društvenoj mreži, funkcija ne
 * radi ništa. Funkcija vraća true ako je dodan novi korisnik, inače vraća false.
 * 
 * @param user nov korisnik koji se dodaje u socialnu serijsku sredinu. 
 * 
 * @return true ako je nov korisnik dodan, inace false.
 */
bool SocialNetwork::addUser(std::string user){
    if(users.find(user) != users.end()){
        return false;
    }

    users.insert(user);
    following[user] = std::set<std::string>();

    return true;
}

/**
 * @brief korisnik user1 počinje pratiti korisnika user2. Ako je user1=user2 ili neki od korisnika ne postoji u društvenoj mreži, funkcija
 * ne radi ništa.
 *
 * @param user1 korisnik koji se traži zahtijev za praćenje.
 * @param user2 korisnik kojemi je zatražen zahtijev za praćenje.
 * 
 * @return void
 */
void SocialNetwork::follow(std::string user1, std::string user2){
    if (users.find(user1) == users.end())
    {
        return;
    }
    if (users.find(user2) == users.end())
    {
        return;
    }
    if(user1 == user2)
    {
        return;
    }
    
    following[user1].insert(user2);

    return;
}


/**
 * @brief korisnik user1 prestaje pratiti korisnika user2. Ako korisnik user1 ne prati korisnika user2 ili neki od korisnika ne postoji u društvenoj mreži,
 * funkcija ne radi ništa.
 * 
 * @param user1 korisnik koji se traži zahtijev za ne praćenje.
 * @param user2 korisnik kojemu je zatražen ne praćenje.
 * 
 * @return void
 */
void SocialNetwork::unfollow(std::string user1, std::string user2){
    if (users.find(user1) == users.end())
    {
        return;
    }
    if (users.find(user2) == users.end())
    {
        return;
    }
    if(following[user1].find(user2) == following[user1].end())
    {
        return;
    }

    following[user1].erase(user2);

    return;
}

/**
 * @brief unkcija briše korisnika user iz društvene mreže. Ako
 * zadanog korisnika nema u društvenoj mreži, funkcija ne radi ništa. Funkcija vraća true ako je
 * korisnik obrisan iz društvene mreže, inače vraća false.
 * 
 * @param user korisnik koji se brise iz društvene mreže.
 * 
 * @return true ako je korisnik obrisan iz društvene mreže,
 */
bool SocialNetwork::removeUser(std::string user){
    if (users.find(user) == users.end())
    {
        return false;
    }

    for (std::string element_users : users)
    {
        if(element_users == user)
        {
            following.erase(element_users);
            continue;
        }
        
        following[element_users].erase(user);
    }
    
    users.erase(user);

    return true;
}

/**
 * @brief unkcija vraća skup pratitelja
 * korisnika user. Ako user nema pratitelje, funkcija vraća prazan skup.
 * 
 * @param
 * 
 * @return skup pratitelja korisnika user.
 */
std::set<std::string> SocialNetwork::getFollowers(std::string user){
    std::set<std::string> pratitelji = std::set<std::string>();
    
    if (users.find(user) == users.end())
    {
        return pratitelji;
    }

    for (std::string element_users : users)
    {
        if(following[element_users].find(user) == following[element_users].end()) continue;

        pratitelji.insert(element_users);
    }

    return pratitelji;
}


/**
 * @brief unkcija vraća skup korisnika koji
 * su predloženi korisniku user za praćenje. Korisnik C je predložen korisniku user ako user nije
 * pratitelj od C, vrijedi user /= C te postoji korisnik B takav da je user pratitelj od B te je B
 * pratitelj od C. Ako takvih korisnika nema, funkcija vraća prazan skup.
 * 
 * @param user Za kojeg korisnika
 * 
 * @return skup korisnika koji su predloženi korisniku user za praćenje.
 */
std::set<std::string> SocialNetwork::recommend(std::string user){
    std::set<std::string> recommended = std::set<std::string>();

    if(users.find(user) == users.end())
    {
        return recommended;
    }

    for (std::string pratitelji_user : following[user])
    {
        for(std::string pratitelji_pratitelja_user : following[pratitelji_user])
        {
            if(pratitelji_pratitelja_user == user) continue;
            if(following[user].find(pratitelji_pratitelja_user) != following[user].end()) continue;

            recommended.insert(pratitelji_pratitelja_user);
        }
    }

    return recommended;
}

bool compare_influencers(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
    return a.second > b.second;
}

/**
 * @brief unkcija vraća vektor korisnika koji su tzv. influenceri. Korisnika user smatramo influencerom ako:
 * – ima strogo više od n/2 pratitelja, gdje je n broj korisnika društvene mreže, te
 * – ima više ili jednako pratitelja nego korisnika koje on prati
 *
 * Vektor je sortiran silazno po broju pratitelja (influencer s najviše pratitelja je na indeksu 0,
 * itd.). Ako ne postoji ni jedan influencer u društvenoj mreži, funkcija vraća prazan vektor.
 * 
 * @param
 * 
 * @return vektor korisnika koji su influenceri.
 */
std::vector<std::string> SocialNetwork::getInfluencers()
{
    std::vector<std::string> influencers = std::vector<std::string>();
    std::set<std::pair<std::string, int>, bool(*)(const std::pair<std::string, int>&, const std::pair<std::string, int>&)> influencers_set(compare_influencers);

    double n = users.size() / 2;

    for (std::string user : users)
    {
        int user_followers = getFollowers(user).size();

        if(user_followers <= n) continue;

        int flag = 1;

        for (std::string user_following_user : following[user])
        {
            int user_following_user_followers = following[user_following_user].size();

            if( user_following_user_followers > user_followers)
            {
                flag = 0;
                break;
            }
        }

        if(flag == 0) continue;

        influencers_set.insert({user, user_followers});
    }

    for (std::pair<std::string, int> user : influencers_set)
    {
        influencers.push_back(user.first);
    }

    return influencers;
}

/**
 * @brief unkcija vraća skup uredenih parova korisnika (A,B) takvih da je A pratitelj od B, B je pratitelj od A te je A po abecedi
 * spred B. Ako takvih parova nema, funkcija vraća prazan skup.
 * 
 * @param
 * 
 * @return skup parova korisnika koji se međusobno prate.
 */
std::set<std::pair<std::string, std::string>> SocialNetwork::getMutualPairs(){
    std::set<std::pair<std::string, std::string>> pairs = std::set<std::pair<std::string, std::string>>();

    for(std::string user : users)
    {
        for(std::string user_following : following[user])
        {
            if(following[user_following].find(user) == following[user_following].end()) continue;

            if(user < user_following) pairs.insert({user, user_following});
            else pairs.insert({user_following, user});
        }
    }

    return pairs;
}
