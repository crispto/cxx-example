#include <iostream>

using namespace std;

class node
{
public:
        node(int val_, node *next_ = nullptr) : val(val_), next(next_){};
        bool lower_than(node &other)
        {
                return val < other.val;
        };
        int val;
        node *next;
};

void print_list(node *head, node *end = nullptr)
{
        node *cur = head;
        while (cur != end) {
                cout << cur->val << ", ";
                cur = cur->next;
        }
        cout << endl;
}
void quick_sort_help(node *head, node *end = nullptr)
{
        print_list(head, end);
        if (head == end || head->next == end)
                return;

        node *base = head;
        while (base->next != end)
                base = base->next;
        cout << "base.val" << base->val << endl;
        node *p1 = head;
        node *p2 = head;
        node *p1ptr = head;
        while (p2 != base) {
                if (p2->lower_than(*base)) {
                        int tmp = p1->val;
                        p1->val = p2->val;
                        p2->val = tmp;
                        p1 = p1->next;
                }
                p2 = p2->next;
        }
        int tmp = p1->val;
        p1->val = base->val;
        base->val = tmp;
        // p1 = p1->next;
        quick_sort_help(head, p1);
        quick_sort_help(p1->next, end);
}

void quick_sort(node *head)
{
        quick_sort_help(head);
}

int main()
{
        node *head = nullptr;
        for (int i = 0; i < 4; i++) {
                node *ptr = new node(i, head);
                head = ptr;
        }
        node *cur = head;
        while (cur != nullptr) {
                cout << cur->val << ", ";
                cur = cur->next;
        }
        cout << endl;

        quick_sort(head);
        cur = head;
        while (cur != nullptr) {
                cout << cur->val << ", ";
                cur = cur->next;
        }
        cout << endl;
}