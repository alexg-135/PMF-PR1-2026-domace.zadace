#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<utility>

#include "social_network.h"

using namespace std;

void printUsers(set<string> users){
    for(set<string>::iterator si = users.begin(); si != users.end(); ++si){
        if(si != users.begin()) cout << ", ";
        cout << *si;
    }
}

void printSocialNetwork(SocialNetwork S){
    if(S.users.empty()){
        cout << "Drustvena mreza je prazna!\n\n";
        return;
    }
    cout << "Korisnici drustvene mreze su ";
    printUsers(S.users);
    cout << endl;

    for(map<string, set<string>>::iterator mi = S.following.begin(); mi != S.following.end(); ++mi){
        if(mi->second.empty()) cout << "Korisnik " << mi->first << " ne prati nikog\n";
        else{
            cout << "Korisnik " << mi->first << " prati korisnike ";
            printUsers(mi->second);
            cout << endl;
        }
    }
    cout << "-------------------------------------------------\n\n";
}


int main(void){

    set<string> users = {"Euler", "Newton", "Gauss"};
    SocialNetwork S(users);

    S.addUser("Lebesgue"); S.addUser("Godel");
    if(!S.addUser("Lebesgue")) cout << "Lebesgue vec je u drustvenoj mrezi!\n\n";

    S.follow("Euler", "Lebesgue"); S.follow("Euler", "Godel"); S.follow("Euler", "Gauss");
    S.follow("Gauss", "Godel"); S.follow("Gauss", "Euler");
    S.follow("Lebesgue", "Godel");
    S.follow("Newton", "Godel"); S.follow("Newton", "Lebesgue");
    S.unfollow("Turing", "Godel");

    printSocialNetwork(S);

    set<string> followers = S.getFollowers("Godel");
    if(followers.empty()) cout << "Godel nema pratitelje!\n";
    else{
        cout << "Godelovi pratitellji su ";
        printUsers(followers);
        cout << endl << endl;
    } 
    
    set<string> recommendations = S.recommend("Gauss");
    if(recommendations.empty()){
        cout << "Gaussu nije predlozen ni jedan korisnik!\n";
    }
    else{
        cout << "Gaussu " << (recommendations.size() == 1 ? "je predlozen korisnik ":"su predlozeni korisnici ");
        printUsers(recommendations);
        cout << endl<< endl;
    }

    S.removeUser("Newton");
    printSocialNetwork(S);

    vector<string> influencers = S.getInfluencers();
    if(influencers.empty()) cout << "U drustvenoj mrezi nema influencera!\n\n";
    else{
        cout << (influencers.size() == 1 ? "Jedini influencer je ":"Influenceri su ");
        for(int i = 0; i < influencers.size(); ++i){
            cout << influencers[i];
            if(i != influencers.size()-1) cout << ", ";
        }
        cout << endl << endl;
    }

    set<pair<string, string>> mutualPairs = S.getMutualPairs();
    if(mutualPairs.empty()) cout << "Nema korisnika koji se medusobno prate!\n\n";
    else{
        cout << "Parovi korisnika koji se medusobno prate su ";
        for(set<pair<string, string>>::iterator si = mutualPairs.begin(); si != mutualPairs.end(); ++si){
            if(si != mutualPairs.begin()) cout << ", ";
            cout << "(" << si->first << ", " << si->second << ")";
        }
        cout << endl;
    }
    
    return 0;
}