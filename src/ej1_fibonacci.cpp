#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;

const int INF = 100000000;
 
struct posible {int v, w, p;};



/*Copyright (c) 2010, Robin Message <Robin.Message@cl.cam.ac.uk>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Univsersity of Cambridge nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OF CAMBRIDGE OR ROBIN MESSAGE
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

struct arista {
    int v, p;
    bool operator<(const arista &b) const {
        return p < b.p;
    }
    bool operator>(const arista &b) const {
        return p > b.p;
    }
};

template <class V> class FibonacciHeap;

template <class V> struct node {
private:
    node<V>* prev;
    node<V>* next;
    node<V>* child;
    node<V>* parent;
    V value;
    int degree;
    bool marked;
public:
    friend class FibonacciHeap<V>;
    node<V>* getPrev() {return prev;}
    node<V>* getNext() {return next;}
    node<V>* getChild() {return child;}
    node<V>* getParent() {return parent;}
    V getValue() {return value;}
    bool isMarked() {return marked;}

    bool hasChildren() {return child;}
    bool hasParent() {return parent;}
};

template <class V> class FibonacciHeap {
protected:
    node<V>* heap;
public:

    FibonacciHeap() {
        heap=_empty();
    }
    virtual ~FibonacciHeap() {
        if(heap) {
            _deleteAll(heap);
        }
    }
    node<V>* insert(V value) {
        node<V>* ret=_singleton(value);
        heap=_merge(heap,ret);
        return ret;
    }
    void merge(FibonacciHeap& other) {
        heap=_merge(heap,other.heap);
        other.heap=_empty();
    }

    bool isEmpty() {
        return heap==NULL;
    }

    V getMinimum() {
        return heap->value;
    }

    V removeMinimum() {
        node<V>* old=heap;
        heap=_removeMinimum(heap);
        V ret=old->value;
        delete old;
        return ret;
    }

    void decreaseKey(node<V>* n,V value) {
        heap=_decreaseKey(heap,n,value);
    }

    node<V>* find(V value) {
        return _find(heap,value);
    }
private:
    node<V>* _empty() {
        return NULL;
    }

    node<V>* _singleton(V value) {
        node<V>* n=new node<V>;
        n->value=value;
        n->prev=n->next=n;
        n->degree=0;
        n->marked=false;
        n->child=NULL;
        n->parent=NULL;
        return n;
    }

    node<V>* _merge(node<V>* a,node<V>* b) {
        if(a==NULL)return b;
        if(b==NULL)return a;
        if(a->value>b->value) {
            node<V>* temp=a;
            a=b;
            b=temp;
        }
        node<V>* an=a->next;
        node<V>* bp=b->prev;
        a->next=b;
        b->prev=a;
        an->prev=bp;
        bp->next=an;
        return a;
    }

    void _deleteAll(node<V>* n) {
        if(n!=NULL) {
            node<V>* c=n;
            do {
                node<V>* d=c;
                c=c->next;
                _deleteAll(d->child);
                delete d;
            } while(c!=n);
        }
    }
    
    void _addChild(node<V>* parent,node<V>* child) {
        child->prev=child->next=child;
        child->parent=parent;
        parent->degree++;
        parent->child=_merge(parent->child,child);
    }

    void _unMarkAndUnParentAll(node<V>* n) {
        if(n==NULL)return;
        node<V>* c=n;
        do {
            c->marked=false;
            c->parent=NULL;
            c=c->next;
        }while(c!=n);
    }

    node<V>* _removeMinimum(node<V>* n) {
        _unMarkAndUnParentAll(n->child);
        if(n->next==n) {
            n=n->child;
        } else {
            n->next->prev=n->prev;
            n->prev->next=n->next;
            n=_merge(n->next,n->child);
        }
        if(n==NULL)return n;
        node<V>* trees[64]={NULL};
        
        while(true) {
            if(trees[n->degree]!=NULL) {
                node<V>* t=trees[n->degree];
                if(t==n)break;
                trees[n->degree]=NULL;
                if(n->value<t->value) {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    _addChild(n,t);
                } else {
                    t->prev->next=t->next;
                    t->next->prev=t->prev;
                    if(n->next==n) {
                        t->next=t->prev=t;
                        _addChild(t,n);
                        n=t;
                    } else {
                        n->prev->next=t;
                        n->next->prev=t;
                        t->next=n->next;
                        t->prev=n->prev;
                        _addChild(t,n);
                        n=t;
                    }
                }
                continue;
            } else {
                trees[n->degree]=n;
            }
            n=n->next;
        }
        node<V>* min=n;
        node<V>* start=n;
        do {
            if(n->value<min->value)min=n;
            n=n->next;
        } while(n!=start);
        return min;
    }

    node<V>* _cut(node<V>* heap,node<V>* n) {
        if(n->next==n) {
            n->parent->child=NULL;
        } else {
            n->next->prev=n->prev;
            n->prev->next=n->next;
            n->parent->child=n->next;
        }
        n->next=n->prev=n;
        n->marked=false;
        return _merge(heap,n);
    }

    node<V>* _decreaseKey(node<V>* heap,node<V>* n,V value) {
        if(n->value<value)return heap;
        n->value=value;
        if(n->parent) {
            if(n->value<n->parent->value) {
                heap=_cut(heap,n);
                node<V>* parent=n->parent;
                n->parent=NULL;
                while(parent!=NULL && parent->marked) {
                    heap=_cut(heap,parent);
                    n=parent;
                    parent=n->parent;
                    n->parent=NULL;
                }
                if(parent!=NULL && parent->parent!=NULL)parent->marked=true;
            }
        } else {
            if(n->value < heap->value) {
                heap = n;
            }
        }
        return heap;
    }

    node<V>* _find(node<V>* heap,V value) {
        node<V>* n=heap;
        if(n==NULL)return NULL;
        do {
            if(n->value==value)return n;
            node<V>* ret=_find(n->child,value);
            if(ret)return ret;
            n=n->next;
        }while(n!=heap);
        return NULL;
    }
};

vector<int> dijkstra(vector<vector<arista>>& grafo, int v, int n) {
    FibonacciHeap<arista> heap;
    heap.insert({v, 0});
    vector<int> dist(n, INF);
    vector<node<arista>*> nodos(n);

    for(int i = 0; i < n; ++i) heap.insert({u, dist[u]});
    vector<bool> esta(n, false);
    dist[v] = 0;

    while(!heap.isEmpty()) {
        int w = heap.getMinimum().v; heap.removeMinimum();
        if(esta[w]) continue;
        esta[w] = true;
        for(arista k : grafo[w]) {
            int p = k.p, u = k.v;
            if(dist[u] > dist[w] + p) {
                dist[u] = dist[w] + p;
                heap.insert({u, dist[u]});
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m, k, s, t; cin >> n >> m >> k >> s >> t;
        --s; --t;

        vector<vector<arista>> grafo(n), grafoT(n);
        for(int i = 0; i < m; ++i) {
            int v, w, p; cin >> v >> w >> p;
            grafo[v-1].push_back({w-1, p});
            grafoT[w-1].push_back({v-1, p});
        } 

        vector<posible> posibles;
        for(int i = 0 ; i < k; ++i) {
            int v, w, p; cin >> v >> w >> p;
            posibles.push_back({v-1, w-1, p});
        }

        vector<int> ds = dijkstra(grafo, s, n); 
        vector<int> dt = dijkstra(grafoT, t, n);
        
        int mn = ds[t];
        for(posible b : posibles) {
            mn = min(mn, ds[b.v] + b.p + dt[b.w]); 
            mn = min(mn, ds[b.w] + b.p + dt[b.v]); 
        }

        cout << (mn < INF ? mn : -1) << endl;
    }
}