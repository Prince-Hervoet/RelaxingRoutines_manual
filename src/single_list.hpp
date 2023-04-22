typedef struct
{
    ListNode *next;
    void *data;
} ListNode;

template <typename T>
class SingleList
{
private:
    int size = 0;
    ListNode *head;
    ListNode *tail;

public:
    SingleList()
    {
    }
    ~SingleList()
    {
        if (head)
        {
        }
    }

    void addLast(T &t)
    {
        ListNode *node = new ListNode();
        node->next = nullptr;
        node->data = (void *)t;
        if (this->head)
        {
            this->tail->next = node;
            this->tail = node;
        }
        else
        {
            this->head = node;
            this->tail = node;
        }
        size += 1;
    }

    T *remove(T &t)
    {
        if (size == 0)
        {
            return nullptr;
        }
        ListNode *target = nullptr;
        ListNode *run = head;
        if (&t == head->data)
        {
            target = head;
            head = head->next;
            T *ans = (T *)target->data;
            delete target;
            size -= 1;
            return ans;
        }
        while (run->next != nullptr)
        {
            if (run->next->data == &t)
            {
                target = run->next;
                run->next = target->next;
                T *ans = (T *)target->data;
                delete target;
                size -= 1;
                return ans;
            }
        }
        return nullptr;
    }
};