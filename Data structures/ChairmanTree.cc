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
    int cntnode = 0;
    int build(int l, int r){
        int id = ++cntnode;
        if(l == r)return id;
        int mid = (l + r) >> 1;
        tree[id].l = build(l, mid);
        tree[id].r = build(mid+1, r);
        return id;
    }
    int Point_Update(int cur, int l, int r, int pos){
        int id = ++cntnode;
        tree[id] = tree[cur];
        if(l == r){
            tree[id].val++;
            return id;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid){
            tree[id].l = Point_Update(tree[cur].l, l, mid, pos);
        }
        else{
            tree[id].r = Point_Update(tree[cur].r, mid + 1, r, pos);
        }
        tree[id].val = tree[tree[id].l].val + tree[tree[id].r].val;
        return id;
    }
    int get(int id, int l, int r, int lo, int hi){
        if(l > hi || r < lo)return 0;
        else if(l >= lo && r <= hi){
            return tree[id].val;
        }
        int mid = (l + r) >> 1;
        return get(tree[id].l, l, mid, lo, hi) + get(tree[id].r, mid + 1, r, lo, hi);
    }
public:
    int init(int len){
        n = len;
        tree.assign(20 * n, node());
        return build(1, n);
    }
    int Point_Update(int root, int pos){
        return Point_Update(root, 1, n, pos);
    }
    int get(int root, int l, int r){
        return get(root, 1, n, l, r);
    }
};
