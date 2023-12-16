# include<iostream>
# include<map>
# include<string>

int main() {

    std::map<std::string, int> marksMap;

    marksMap["Ishan"] =98;
    marksMap["Sachin"] = 100;
    marksMap["kaushik"] = 23; 
    std::map<std::string, int> :: iterator itr;
    for(itr=marksMap.begin();itr!=marksMap.end(); itr++){

        std::cout<<(*itr).first<<" "<<(*itr).second<<"\n";
    }

    return 0;

}

