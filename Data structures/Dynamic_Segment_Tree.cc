class Dynamic_Segment_Tree
{
private:
    struct node{
        int l, r;
        ll val;
        node() {
            l = 0;
            r = 0;
            val = 0;
        }
    };
    ll n;
    vector<node> tree;
    int new_node(node x = node()){
        tree.push_back(x);
        return tree.size() - 1;
    }
    int Point_Update(int id, ll l, ll r, ll pos, ll v){
        if(!id) id = new_node();
        if(l == r){
            tree[id].val += v;
            return id;
        }
        ll mid = (l + r) >> 1;
        if(pos <= mid) tree[id].l = Point_Update(tree[id].l, l, mid, pos, v);
        else tree[id].r = Point_Update(tree[id].r, mid + 1, r, pos, v);
        tree[id].val = tree[tree[id].l].val + tree[tree[id].r].val;
        return id;
    }
    ll get(int id, ll l, ll r, ll lo, ll hi){
        if(!id || l > hi || r < lo) return 0;
        if(l >= lo && r <= hi) return tree[id].val;
        ll mid = (l + r) >> 1;
        return get(tree[id].l, l, mid, lo, hi) + get(tree[id].r, mid + 1, r, lo, hi);
    }
public:
    void init(ll len, int qrscnt = 100000){
        n = len;
        tree.assign(2, node());
        tree.reserve(qrscnt * (log2(n) + 2) + 3);
    }
    void Point_Update(ll pos, ll v){
        Point_Update(1, 1, n, pos, v);
    }
    ll get(ll l, ll r){
        return get(1, 1, n, l, r);
    }
};
