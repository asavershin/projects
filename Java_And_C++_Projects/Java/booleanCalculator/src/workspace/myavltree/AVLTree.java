package workspace.myavltree;

import workspace.formulanodes.ParamValue;

public class AVLTree {

    class Node {
        Node left;
        Node right;
        Node parent;
        protected ParamValue data;
        int balance;
        Node(ParamValue X){
            this.right = null;
            this.left = null;
            this.parent = null;
            this.data = X;
            this.balance = 0;
        }



        void delete() {
            if (left != null) left.delete();
            if (right != null) right.delete();
            left = right = parent = null;
        }
        protected Node minimum() {
            Node now = this;
            while (now.left != null) {
                now = now.left;
            }
            return now;
        }
        protected Node maximum() {
            Node now = this;
            while (now.right != null){
                now = now.right;
            }
            return now;
        }
        protected Node next() {
            if (right != null){
                return right.minimum();
            }
            Node p = parent;
            Node now = this;
            while (p != null) {
                if (now == p.left){
                    break;
                }
                now = p;
                p = p.parent;
            }
            return p;
        }
        Node prev() {
            if (left != null) {
                return left.maximum();
            }
            Node p = parent;
            Node now = this;
            while (p != null) {
                if (now == p.right) {
                    break;
                }
                now = p;
                p = p.parent;
            }
            return p;
        }
        int level(){
            int L = (left != null) ? left.level() : 0;
            int R = (right != null) ? right.level() : 0;
            return L > R ? L + 1 : R + 1;
        }
    };
    public class iterator {

        public Node now;
        public iterator(){
            this.now = null;
        }
        public iterator(Node now){
            this.now = now;
        }

        public ParamValue getData(){
            return now.data;
        }

        public boolean isEqual(iterator A){
            return now == A.now;
        }

        public boolean hasNext() {
            return now != null;
        }

        public iterator next() {
            if(this.hasNext()){
                now = now.next();
            }
            return this;
        }

        public boolean hasPrev(){return now != null;}
        public iterator prev(){
            if(this.hasPrev()){
                now = now.prev();
            }
            return this;
        }

        public iterator begin(){
            if (root != null) {
                return new iterator(root.minimum());
            }
            return end();
        }
        public iterator end(){
            return new iterator(null);
        }
    };


    Node root;
    public iterator iter;
    int count;
    Node _RightRotate(Node X){
        if (X.balance != -2){
            return X;
        }
        Node a = X.left;
        if (a.balance == 1) {
            return X;
        }

        X.left = a.right;
        if (a.right != null){
            a.right.parent = X;
        }

        a.parent = X.parent;
        if (X.parent != null) {
            if (X.parent.left == X)
                X.parent.left = a;
            else
                X.parent.right = a;
        } else {
            root = a;
        }

        a.right = X;
        X.parent = a;

        if (a.balance == -1) {
            a.balance = 0;
            X.balance = 0;
        } else {
            a.balance = 1;
            X.balance = -1;
        }

        return a;
    }
    Node _LeftRotate(Node X){
        if (X.balance != 2){
            return X;
        }
        Node b = X.right;
        if (b.balance == -1){
            return X;
        }

        X.right = b.left;
        if (b.left != null){
            b.left.parent = X;
        }

        b.parent = X.parent;
        if (X.parent != null) {
            if (X.parent.left == X)
                X.parent.left = b;
            else
                X.parent.right = b;
        } else {
            root = b;
        }

        b.left = X;
        X.parent = b;

        if (b.balance == 1) {
            X.balance = 0;
            b.balance = 0;
        } else {
            X.balance = 1;
            b.balance = -1;
        }

        return b;
    }
    Node _DoubleRightRotate(Node X){
         if (X.balance != -2){
             return X;
         }
        Node a = X.left;
        if (a.balance != 1){
            return X;
        }
        Node b = a.right;

        a.right = b.left;
        if (b.left != null){
            b.left.parent = a;
        }
        X.left = b.right;
        if (b.right != null){
            b.right.parent = X;
        }

        b.parent = X.parent;
        if (X.parent != null) {
            if (X.parent.left == X)
                X.parent.left = b;
            else
                X.parent.right = b;
        } else {
            root = b;
        }

        b.left = a;
        a.parent = b;
        b.right = X;
        X.parent = b;

        if (b.balance == 0) {
            a.balance = 0;
            X.balance = 0;
        } else if (b.balance == 1) {
            a.balance = -1;
            X.balance = 0;
        } else {
            a.balance = 0;
            X.balance = 1;
        }
        b.balance = 0;

        return b;
    };
    Node _DoubleLeftRotate(Node X){
        if (X.balance != 2){
            return X;
        }
        Node c = X.right;
        if (c.balance != -1){
            return X;
        }
        Node b = c.left;

        X.right = b.left;
        if (b.left != null){
            b.left.parent = X;
        }

        c.left = b.right;
        if (b.right != null) {
            b.right.parent = c;
        }

        b.parent = X.parent;
        if (X.parent != null) {
            if (X.parent.left == X)
                X.parent.left = b;
            else
                X.parent.right = b;
        } else {
            root = b;
        }

        b.left = X;
        X.parent = b;
        b.right = c;
        c.parent = b;

        if (b.balance == 0) {
            X.balance = 0;
            c.balance = 0;
        } else if (b.balance == 1) {
            X.balance = -1;
            c.balance = 0;
        } else {
            X.balance = 0;
            c.balance = 1;
        }
        b.balance = 0;
        return b;
    };

