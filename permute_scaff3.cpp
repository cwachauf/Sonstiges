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
#include <string>
#include <utility>
#include <iterator>

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

class CFindPermuation
{
//private:
    int permutations[7560][16];
    //vector<pair<int,int>> num_matches; // contains for each shift (0..7559), the number of
    int num_matches[7560];
    
public:
    void ReadData();
    void EvaluateData();
    
};

void CFindPermuation::ReadData()
{
    // loop through
    string path("//Users//christianwachauf//Documents//sonstiges//scaffold_sequences//");
    string complete_filename;
    string prefixes[16] = {"AT_AT","AT_CG","AT_GC","AT_TA","CG_AT","CG_CG","CG_GC","CG_TA","GC_AT","GC_CG","GC_GC","GC_TA","TA_AT","TA_CG","TA_GC","TA_TA"};
    for(int i=0;i<16;i+=1)
    {
        //cout << prefixes[i] << endl;
        string curr_filename = prefixes[i] + "_p7560.txt";
       // cout << curr_filename << endl;
        complete_filename = path + curr_filename;
        cout << complete_filename << endl;
        
        FILE* fp = fopen(complete_filename.c_str(),"rt");
        
        int temp_num_matches;
        int temp_index_on_scaffold;
        
        //fscanf(fp,"%d %d\n",&temp_num_matches,&temp_index_on_scaffold);
        //cout << temp_index_on_scaffold << " " << temp_num_matches << endl;
        
        for(int j=0;j<7560;j+=1)
        {
            fscanf(fp,"%d %d\n",&temp_num_matches,&temp_index_on_scaffold);
            //cout << temp_num_matches << endl;
            this->permutations[temp_index_on_scaffold][i]=temp_num_matches;
            
        }
        
        fclose(fp);
    }
}

