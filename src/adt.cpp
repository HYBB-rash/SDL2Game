//
// Created by hyong on 2020/12/6.
//

#include "adt.h"
#include <cstdlib>
#include <cstring>

void LinkNode::initLinkNode() {
    element = nullptr;
    pre = nxt = nullptr;
}

LinkNode *LinkNode::createLinkNode(void *element) {
    LinkNode *self;
    self->initLinkNode();
    self->element = element;
    return self;
}

void *LinkNode::getElement() const {
    return element;
}

void LinkNode::setElement(void *element) {
    LinkNode::element = element;
}

LinkNode *LinkNode::getPre() const {
    return pre;
}

void LinkNode::setPre(LinkNode *pre) {
    LinkNode::pre = pre;
}

LinkNode *LinkNode::getNxt() const {
    return nxt;
}

void LinkNode::setNxt(LinkNode *nxt) {
    LinkNode::nxt = nxt;
}

void LinkList::initLinkList() {
    head = tail = nullptr;
}

LinkList *LinkList::createLinkList() {
    auto *self = new LinkList();
    self->initLinkList();
    return self;
}

void LinkList::destroyLinkList() {
    for (LinkNode *p = head, *nxt; p; p = nxt){
        nxt = p->getNxt();
        free(p);
    }
    free(this);
}

LinkNode *LinkList::getHead() const {
    return head;
}

void LinkList::setHead(LinkNode *head) {
    LinkList::head = head;
}

LinkNode *LinkList::getTail() const {
    return tail;
}

void LinkList::setTail(LinkNode *tail) {
    LinkList::tail = tail;
}

void LinkList::pushLinkNode(LinkNode *node) {
    if (head == nullptr) head = tail = node;
    else {
        tail->setNxt(node);
        node->setPre(tail);
        tail = node;
    }
}

void LinkList::pushLinkNodeAtHead(LinkNode *node) {
    if (head == nullptr) head = tail = node;
    else {
        node->setNxt(head);
        head->setPre(node);
        head = node;
    }
}

void LinkList::removeLinkNode(LinkNode *node) {
    if (node->getPre()) node->getPre()->setNxt(node->getNxt());
    else head = node->getNxt();
    if (node->getNxt()) node->getNxt()->setPre(node->getPre());
    else tail = node->getPre();
    free(node);
}


