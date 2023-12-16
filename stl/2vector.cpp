// std::vector <T>
// Vector is a sequence Container , also known as a Sequence Container or dynamic array or array list.

# include<iostream>
# include<vector>

void display(std::vector<int> &v){

    for(int i=0;i < v.size();i++)
    {
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
}
int main() {

    std::vector<int> vec1;
    int element;
    for(int i =0;i < 4; i++)
    {
        std::cout<<"enter an vector element"<<std::endl;
        std::cin>>element;
        vec1.push_back(element);
    }
    display(vec1);

    return 0;
}
