#include <fstream>
#include <iostream>

#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

#include "social_network.h"

using namespace std;

void printUsers(set<string> users, ofstream &fout){
    for(set<string>::iterator si = users.begin(); si != users.end(); ++si){
        if(si != users.begin()) fout << ", ";
        fout << *si;
    }
}

void printSocialNetwork(SocialNetwork S, ofstream &fout){
    if(S.users.empty()){
        fout << "Drustvena mreza je prazna!\n\n";
        return;
    }
    fout << "Korisnici drustvene mreze su ";
    printUsers(S.users, fout);
    fout << endl;

    for(map<string, set<string>>::iterator mi = S.following.begin(); mi != S.following.end(); ++mi){
        if(mi->second.empty()) fout << "Korisnik " << mi->first << " ne prati nikog\n";
        else{
            fout << "Korisnik " << mi->first << " prati korisnike ";
            printUsers(mi->second, fout);
            fout << endl;
        }
    }
    fout << "-------------------------------------------------\n\n";
}

void main1(string in_file_name){ // s Merlina

    ofstream fout (in_file_name);

    set<string> users = {"Euler", "Newton", "Gauss"};
    SocialNetwork S(users);

    S.addUser("Lebesgue"); S.addUser("Godel");
    if(!S.addUser("Lebesgue")) fout << "Lebesgue vec je u drustvenoj mrezi!\n\n";

    S.follow("Euler", "Lebesgue"); S.follow("Euler", "Godel"); S.follow("Euler", "Gauss");
    S.follow("Gauss", "Godel"); S.follow("Gauss", "Euler");
    S.follow("Lebesgue", "Godel");
    S.follow("Newton", "Godel"); S.follow("Newton", "Lebesgue");
    S.unfollow("Turing", "Godel");

    printSocialNetwork(S, fout);

    set<string> followers = S.getFollowers("Godel");
    if(followers.empty()) fout << "Godel nema pratitelje!\n";
    else{
        fout << "Godelovi pratitellji su ";
        printUsers(followers, fout);
        fout << endl << endl;
    } 
    
    set<string> recommendations = S.recommend("Gauss");
    if(recommendations.empty()){
        fout << "Gaussu nije predlozen ni jedan korisnik!\n";
    }
    else{
        fout << "Gaussu " << (recommendations.size() == 1 ? "je predlozen korisnik ":"su predlozeni korisnici ");
        printUsers(recommendations, fout);
        fout << endl<< endl;
    }

    S.removeUser("Newton");
    printSocialNetwork(S, fout);

    vector<string> influencers = S.getInfluencers();
    if(influencers.empty()) fout << "U drustvenoj mrezi nema influencera!\n\n";
    else{
        fout << (influencers.size() == 1 ? "Jedini influencer je ":"Influenceri su ");
        for(int i = 0; i < influencers.size(); ++i){
            fout << influencers[i];
            if(i != influencers.size()-1) fout << ", ";
        }
        fout << endl << endl;
    }

    set<pair<string, string>> mutualPairs = S.getMutualPairs();
    if(mutualPairs.empty()) fout << "Nema korisnika koji se medusobno prate!\n\n";
    else{
        fout << "Parovi korisnika koji se medusobno prate su ";
        for(set<pair<string, string>>::iterator si = mutualPairs.begin(); si != mutualPairs.end(); ++si){
            if(si != mutualPairs.begin()) fout << ", ";
            fout << "(" << si->first << ", " << si->second << ")";
        }
        fout << endl;
    }

    fout.close();
}

