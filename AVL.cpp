#include "AVL.h"
using namespace std;

AVLNode::AVLNode(int key) : key_(key), balancefactor(0), height(0), parent_(), left_(), right_() {}

AVLNode::AVLNode(int key, std::weak_ptr<AVLNode> parent) : key_(key), balancefactor(0), height(0), parent_(parent), left_(), right_() {}

bool AVLNode::IsLeaf() const {
    return left_ == nullptr && right_ == nullptr;
}

bool AVLNode::IsMissingChild() const {
    return left_ == nullptr || right_ == nullptr;
}

bool AVLNode::HasLeftChild() const {
    return left_ != nullptr;
}

bool AVLNode::HasRightChild() const {
    return right_ != nullptr;
}

AVL::AVL() : root_(), size_(0) {}

int AVL::height(std::shared_ptr<AVLNode> N) {
    if (N == nullptr){
        return -1;}
    return N->height;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

std::shared_ptr<AVLNode> AVL::newNode(int key) {
    std::shared_ptr<AVLNode> node = std::make_shared<AVLNode>(key);
    node->left_ = nullptr;
    node->right_ = nullptr;
    node->height = 0;
    return node;
}
std::shared_ptr<AVLNode> AVL::rightRotate(std::shared_ptr<AVLNode> y) {
    std::shared_ptr<AVLNode> x = y->left_;
    std::shared_ptr<AVLNode> z = x->right_;

    // Perform rotation
    x->right_ = y;
    y->left_ = z;

    // Update parent pointers
    x->parent_ = y->parent_;
    y->parent_ = x;
    if (z != nullptr) {
        z->parent_ = y;
    }

    // Update heights
    y->height = max(height(y->left_), height(y->right_)) + 1;
    x->height = max(height(x->left_), height(x->right_)) + 1;

    return x;
}

std::shared_ptr<AVLNode> AVL::leftRotate(std::shared_ptr<AVLNode> x) {
    std::shared_ptr<AVLNode> y = x->right_;
    std::shared_ptr<AVLNode> z = y->left_;

    // Perform rotation
    y->left_ = x;
    x->right_ = z;

    // Update parent pointers
    y->parent_ = x->parent_;
    x->parent_ = y;
    if (z != nullptr) {
        z->parent_ = x;
    }

    // Update heights
    x->height = max(height(x->left_), height(x->right_)) + 1;
    y->height = max(height(y->left_), height(y->right_)) + 1;

    return y;
}
int AVL::getBalance(std::shared_ptr<AVLNode> N) {
    if (N == nullptr)
        return 0;
    return height(N->right_) - height(N->left_);
}
std::shared_ptr<AVLNode> AVL::insert(std::shared_ptr<AVLNode> node, int key) {
    if (node == nullptr)
        return newNode(key);

    if (key < node->key_) {
        node->left_ = insert(node->left_, key);
        node->left_->parent_ = node;
    } else if (key > node->key_) {
        node->right_ = insert(node->right_, key);
        node->right_->parent_ = node;
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left_), height(node->right_));

    int balance = getBalance(node);

if (balance < -1 && key < node->left_->key_)
        return rightRotate(node);


else if (balance > 1 && key > node->right_->key_)
    return leftRotate(node);

else if (balance <-1 && key > node->left_->key_) {
    node->left_ = leftRotate(node->left_);
    return rightRotate(node);
}

else if (balance > 1 && key < node->right_->key_) {
    node->right_ = rightRotate(node->right_);
    return leftRotate(node);
}

return node;

}

void AVL::Insert(int key) {
root_ = insert(root_, key);
size_++;
}

bool AVL::Find(int key) const {
std::shared_ptr<AVLNode> currentNode = root_;



while (currentNode != nullptr) {
    if (key == currentNode->key_) {
        return true;
    } else if (key < currentNode->key_) {
        currentNode = currentNode->left_;
    } else {
        currentNode = currentNode->right_;
    }
}

return false;

}

std::string AVL::JSON() {
nlohmann::json result;
std::queue<std::shared_ptr<AVLNode>> nodes;


if (root_ != nullptr) {
    result["root"] = root_->key_;
    nodes.push(root_);

    while (!nodes.empty()) {
        auto v = nodes.front();
        nodes.pop();
        std::string key = std::to_string(v->key_);

        result[key]["height"] = v->height;

        result[key]["balance factor"] = getBalance(v);

        if (v->left_ != nullptr) {
            result[key]["left"] = v->left_->key_;
            nodes.push(v->left_);
        }
        if (v->right_ != nullptr) {
            result[key]["right"] = v->right_->key_;
            nodes.push(v->right_);
        }
        if (v->parent_.lock() != nullptr) {
            result[key]["parent"] = v->parent_.lock()->key_;
        } else {
            result[key]["root"] = true;
            result["height"] = v->height;
        }
    }
}

result["size"] = size_;

return result.dump(2) + "\n";

}

size_t AVL::size() const {
return size_;
}

bool AVL::empty() const {
return size_ == 0;
}
