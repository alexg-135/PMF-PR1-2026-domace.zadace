#include "turnir.h"

#include <iostream>

using namespace std;

int main() {

    list<pair<string,int>> kar1, kar2, kar3, kar4, kar5, kar6, kar7;

    kar1.push_back(make_pair("single",26));
    kar2.push_back(make_pair("single",10));
    kar2.push_back(make_pair("doubles",120));
    kar3.push_back(make_pair("single",92));
    kar4.push_back(make_pair("doubles",64));
    kar5.push_back(make_pair("doubles",12));
    kar6.push_back(make_pair("doubles",7));
    kar7.push_back(make_pair("doubles",42));
    

    list<igrac> L1, L2;
    igrac i1, i2, i3;

    i1=igrac("Sindhu",'Z',kar1);
    i2=igrac("Chen",'Z',kar2);
    i3=igrac("Li",'Z',kar3);

    L1.push_back(i1);
    L1.push_back(i2);
    L1.push_back(i3);

    L2.push_back(i3);
    L2.push_back(i2);

    pojedinacni T1("All England", L1);

    list<igrac>::iterator li;

    for(li=turnir::igraci.begin(); li!=turnir::igraci.end(); li++)
        cout<< li->prezime << endl;
    
    {
        pojedinacni T2("Denmark Open",L2);

        cout << "--pocetak bloka--" << endl;
        for(li=turnir::igraci.begin(); li!=turnir::igraci.end(); li++)
            cout<< li->prezime << endl;
        cout << "--kraj bloka--" << endl;    
    }

    for(li=turnir::igraci.begin(); li!=turnir::igraci.end(); li++)
        cout<< li->prezime << endl;

    cout << turnir::broj_igraca << endl;

    list<pair<igrac,igrac>> L3;
    igrac i4, i5, i6, i7;

    i4=igrac("Yang",'M',kar4);
    i5=igrac("Wang",'M',kar5);
    i6=igrac("Seo",'M',kar6);
    i7=igrac("Kim",'M',kar7);    

    L3.push_back(make_pair(i4,i5));
    L3.push_back(make_pair(i6,i7));

    parski T2("Summer Olympics",L3);

    cout << "--nakon dodavanja parova--" << endl;

    for(li=turnir::igraci.begin(); li!=turnir::igraci.end(); li++)
        cout<< li->prezime << endl;

    cout << turnir::broj_igraca << endl;

    // funkcija procjena_pobjednika

    vector<string> procijenjeni=T1.procjena_pobjednika();
    vector<string>::iterator vi;

    cout << "-- procijenjeni pobjednik All England-a --" << endl;

    for(vi=procijenjeni.begin(); vi!=procijenjeni.end(); vi++)
        cout << *vi << endl;

    procijenjeni=T2.procjena_pobjednika();

     cout << "-- procijenjeni pobjednici Summer Olympics-a --" << endl;

    for(vi=procijenjeni.begin(); vi!=procijenjeni.end(); vi++)
        cout << *vi << endl;

    // funkcija match

    T1.match(&i1,&i2,2,1).match(&i1,&i3,0,2);

    cout << "--nakon matcheva na turniru All England--" << endl;

    for(li=(T1.single).begin(); li!=(T1.single).end(); li++)
        cout<< li->prezime << endl;

    T2.match(&i4,&i5,0,2,&i6,&i7);

    cout << "--nakon matcha Yang-Wang i Seo-Kim--" << endl;

    list<pair<igrac,igrac>>::iterator lii;

    for(lii=(T2.doubles).begin(); lii!=(T2.doubles).end(); lii++)
        cout<< (lii->first).prezime << endl << (lii->second).prezime << endl;

    return 0;
}