void main2(string in_file_name){ // addUser, follow, unfollow

    ofstream fout (in_file_name);

    SocialNetwork S;
    printSocialNetwork(S, fout);

    S.addUser("Galois"); S.addUser("Turing");
    bool added = S.addUser("Leibniz");
    if(added) fout << "Leibniz je dodan u drustvenu mrezu\n";
    else fout << "Leibniz je vec u drustvenoj mrezi\n";
    added = S.addUser("Leibniz");
    if(added) fout << "Leibniz je dodan u drustvenu mrezu\n";
    else fout << "Leibniz je vec u drustvenoj mrezi\n";
    printSocialNetwork(S, fout);


    set<string> users = {"Bernoulli", "Lagrange", "Fourier", "Hilbert", "Cauchy", "Banach"};
    SocialNetwork SN(users);
    printSocialNetwork(SN, fout);
    SN.follow("Bernoulli", "Lagrange"); SN.follow("Lagrange", "Bernoulli"); SN.follow("Fourier", "Hilbert");
    SN.follow("Hilbert", "Banach"); SN.follow("Hilbert", "Banach");
    SN.follow("Fourier", "Fourier"); SN.follow("Neumann", "Cauchy"); SN.follow("Cauchy", "Neumann");
    
    printSocialNetwork(SN, fout);

    SN.unfollow("Fourier", "Neumann"); SN.follow("Neumann", "Cauchy");
    SN.unfollow("Banach", "Hilbert"); SN.unfollow("Lagrange", "Bernoulli");
    SN.unfollow("Hilbert", "Banach"); SN.unfollow("Hilbert", "Banach");

    printSocialNetwork(SN, fout);
    
    fout.close();
}


void main3(string in_file_name){ // follow, removeUser

    ofstream fout (in_file_name);
    set<string> users = {"Riemann", "Goldbach", "Fermat", "Stokes", "Ramanujan", "Poincare"};
    SocialNetwork SN(users);
    printSocialNetwork(SN, fout);
    bool removed = SN.removeUser("Cantor");
    if(removed) fout << "Cantor je izbrisan iz drustvene mreze\n";
    else fout << "Cantora nema u drustvenoj mrezi\n";
    removed = SN.removeUser("Stokes");
    if(removed) fout << "Stokes je izbrisan iz drustvene mreze\n";
    else fout << "Stokesa nema u drustvenoj mrezi\n";
    printSocialNetwork(SN, fout);


    vector<string> V(SN.users.begin(), SN.users.end());
    for(int i = 0; i < V.size(); ++i){
        for(int j = i+1; j < V.size(); ++j){
            SN.follow(V[i], V[j]);
            SN.follow(V[j], V[i]);
        }
    }
    printSocialNetwork(SN, fout);

    SN.removeUser("Riemann"); SN.removeUser("Ramanujan");
    printSocialNetwork(SN, fout);

    fout.close();
}

void main4(string in_file_name){ // followers, mutualPairs

    ofstream fout (in_file_name);

    set<string> users = {"Noether", "Church", "Cohen", "Gentzen", "Heyting"};
    SocialNetwork SN(users);

    set<pair<string,string>> mutual_pairs = SN.getMutualPairs();
    if(mutual_pairs.empty()) fout << "Nema korisnika koji se medjusobno prate\n";
    else{
        for(set<pair<string,string>>::iterator si = mutual_pairs.begin(); si != mutual_pairs.end(); ++si){
            if(si != mutual_pairs.begin()) fout << ", ";
            fout << "(" << si->first << ", " << si->second << ")";
        }
    }

    map<string, set<string>> following;
    following["Noether"].insert("Cohen"); following["Noether"].insert("Church");
    following["Church"].insert("Cohen"); following["Heyting"].insert("Cohen");
    
    SN.following = following;
    set<string> followers_cohen = SN.getFollowers("Cohen");
    set<string> followers_heyting = SN.getFollowers("Heyting");
    set<string> followers_peano = SN.getFollowers("Peano");

    if(followers_cohen.empty()) fout << "Cohen nema pratitelja\n";
    else{
        fout << "Cohenovi pratitelji su "; printUsers(followers_cohen, fout);
    }

    if(followers_heyting.empty()) fout << "Heyting nema pratitelja\n";
    else{
        fout << "Heytingovi pratitelji su "; printUsers(followers_heyting, fout);
    }
    
    if(followers_peano.empty()) fout << "Peano nema pratitelja\n";
    else{
        fout << "Peanovi pratitelji su "; printUsers(followers_peano, fout);
    }

    SN.following["Cohen"].insert("Nother"); SN.following["Church"].insert("Noether"); 
    SN.following["Gentzen"].insert("Heyting"); SN.following["Heyting"].insert("Gentzen");

    mutual_pairs = SN.getMutualPairs();
    if(mutual_pairs.empty()) fout << "Nema korisnika koji se medjusobno prate\n";
    else{
        for(set<pair<string,string>>::iterator si = mutual_pairs.begin(); si != mutual_pairs.end(); ++si){
            if(si != mutual_pairs.begin()) fout << ", ";
            fout << "(" << si->first << ", " << si->second << ")";
        }
    }

    fout.close();
}

