#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;


void getData(set<string> &Data, string choice, string fileName){
    ifstream f(fileName);

    if(f.good()){
        json data = json::parse(f);

        if(choice == "following"){
            data = data["relationships_following"];
        }

        for(int i = 0; i < data.size(); i++){
            Data.insert(data[i]["string_list_data"][0]["value"]);
        }
    }
    f.close();
}

vector<string> getAccounts(set<string> &followers, set<string> &following){
    int initialSize;
    set<string> followersTemp = followers;
    vector<string> Accounts;

    for(string follow : following){
        initialSize = followersTemp.size();
        followersTemp.insert(follow);
        if(initialSize != followersTemp.size()){
            Accounts.push_back(follow);
        }
    }
    return Accounts;
}

void printAccounts(vector<string> & Accounts){
    for(int i = 0; i < Accounts.size(); i++){
        cout << Accounts[i] << endl;
    }
}

int main(int argc, char* argv[]){
    set<string> followers;
    set<string> following;

    getData(followers, "followers", "followers_1.json");
    getData(following, "following", "following.json");

    cout << "Number of followers: " << followers.size() << endl;
    cout << "Number of Following: " << following.size() << endl;

    vector<string> Accounts = getAccounts(followers, following);
    printAccounts(Accounts);

    return 1;
}
