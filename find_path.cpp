//
//  main.cpp
//  task0
//
//  Created by sudip on 7/11/19.
//  Copyright © 2019 sudip. All rights reserved.
//
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include <iomanip>

int max=100000;
float hue=0;
bool informS=false;
//structure of the formated data in the file
struct paths {
    std::string start;
    std::string end;
    float distance;
    bool operator ()(paths a, paths b)
    {
        return a.distance<b.distance;
    }
}cmp;

struct way {
    std::string itself;
    std::string parent;
    float travelled;
    float heu;
    bool operator ()(way a, way b)
    {
        if(!informS) return a.travelled<b.travelled;
        return a.heu<b.heu;
    }
}cmp2;

struct heu{
    std::string city;
    float heu_dis;
    
};
std::vector<paths> cities;  //vector to save the content of the file
std::vector<way> fringe; //vector to save the remaining element to be extend
std::vector<std::string> close_v; //vector to save the  elements that are already extended
std::vector<way>allpath;//vector to store the sucessesor of current node
std::vector<way>tempfringe;
std::vector<std::string>finalpath;
std::vector<heu>heuristic;

float tdistance=max;                //total distance from start to our goal state
std::string startFrom;              //where to start
std::string endTo;                  //where to end
int node_expanded=0;        //total number of node expanded while program in running
int node_generated=0;       //total number of node are generated during the execution
unsigned long node_in_mem=0;          //maximum number of node during the execution


bool parse_file(char*);   // function to parce put file and import it to our program
void uniformed_search(int argc, char* argv[]);  //function search the path if exist based on Graph search algorithm
void informed_search(int argc, char* argv[]);
void find_path(way);
void print();
void extend(std::string,std::string node, int distance,float hue);
void get_heuristic(char*);



int main(int argc, char* argv[])
{
    if(!parse_file(argv[1]))
        return -1;
   /* for(int i=0;i<cities.size();i++)
     {
     std::cout<<cities[i].start<<"\t"<<cities[i].end<<"\t"<<cities[i].distance<<std::endl;
     }
     std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";*/
    startFrom=argv[2];
    endTo=argv[3];
    
    if(argc==4)
    {
        
        uniformed_search(argc,argv);
        
    }
    else if(argc==5)
    {
        get_heuristic(argv[4]);
        /*for(int i=0;i<heuristic.size();i++)
         {
         std::cout<<heuristic[i].city<<"\t"<<heuristic[i].heu_dis<<std::endl;
         }*/
        informS=true;
        informed_search(argc,argv);
        
        
    }
    else
    {
        std::cout<<"Enter valid argument"<<std::endl;
    }
    finalpath.push_back(startFrom);
    print();
    
    
    /* std::vector<std::string>::iterator it2 = finalpath.begin();
     
     for(;it2!=finalpath.end();it2++)
     {
     std::cout<<"final path actual-"<<*it2<<std::endl;
     }*/
    
    return 0;
}

bool parse_file(char* filename)
{
    std::string str;
    std::ifstream inputFile; //Input file stream object
    inputFile.open(filename); //Opening the file
    if(!inputFile)
    { std::cout << "No such file exist!"<<std::endl; //Throw exception
        return false;
    }
     paths city,city2;
    //Read numbers from file and push into the vector
    while (inputFile>>city.start>>city.end>>city.distance)
    {
       
       /* int temp=std::atoi("INPUT");
        inputFile>>city.start;
        inputFile>>city.end;
        inputFile>>city.distance;
        if(city.start=="END" && city.end=="OF"&& city.distance==temp)
            break;*/
        cities.push_back(city);
        city2.start=city.end;
        city2.end=city.start;
        city2.distance=city.distance;
        
        cities.push_back(city2);
        
    }
    //close the file
    inputFile.close();
    // std::sort(cities.begin(),cities.end(),cmp);
    
    return true;
}



void get_heuristic(char* filename)
{
        heu city;
    std::ifstream inputFile; //Input file stream object
    inputFile.open(filename); //Opening the file
    
    while (inputFile>>city.city>>city.heu_dis)
    {
       
       // int temp=std::atoi("OF");
        //inputFile>>city.city;
        //inputFile>>city.heu_dis;
       //if(city.city=="END" && city.heu_dis==temp)
          // break;
        heuristic.push_back(city);
    }
    inputFile.close();
    
}



