#include <iostream>
#include <cassert>
#include "social_network.h"

void testAddRemove() {
    SocialNetwork s;

    assert(s.addUser("A") == true);
    assert(s.addUser("A") == false); // već postoji

    assert(s.removeUser("B") == false);
    assert(s.removeUser("A") == true);
    assert(s.removeUser("A") == false);
}

void testFollowUnfollow() {
    SocialNetwork s({"A", "B", "C"});

    s.follow("A", "B");
    s.follow("A", "C");
    s.follow("A", "A"); // ne smije ništa

    auto f = s.getFollowers("B");
    assert(f.count("A") == 1);

    s.unfollow("A", "B");
    f = s.getFollowers("B");
    assert(f.count("A") == 0);
}

void testFollowers() {
    SocialNetwork s({"A", "B", "C"});

    s.follow("A", "C");
    s.follow("B", "C");

    auto f = s.getFollowers("C");
    assert(f.size() == 2);
    assert(f.count("A"));
    assert(f.count("B"));
}

void testRecommend() {
    SocialNetwork s({"A", "B", "C", "D"});

    s.follow("A", "B");
    s.follow("B", "C");

    auto rec = s.recommend("A");

    assert(rec.count("C") == 1); // A -> B -> C
    assert(rec.count("A") == 0);
}

void testInfluencers() {
    SocialNetwork s({"A", "B", "C", "D", "E"});

    s.follow("A", "C");
    s.follow("B", "C");
    s.follow("D", "C");
    s.follow("E", "C");

    auto inf = s.getInfluencers();

    assert(inf.size() == 1);
    assert(inf[0] == "C");
}

void testMutual() {
    SocialNetwork s({"A", "B", "C"});

    s.follow("A", "B");
    s.follow("B", "A");

    s.follow("A", "C");

    auto pairs = s.getMutualPairs();

    assert(pairs.size() == 1);
    assert(pairs.count({"A", "B"}) == 1);
}

void testExampleFromPDF() {
    SocialNetwork s({"Euler", "Newton", "Gauss", "Godel", "Lebesgue"});

    s.follow("Euler", "Gauss");
    s.follow("Euler", "Godel");
    s.follow("Euler", "Lebesgue");

    s.follow("Newton", "Godel");
    s.follow("Newton", "Lebesgue");

    s.follow("Gauss", "Godel");
    s.follow("Gauss", "Euler");

    s.follow("Lebesgue", "Godel");

    auto inf = s.getInfluencers();
    assert(inf.size() == 1);
    assert(inf[0] == "Godel");

    auto rec = s.recommend("Gauss");
    assert(rec.count("Lebesgue") == 1);

    auto pairs = s.getMutualPairs();
    assert(pairs.count({"Euler", "Gauss"}) == 1);
}

int main() {
    testAddRemove();
    testFollowUnfollow();
    testFollowers();
    testRecommend();
    testInfluencers();
    testMutual();
    testExampleFromPDF();

    std::cout << "Svi testovi prosli!\n";
    return 0;
}
