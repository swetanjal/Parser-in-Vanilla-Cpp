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


    cout << "\n\nCompute Closures.\n\n";
    
    int kiko = 0;
    int kernel_size;
    cin >> kernel_size;

    vector <string> lhs;
    vector <vector <string> > rhs;
    vector <int> dot_pos;

    set < pair < string, vector < string > > > closure;

    while(kiko < kernel_size)
    {
        int len;
        cin >> len;
        string sym;
        cin >> sym;
        vector <string> item;
        set <string> fst;
        int pos = -1;
        for(int i = 0; i < len; ++i)
        {
            string t;
            cin >> t;
            item.push_back(t);

            if(t == ".")
                pos = i;
        }
        lhs.push_back(sym);
        dot_pos.push_back(pos);
        rhs.push_back(item);
        kiko++;
    }

    kiko = 0;
    while(kiko < lhs.size())
    {
        int len = rhs[kiko].size();
        string sym = lhs[kiko];
        // cout << lhs[kiko] << endl;
        closure.insert({lhs[kiko], rhs[kiko]});
        vector <string> item;
        set <string> fst;
        int pos = -1;
        for(int i = 0; i < len; ++i)
        {
            string t = rhs[kiko][i];
            item.push_back(t);
            if(t == ".")
                pos = i;
        }

        if(pos <= (len - 3) && NT.find(item[pos + 1]) != NT.end())
        {
                int cnt = 0;
                for(int j = pos+2; j < len; ++j)
                {
                    if(NT.find(item[j]) == NT.end())
                    {
                        fst.insert(item[j]);
                        break;
                    }
                    else{
                        int ep = 0;
                        for(auto el: FIRST[item[j]])
                        {
                            if(el == "epsilon")
                            {
                                ep = 1;
                            }
                            else{
                                fst.insert(el);
                            }
                        }
                        if(ep == 0)
                            break;
                        else
                            cnt++;
                    }
                }
                if(cnt == len)
                {
                    fst.insert("epsilon");
                }

                for(auto vec: H[item[pos + 1]])
                {
                    for(auto ch: fst)
                    {
                        vector <string> tmp;
                        tmp.push_back(".");
                        for(auto c: vec)
                            tmp.push_back(c);
                        tmp.push_back(ch);

                        if(closure.find({item[pos + 1], tmp}) == closure.end())
                        {
                            closure.insert({item[pos + 1], tmp});
                            lhs.push_back(item[pos + 1]);
                            rhs.push_back(tmp);
                            dot_pos.push_back(0);
                        }
                        
                    }
                }
        }
        kiko++;
    }

    for(auto el: closure)
    {
        cout << el.first << "-> ";
        for(auto c: el.second)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    return 0;
}