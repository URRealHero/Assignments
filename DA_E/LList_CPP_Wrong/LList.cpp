#include "LinkList.h"
#include <cstddef>
#include <ostream>
LList::LList(){
  L = new LNode; 
  L->next = NULL;
  ListTraverse();
}
LList::LList(int ElemNum){
  L = new LNode;
  L->next = NULL;
  int cnt = 1;
  LinkList P;
  while(cnt <= ElemNum){
	ElemType v;
	std::cin >> v;
	P = new LNode;
	P->data = v;
	P->next = L->next;
	L->next = P;
  }
  ListTraverse();
}
LList::~LList(){
  LinkList P = L->next;
  while (P) {
      L->next = P->next;
      delete P;
      P = L->next;
  }
  delete L;
  L=NULL;
  std::cout << "The Link List is cleaned and the space is released!" << std::endl;
}


status LList::DestroyList(){
    if(!L) return INFEASIBLE;
    LinkList P = L->next;
    while (P) {
        L->next = P->next;
        delete P;
        P = L->next;
    }
    delete L;
    L=NULL;
    return OK;

}
