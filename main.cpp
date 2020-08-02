#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node* lchild;
    node* rchild;
}*root;

class AVL
{
private:
    int BalanceFactor(node* p);
    node* LLrotation(node* p);
    node* LRrotation(node* p);
    node* RRrotation(node* p);
    node* RLrotation(node* p);
    node* inorderPre(node* p);
    node* inorderSucc(node* p);
public:
    AVL()
    {
        root=NULL;
    }
    node* insert(node* p,int n);
    node* deleted(node* p,int key);
    node* search(node* p,int key);
    int height(node* p);
    void inorder(node* p);
    void preorder(node* p);
    void postorder(node* p);
};

int AVL::height(node* p)
{
        int x,y;
        if(p==NULL)
            return 0;
        else
        {
            x=height(p->lchild);
            y=height(p->rchild);
            return x>y?x+1:y+1;
        }
}

int AVL::BalanceFactor(node* p)
{
        int x,y;
        if(p==NULL)
            return 0;
        else
        {
            x=height(p->lchild);
            y=height(p->rchild);
            return x-y;
        }
}

node* AVL::LLrotation(node* p)
{
    node* pl=p->lchild;
    node* plr=pl->rchild;
    pl->rchild=p;
    p->lchild=plr;
    
    if(p==root)
        root=pl;
    return pl;
}

node* AVL::LRrotation(node* p)
{
    node* pl=p->lchild;
    node* plr=pl->rchild;
    pl->rchild=plr->lchild;
    p->lchild=plr->rchild;
    plr->lchild=pl;
    plr->rchild=p;
    if(p==root)
        root=plr;
    return plr;
}

node* AVL::RRrotation(node* p)
{
    node* pr=p->rchild;
    node* prl=pr->lchild;
    pr->lchild=p;
    p->rchild=prl;
    if(root==p)
        root=pr;
    return pr;
}

node* AVL::RLrotation(node* p)
{
    node* pr=p->rchild;
    node* prl=pr->lchild;
    pr->lchild=prl->rchild;
    p->rchild=prl->lchild;
    prl->lchild=p;
    prl->rchild=pr;
    if(root==p)
        root=prl;
    return prl;
}

node* AVL::inorderPre(node* p)
{
    while(p && p->rchild)
        p=p->rchild;
    return p;
}

node* AVL::inorderSucc(node* p)
{
    while(p && p->lchild)
        p=p->lchild;
    return p;
}

node* AVL::search(node* p,int key)
{
    if(p==NULL)
        return NULL;
    if(p->data==key)
        return p;
    else if(key<p->data)
        return search(p->lchild,key);
    else
        return search(p->rchild,key);
        
    return NULL;
}

node* AVL::insert(node* p,int n)
{
    if(p==NULL)
    {
        node* t=new node;
        t->data=n;
        t->lchild=t->rchild=NULL;
        return t;
    }
    if(n<p->data)
        p->lchild=insert(p->lchild,n);
    else if(n>p->data)
        p->rchild=insert(p->rchild,n);
    
    if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
         return LLrotation(p);
    else if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
         return LRrotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==-1)
         return RRrotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==1)
         return RLrotation(p);
        
    return p;
}

node* AVL::deleted(node* p,int key)
{
    if(p==NULL)
        return NULL;
    if(p->lchild==NULL && p->rchild==NULL && p->data==key)
        {
            if(p==root)
                root=NULL;
            delete p;
            return NULL;
        }
   if(key<p->data)
       p->lchild=deleted(p->lchild,key);
   else if(key>p->data)
       p->rchild=deleted(p->rchild,key);
    else //key is found
    {
        if(height(p->lchild)>height(p->rchild))
        {
            node* q=inorderPre(p->lchild);
            p->data=q->data;
            p->lchild=deleted(p->lchild,q->data);
        }
        else
        {
            node* q=inorderSucc(p->rchild);
            p->data=q->data;
            p->rchild=deleted(p->rchild,q->data);
        }
    }
    if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
         return LLrotation(p);
    else if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
         return LRrotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==-1)
         return RRrotation(p);
    else if(BalanceFactor(p)==-2 && BalanceFactor(p->rchild)==1)
         return RLrotation(p);
         
    return p;
}

void AVL::inorder(node* p)
{
    if(p)
    {
        inorder(p->lchild);
        cout<<p->data<<" ";
        inorder(p->rchild);
    }
}

void AVL::preorder(node* p)
{
    if(p)
    {
        cout<<p->data<<" ";
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void AVL::postorder(node* p)
{
    if(p)
    {
        postorder(p->lchild);
        postorder(p->rchild);
        cout<<p->data<<" ";
    }
}
int main()
{
    AVL t;
    char ch;
    int choice,val1,val2,val3,h;
    node* s;
    
    do
    {
    cout<<"Enter choice:\n1.Insert\n2.Delete\n3.Search\n4.Height\n5.Inorder traversal\n6.Preorder traversal\n7.Postorder traversal\n";
    cin>>choice;
    switch(choice)
    {
        case 1:cout<<"\nEnter value to be inserted: ";
                cin>>val1;
                if(root==NULL)
                root=t.insert(root,val1);
                else
                    t.insert(root,val1);
                break;
        case 2:cout<<"\nEnter value to be deleted: ";
                cin>>val2; cout<<endl;
                t.deleted(root,val2);
                break;
        case 3:cout<<"\nEnter value to be searched: ";
                cin>>val3;
                s=t.search(root,val3);
                if(s==NULL) cout<<"Key "<<val3<<" is not found!"<<endl;
                else if(s->data==val3) cout<<"Key "<<val3<<" is found!"<<endl;
                break;
        case 4:h=t.height(root);
                cout<<"Height is: "<<h<<endl;
                break;
        case 5:t.inorder(root); cout<<endl;
                break;
        case 6:t.preorder(root); cout<<endl;
                break;
        case 7:t.postorder(root); cout<<endl;
                break;
        default: cout<<"INVALID OPTION!"<<endl;
                break;
    }
    cout<<"\nContinue?"<<endl;
    cin>>ch; cout<<endl;
    }while(ch=='y');

	return 0;
}
