struct PersistentSegTree {
    struct Node {
        int val;
        int l, r;

        Node() : val(0), l(-1), r(-1) {}
        Node(int v) : val(v), l(-1), r(-1) {}
        Node(int v, int L, int R) : val(v), l(L), r(R) {}

        Node operator+(const Node &other) const {
            return Node(val + other.val);
        }
    };

    vector<Node> st;
    int n;

    void init(int _n) {
        n = _n;
        st.clear();
        st.reserve(20 * n + 5);
    }

    int newNode(const Node &x = Node()) {
        st.push_back(x);
        return (int)st.size() - 1;
    }

    int build(int l, int r) {
        int cur = newNode();

        if (l == r)
            return cur;

        int mid = (l + r) >> 1;

        int left = build(l, mid);
        int right = build(mid + 1, r);

        st[cur] = st[left] + st[right];
        st[cur].l = left;
        st[cur].r = right;

        return cur;
    }

    int update(int cur, int l, int r, int pos, int val) {
        if (pos < l || pos > r)
            return cur;

        if (l == r)
            return newNode(Node(val));

        int mid = (l + r) >> 1;

        int left = st[cur].l;
        int right = st[cur].r;

        if (pos <= mid)
            left = update(left, l, mid, pos, val);
        else
            right = update(right, mid + 1, r, pos, val);

        int me = newNode(st[left] + st[right]);
        st[me].l = left;
        st[me].r = right;

        return me;
    }

    int query(int cur, int l, int r, int L, int R) const {
        if (R < l || r < L)
            return 0;

        if (L <= l && r <= R)
            return st[cur].val;

        int mid = (l + r) >> 1;

        return query(st[cur].l, l, mid, L, R) +
               query(st[cur].r, mid + 1, r, L, R);
    }
};
