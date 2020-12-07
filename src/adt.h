//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_ADT_H
#define SDL2GAME_ADT_H
class LinkNode {
public:
    void* element;
    struct _LinkNode *pre, *nxt;
};
class LinkList{
public:
    LinkNode *head, *tail;
} ;

/**
 * 初始化链表的节点为null
 * @param self
 */
void initLinkNode(LinkNode* self);

/**
 * 创建一个链表的节点
 * @param element 链表内的内容
 * @return 返回一个节点
 */
LinkNode* createLinkNode(void* element);

/**
 * 初始化链表，把链表的头节点和尾节点初始化为null
 * @param self 一个链表
 */
void initLinkList(LinkList* self);

/**
 * 创建一个链表结构
 * @return 链表指针
 */
LinkList* createLinkList();

/**
 * 历遍整个链表，把所有的链表节点删除
 * @param self 一个链表
 */
void destroyLinkList(LinkList* self);

/**
 * 将所有的链表的节点对应的动画效果删除，并每删除一个动画，就移除一个链表节点
 * @param list
 */
void destroyAnimationsByLinkList(LinkList* list);

void removeAnimationFromLinkList(LinkList* list, Animation* ani);

/**
 * 将节点插入链表中
 * @param list 待插入的链表（双向链表的插法）
 * @param node 待插入的节点
 */
void pushLinkNode(LinkList* self, LinkNode* node);

/**
 * 将节点插入链表中（头插法）
 * @param list 待插入的链表（双向链表的插法）
 * @param node 待插入的节点
 */
void pushLinkNodeAtHead(LinkList* self, LinkNode* node);

/**
 * 删除链表中的节点
 * @param list
 * @param node
 */
void removeLinkNode(LinkList* self, LinkNode* node);

#endif //SDL2GAME_ADT_H
