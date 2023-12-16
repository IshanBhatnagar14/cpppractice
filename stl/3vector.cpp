// std::vector <T>
// Vector is a sequence Container , also known as a Sequence Container or dynamic array or array list.
// Vector template

# include<iostream>
# include<vector>

template <class T>

class Ishan{
    public:
    std::vector<T> data;

    Ishan () {

    }
    Ishan(T a){
        data = a;
    }
};

void display(da.data &v){

    for(int i=0;i < v.size();i++)
    {
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
}
int main() {
    float element;
    Ishan<float> da;
    
    for(int i =0;i < 4; i++)
    {
        std::cout<<"enter an vector element"<<std::endl;
        std::cin>>element;
        da.data.push_back(element);
    }
    display(da.data);

    return 0;
}