void main5(string in_file_name){ // recommend

    ofstream fout (in_file_name);

    set<string> users = {"Veltman", "Visser", "Kripke", "Verbrugge", "Goldblatt", "van Benthem", "Boole", "Prior"};
    SocialNetwork SN(users);

    map<string, set<string>> following;
    set<string> veltman_recomendations = SN.recommend("Veltman");
    if(veltman_recomendations.empty()) fout << "Nema prijedloga za Veltmana\n";
    else{
        fout << "Prijedlozi za Veltmana su "; printUsers(veltman_recomendations, fout);
    }

    following["Goldblatt"].insert("van Benthem");
    following["van Benthem"].insert("Goldblatt");
    SN.following = following;

    set<string> goldblatt_recommendations = SN.recommend("Goldblatt");
    if(goldblatt_recommendations.empty()) fout << "Nema prijedloga za Goldblatta\n";
    else{
        fout << "Prijedlozi za Goldblatta su "; printUsers(goldblatt_recommendations, fout);
    }

    set<string> godel_recommendations = SN.recommend("Godel");
    if(godel_recommendations.empty()) fout << "Nema prijedloga za Godela\n";
    else{
        fout << "Prijedlozi za Godela su "; printUsers(godel_recommendations, fout);
    }
    
    SN.following["Verbrugge"].insert("Veltman");  SN.following["Verbrugge"].insert("Visser"); SN.following["Verbrugge"].insert("Boole");
    SN.following["Veltman"].insert("Visser"); SN.following["Veltman"].insert("Verbrugge"); SN.following["Veltman"].insert("Goldblatt"); SN.following["Veltman"].insert("Prior");
    SN.following["Visser"].insert("Kripke"); SN.following["Visser"].insert("Veltman"); SN.following["Visser"].insert("Goldblatt");
    

    set<string> verbrugge_recommendations = SN.recommend("Verbrugge");
    if(verbrugge_recommendations.empty()) fout << "Nema prijedloga za Verbrugge\n";
    else{
        fout << "Prijedlozi za Verbrugge su "; printUsers(verbrugge_recommendations, fout);
    }

    fout.close();
}

void main6(string in_file_name){ // influencers

    ofstream fout (in_file_name);

    set<string> users = {"Euler", "Gauss", "Riemann", "Cantor", "Fourier", "Cohen", "Noether", "Cauchy"};
    SocialNetwork SN(users);
    vector<string> influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl;
    }

    SN.following["Euler"].insert("Gauss"); 
    SN.following["Gauss"].insert("Riemann"); 
    SN.following["Riemann"].insert("Cantor");
    influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl;
    }

    for(set<string>::iterator si = users.begin(); si != users.end(); ++si){
        if(*si != "Noether")
            SN.following[*si].insert("Noether");
    }

    influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl; 
    }
    SN.following["Euler"].insert("Cantor"); SN.following["Gauss"].insert("Cantor"); 

    SN.following["Euler"].insert("Fourier"); SN.following["Gauss"].insert("Fourier"); SN.following["Cohen"].insert("Fourier"); 
    SN.following["Noether"].insert("Fourier"); SN.following["Riemann"].insert("Fourier");

    influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl; 
    }

    

    SN.following["Fourier"] = users; SN.following["Fourier"].erase("Fourier");
    influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl; 
    }

    SN.following["Noether"].insert("Cantor");
     influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl; 
    }

    SN.users.insert("Lagrange"); SN.users.insert("Fibonacci");

    influencers = SN.getInfluencers();
    if(!influencers.size()) fout << "Nema influencera u drustvenoj mrezi\n";
    else{
        fout << "Influenceri su ";
        for(int i = 0; i < influencers.size(); ++i) {
            fout << influencers[i];
            if(i != influencers.size() - 1) fout << ", ";
        }
        fout << endl; 
    }

    fout.close();
}

int main(int argc, char **argv) {
	int i;
	i = atoi(argv[1]);
	switch (i) {
		case 1:
			main1("izlaz1.out");
			break;
		case 2:
			main2("izlaz2.out");
			break;
		case 3:
			main3("izlaz3.out");
			break;
		case 4:
			main4("izlaz4.out");
			break;
		case 5:
			main5("izlaz5.out");
			break;
		case 6:
			main6("izlaz6.out");
			break;
	}
	return 0;
}