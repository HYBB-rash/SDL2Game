#ifndef SNAKE_ADT_H_
#define SNAKE_ADT_H_

// ADT
class LinkNode{
public:
    void* element;
    LinkNode *pre, *nxt;
};
class LinkList{
public:
    LinkNode *head, *tail;
} ;

void initLinkNode(LinkNode* self);

LinkNode* createLinkNode(void* element);

void initLinkList(LinkList* self);

LinkList* createLinkList();

void destroyLinkList(LinkList* self);

void destroyAnimationsByLinkList(LinkList* list);

void removeAnimationFromLinkList(LinkList* list, Animation* ani);

void pushLinkNode(LinkList* self, LinkNode* node);

void pushLinkNodeAtHead(LinkList* self, LinkNode* node);

void removeLinkNode(LinkList* self, LinkNode* node);

#endif
