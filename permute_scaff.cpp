//
//  main.cpp
//  PermuteScaffSequ
//
//  Created by Christian Wachauf on 25.11.16.
//  Copyright © 2016 Christian Wachauf. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>

using namespace std;

enum Base {A,C,T,G};

const char* GetBaseName(enum Base base)
{
    switch(base)
    {
        case A: return "A";
        case C: return "C";
        case T: return "T";
        case G: return "G";
    }
}

class CSearchPattern
{
private:
    int m_num_search_patterns;
    map<int,Base> m_patterns;
public:
    void SetSearchPatterns(int num_patterns,int* indices,Base* bases);
    void PrintSearchPatterns();
    vector<int> CheckForOccurence(const char* target_string,int length_string);
};

vector<int> CSearchPattern::CheckForOccurence(const char* target_string, int length_string)
{
    // a distinction could be make between "wrapping around (y/n)",....
    vector<int> ff_indices;
    
    for(int ind_start=0;ind_start<length_string;ind_start+=1)
    {
        bool fulfilled = true;
        // loop over all search patterns, if one is not fulfilled, then set "fulfilled" to false
        map<int,Base>::const_iterator it;
        
        for(it=m_patterns.begin();it!=m_patterns.end();it++)
        {
            if(strncmp(&target_string[(ind_start+it->first)%length_string],GetBaseName(it->second),1))
            {
                fulfilled=false;
                break;
            }
        }
        if(fulfilled==true)
        {
            ff_indices.push_back(ind_start);
        }
    }
    return(ff_indices);
}

void CSearchPattern::SetSearchPatterns(int num_patterns, int* indices,Base* bases)
{
    m_num_search_patterns = num_patterns;
    for(int i=0;i<m_num_search_patterns;i+=1)
    {
        m_patterns[indices[i]] = bases[i];
    }
    
}

void CSearchPattern::PrintSearchPatterns()
{
    // looping throught entries with an iterator:
    map<int,Base>::const_iterator it;
    
    for(it=m_patterns.begin();it!=m_patterns.end();it++)
    {
        cout << it->first << " " << GetBaseName(it->second) << endl;
    }
}

int main(int argc, const char * argv[])
{
    FILE* pFile;
    char sequence[7565];
    char* filename1 = new char[256];
    strcpy(filename1,"//Users//christianwachauf//Documents//sonstiges//scaffold_sequences//p7560.txt");
    pFile = fopen(filename1,"rt");
    fscanf(pFile,"%s\n",sequence);
    printf("%s\n",sequence);
    fclose(pFile);
    // open text-file with scaffold-sequence
    Base Bases[3]={A,A,G};
    int indices[3]={0,1,2};
    
    CSearchPattern spc;
    spc.SetSearchPatterns(3,indices,Bases);
    spc.PrintSearchPatterns();
    vector<int> indices_on_string = spc.CheckForOccurence(sequence,7560);
    
    for(int i=0;i<indices_on_string.size();i++)
    {
        cout << indices_on_string[i] << endl;
    }
    
    cout << "number of matches: " << indices_on_string.size() << endl;
    return 0;
}
