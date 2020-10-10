#include "bits/stdc++.h"
using namespace std;
int productions;
vector < vector <string> > dummy;
set <string> dummy2;
map < string, vector < vector <string> > > H;
map < string, int > NT;

map < string, set <string> > FIRST;
map <string, set <string> > FOLLOW;

int main()
{
    cout << "HELP:\n\n\n\nRULE FOR ENTERING PRODUCTIONS:\nEnter Number of (N U T)* on R.H.S followed by left side non terminal then right side elements separated by space\n\n\n";

    cout << "Enter number of Productions.\n";
    cin >> productions;

    for(int i = 1; i <= productions; ++i)
    {
        
        int tmp;
        cin >> tmp;

        string S;
        // cout << "Enter left side non terminal.\n";
        cin >> S;

        // cout << "Enter right side elements separated by space.\n";

        vector <string> elements;
        for(int j = 1; j <= tmp; ++j)
        {
            string t;
            cin >> t;
            elements.push_back(t);
        }

        if(H.find(S) == H.end())
            H[S] = dummy;
        NT[S] = 1;
        H[S].push_back(elements);
    }
    for(auto N: H)
    {
        FIRST[N.first] = dummy2;
        FOLLOW[N.first] = dummy2;
    }

    for(int i = 1; i <= 100; ++i)
    {
        for(auto N: H)
        {
            string non_terminal = N.first;
            for(auto vec: N.second)
            {
                int l = vec.size();
                int cnt = 0;
                for(int j = 0; j < l; ++j)
                {
                    if(NT.find(vec[j]) == NT.end())
                    {
                        FIRST[non_terminal].insert(vec[j]);
                        break;
                    }
                    else{
                        int ep = 0;
                        for(auto el: FIRST[vec[j]])
                        {
                            if(el == "epsilon")
                            {
                                ep = 1;
                            }
                            else{
                                FIRST[non_terminal].insert(el);
                            }
                        }
                        if(ep == 0)
                            break;
                        else
                            cnt++;
                    }
                }
                if(cnt == l)
                {
                    FIRST[non_terminal].insert("epsilon");
                }
            }
        }
    }

    cout << "\n\nFIRST SET:\n";

    for(auto N: H)
    {
        string non_terminal = N.first;
        cout << non_terminal << ": ";
        int l = FIRST[non_terminal].size();
        for(auto ch: FIRST[non_terminal])
            cout << ch << " ";
        cout << endl;
    }

    cout << "\n\nFOLLOW SET:\n";

    for(int i = 1; i <= 100; ++i)
    {
        for(auto N: H)
        {
            string non_terminal = N.first;

            for(auto n: H)
            {
                for(auto prods: n.second)
                {
                    int L = prods.size();
                    int it = 0;
                    for(auto el: prods)
                    {
                        // Go through each element in a production.
                        if(el == non_terminal)
                        {
                            int tmp_idx = it;
                            while(tmp_idx < L)
                            {
                                tmp_idx++;
                                if(tmp_idx == L)
                                {
                                    // Everything in FOLLOW n is in FOLLOW N.
                                    int ep = 0;
                                    for(auto element: FOLLOW[n.first])
                                    {
                                        if(element == "epsilon")
                                        {
                                            ep = 1;
                                        }
                                        else{
                                            FOLLOW[non_terminal].insert(element);
                                        }
                                    }

                                }
                                else{
                                    string NUT = prods[tmp_idx];
                                    int ep = 0;
                                    if(NT.find(NUT) == NT.end())
                                    {
                                        FOLLOW[non_terminal].insert(NUT);
                                        break;
                                    }
                                    else{
                                        for(auto element: FIRST[NUT])
                                        {
                                            if(element == "epsilon")
                                            {
                                                ep = 1;
                                            }
                                            else{
                                                FOLLOW[non_terminal].insert(element);
                                            }
                                        }
                                        if(ep == 0)
                                        {
                                            break;
                                        }
                                    }
                                }
                            }   
                        }
                        it++;
                    }
                }
            }
        }
    }

    for(auto N: H)
    {
        string non_terminal = N.first;
        cout << non_terminal << ": ";
        int l = FOLLOW[non_terminal].size();
        for(auto ch: FOLLOW[non_terminal])
            cout << ch << " ";
        cout << endl;
    }

    cout << "\n\nComputing FIRST+ Set of productions:\n";

    for(auto N: H)
    {
        for(auto prod: N.second)
        {
            cout << "FIRST+(" << N.first << " -> ";
            for(auto el: prod)
            {
                cout << el << " ";
            }
            cout << "): ";
            for(auto el:prod)
            {
                if(NT.find(el) == NT.end() && el != "epsilon")
                {
                    cout << el;
                }
                else if(el == "epsilon")
                {
                    for(auto s: FOLLOW[N.first])
                    {
                        cout << s << " ";
                    }
                    // cout << endl;
                }
                else{
                    int ep = 0;
                    for(auto s: FIRST[el])
                    {
                        if(s == "epsilon")
                        {
                            ep = 1;
                        }
                        else{
                            cout << s << " ";
                        }
                    }

                    if(ep){
                        for(auto s: FOLLOW[N.first])
                        {
                            cout << s << " ";
                        }
                    }
                }
                cout << endl;
                break;
            }
            
        }
    }
    return 0;
}