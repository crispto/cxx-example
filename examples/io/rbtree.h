#ifndef __ST_HPC_PPL_CORE_INTERNAL_RBTREE_H_
#define __ST_HPC_PPL_CORE_INTERNAL_RBTREE_H_

#include "pair.h"
#include <cstddef> // size_t
#include <cstdint>

namespace ppl
{
namespace core
{
namespace internal
{

template <typename Key, typename Value, typename GetKeyFromValue, typename Comparator, typename Allocator> class RBTree final
{

private:
    enum {
        RB_RED = 0,
        RB_BLACK = 1,
    };

    class
#ifdef _MSC_VER
        __declspec(align(8))
#else
        __attribute__((aligned(sizeof(uintptr_t))))
#endif
            Node final
    {
    public:
        Node(const Value &value) : value_(value)
        {
            left_ = right_ = nullptr;
            parent_and_color_ = 0;
        }
        ~Node()
        {
        }
        Node *Parent() const
        {
            return (Node *)(parent_and_color_ & ~3);
        }
        void SetParent(Node *parent)
        {
            parent_and_color_ = (parent_and_color_ & 3) | (uintptr_t)parent;
        }
        int Color() const
        {
            return (parent_and_color_ & 1);
        }
        void SetColor(int c)
        {
            parent_and_color_ = (parent_and_color_ & ~1) | c;
        }
        bool IsRed() const
        {
            return (Color() == RB_RED);
        }
        bool IsBlack() const
        {
            return (Color() == RB_BLACK);
        }
        void SetRed()
        {
            parent_and_color_ &= ~1;
        }
        void SetBlack()
        {
            parent_and_color_ |= 1;
        }
        Node *Left() const
        {
            return left_;
        }
        void SetLeft(Node *node)
        {
            left_ = node;
        }
        Node **LeftAddr()
        {
            return &left_;
        }
        Node *Right() const
        {
            return right_;
        }
        void SetRight(Node *node)
        {
            right_ = node;
        }
        Node **RightAddr()
        {
            return &right_;
        }
        const Value *Data() const
        {
            return &value_;
        }
        Value *Data()
        {
            return &value_;
        }

    private:
        Value value_;
        Node *left_;
        Node *right_;
        /*
         * the last bit is used to mark RED/BLACK, since `Node`
         * is aligned to sizeof(uintptr_t), the last 1~3 bits(depend on arch)
         * of its address must be 0 and are unused.
         */
        uintptr_t parent_and_color_;
    };

public:
    class Iterator final
    {
    public:
        Iterator(Node *node = nullptr) : node_(node)
        {
        }
        Value *operator->()
        {
            return node_->Data();
        }
        const Value *operator->() const
        {
            return node_->Data();
        }
        Value &operator*()
        {
            return *node_->Data();
        }
        const Value &operator*() const
        {
            return *node_->Data();
        }
        // 这里是找后继节点
        void operator++()
        {
            if (node_->Parent() == node_) {
                node_ = nullptr;
                return;
            }

            if (node_->Right()) {
                node_ = node_->Right();
                while (node_->Left()) {
                    node_ = node_->Left();
                }
                return;
            }

            Node *parent;
            while ((parent = node_->Parent()) && (node_ == parent->Right())) {
                node_ = parent;
            }

            node_ = parent;
        }
        bool operator==(const Iterator &it) const
        {
            return (node_ == it.node_);
        }
        bool operator!=(const Iterator &it) const
        {
            return (node_ != it.node_);
        }

    private:
        friend class RBTree;
        Node *node_;
    };

public:
    RBTree() : size_(0), root_(nullptr)
    {
    }
    RBTree(const Comparator &comparator) : size_(0), root_(nullptr), comparator_(comparator)
    {
    }
    ~RBTree()
    {
        Destroy();
    }

    Pair<Iterator, bool> insert(const Value &value)
    {
        Node *parent = nullptr;
        Node **cursor = &root_;
        const Key &key_of_value = get_key_from_value_(value);

        while (*cursor) {
            parent = *cursor;
            const Key &key_of_node = get_key_from_value_(*parent->Data());
            if (comparator_(key_of_value, key_of_node)) {
                cursor = parent->LeftAddr();
            } else if (comparator_(key_of_node, key_of_value)) {
                cursor = parent->RightAddr();
            } else {
                return MakePair(Iterator(parent), false);
            }
        }

        Node *node = nullptr;
        allocator_.Alloc(sizeof(Node), (void **)(&node));
        if (!node) {
            return MakePair(end(), false);
        }

        new (node) Node(value);
        node->SetParent(parent);

        *cursor = node;
        InsertRebalance(node);

        ++size_;
        return MakePair(Iterator(node), true);
    }

    Iterator find(const Key &key) const
    {
        Node *cursor = root_;
        while (cursor) {
            const Key &key_of_node = get_key_from_value_(*cursor->Data());
            if (comparator_(key, key_of_node)) {
                cursor = cursor->Left();
            } else if (comparator_(key_of_node, key)) {
                cursor = cursor->Right();
            } else {
                return Iterator(cursor);
            }
        }
        return end();
    }

    size_t erase(const Key &key)
    {
        auto iter = find(key);
        if (iter == end()) {
            return 0;
        }

        erase(iter);
        return 1;
    }

    void erase(Iterator iter)
    {
        if (iter.node_) {
            Remove(iter.node_);
            iter.node_->~Node();
            allocator_.Free(iter.node_);
            --size_;
        }
    }

    size_t size() const
    {
        return size_;
    }
    bool empty() const
    {
        return (size_ == 0);
    }

    Iterator begin() const
    {
        return Iterator(FindFirst());
    }

    const Iterator &end() const
    {
        return end_iterator_;
    }

private:
    /*
     *     x              y
     *    / \            / \
     *  xl   y    =>    x   yr
     *      / \        / \
     *    yl   yr    xl   yl
     */
    void RotateLeft(Node *x)
    {
        Node *y = x->Right();
        Node *px = x->Parent();

        x->SetRight(y->Left());
        y->SetParent(px);
        if (y->Left()) {
            y->Left()->SetParent(x);
        }

        if (px) {
            if (x == px->Left()) {
                px->SetLeft(y);
            } else {
                px->SetRight(y);
            }
        } else {
            root_ = y;
        }

        y->SetLeft(x);
        x->SetParent(y);
    }

    /*
     *       x            y
     *      / \          / \
     *     y   xr  =>  yl   x
     *    / \              / \
     *  yl   yr          yr   xr
     */
    void RotateRight(Node *x)
    {
        Node *y = x->Left();
        Node *px = x->Parent();

        x->SetLeft(y->Right());
        y->SetParent(px);
        if (y->Right()) {
            y->Right()->SetParent(x);
        }

        if (px) {
            if (x == px->Left()) {
                px->SetLeft(y);
            } else {
                px->SetRight(y);
            }
        } else {
            root_ = y;
        }

        y->SetRight(x);
        x->SetParent(y);
    }

    Node *FindFirst() const
    {
        if (!root_) {
            return nullptr;
        }

        auto node = root_;
        while (node->Left()) {
            node = node->Left();
        }

        return node;
    }

    void Remove(Node *node)
    {
        int color;
        Node *parent, *child = nullptr;

        if (node->Left() && node->Right()) {
            Node *old = node;
            Node *old_parent = node->Parent();

            node = node->Right();
            while (node->Left()) {
                node = node->Left();
            }

            if (old_parent) {
                if (old == old_parent->Left()) {
                    old_parent->SetLeft(node);
                } else {
                    old_parent->SetRight(node);
                }
            } else {
                root_ = node;
            }

            child = node->Right();
            parent = node->Parent();
            color = node->Color();

            if (parent == old) {
                parent = node;
            } else {
                if (child) {
                    child->SetParent(parent);
                }
                parent->SetLeft(child);

                node->SetRight(old->Right());
                old->Right()->SetParent(node);
            }

            node->SetParent(old->Parent());
            node->SetColor(old->Color());
            node->SetLeft(old->Left());
            old->Left()->SetParent(node);
            goto rebalance;
        }

        if (!node->Left()) {
            child = node->Right();
        } else {
            child = node->Left();
        }

        parent = node->Parent();
        color = node->Color();

        if (child) {
            child->SetParent(parent);
        }

        if (parent) {
            if (node == parent->Left()) {
                parent->SetLeft(child);
            } else {
                parent->SetRight(child);
            }
        } else {
            root_ = child;
        }

    rebalance:
        if (color == RB_BLACK) {
            RemoveRebalance(child, parent);
        }
    }

    void InsertRebalance(Node *node)
    {
        Node *parent, *gparent, *uncle;

        while ((parent = node->Parent()) && parent->IsRed()) {
            gparent = parent->Parent();

            if (parent == gparent->Left()) {
                uncle = gparent->Right();
                if (uncle && uncle->IsRed()) {
                    uncle->SetBlack();
                    parent->SetBlack();
                    gparent->SetRed();
                    node = gparent;
                    continue;
                }

                if (node == parent->Right()) {
                    RotateLeft(parent);
                    Node *tmp = node;
                    node = parent;
                    parent = tmp;
                }

                RotateRight(gparent);
                parent->SetBlack();
                gparent->SetRed();
                continue;
            }

            uncle = gparent->Left();
            if (uncle && uncle->IsRed()) {
                parent->SetBlack();
                uncle->SetBlack();
                gparent->SetRed();
                node = gparent;
                continue;
            }

            if (node == parent->Left()) {
                RotateRight(parent);
                Node *tmp = node;
                node = parent;
                parent = tmp;
            }

            RotateLeft(gparent);
            gparent->SetRed();
            parent->SetBlack();
        }

        root_->SetBlack();
    }

    void RemoveRebalance(Node *node, Node *parent)
    {
        Node *sibling;

        while ((!node || node->IsBlack()) && (node != root_)) {
            if (node == parent->Left()) {
                sibling = parent->Right();

                if (sibling->IsRed()) {
                    RotateLeft(parent);
                    parent->SetRed();
                    sibling->SetBlack();
                    sibling = parent->Right();
                }

                if ((!sibling->Left() || sibling->Left()->IsBlack()) && (!sibling->Right() || sibling->Right()->IsBlack())) {
                    sibling->SetRed();
                    node = parent;
                    parent = node->Parent();
                } else {
                    if (!sibling->Right() || sibling->Right()->IsBlack()) {
                        sibling->Left()->SetBlack();
                        sibling->SetRed();
                        RotateRight(sibling);
                        sibling = parent->Right();
                    }
                    sibling->SetColor(parent->Color());
                    parent->SetBlack();
                    sibling->Right()->SetBlack();
                    RotateLeft(parent);
                    node = root_;
                    break;
                }
            } else {
                sibling = parent->Left();
                if (sibling->IsRed()) {
                    RotateRight(parent);
                    parent->SetRed();
                    sibling->SetBlack();
                    sibling = parent->Left();
                }

                if ((!sibling->Left() || sibling->Left()->IsBlack()) && (!sibling->Right() || sibling->Right()->IsBlack())) {
                    sibling->SetRed();
                    node = parent;
                    parent = node->Parent();
                } else {
                    if (!sibling->Left() || sibling->Left()->IsBlack()) {
                        sibling->Right()->SetBlack();
                        sibling->SetRed();
                        RotateLeft(sibling);
                        sibling = parent->Left();
                    }

                    sibling->SetColor(parent->Color());
                    parent->SetBlack();
                    sibling->Left()->SetBlack();
                    RotateRight(parent);
                    node = root_;
                    break;
                }
            }
        }

        if (node) {
            node->SetBlack();
        }
    }

    void Destroy()
    {
        Node *node = root_;
        while (node) {
            if (node->Left()) {
                node = node->Left();
            } else if (node->Right()) {
                node = node->Right();
            } else {
                Node *tmp = node;
                node = node->Parent();
                if (node) {
                    if (tmp == node->Left()) {
                        node->SetLeft(nullptr);
                    } else {
                        node->SetRight(nullptr);
                    }
                }
                tmp->~Node();
                allocator_.Free(tmp);
            }
        }
        root_ = nullptr;
        size_ = 0;
    }

public:
    RBTree(const RBTree &t)
    {
        size_ = t.size_;
        end_iterator_ = t.end_iterator_;
        comparator_ = t.comparator_;
        get_key_from_value_ = t.get_key_from_value_;
        root_ = CopyTree(nullptr, t.root_);
    }

    RBTree &operator=(const RBTree &t)
    {
        Destroy();
        root_ = CopyTree(nullptr, t.root_);
        size_ = t.size_;
        return *this;
    }

private:
    Node *CopyTree(Node *new_parent, Node *root)
    {
        if (!root) {
            return nullptr;
        }

        Node *new_root = nullptr;
        allocator_.Alloc(sizeof(Node), (void **)(&new_root));
        if (!new_root) {
            return nullptr;
        }
        new (new_root) Node(*root->Data());

        new_root->SetLeft(CopyTree(new_root, root->Left()));
        new_root->SetRight(CopyTree(new_root, root->Right()));
        new_root->SetParent(new_parent);
        new_root->SetColor(root->Color());
        return new_root;
    }

private:
    size_t size_;
    Node *root_;
    Iterator end_iterator_;
    Comparator comparator_;
    Allocator allocator_;
    GetKeyFromValue get_key_from_value_;
};

} // namespace internal
} // namespace core
} // namespace ppl

#endif
