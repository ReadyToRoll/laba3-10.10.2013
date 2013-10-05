#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
    int n;
    int count;
    node*left,*right;
};

class Tree
{

public:
    int n;
    node*root;
    Tree(){root=0;}
    Tree(int t);
    void DelTree(node *wer);
    ~Tree()
    {
        DelTree(root);
    }
    void Push(node*&wer,int data);// Вставка элемента в дерево
    void Look(node*wer);          //- Вывод дерева на экран
    void PrintLeaves(node *wer);  // Вывод листьев дерева на экран
    bool is_in_tree(node*wer,int k);
    Tree operator+(Tree &b);    //объединение
    void Union(node*wer,Tree &buf);
   // Tree operator-(Tree &b);    //пересечение
   // Tree operator*(Tree &b);    //разность
};



Tree::Tree(int t)
{
    n=t;
    root=0;
    for(int i=0; i<t; i++)
    {
        int k=rand();
        if(is_in_tree(root,k)==false)
        Push(root,k);
        else
        t++;
    }
}

Tree Tree::operator+(Tree &tr2)
{
    Tree buf;
    Union(root,buf);
    Union(tr2.root,buf);
   return buf;
}

void Tree::Union(node*wer,Tree &buf)
{
    if(wer!=0)
    {
        Union(wer->left,buf);
        Push(buf.root,wer->n);
        Union(wer->right,buf);
    }
}

void Tree::DelTree(node *wer)
{
    if(root!=0)
    {
    if(wer->left!=0)DelTree(wer->left);
    if(wer->right!=0)DelTree(wer->right);
    delete wer;
    }
}
void Tree::Push(node*&wer,int data)
{
    if(wer==0)
    {
        wer=new node;
        wer->n=data;
        wer->left=0;
        wer->right=0;
        wer->count=1;
    }
    else if(data<wer->n)Push(wer->left,data);
    else if(data>wer->n)Push(wer->right,data);
    else wer->count++;
}

void Tree::Look(node*wer)
{
    if(wer!=0)
    {
        Look(wer->left);
        cout<<wer->n<<" ";
        Look(wer->right);
    }
}

bool Tree::is_in_tree(node*wer,int k)
{
    if(wer!=0)
    {
        is_in_tree(wer->left,k);
        if(wer->n==k)
        return true;
        is_in_tree(wer->right,k);
    }
    return false;
}

void Tree::PrintLeaves(node *wer)
{
    if(wer==0)return;
    else if( (wer->left==0)&&(wer->right==0) )
    {
        cout<<wer->n<<"  ";
    }
    else
    {
        PrintLeaves(wer->left);
        PrintLeaves(wer->right);
    }
}

int main()
{
 int w=0,k,n;
    cout<<"Input a size of set: ";
    cin>>n;
    Tree tr(n);
    Tree tr2(n);
    do
    {
        cout<<"select the required operation:"<<endl;
          cout<<" 1 - Push element to set"<<endl;
          cout<<" 2 - Show set"<<endl;
         // cout<<" 3 - Print leaves"<<endl;
          cout<<" 4 - is in set"<<endl;
          cout<<" 5 - union"<<endl;
         // cout<<" 6 - difference"<<endl;
         // cout<<" 7 - interception"<<endl;
        cout<<" 8 - exit"<<endl<<endl;
        cin>>w;
        switch(w)
        {
                 case 1:
                     int data;
                       cout<<"Enter value ";
                       cin>>data;
                       if(tr.is_in_tree(tr.root,data)==true)
                            cout<<"value already in set"<<endl;
                        else
                       tr.Push(tr.root,data);
                     break;
                case 2:
                    int ch;
                    cout<<"for first set enter 0, for second - 1"<<endl;
                    cin>>ch;
                  if(ch==true)
                  {
                  if(tr.root==0)
                    cout<<"Set empty";
                       else
                           {
                            cout<<"Set:"<<endl;
                            tr.Look(tr.root);
                           }
                           cout<<endl<<endl;
                  }
                  else
                    {
                  if(tr2.root==0)
                    cout<<"Set empty";
                       else
                           {
                            cout<<"Set:"<<endl;
                            tr2.Look(tr2.root);
                           }
                           cout<<endl<<endl;
                  }
                 break;
             /*    case 3:
                    if(tr.root==0)
                        cout<<"Tree empty";
                       else{
                            cout<<"Leaves:"<<endl;
                            tr.PrintLeaves(tr.root);
                           }
                           cout<<endl<<endl;
                     break;*/
                 case 4:
                     {
                         cout<<"enter value to check: ";
                         cin>>k;
                        if(tr.is_in_tree(tr.root,k)==true)
                            cout<<"value already in set"<<endl;
                        else
                            cout<<"don't have this value"<<endl;
                     break;
                     }
               case 5:
                     {
                      cout<<"Set 1:"<<endl;
                            tr.Look(tr.root);
                            cout<<"Set 2:"<<endl;
                            tr2.Look(tr2.root);
                     Tree tr3;
                     tr3=tr+tr2;
                     if(tr3.root==0)
                    cout<<"Set empty";
                       else
                           {
                            cout<<"Set:"<<endl;
                            tr3.Look(tr3.root);
                           }
                           cout<<endl<<endl;
                     break;
                     }
              /*         case 6:
                      cout<<"Input a number of multiplicities to work: ";
                    cin>>d>>v;
                    d--;
                    v--;
                    if(d>k||v>k)
                     {
                     cout<<"no needed multiplie(s)"<<endl;
                     break;
                    }
                    else
                     spis[v]->hard_function(*spis,k,n,d).show(99);
                      break;*/
        case 8:
            break;
        }
    }
    while(w!=8);
    tr.~Tree();
    tr2.~Tree();
}
