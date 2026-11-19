class Chairman_Tree
{
private:
    struct node{
        int l, r;
        int val;
        node(){
            l = 0;
            r = 0;
            val = 0;
        }
    };
    int n;
    vector<node> tree;
    int new_node(node x = node()){
        tree.push_back(x);
        return tree.size() - 1;
    }
    int Point_Update(int cur, int l, int r, int pos){
        int id = new_node(tree[cur]);
        if(l == r){
            tree[id].val++;
            return id;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) tree[id].l = Point_Update(tree[id].l, l, mid, pos);
        else tree[id].r = Point_Update(tree[id].r, mid + 1, r, pos);
        tree[id].val = tree[tree[id].l].val + tree[tree[id].r].val;
        return id;
    }
    int get(int id, int l, int r, int lo, int hi){
        if (!id || l > hi || r < lo) return 0;
        if (l >= lo && r <= hi) return tree[id].val;
        int mid = (l + r) >> 1;
        return get(tree[id].l, l, mid, lo, hi) + get(tree[id].r, mid + 1, r, lo, hi);
    }
public:
    int init(int len, int qrscnt = 100000){
        n = len;
        tree.assign(1, node());
        tree.reserve(qrscnt * (log2(n) + 2) + 3);
        return new_node();
    }
    int Point_Update(int root, int pos){
        return Point_Update(root, 1, n, pos);
    }
    int get(int root, int l, int r){
        return get(root, 1, n, l, r);
    }
};
