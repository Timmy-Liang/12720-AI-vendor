#include<iostream>
#include<set>
using namespace std;
void sellcmdty(auto it,int type_w);
void addcmdt(int w,int v);
class cmdty {
  public:
    cmdty(int w,int v):weight(w),price(v) {
        num=1;
    }
    cmdty(int w,int v,int nu):weight(w),price(v),num(nu) {}
    int weight;
    int price;
    int num;
};

struct wcomp {
    bool operator ()(const cmdty &lhs,const cmdty &rhs) {
        if(lhs.weight!=rhs.weight)return lhs.weight<rhs.weight;
        return lhs.price<rhs.price;
    }
};

struct vcomp {
    bool operator ()(const cmdty &lhs,const cmdty &rhs) {
        if(lhs.price!=rhs.price)return lhs.price>rhs.price;
        return lhs.weight<rhs.weight;
    }
};

set<cmdty,wcomp> wset;
set<cmdty,vcomp> vset;

int main(void) {
    int N,M;
    cin>>N;
    for(int i=0; i<N; i++) {
        int w,v;
        cin>>w>>v;
        addcmdt(w,v);
    }
    int op,va,vb;
    cin>>M;
    for(int i=0; i<M; i++) {
        cin>>op;
        if(op==1) {
            cin>>va>>vb;
            addcmdt(va,vb);
        } else if(op==2) {
            cin>>va>>vb;
            auto it=wset.find(cmdty (va,vb));
            if(it!=wset.end()) {
                sellcmdty(it,1);
                cout<<"OK"<<endl;
            } else cout<<"No Item"<<endl;
        } else if(op==3) {
            cin>>va;
            auto it=wset.lower_bound(cmdty(va,0));
            if(it!=wset.end()) {
                cout<<"OK "<<(it->weight)<<" "<<(it->price)<<endl;
                sellcmdty(it,1);
            } else cout<<"No Item"<<endl;
        } else if(op==4) {
            cin>>va;
            auto it=vset.lower_bound(cmdty(0,va));
            if(it!=vset.end()) {
                cout<<"OK "<<(it->weight)<<" "<<(it->price)<<endl;
                sellcmdty(it,0);
            } else cout<<"No Item"<<endl;
        }
    }
    return 0;
}

void sellcmdty(auto it,int type_w) {
    if(it->num>1) {
        int we=it->weight;
        int pr=it->price;
        int nu=it->num;
        wset.erase(cmdty(we,pr));
        vset.erase(cmdty(we,pr));
        wset.insert(cmdty(we,pr,nu-1));
        vset.insert(cmdty(we,pr,nu-1));

    } else {
        if(type_w)wset.erase(it),vset.erase(cmdty(it->weight,it->price));
        else vset.erase(it),wset.erase(cmdty(it->weight,it->price));
    }
}
void addcmdt(int w,int v) {
    auto it=wset.find(cmdty(w,v));
    int nu;
    if(it!=wset.end()) {
        nu=it->num;
        it->num--;
        wset.erase(cmdty(w,v));
        vset.erase(cmdty(w,v));
        wset.insert(cmdty(w,v,nu+1));
        vset.insert(cmdty(w,v,nu+1));
    } else {
        wset.insert(cmdty(w,v));
        vset.insert(cmdty(w,v));
    }
}
