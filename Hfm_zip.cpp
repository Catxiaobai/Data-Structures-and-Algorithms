#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<cstring>
#include<stack>
using namespace std;
struct Hfm
{
    char name;
    int val;
    int parent,lchild,rchild;
    void Show()
    {
        cout<<name<<" "<<val<<" "<<parent<<" "<<lchild<<" "<<rchild<<endl;
    }
};
int ShowHelp()
{
    cout << "[zip|unzip]" << endl;
    cout << "zip means zip sourcefile to destfile"<<endl<<"unzip means extract sourcefile to destfile." << endl;
    return 0;
}
int Select(vector<Hfm> T,int &m,int &n)
{
    m=-1,n=-2;
    for(int i=0;i<T.size();i++)
    {
        if(T[i].parent==-1){
        if(m==-1||T[m].val>T[i].val)
        {
            n=m;
            m=i;
        }
        else if(n==-1||T[n].val>T[i].val)
        {
            n=i;
        }
        }
    }
    return 0;
}

int CreatTree(map<char,int> arr,vector<Hfm> &T)
{
    int len=arr.size();
    map<char,int>::iterator iter;
	for (iter = arr.begin(); iter != arr.end(); iter++) {
            Hfm tt;
    tt.name=iter->first;
    tt.val=iter->second;
    tt.parent=-1;
    tt.lchild=-1;
    tt.rchild=-1;
    T.push_back(tt);
	}
    for(int i=0;i<len-1;i++)
    {
        int m,n;
        Select(T,m,n);
        Hfm tt;
    tt.name=-1;
    tt.val=T[m].val+T[n].val;
    tt.parent=-1;
    tt.lchild=m;
    tt.rchild=n;
    T.push_back(tt);
        //T.push_back(Hfm(-1,T[m].val+T[n].val,-1,m,n));
        T[m].parent=T.size()-1;
        T[n].parent=T.size()-1;
    }
    return 0;
}

int Hfmcode(vector<Hfm> T,map<char,string> &Code)
{
    for(int i=0;i<T.size();i++)
    {
        string s;
        stack<char> c;
        if(T[i].lchild==-1&&T[i].rchild==-1)
        {
            int j=i;
            while(T[j].parent>=0){
                    int temp=j;
            j=T[j].parent;
            if(T[j].lchild==temp)
            {
                c.push('0');
            }
            else c.push('1');
            }
        }
        else break;
        while(!c.empty())
        {
            s=s+c.top();
            c.pop();
        }
        Code[T[i].name]=s;
    }
    return 0;
}

string Str(string s)//将01二进制数转换成字符
{
    map<int,int> change;
    change[7]=1;
    change[6]=2;
    change[5]=4;
    change[4]=8;
    change[3]=16;
    change[2]=32;
    change[1]=64;
    change[0]=128;
    unsigned char c;
    int n=0;
    string t;
    for(int i=0;i<s.size();i++)
    {
        if(i%8==0&&i!=0)
        {
            c=n;
            t+=c;
            n=0;
        }
        if(s[i]=='1')
            n+=change[i%8];
    }
    c=n;
    t+=c;
    return t;
}

int Compresses(vector<Hfm> T,string s,char *file)
{
    cout<<"Zipping..."<<endl;
    ofstream out(file,ios::out|ios::binary);
    int num=T.size();
    out.write((char*)&num,sizeof(int));//树的大小
    out.write((char*)&T[0],T.size()*sizeof(Hfm));//哈夫曼树
    int num2=s.size();
    out.write((char*)&num2,sizeof(int));//文件的大小
    out<<Str(s);//哈夫曼编码
    cout<<"Zipped!"<<endl;
    out.close();
    return 0;
}

string Bin(string t,int n)//将0-256的数转换成8位二进制
{
    map<int,int> change;
    change[7]=1;
    change[6]=2;
    change[5]=4;
    change[4]=8;
    change[3]=16;
    change[2]=32;
    change[1]=64;
    change[0]=128;
    string s;
    for(int j=0;j<t.size();j++)
    {
        unsigned char c=t[j];
        int a=c;
        for(int i=0;i<8;i++)
        {
            if(a>=change[i])
            {
                a-=change[i];
                s+='1';
            }
            else s+='0';
        }
    }
    int sur=8-n%8;
    while(sur--)
    {
        s.erase(s.end()-1);
    }
    return s;
}

int Uncode(vector<Hfm> T,string t,int sur,char *file)
{
    ofstream Un(file,ios::out|ios::binary);
    int r=T.size()-1;
    int temp=r;
    string s=Bin(t,sur);
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='0')
        {
            temp=T[r].lchild;
            if(T[temp].lchild==-1&&T[temp].rchild==-1)
            {
                Un.put(T[temp].name);
                r=T.size()-1;
            }
            else r=temp;
        }
        else
        {
            temp=T[r].rchild;
            if(T[temp].lchild==-1&&T[temp].rchild==-1)
            {
                Un.put(T[temp].name);
                r=T.size()-1;
            }
            else r=temp;
        }
    }
    Un.close();

    return 0;
}

int Uncode2(char *file1,char *file2)
{
    ifstream ss(file1,ios::in|ios::binary);
    int f;
    ss.read((char*)&f,sizeof(int));
    vector<Hfm> T0(f);
    ss.read((char*)&T0[0],T0.size()*sizeof(Hfm));
    int f2;
    ss.read((char*)&f2,sizeof(int));
    char x;
    string t;
    while(ss.get(x))
    {
        t+=x;
    }
    ss.close();
    Uncode(T0,t,f2,file2);
    cout<<"Unzipped!"<<endl;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        ShowHelp();
    }
    else if(strcmp(argv[1],"zip")==0)
    {
    map<char,int> arr;
    ifstream infile(argv[2],ios::in|ios::binary);
    if(!infile) {
        cout<<"false open "<<argv[2]<<endl;
        return 0;
    }
    string s;
    char ch;
    while(infile.get(ch))
    {
        arr[ch]++;
        s+=ch;
    }
    infile.close();//*/
    vector<Hfm> T;
    map<char,string> Code;
    CreatTree(arr,T);
    Hfmcode(T,Code);
    string Zip;
    for(int i=0;i<s.size();i++)
    {
        Zip+=Code[s[i]];
    }
    Compresses(T,Zip,argv[3]);
    }
    else if(strcmp(argv[1],"unzip")==0)
    {
        cout<<"Unzipping..."<<endl;
        Uncode2(argv[2],argv[3]);
    }
    else ShowHelp();
    return 0;
}
