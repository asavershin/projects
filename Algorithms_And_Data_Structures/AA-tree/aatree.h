#include <iostream>

template<typename T>
class AATree{
    struct Node {
        T key;
        T level;
        Node* left;
        Node* right;
        Node(T k) {
            key = k;
            level = 1;
            left = nullptr;
            right = nullptr;
        }
        ~Node(){
            if (left) {
                delete left;
            }
            if (right) {
                delete right;
            }
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* skew(Node* t) {

        if (t == nullptr || t->left == nullptr) {
            return t;
        }

        if (t->left->level == t->level) {
            Node* l = t->left;
            t->left = l->right;
            l->right = t;
            return l;
        }
        return t;
    }

    Node* split(Node* t) {
        if (t == nullptr || t->right == nullptr || t->right->right == nullptr) {
            return t;
        }
        if (t->level == t->right->right->level) {
            Node* r = t->right;
            t->right = r->left;
            r->left = t;
            r->level = t->level + 1;
            return r;
        }
        return t;
    }

    Node* deleteNode(Node* t, int key) {
        if (t == nullptr) {
            return nullptr;
        }

        if (key < t->key) {
            t->left = deleteNode(t->left, key);
        }
        else if (key > t->key) {
            t->right = deleteNode(t->right, key);
        }
        else {
            if (t->left == nullptr && t->right == nullptr) {
                delete t;
                return nullptr;
            }
            if (t->left == nullptr) {
                Node* temp = t->right;
                t->right = nullptr;
                delete t;
                return temp;
            }
            if (t->right == nullptr) {
                Node* temp = t->left;
                t->left = nullptr;
                delete t;
                return temp;
            }
            Node* minNode = t->right;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
            }
            t->key = minNode->key;
            t->right = deleteNode(t->right, minNode->key);
        }

        // update the level of the node
        int leftLevel = (t->left == nullptr) ? 0 : t->left->level;
        int rightLevel = (t->right == nullptr) ? 0 : t->right->level;
        int newLevel = std::min(leftLevel, rightLevel) + 1;
        if (newLevel < t->level) {
            t->level = newLevel;
            if (rightLevel > newLevel && t->right != nullptr) {
                t->right->level = newLevel;
            }
        }

        t = skew(t);
        t->right = skew(t->right);
        if (t->right != nullptr) {
            t->right->right = skew(t->right->right);
        }
        t = split(t);
        t->right = split(t->right);

        return t;
    }

    bool search(Node* t, int key) {
        if (t == nullptr) {
            return false;
        }
        if (key < t->key) {
            return search(t->left, key);
        }
        if (key > t->key) {
            return search(t->right, key);
        }
        return true;
    }
public:
    AATree() {
        root = nullptr;
    }
    
    ~AATree() {
        if (root){
            delete root;
        }
        root = nullptr;
    }

    Node* insert(Node* t, int key) {

        if (t == nullptr) {
            t = new Node(key);
        }
        else if (key < t->key) {
            t->left = insert(t->left, key);
        }
        else if (key > t->key) {
            t->right = insert(t->right, key);
        }
        else {
            return t;
        }

        t = skew(t);
        t = split(t);
        return t;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void print(Node* t, int level) {
        if (t == nullptr) {
            return;
        }
        print(t->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "\t";
        }
        std::cout << t->key << ":" << t->level << std::endl;
        print(t->left, level + 1);
    }

    void print() {
        print(root, 0);
    }

    int rootLevel(){
        return root == nullptr ? 0 : root->level;
    }

    bool search(int key) {
        return search(root, key);
    }
};

