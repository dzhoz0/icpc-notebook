class Lazy_Chairman_Tree
{
private:
    struct node{
        int l, r;
        ll val, lazy;
        node(){
            l = 0;
            r = 0;
            val = 0;
            lazy = 0;
        }
    };
    int n;
    vector<node> tree;
    int new_node(node x = node()){
        tree.push_back(x);
        return tree.size() - 1;
    }
    void apply(int id, int l, int r, ll v){
        tree[id].val += v * (r - l + 1);
        tree[id].lazy += v;
    }
    void push(int id, int l, int r){
        if (tree[id].lazy == 0 || l == r) return;
        int mid = (l + r) >> 1;
        tree[id].l = new_node(tree[tree[id].l]);
        tree[id].r = new_node(tree[tree[id].r]);
        apply(tree[id].l, l, mid, tree[id].lazy);
        apply(tree[id].r, mid + 1, r, tree[id].lazy);
        tree[id].lazy = 0;
    }
    int Range_Update(int cur, int l, int r, int lo, int hi, ll v){
        if(l > hi || r < lo) return cur;
        int id = new_node(tree[cur]);
        if (l >= lo && r <= hi) {
            apply(id, l, r, v);
            return id;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        if(lo <= mid) tree[id].l = Range_Update(tree[id].l, l, mid, lo, hi, v);
        if(hi > mid) tree[id].r = Range_Update(tree[id].r, mid + 1, r, lo, hi, v);
        tree[id].val = tree[tree[id].l].val + tree[tree[id].r].val;
        return id;
    }
    ll get(int id, int l, int r, int lo, int hi){
        if(!id || l > hi || r < lo) return 0;
        if(l >= lo && r <= hi) return tree[id].val;
        push(id, l, r);
        int mid = (l + r) >> 1;
        return get(tree[id].l, l, mid, lo, hi) + get(tree[id].r, mid + 1, r, lo, hi);
    }
public:
    int init(int len, int qrscnt = 100000){
        n = len;
        tree.assign(1, node());
        tree.reserve(qrscnt * 6 * (log2(n) + 2) + 3);
        return new_node();
    }
    int Range_Update(int root, int lo, int hi, ll v){
        return Range_Update(root, 1, n, lo, hi, v);
    }
    ll get(int root, int lo, int hi){
        return get(root, 1, n, lo, hi);
    }
};
