/*
 * 
 * 	^v^
 * 
 */
#include "price.cpp"
#include "idexception.h"
#include "notempty.h"
#include <chrono>
int main(){
	iamtefu;
	#if defined(airths)
		auto t1=chrono::high_resolution_clock::now();
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif
		Org org=Org();
		cout<<"\n--Initialized and Empty tree--\n";
		cout<<"\nis Tree Empty- "<<(org.isEmpty()?"true":"false")<<"\n";
		try{
			org.hireOwner(1);
			cout<<"Hired Owner successfully with id=1\n";
		} catch (NotEmptyException e){
			cout<<e.what()<<"\n";
		}
		cout<<"\nis Tree Empty- "<<(org.isEmpty()?"true":"false")<<"\n";
		cout<<"\n--Trying to hire owner with id = 2--\n";
		try{
			org.hireOwner(2);
		} catch (NotEmptyException e){
			cout<<e.what()<<"\n";
		}
		try{
			org.hireEmployee(3,1);
			cout<<"\nHired successfully Employee with id=3\n";
			org.hireEmployee(2,1);
			cout<<"\nHired successfully Employee with id=2\n";
			org.hireEmployee(12,1);
			cout<<"\nHired successfully Employee with id=12\n";
			org.hireEmployee(8,3);
			cout<<"\nHired successfully Employee with id=8\n";
			org.hireEmployee(4,3);
			cout<<"\nHired successfully Employee with id=4\n";
			org.hireEmployee(7,2);
			cout<<"\nHired successfully Employee with id=7\n";
			org.hireEmployee(10,12);
			cout<<"\nHired successfully Employee with id=10\n";
			org.hireEmployee(16,8);
			cout<<"\nHired successfully Employee with id=16\n";
			org.hireEmployee(5,8);
			cout<<"\nHired successfully Employee with id=5\n";
		} catch(IllegalIDException e) {
			cout<<e.what()<<"\n";
		}
		int size1=org.size();
		cout<<"New Organisation size: "<<size1<<"\n";
		if (size1!=10){
			cout<<"Fail\n";
		} else {
			cout<<"Pass\n";
		}
		cout<<org.toString(1)<<"\n";
		try{
			cout<<"What is the level of Employee 5?\n";
			int l=org.level(5);
			cout<<"Level = "<<l<<"\n";
			if (l!=4){
				cout<<"Fail\n";
			} else {
				cout<<"Pass\n";
			}
		} catch (IllegalIDException e){
			cout<<e.what()<<"\n";
		}
		try {
			cout<<"\n--Trying to fire Employee with id = 7--\n";
			org.fireEmployee(7);
			size1=org.size();
			cout<<"--Employee fired successfully--\n";
			cout<<"Size: "<<size1<<"\n";
			cout<<"Updated Organisation = "<<org.toString(1)<<"\n";
			if (size1!=9){
				cout<<"Fail\n";
			} else {
				cout<<"Pass\n";
			}
		} catch (IllegalIDException e){
			cout<<e.what()<<"\n";
		}
		try{
			cout<<"\n--fire employeee with id = 8 and make id = 4 new boss of its children--\n";
			org.fireEmployee(8,4);
			size1=org.size();
			cout<<"--Employee fired successfully--\n";
			cout<<"Size: "<<size1<<"\n";
			cout<<"New Tree- "<<org.toString(1)<<"\n";
			cout<<"Subtree rooted at 3- "<<org.toString(3)<<"\n";
			int boss1=org.boss(5);
			cout<<boss1<<"\n";
			if (boss1!=4){
				cout<<"Fail\n";
			} else {
				cout<<"--Employee 4 is made new boss successfully--\n";
				cout<<"PASS\n";
			}
			cout<<org.toString(1)<<"\n";
		} catch(IllegalIDException e){
			cout<<e.what()<<"\n";
		}
		try{
			cout<<"\n--Find lowest common boss of employees 3 and 10--\n";
			int lcb=0;
			lcb=org.lowestCommonBoss(3,10);
			cout<<"Lowest common Boss = "<<lcb<<"\n";
			if (lcb!=1){
				cout<<"FAIL\n";
			} else {
				cout<<"PASS\n";
			}
		} catch (IllegalIDException e){
			cout<<e.what()<<"\n";
		}
	#if defined(airths)
		auto t2=chrono::high_resolution_clock::now();
		long double ti=chrono::duration_cast<chrono::nanoseconds>(t2-t1).count();
		ti*=1e-6;
		cerr<<"Time: "<<ti<<setprecision(9);
		cerr<<"ms\n";
	#endif
	return 0;
}