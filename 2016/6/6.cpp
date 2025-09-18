#include <stdio.h>
#include <string.h>

struct letter
{
    char c;
    int count;

    letter(char d)
    : c(d)
    , count(1)
    {}

    bool less(const letter& other)
    {
        return count < other.count;
    }
};

struct node
{
    char c;
    int count;
    node* left = nullptr;
    node* right = nullptr;

    bool less(char d, int i)
    {
        return count < i || (count == i && c < d);
    }

    bool greater(char d, int i)
    {
        return count > i || (count == i && c > d);
    }
};

node* createNode(char c, int count)
{
    node* newNode = new node();
    newNode->c = c;
    newNode->count = count;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

node* find(node* root, char c)
{
    if (root == nullptr || root->c == c)
        return root;

    node* findLeft = find(root->left, c);
    if (findLeft != nullptr)
        return findLeft;

    return find(root->right, c);
}

node* insert(node* root, char c, int count)
{
    if (root == nullptr)
    {
        return createNode(c, count);
    }

    node* k = find(root, c);
    if (k != nullptr)
        return root;

    if (root->less(c, count))
    {
        root->right = insert(root->right, c, count);
    }
    else if (root->greater(c, count))
    {
        root->left = insert(root->left, c, count);
    }

    return root;
}

node* min(node* root)
{
    node* result = root;
    while (result != nullptr && result->left != nullptr)
    {
        result = result->left;
    }
    return result;
}

node* max(node* root)
{
    node* result = root;
    while (result != nullptr && result->right != nullptr)
    {
        result = result->right;
    }
    return result;
}

node* remove(node* root, char c, int count)
{
    if (root == nullptr)
        return root;

    if (root->greater(c, count))
    {
        root->left = remove(root->left, c, count);
    }
    else if (root->less(c, count))
    {
        root->right = remove(root->right, c, count);
    }
    else
    {
        if (root->left == nullptr)
        {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* temp = max(root->left);

        root->c = temp->c;
        root->count = temp->count;
        root->left = remove(root->left, temp->c, temp->count);
    }

    return root;
}

node* increment(node* root, char c, int count)
{
    node* newRoot = remove(root, c, count);
    return insert(newRoot, c, count + 1);
}

int main()
{
    char message[10];
    node* trees[10];
    int n = 0;
    for (int i = 0; i < 10; i++)
    {
        trees[i] = nullptr;
    }

    for (int i = 0; i < 572; i++)
    {
        scanf("%s\n", message);
        n = strlen(message);
        for (int j = 0; j < n; j++)
        {
            if (trees[j] == nullptr)
            {
                trees[j] = createNode(message[j], 1);
            }
            else
            {
                node* k = find(trees[j], message[j]);
                if (k == nullptr)
                    trees[j] = insert(trees[j], message[j], 1);
                else
                    trees[j] = increment(trees[j], message[j], k->count);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%c", max(trees[i])->c);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%c", min(trees[i])->c);
    }
    printf("\n");
}