    public AVLTree(){
        this.root = null;
        this.count = 0;
        this.iter = new iterator();
    }

    public int size(){ return count; }
    public int height(){ return (root != null) ? root.level() : 0; }
    public void clear() {
        if (root != null) root.delete();
        root = null;
    }
    public void insert(ParamValue X) {
        ++count;
        if (root == null) {
            root = new Node(X);
            return;
        }
        Node now;
        Node p;
        boolean toLeft;
        now = root;
        do {
            p = now;
            if (X.getCh() < now.data.getCh()) {
                now = now.left;
                toLeft = true;
            }
            else {
                now = now.right;
                toLeft = false;
            }
        } while (now != null);
        now = new Node(X);
        if (toLeft) {
            p.left = now;
        } else {
            p.right = now;
        }
        now.parent = p;

        // �������������� �������
        do {
            if (now.parent.left == now) {
                now.parent.balance -= 1;
            }
            else{
                now.parent.balance += 1;
            }
            now = now.parent;
            switch (now.balance) {
                case 2:
                    if (now.right.balance == -1){
                        now = _DoubleLeftRotate(now);
                    }
                    else{
                        now = _LeftRotate(now);
                    }
                    break;
                case -2:
                    if (now.left.balance == 1){
                        now = _DoubleRightRotate(now);
                    }
                    else{
                        now = _RightRotate(now);
                    }
                    break;
            }
        } while (now != root && now.balance != 0);

    }


    public iterator find(ParamValue X){
        Node now = root;
        while (now != null) {
            if (X.getCh() == now.data.getCh()) break;
            if (X.getCh() < now.data.getCh()){
                now = now.left;
            }
            else {
                now = now.right;
            }
        }
        return new iterator(now);
    }
    public void erase(iterator pos){
        Node toDelete = pos.now;
        if (toDelete == null) return;
        Node Alt;
        if (toDelete.right == null)
            Alt = toDelete.left;
        else if (toDelete.left == null)
            Alt = toDelete.right;
        else {
            Alt = toDelete.right.minimum();
            if (Alt.parent != toDelete) {
                Alt.parent.left = Alt.right;
                if (Alt.right != null){
                    Alt.right.parent = Alt.parent;
                }
                Alt.right = toDelete.right;
                toDelete.right.parent = Alt;
            }
            Alt.left = toDelete.left;
            toDelete.left.parent = Alt;
        }

        Node notBalanced;
        if (Alt == null) {
            notBalanced = toDelete.parent;
            if (notBalanced != null) {
                if (notBalanced.left == toDelete){
                    notBalanced.balance += 1;
                }
                else {
                    notBalanced.balance -= 1;
                }
            }
        }
        else {
            Alt.balance = toDelete.balance;
            if (Alt.parent == toDelete) {
                notBalanced = Alt;
                if (Alt == toDelete.left) {
                    notBalanced.balance += 1;
                }
                else {
                    notBalanced.balance -= 1;
                }
            } else {
                notBalanced = Alt.parent;
                notBalanced.balance += 1;
            }
        }


        if (toDelete.parent == null) {
            root = Alt;
        }
        else {
            if (toDelete.parent.left == toDelete) {
                toDelete.parent.left = Alt;
            }
            else {
                toDelete.parent.right = Alt;
            }
        }
        if (Alt != null) {
            Alt.parent = toDelete.parent;
        }

        toDelete.right = null;
        toDelete.left = null;
        toDelete.delete();
        --count;

        // �������������� ������������
        while (notBalanced != null) {
            switch (notBalanced.balance) {
                case 2:
                    if (notBalanced.right.balance == -1) {
                        notBalanced = _DoubleLeftRotate(notBalanced);
                    }
                    else {
                        notBalanced = _LeftRotate(notBalanced);
                    }
                    break;
                case -2:
                    if (notBalanced.left.balance == 1) {
                        notBalanced = _DoubleRightRotate(notBalanced);
                    }
                    else {
                        notBalanced = _RightRotate(notBalanced);
                    }
                    break;
            }
            if (notBalanced.balance == 1 || notBalanced.balance == -1) {
                break;
            }
            if (notBalanced.parent != null) {
                if (notBalanced.parent.left == notBalanced) {
                    notBalanced.parent.balance += 1;
                }
                else {
                    notBalanced.parent.balance -= 1;
                }
            }
            notBalanced = notBalanced.parent;
        }
    };

}