void CFindPermuation::EvaluateData()
{
 
    int num_matches_eights[7560];
    for(int i=0;i<7560;i+=1)
    {
        this->num_matches[i] = 0;
        num_matches_eights[i] = 0;
        
        for(int j=0;j<16;j+=1)
        {
            this->num_matches[i]+=this->permutations[i][j];
            if(this->permutations[i][j]==8)
            {
                num_matches_eights[i]+=1;
            }
        }
        // print out the results:
        //cout << "matches at: " << i << ": " << this->num_matches[i] << endl;
        if(this->num_matches[i]>=118)
        {
            cout << "matches at: " << i << ": " << this->num_matches[i] << endl;
            for(int z=0;z<16;z+=1)
            {
                cout << permutations[i][z] << " \t";
            }
            cout << endl << endl;
        }
    }
    for(int i=0;i<7560;i+=1)
    {
        if(num_matches_eights[i]>=10)
        {
            cout << "matches with 8 at: " << i << " " << num_matches_eights[i] << endl;
        }
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
    vector<pair<int,int>> CheckForOccurence2(const char* target_string,int length_string,int spiel);
    string ReturnFinalString(const char* sequence,int index,int str_length);
    vector<pair<int,int>> LoopThroughPartOfSearchPatterns(const char* target_string,int length_string,int spiel);
    void SaveMapToFile(char* filename,vector<pair<int,int>> res_map);
    
    void Test();
    
};

void CSearchPattern::SaveMapToFile(char* filename,vector<pair<int,int>> res_map)
{
    FILE* fp = fopen(filename,"wt");
    
    for(int i=0;i<res_map.size();i++)
    {
        fprintf(fp,"%d \t %d\n",res_map[i].first,res_map[i].second);
    }
    fclose(fp);
}

void CSearchPattern::Test()
{
    int test_array[8];
    memset(test_array,0,sizeof(test_array));
    for(int i=0;i<8;i+=1)
    {
        cout << test_array[i] << endl;
    }
   /* for(int i=0;i<8;i+=1)
    {
        
    }*/
 /*   map<int,Base>::const_iterator it;
    for(it=m_patterns.begin();it!=m_patterns.end();advance(it,2))
    {
        int diff = std::distance(m_patterns.begin(),it);
        
    }*/
}

vector<pair<int,int>> CSearchPattern::LoopThroughPartOfSearchPatterns(const char* target_string, int length_string,int spiel)
{
    vector<pair<int,int>> vector_matches;
    string sequ_string(target_string);
    
    int local_matches[8];
    for(int ind_start=0;ind_start<length_string;ind_start+=1)
    {
        map<int,Base>::const_iterator it;
        int nm = 0; // number of matches
        int curr_index = 0;
       // memset(local_matches,)
        memset(local_matches,0,sizeof(local_matches));
        for(it=m_patterns.begin();it!=m_patterns.end();advance(it,2))
        {
            
            string curr_string = GetBaseName(it->second); // + GetBaseName(next(it,1)->second);
            curr_string+=GetBaseName(next(it,1)->second);
            if(ind_start%100==0)
                cout << ind_start << endl;
            //cout << curr_string << endl;
            // for each pattern and each scaffold permuation, loop over +/- spiel,
            // to find matches
            for(int shift1=-spiel;shift1<=spiel;shift1+=1)
            {
                if(sequ_string.compare((ind_start+it->first+shift1)%length_string,2,curr_string)==0)
                {
                 //   nm+=1;
                    local_matches[curr_index] = 1;
                }
                //cout << it->first << " " << GetBaseName(it->second) << endl;
                //cout << (next(it,1))->first << " " << GetBaseName(next(it,1)->second) << endl;
                
            }
            curr_index+=1;
        }
        // evaluate the particular number of matches:
        
        int sum=0;
        for(int ind=0;ind<8;ind+=1)
        {
            sum+=local_matches[ind];
        }
        pair<int,int> aPair;
        aPair.first=sum;
        aPair.second=ind_start;
        vector_matches.push_back(aPair);
    }
    return(vector_matches);
}

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
    int indices2[] = {1062,1063,1458,1459,1857,1858,2261,2262,6574,6575,6194,6195,5817,5818,5445,5446};
    //Base Bases2[] = {C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G};
    
    
    CFindPermuation cfp;
    cfp.ReadData();
    cfp.EvaluateData();
    
    CSearchPattern spc;
    string final_string = spc.ReturnFinalString(sequence,2741,7560);
    cout << final_string << endl;
    
    ///Base Bases2[] = {A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A};
    //Base Bases2[] = {A,C,A,C,A,C,A,C,A,C,A,C,A,C,A,C};
    //Base Bases2[] = {A,G,A,G,A,G,A,G,A,G,A,G,A,G,A,G};
    //Base Bases2[] = {A,T,A,T,A,T,A,T,A,T,A,T,A,T,A,T};
    //Base Bases2[] = {C,A,C,A,C,A,C,A,C,A,C,A,C,A,C,A};
    //Base Bases2[] = {C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C};
    //Base Bases2[] = {C,G,C,G,C,G,C,G,C,G,C,G,C,G,C,G};
    //Base Bases2[] = {C,T,C,T,C,T,C,T,C,T,C,T,C,T,C,T};
    //Base Bases2[] = {G,A,G,A,G,A,G,A,G,A,G,A,G,A,G,A};
    //Base Bases2[] = {G,C,G,C,G,C,G,C,G,C,G,C,G,C,G,C};
    //Base Bases2[] = {G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G};
    //Base Bases2[] = {G,T,G,T,G,T,G,T,G,T,G,T,G,T,G,T};
    //Base Bases2[] = {T,A,T,A,T,A,T,A,T,A,T,A,T,A,T,A};
    //Base Bases2[] = {T,C,T,C,T,C,T,C,T,C,T,C,T,C,T,C};
    //Base Bases2[] = {T,G,T,G,T,G,T,G,T,G,T,G,T,G,T,G};
    //Base Bases2[] = {T,T,T,T,T,T,T,T,T,T,T,T,T,T,T,T};
    
    
    
    /*CSearchPattern spc;
    spc.SetSearchPatterns(16,indices2,Bases2);
    //spc.PrintSearchPatterns();
    vector<pair<int,int>> vp_comparisons=spc.LoopThroughPartOfSearchPatterns(sequence,7560,15);
    sort(vp_comparisons.begin(),vp_comparisons.end());
    reverse(vp_comparisons.begin(),vp_comparisons.end());
    for(int i=0;i<vp_comparisons.size();i++)
    {
        cout << vp_comparisons[i].first << " " << vp_comparisons[i].second << endl;
    }
    string final_string = spc.ReturnFinalString(sequence,vp_comparisons[2].second,7560);
    cout << final_string << endl;
    
    char* filename2 = new char[256];
    strcpy(filename2,"//Users//christianwachauf//Documents//sonstiges//scaffold_sequences//TA_TA_p7560.txt");
    spc.SaveMapToFile(filename2,vp_comparisons);*/
    
    //spc.Test();
    //spc.SetSearchPatterns(16,indices,Bases);
    //spc.PrintSearchPatterns();
    //vector<pair<int,int>> vp_comparisons = spc.CheckForOccurence(sequence,7560)
    
    /*sort(vp_comparisons.begin(),vp_comparisons.end());
    reverse(vp_comparisons.begin(),vp_comparisons.end());
    
    
    for(int i=0;i<vp_comparisons.size();i++)
    {
        cout << vp_comparisons[i].first << " " << vp_comparisons[i].second << endl;
    }
    
    cout << "and the winner is: " << endl;
    cout << vp_comparisons[0].second << endl;
    
    string final_string = spc.ReturnFinalString(sequence,vp_comparisons[0].second,7560);
    cout << final_string << endl;
    */
    return 0;
}
