#ifndef SNAKE_ADT_H_
#define SNAKE_ADT_H_

// ADT
class LinkNode{
public:
    void* element;
    LinkNode *pre, *nxt;

    void initLinkNode();
};

LinkNode* createLinkNode(void* element);

class LinkList{
public:
    LinkNode *head, *tail;

    void initLinkList();
    void destroyLinkList();
    void pushLinkNode(LinkNode *node);
    void pushLinkNodeAtHead(LinkNode *node);
    void removeLinkNode(LinkNode *node);
} ;

LinkList* createLinkList();

void destroyAnimationsByLinkList(LinkList* list);

void removeAnimationFromLinkList(LinkList* list, Animation* ani);

#endif
