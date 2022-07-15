/*
 * 
 * 	^v^
 * 
 */
#ifndef PRICE_CPP
#define PRICE_CPP
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>
#include <chrono>
#include "idexception.h"
#include "notempty.h"
using namespace std;
#define iamtefu ios_base::sync_with_stdio(false); cin.tie(0);
class Employee{
public:
	Employee* boss=nullptr;
	Employee* chead=nullptr;//head of child list
	Employee* ctail=nullptr;//tail of child list
	Employee* levnext=nullptr;//next neighbour in same level
	Employee* levprev=nullptr;//previous neighbour in same level
	int id;
	int lev=0;
	Employee()=default;
	Employee(int i):boss{nullptr}, id{i}{}
	Employee(int i, int le):id{i}, lev{le}{}
	Employee(int i, Employee* bo, int le):id{i}, boss{bo}, lev{le}{}
	void addemp(Employee* emp){
		if (emp==nullptr){
			throw IllegalIDException("Employee ID not found");
		}
		emp->boss=this;
		if (chead==nullptr){
			chead=emp;
			ctail=emp;
		} else {
			ctail->levnext=emp;
			emp->levprev=ctail;
			ctail=emp;
		}
	}
	void rememp(Employee* emp){
		Employee* h=chead;
		while (h!=nullptr && h!=emp){
			h=h->levnext;
		}
		if (h->levprev==nullptr && h->levnext==nullptr){
			ctail=chead=nullptr;
		} else {
			if (h->levnext==nullptr){
				ctail=h->levprev;
				ctail->levnext=nullptr;
			} else if (h->levprev==nullptr){
				chead=h->levnext;
				chead->levprev=nullptr;
			} else {
				Employee* t=h->levnext;
				t->levprev=h->levprev;
				h->levprev->levnext=t;
			}
		}
	}
};
typedef Employee* EmpPtr;
void merge(vector <EmpPtr> &a1, vector <EmpPtr> &a2, int i, int mid, int j){
	vector <EmpPtr> gg=a1;
	int il=i, ir=mid+1, curi=i;
	while (il<=mid && ir<=j){
		if (a1[il]->id<a2[ir]->id){
			gg[curi]=a1[il];
			il++;
			curi++;
		} else {
			gg[curi]=a2[ir];
			ir++;
			curi++;
		}
	}
	while (il<=mid){
		gg[curi]=a1[il];
		il++;
		curi++;
	}
	while (ir<=j){
		gg[curi]=a2[ir];
		ir++;
		curi++;
	}
	a1=gg;
}
void mergesort(vector <EmpPtr> &a, int i, int j){
	if (i==j){
		return;
	}
	int mid=(i+j)/2;
	vector <EmpPtr> a1=a;
	vector <EmpPtr> a2=a;
	mergesort(a1, i, mid);
	mergesort(a2, mid+1, j);
	merge(a1, a2, i, mid, j);
	a=a1;
}
class Node{
public:
	int key;
	Node* left=nullptr;
	Node* right=nullptr;
	Node* par=nullptr;
	Employee* emp=nullptr;
	int bf=0;
	Node():key{0}, left{nullptr}, right{nullptr}, par{nullptr}, bf{0}{}
	Node(int k):key{k}, left{nullptr}, right{nullptr}, par{nullptr}, bf{0}{}
	Node(int k, int b):key{k}, left{nullptr}, right{nullptr}, par{nullptr}, bf{b}{}
	Node(int k, Node* l, Node* r, Node* p, Employee* em, int b):key{k}, left{l}, right{r}, par{p}, emp{em}, bf{b}{}
	Node(Node &a){
		Node(a.key, a.left, a.right, a.par, a.emp, a.bf);
	}
	bool operator<(const Node &p){
		if (key<p.key){
			return true;
		}return false;
	}
	bool operator>(const Node &p){
		if (key>p.key){
			return true;
		}
		return false;
	}
};
class AVL{
public:
	Node* root=nullptr;
	AVL()=default;
	AVL(int k){
		root=new Node(k);
	}
	AVL(Node* k){
		root=k;
	}
	void preordernode(Node* x){
		if (x!=nullptr){
			cout<<x->key<<" ";
			preordernode(x->left);
			preordernode(x->right);
		}
	}
	void preorder(){
		preordernode(this->root);
		cout<<"\n";
	}
	Node* sear(int k){
		Node* x=root;
		while (x!=nullptr && x->key!=k){
			if (x->key>k){
				x=x->left;
			} else {
				x=x->right;
			}
		}
		if (x==nullptr){
			throw IllegalIDException("Employee ID not found");
		}
		return x;
	}
	Node* mn(Node* m){
		while (m->left!=nullptr){
			m=m->left;
		}
		return m;
	}
	Node* mx(Node* m){
		while (m->right!=nullptr){
			m=m->right;
		}
		return m;
	}
	Node* pre(Node* x){
		if (x->left!=nullptr){
			x=x->left;
			while (x->right!=nullptr){
				x=x->right;
			}
			return x;
		} else {
			Node* y=x->par;
			while (y!=nullptr && x==y->right){
				x=y;
				y=y->par;
			}
			return x;
		}
	}
	Node* suc(Node* x){
		if (x->right!=nullptr){
			x=x->right;
			while (x->left!=nullptr){
				x=x->left;
			}
			return x;
		} else {
			Node* y=x->par;
			while (y!=nullptr && x==y->left){
				x=y;
				y=y->par;
			}
			return x;
		}
	}
	void updbal(Node* x){
		if (x!=nullptr){
			if (x->bf<-1 || x->bf>1){
				bal(x);
				return;
			}
			if (x->par!=nullptr){
				if (x==x->par->left){
					x->par->bf-=1;
				}
				if (x==x->par->right){
					x->par->bf+=1;
				}
				if (x->par->bf!=0){
					updbal(x->par);
				}
			}
		}
	}
	void dbal(Node* x){
		if (x!=nullptr){
			if (x->bf<-1 || x->bf>1){
				bal(x);
			}
			if (x->par!=nullptr){
				if (x==x->par->left){
					x->par->bf+=1;
				}
				if (x==x->par->right){
					x->par->bf-=1;
				}
				dbal(x->par);
			}
		}
	}
	void bal(Node* x){
		if (x!=nullptr && x->bf>0){
			if (x->right!=nullptr && x->right->bf<0){
				rightrotate(x->right);
				leftrotate(x);
			} else if (x->right!=nullptr){
				leftrotate(x);
			}
		} else if (x!=nullptr && x->bf<0){
			if (x->left!=nullptr && x->left->bf>0){
				leftrotate(x->left);
				rightrotate(x);
			} else if (x->left!=nullptr){
				rightrotate(x);
			}
		}
	}
	void insert(Node* z){
		Node* x=root;
		Node* y=nullptr;
		while (x!=nullptr){
			y=x;
			if (x->key>z->key){
				x=x->left;
			} else {
				x=x->right;
			}
		}
		z->par=y;
		if (y==nullptr){
			root=z;
		} else if (y->key<z->key){
			(y->right)=z;
		} else {
			(y->left)=z;
		}
		updbal(z);
	}
	void insert(int k){
		Node* x=new Node(k);
		insert(x);
	}
	void leftrotate(Node *x){
		if (x!=nullptr && x->right!=nullptr){
			Node* y=x->right;
			x->right=y->left;
			if (y->left!=nullptr){
				y->left->par=x;
			}
			y->left=x;
			y->par=x->par;
			if (x->par==nullptr){
				root=y;
			} else if (x==x->par->left){
				x->par->left=y;
			} else {
				x->par->right=y;
			}
			x->par=y;
			x->bf=(x->bf)-1-max(0, y->bf);
			y->bf=(y->bf)-1+min(0, x->bf);
		}
	}
	void rightrotate(Node* x){
		if (x!=nullptr && x->left!=nullptr){
			Node* y=x->left;
			x->left=y->right;
			if (y->right!=nullptr){
				y->right->par=x;
			}
			y->right=x;
			y->par=x->par;
			if (x->par==nullptr){
				root=y;
			} else if (x==x->par->left){
				x->par->left=y;
			} else {
				x->par->right=y;
			}
			x->par=y;
			x->bf=x->bf+1-min(0,y->bf);
			y->bf=y->bf+1+max(0,x->bf);
		}
	}
	void trans(Node* u, Node* v){
		if (u->par==nullptr){
			root=v;
		} else if (u==u->par->left){
			u->par->left=v;
		} else {
			u->par->right=v;
		}
		if (v!=nullptr){
			v->par=u->par;
			v->bf=u->bf;
		}
	}
	void del(Node* z){
		Node* cur=(sear(z->key));
		if (z->left==nullptr){
			Node* gg=z->par;
			trans(z, z->right);
			dbal(gg);
		} else if (z->right==nullptr){
			Node* yo=z->par;
			trans(z, z->left);
			dbal(yo);
		} else {
			Node* y=mn(z->right);
			if (y!=z->right){
				Node* g=y->par;
				trans(y,y->right);
				dbal(g);
				y->right=z->right;
				y->right->par=y;
			}
			Node* h=z->par;
			trans(z,y);
			dbal(h);
			y->left=z->left;
			y->left->par=y;
		}
		delete z;
	}
	void prin(Node* root, string s, bool bo){
		if (root!=nullptr){
			cout<<s;
			if (bo){
				cout<<"R----";
				s+="     ";
			} else {
				cout<<"L----";
				s+="|    ";
			}
			cout<<root->key<<"( BF = "<<root->bf<<")"<<'\n';
			prin(root->left, s, false);
			prin(root->right, s, true);
		}
	}
	void trpri(){
		prin(this->root, "", true);
	}
};
class Org{
private:
	int n;
	AVL tree;
	Employee* root;
public:
	Org(){
		n=0;
		tree=AVL();;
		root=nullptr;
	}
	bool isEmpty(){
		return (n==0);
	}
	int size(){
		return n;
	}
	int level(int id){
		Node* x = tree.sear(id);
		if (x==nullptr){
			return -1;
		}
		return x->emp->lev;
	}
	void hireOwner(int id){
		if (n!=0){
			throw NotEmptyException("Organization already has an owner cannot hire another");
		}
		root=new Employee(id, 1);
		Node* r = new Node(id);
		r->emp=root;
		tree.insert(r);
		n++;
	}
	void hireEmployee(int id,int Bossid){
		Node* hu=tree.sear(Bossid);
		Employee* b=hu->emp;
		Employee* emp = new Employee(id, b->lev+1);
		b->addemp(emp);
		emp->boss=b;
		Node* em = new Node(id);
		em->emp=emp;
		tree.insert(em);
		n++;
	}
	void fireEmployee(int id){
		Node* hy=tree.sear(id);
		if (hy->emp->chead!=nullptr){
			throw IllegalIDException("Cannot fire Employee without ManageID, Employee has some workers working under him");
		}
		if (hy->emp->boss==nullptr){
			throw IllegalIDException("Can't Fire Owner");
		}
		Employee* boss=hy->emp->boss;
		boss->rememp(hy->emp);
		tree.del(hy);
		n--;
	}
	void fireEmployee(int id, int manageid){
		Node* hy=tree.sear(id);
		Node* mg=tree.sear(manageid);
		if (hy->emp->lev!=mg->emp->lev){
			throw IllegalIDException("ID and ManageID are not on same level");
		}
		if (hy->emp->boss==nullptr){
			throw IllegalIDException("Can't Fire Owner");
		}
		Employee* cur=hy->emp;
		Employee* ne=mg->emp;
		Employee* ch=cur->chead;
		while (ch!=nullptr){
			ne->addemp(ch);
			ch=ch->levnext;
		}
		hy->emp->boss->rememp(hy->emp);
		tree.del(hy);
		n--;
	}
	int boss(int id){
		Node* hu=tree.sear(id);
		if (hu->emp->lev==0){
			return -1;
		} else {
			return (hu->emp->boss->id);
		}
	}
	int lowestCommonBoss(int id1, int id2){
		Employee* emp1=tree.sear(id1)->emp;
		Employee* emp2=tree.sear(id2)->emp;
		if (emp1->id==root->id || emp2->id==root->id){
			return -1;
		}
		emp1=emp1->boss;
		emp2=emp2->boss;
		while (emp1!=nullptr && emp2!=nullptr && emp1->lev!=emp2->lev){
			if (emp1->lev>emp2->lev){
				emp1=emp1->boss;
			} else {
				emp2=emp2->boss;
			}
		}
		while (emp1!=nullptr && emp2!=nullptr && emp1->id!=emp2->id){
			emp1=emp1->boss;
			emp2=emp2->boss;
		}
		return emp1->id;
	}
	string toString(int id){
		Employee* x=tree.sear(id)->emp;
		string org="";
		vector <Employee*> a={x};
		while (a.size()>0){
			vector <Employee*> b;
			for (Employee* emp:a){
				string emp_str="";
				int emp_id=emp->id;
				while (emp_id){
					emp_str+=('0'+emp_id%10);
					emp_id/=10;
				}
				for (int i=emp_str.size()-1; i>=0; i--){
					org+=emp_str[i];
				}
				org+=' ';
				Employee* ch=emp->chead;
				while (ch!=nullptr){
					b.push_back(ch);
					ch=ch->levnext;
				}
			}
			if (b.size()){
				mergesort(b, 0, b.size()-1);
			}
			a=b;
		}
		return org;
	}
	void it(int id){
		Employee* h=tree.sear(id)->emp;
		Employee* gg=h->ctail;
		while (gg!=nullptr){
			cout<<gg->id<<" ";
			gg=gg->levprev;
		}
		cout<<"\n";
	}
};
#endif