void uniformed_search(int argc, char* argv[])
{
    std::vector<paths>::iterator it = cities.begin();
    way city;
    for(;it!=cities.end();it++)
    {
        // std::cout<<"12121212121212\n";
        if(it->start==argv[2])
        {
            //std::cout<<"111111\n";
            city.parent=it->start;
            city.itself=it->start;
            city.travelled=0.0;
            fringe.push_back(city);
            tempfringe.push_back(city);
            break;
        }
    }
    if (fringe.size()==0) {
        std::cout<<"No Path Found"<<std::endl;
        return;
    }
    do{
        std::sort(fringe.begin(),fringe.end(),cmp2);
        int count=0;
        std::vector<std::string>::iterator it1 = close_v.begin();
        for(;it1!=close_v.end();it1++)
        {
            if(*it1==fringe[0].itself)
            {
                //std::cout<<"1\n";
                count++;
                
            }
        }
        if(count>0 && fringe[0].itself!=endTo)
        {
            // std::cout<<"expanded from cout== "<<fringe[0].itself<<std::endl;
            node_expanded+=1;
            fringe.erase(fringe.begin());
            // std::cout<<"__________________________"<<std::endl;
            continue;
        }
        /* std::vector<way>::iterator it2 = fringe.begin();
         for(;it2!=fringe.end();it2++)
         {
         std::cout<<it2->itself<<", ";
         }*/
        //std::cout<<"\n";
        // std::cout<<"expanded nodes- "<<node_expanded<<std::endl;
        close_v.push_back(fringe[0].itself);
        if(count==0 && fringe[0].itself!=endTo)
        {
            //std::cout<<"2\n";
            extend(fringe[0].itself,endTo,fringe[0].travelled,fringe[0].heu);
        }
        
        if(fringe[0].itself==endTo)
        {
            //std::cout<<"3\n";
            node_expanded+=1;
            find_path(fringe[0]);
            return;
        }
        
        // close_v.push_back(fringe[0].);
        fringe.erase(fringe.begin());
        if(node_in_mem<fringe.size())
            node_in_mem= fringe.size();
        
    }while(fringe.size()!=0);
    
}



void extend(std::string node,std::string end,int sdistance,float hue)
{
    // std::cout<<"expanded from main function == "<<node<<std::endl;
    //std::cout<<"vvvvvvvvvvvvvvvvvvvv"<<std::endl;
    
    
    // std::cout<<"expanded\n";
        //std::cout<<"expanded from cout\n";
        node_expanded+=1;
    std::string start;
    std::string stop;
    way city;
    std::vector<paths>::iterator it = cities.begin();
    for(;it!=cities.end();it++)
    {
        //std::cout<<"4\n";
        if(it->start==node )
        {
            //std::cout<<"Node Generated "<<it->end<<std::endl;
            if(informS)
            {
                std::vector<heu>::iterator he = heuristic.begin();
                for(;he!=heuristic.end();he++)
                {
                    if(it->end==he->city)
                        hue=he->heu_dis;
                }
                
            }
            //std::cout<<"5\n";
            node_generated+=1;
            city.parent=it->start;
            city.itself=it->end;
            city.travelled=it->distance+sdistance;
            city.heu=it->distance+sdistance+hue;
            fringe.push_back(city);
            tempfringe.push_back(city);
            if(endTo==city.itself && city.travelled<tdistance){
                //std::cout<<"6\n";
                tdistance=city.travelled;
            }
        }
    }
    
    // std::sort(fringe.begin(),fringe.end(),cmp2);
    //std::cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^"<<std::endl;
}




void informed_search(int argc, char* argv[])
{
    informS=true;
    uniformed_search(argc,argv);
    
}

void find_path(way end)
{
    //std::cout<<"7\n";
    way temp;
    
    std::vector<paths>::iterator it = cities.begin();
    std::vector<way>::iterator it2 = tempfringe.begin();
    for(;it!=cities.end();it++)
    {
        //std::cout<<"8\n";
        if(it->start==end.parent&&it->end==end.itself)
        {
            //std::cout<<"9\n";
            
            temp.travelled=end.travelled-it->distance;
            temp.itself=it->start;
            temp.parent="unknown";
            finalpath.push_back(it->end);
            //finalpath.push_back(it->start);
        }
        if(end.parent==end.itself)
        {
            //std::cout<<"10\n";
            //finalpath.push_back(end.parent);
            return;
        }
    }
    
    for(;it2!=tempfringe.end();it2++)
    {
        //std::cout<<"11\n";
        if(it2->itself==temp.itself && it2->travelled==temp.travelled)
        {
            //std::cout<<"12\n";
            find_path(*it2);
        }
    }
}


void print()
{
    int count=0;
    std::cout<<"node extended: "<<node_expanded<<"\n";
    std::cout<<"node generated: "<<node_generated<<"\n";
    std::cout<<"max node in memory "<<node_in_mem<<"\n";
    if(tdistance!=max)
        std::cout<<"distance: "<<std::setprecision(1)<<std::fixed<<tdistance<<" km\n";
    else
        {
            std::cout<<"distance: infinity"<<std::endl;
            std::cout<<"route: \nnone"<<std::endl;
            return;
        }
    std::cout<<"route:"<<std::endl;
    unsigned long t=finalpath.size()-1;
    for(int i=0;i<finalpath.size();i++)
    {
        //std::cout<<finalpath[i]<<" ";
        std::vector<paths>::iterator it2 = cities.begin();
        for(;it2!=cities.end();it2++)
        {
            
            if(finalpath[t-i]==it2->start && finalpath[t-i-1]==it2->end)
            {
                count++;
                std::cout<<it2->start<<" to "<<it2->end<<", "<<std::setprecision(1)<<std::fixed<<it2->distance<<" km"<<std::endl;
                if((t-i-1)<0||finalpath[t-i-1]==endTo)
                {
                    return;
                }
                break;
            }
        }
        
    }
}
