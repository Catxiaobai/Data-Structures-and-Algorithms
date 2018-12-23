#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;
struct Co
{
    string name;//��
    int weight;//���ִ���
    Co(string n)
    {
        name=n;
        weight=1;
    }
};
bool Charjudge(string s)
{
    if(s=="��"||s=="��"||s=="��"||s=="��"||s=="��")
    {
        return true;
    }
    return false;
}
int AddStart(string s,vector<string> &Start)
{
    for(int i=0;i<Start.size();i++)
    {
        if(s==Start[i])
            return 0;
    }
    Start.push_back(s);
    return 0;
}
int AddToken(string s,vector<vector<Co> > &Token,int lo)
{

    for(int i=0;i<Token[lo].size();i++)
    {
        if(Token[lo][i].name==s)
        {
            Token[lo][i].weight++;
            return 0;
        }
    }
    Token[lo].push_back(Co(s));
    //cout<<Token[lo][Token[lo].size()-1].name<<endl;
    return 0;
}
int Read(vector<string> &Start,map<string,int> &T,vector<vector<Co> > &Token)//ѵ����ɷ������õ��ʵ�
{
    ifstream fin("test.txt");
    if(!fin)
    {
        cout<<"can't find your file"<<endl;
        return 0;
    }
    char p;
    string s;
    bool finish=1;//�ж��Ƿ�Ϊ��ʼToken
    int val=0;//����Token���и���
    int fir=0;
    Token.resize(10000);
    while(fin.get(p))
    {
        if(p=='\n'||p=='\0'||p=='\t') continue;
        if(s.size()==2) //һ�����ֻ����
        {
            if(s=="��"||s=="��"||s=="��"||s=="��"||s=="��"||s=="��") continue;
            int lo=0;
            //pari<string,string>�еĵ�һ��
            int sec=0;//pari<string,string>�еĵڶ���
            if(Charjudge(s)==0) {
                if(T.count(s)==0)//�ж�Token��������û��s,û�оͼ���
                {
                    lo=val;
                    T[s]=val;
                    val++;
                }
                else lo=T[s];
            }
            if(finish==1)//��ʼ
            {

                AddStart(s,Start);
                finish=0;
                //AddToken(s,Token,lo);
            }
            else
            {
                if(Charjudge(s)==1)//����
                {
                    finish=1;
                    //AddToken(s,Token,lo);
                }
                AddToken(s,Token,fir);
                //AddToken(s,Token,lo);
            }
            fir=lo;
            s.clear();
        }
        s+=p;
    }
    fin.close();
    return 0;
}
string Max(vector<vector<Co> >Token,int lo)
{
    int M=Token[lo][0].weight;
    string N=Token[lo][0].name;
    for(int i=0;i<Token[lo].size();i++)
    {
        if(M<Token[lo][i].weight)
        {
            M=Token[lo][i].weight;
            N=Token[lo][i].name;
        }
    }
    return N;
}
string Rand(vector<vector<Co> >Token,int lo)
{
    int r=rand()%(Token[lo].size());
    return Token[lo][r].name;
}
int Write(vector<string> Start,map<string,int> T,vector<vector<Co> > Token)
{
    srand((unsigned)time(NULL));
    int r=rand()%(Start.size());
    string first=Start[r];
    string sen=Max(Token,T[first]);
    map<string,int> xxx;
    cout<<first;
    xxx[first]++;
    int n=200;
    while(n>0)
    {
        cout<<sen;
        xxx[sen]++;
        if(sen=="��")
        {
            int t=rand()%(Start.size());
            sen=Max(Token,T[Start[t]]);
            xxx[Start[t]]++;
            cout<<Start[t];
        }
        else if(Charjudge(sen)) break;
        else
        {
            if(xxx[sen]>0)
            sen=Rand(Token,T[sen]);
            else sen=Max(Token,T[sen]);
        }
        n--;
    }
    cout<<endl;
    return 0;
}
int main()
{
    vector<string> Start;//��ʼtoken
    //map<string,int> End;//��ֹtoken
    map<string,int> T;//Token����
    vector<vector<Co> > Token;//�ʵ�
    Read(Start,T,Token);
/*
    map<string,int>::iterator iter;
    for(iter = T.begin(); iter != T.end(); iter++) {
        cout << iter->first << " : ";
        for(int i=0;i<Token[iter->second].size();i++)
            cout<<Token[iter->second][i].name<<Token[iter->second][i].weight<<" ";
        cout<<endl;
    }*/
    char ch;
    cout<<"�Ƿ����ɾ���(Y/N)��";
    cin>>ch;
    while(ch=='Y'||ch=='y')
    {
        Write(Start,T,Token);
        cout<<endl;
        cout<<"�Ƿ����(Y/N): ";
        cin>>ch;
    }
    return 0;
}
