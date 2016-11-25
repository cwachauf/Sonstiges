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
#include <string>s
#include <utility>


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
    //map<int,int> CheckForOccurence(const char* target_string,int length_string);
    vector<pair<int,int>> CheckForOccurence(const char* target_string,int length_string);
    string ReturnFinalString(const char* sequence,int index,int str_length);
};


string CSearchPattern::ReturnFinalString(const char* sequence,int index,int str_length)
{
    string cpp_string = sequence;
    string result_string = cpp_string.substr(index,str_length)+cpp_string.substr(0,index);
    return(result_string);
}

vector<pair<int,int>> CSearchPattern::CheckForOccurence(const char* target_string,int length_string)
{
    vector<pair<int,int>> vector_matches;
    for(int ind_start=0;ind_start<length_string;ind_start+=1)
    {
        bool fulfilled = true;
        int nm=0;
        // loop over all search patterns, if one is not fulfilled, then set "fulfilled" to false
        map<int,Base>::const_iterator it;
        
        for(it=m_patterns.begin();it!=m_patterns.end();it++)
        {
            if(strncmp(&target_string[(ind_start+it->first)%length_string],GetBaseName(it->second),1)==0)
            {
                nm+=1;
            }
        }
        pair<int,int> aPair;
        aPair.first=nm;
        aPair.second=ind_start;
        vector_matches.push_back(aPair);
        
    }
    return(vector_matches);

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
    char sequence[7561];
    char* filename1 = new char[256];
    strcpy(filename1,"//Users//christianwachauf//Documents//sonstiges//scaffold_sequences//p7560.txt");
    pFile = fopen(filename1,"rt");
    fscanf(pFile,"%s\n",sequence);
    printf("%s\n",sequence);
    fclose(pFile);
    // open text-file with scaffold-sequence
    Base Bases[]={G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C};
    int indices[]={3856,3857,3814,3815,4950,4951,2640,2641,2577,2578,3667,3668,3636,3637,2440,2441};
    
    CSearchPattern spc;
    spc.SetSearchPatterns(16,indices,Bases);
    spc.PrintSearchPatterns();
    vector<pair<int,int>> vp_comparisons = spc.CheckForOccurence(sequence,7560);
    
    sort(vp_comparisons.begin(),vp_comparisons.end());
    reverse(vp_comparisons.begin(),vp_comparisons.end());
    
    
    for(int i=0;i<vp_comparisons.size();i++)
    {
        cout << vp_comparisons[i].first << " " << vp_comparisons[i].second << endl;
    }
    
    cout << "and the winner is: " << endl;
    cout << vp_comparisons[0].second << endl;
    
    string final_string = spc.ReturnFinalString(sequence,vp_comparisons[0].second,7560);
    cout << final_string << endl;
    
    return 0;
}
