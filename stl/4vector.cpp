// std::vector <T>
// Vector is a sequence Container , also known as a Sequence Container or dynamic array or array list.

# include<iostream>
# include<vector>

void display(std::vector<uint16_t> &v){

    for(int i=0;i < v.size();i++)
    {
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
}
int main() {

    std::vector<uint16_t> vec1;
    vec1 = {1,2,3,4,5,6,7};
    display(vec1);

    return 0;
}

